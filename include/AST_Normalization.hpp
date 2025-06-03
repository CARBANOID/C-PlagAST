#ifndef AST_NORMALIZATION_HPP
#define AST_NORMALIZATION_HPP

#include "c_parser.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <iomanip>
#include <sstream> 
#include <algorithm> 
#include <vector> 
#include <functional>
#include <memory>

std::vector<ASTNode*> redundant_nodes = []() {
    std::vector<ASTNode*> vec;
    vec.reserve(1000); 
    return vec;
}();

thread_local std::unordered_set<ASTNodeType> meaningful_ops_cache = {
    AST_ASSIGNMENT, AST_RETURN, AST_PLUS, AST_MINUS, 
    AST_MUL, AST_DIV, AST_MOD, AST_MEMBER_ACCESS, AST_PTR_MEMBER_ACCESS,
    AST_IF, AST_ITERATION_STMT, AST_SWITCH, AST_FUNCTION_CALL,
    AST_LT, AST_GT, AST_LE, AST_GE, AST_EQUALS, AST_NOT_EQUALS,
    AST_UNARY_PLUS, AST_UNARY_MINUS
};

thread_local std::unordered_map<ASTNode*, bool> empty_block_cache;

inline bool is_empty_block(ASTNode *node) noexcept {
    if (!node) return true;
    auto cache_it = empty_block_cache.find(node);
    if (cache_it != empty_block_cache.end()) return cache_it->second;
    
    if (meaningful_ops_cache.count(node->type) || 
        (node->type == AST_DECLARATION && node->child_count > 0)) {
        empty_block_cache[node] = false;
        return false;
    }
    
    if (node->child_count == 0) {
        empty_block_cache[node] = true;
        return true;
    }
    
    for (int i = 0; i < node->child_count; ++i) {
        if (node->children[i] && !is_empty_block(node->children[i])) {
            empty_block_cache[node] = false;
            return false;
        }
    }
    empty_block_cache[node] = true;
    return true;
}

enum ConditionValue { ALWAYS_FALSE, ALWAYS_TRUE, UNKNOWN };

inline ConditionValue evaluate_condition(ASTNode *node) noexcept {
    if (!node) return UNKNOWN;
    if (node->type == AST_NUMBER || node->type == AST_LITERAL) {
        const std::string& val = node->value;
        return (val.size() == 1 && val[0] == '0') ? ALWAYS_FALSE : ALWAYS_TRUE;
    }
    return UNKNOWN;
}

inline void remove_child_subtree(ASTNode *node, int idx) noexcept {
    if (!node || idx < 0 || idx >= node->child_count) return;
    ASTNode *child = node->children[idx] ;    
    node->children.erase(node->children.begin() + idx);
    node->child_count--;

    if (!child) return ;

    std::vector<ASTNode*> to_process;
    to_process.reserve(64);
    to_process.push_back(child); 
    while (!to_process.empty()) {
        ASTNode* current = to_process.back();
        to_process.pop_back();
        if (!current) continue;
        for (int i = 0; i < current->child_count; ++i) if (current->children[i]) to_process.push_back(current->children[i]);     
        current->children.clear();
        redundant_nodes.push_back(current);
    }
}

ASTNode* clone_node(ASTNode* original) {
    if (!original) return nullptr;
    struct CloneWork {
        ASTNode* original;
        ASTNode* cloned;
        int child_index;      
        CloneWork(ASTNode* orig, ASTNode* clone, int idx = 0) : original(orig), cloned(clone), child_index(idx) {}
    };
    
    std::vector<CloneWork> work_stack;
    work_stack.reserve(32); 
    ASTNode* root_clone = new ASTNode(original->type, original->val, original->value, original->child_count, std::vector<ASTNode*>(original->child_count));
    
    if (original->child_count > 0) work_stack.emplace_back(original, root_clone, 0);
     
    while (!work_stack.empty()) {
        CloneWork& work = work_stack.back();
        
        if (work.child_index >= work.original->child_count) {
            work_stack.pop_back();
            continue;
        }
        
        ASTNode* child_original = work.original->children[work.child_index];
        if (child_original) {
            ASTNode* child_clone = new ASTNode(child_original->type, child_original->val, 
                                   child_original->value, child_original->child_count,
                                   std::vector<ASTNode*>(child_original->child_count));
            
            work.cloned->children[work.child_index] = child_clone;
            if (child_original->child_count > 0) work_stack.emplace_back(child_original, child_clone, 0);
        }
        work.child_index++;
    }
    return root_clone;
}

// Converts: int a, b=5, c; -> int a; int b; b = 5; int c;
inline void normalize_variable_declarations(ASTNode *node) {
    if (!node) return;
    std::vector<ASTNode*> node_stack;
    node_stack.reserve(64);
    node_stack.push_back(node);
    
    while (!node_stack.empty()) {
        ASTNode* current = node_stack.back();
        node_stack.pop_back();
        
        if (!current) continue;
        
        // Process compound statements that can contain declarations
        if (current->type == AST_COMPOUND_STMT || current->type == AST_BLOCK || 
            current->type == AST_TRANS || current->type == AST_LIST ||
            current->type == AST_FUNCTION_DEF) {
            
            std::vector<ASTNode*> new_children;
            new_children.reserve(current->child_count * 4);
            bool made_changes = false;
            
            for (int i = 0; i < current->child_count; ++i) {
                ASTNode* child = current->children[i];
                
                if (!child) continue;
                
                // Look for declaration patterns: Declaration -> List(TypeSpec) -> List(InitDeclarator)
                if (child->type == AST_DECLARATION && child->child_count >= 2) {
                    ASTNode* type_list = child->children[0];  // First List containing type specifier
                    ASTNode* decl_list = child->children[1];  // Second List containing declarators
                    
                    if (!type_list || !decl_list || 
                        type_list->type != AST_LIST || decl_list->type != AST_LIST) {
                        new_children.push_back(child);
                        continue;
                    }  
                    // Find type specifier in first list
                    ASTNode* type_spec = nullptr;
                    for (int j = 0; j < type_list->child_count; ++j) {
                        if (type_list->children[j] && type_list->children[j]->type == AST_TYPE_SPECIFIER) {
                            type_spec = type_list->children[j];
                            break;
                        }
                    }
                    if (!type_spec) {
                        new_children.push_back(child);
                        continue;
                    }
                    // Process declarators in second list
                    bool needs_splitting = false;
                    std::vector<ASTNode*> declarators;
                    
                    for (int j = 0; j < decl_list->child_count; ++j) {
                        ASTNode* declarator = decl_list->children[j];
                        if (declarator) {
                            declarators.push_back(declarator);
                            if (declarator->type == AST_INIT_DECLARATOR) {
                                needs_splitting = true;
                            }
                        }
                    }       
                    // Split if needed
                    if (needs_splitting || declarators.size() > 1) {
                        for (ASTNode* declarator : declarators) {
                            if (!declarator) continue;
                            
                            if (declarator->type == AST_INIT_DECLARATOR && declarator->child_count >= 2) {
                                // Split InitDeclarator: int x = 10; -> int x; x = 10;
                                ASTNode* var_declarator = declarator->children[0];
                                ASTNode* initializer = declarator->children[1];
                                
                                // Create plain declaration: int x;
                                ASTNode* new_decl = new ASTNode(AST_DECLARATION, 0, "", 2, std::vector<ASTNode*>(2));
                                
                                // Create type list
                                ASTNode* new_type_list = new ASTNode(AST_LIST, 0, "", 1, std::vector<ASTNode*>(1));
                                new_type_list->children[0] = clone_node(type_spec);
                                new_decl->children[0] = new_type_list;
                                
                                // Create declarator list (without initialization)
                                ASTNode* new_decl_list = new ASTNode(AST_LIST, 0, "", 1, std::vector<ASTNode*>(1));
                                new_decl_list->children[0] = clone_node(var_declarator);
                                new_decl->children[1] = new_decl_list;
                                
                                new_children.push_back(new_decl);
                                
                                // Extract variable name for assignment
                                std::function<std::string(ASTNode*)> extract_var_name = [&](ASTNode* n) -> std::string {
                                    if (!n) return "";
                                    if (n->type == AST_IDENTIFIER) return n->value;
                                    for (int idx = 0; idx < n->child_count; ++idx) {
                                        std::string result = extract_var_name(n->children[idx]);
                                        if (!result.empty()) return result;
                                    }
                                    return "";
                                };
                                std::string var_name = extract_var_name(var_declarator);
                                if (!var_name.empty() && initializer) {
                                    // Create assignment statement: x = 10;
                                    ASTNode* assignment = new ASTNode(AST_ASSIGNMENT, 0, "", 2, std::vector<ASTNode*>(2));
                                    assignment->children[0] = new ASTNode(AST_IDENTIFIER, 0, var_name, 0, std::vector<ASTNode*>());
                                    assignment->children[1] = clone_node(initializer);
                                    new_children.push_back(assignment);
                                }
                                
                            } else if (declarator->type == AST_DECLARATOR) {
                                // Regular declarator without initialization - create separate declaration
                                ASTNode* new_decl = new ASTNode(AST_DECLARATION, 0, "", 2, std::vector<ASTNode*>(2));
                                
                                // Create type list
                                ASTNode* new_type_list = new ASTNode(AST_LIST, 0, "", 1, std::vector<ASTNode*>(1));
                                new_type_list->children[0] = clone_node(type_spec);
                                new_decl->children[0] = new_type_list;
                                
                                // Create declarator list
                                ASTNode* new_decl_list = new ASTNode(AST_LIST, 0, "", 1, std::vector<ASTNode*>(1));
                                new_decl_list->children[0] = clone_node(declarator);
                                new_decl->children[1] = new_decl_list;
                                
                                new_children.push_back(new_decl);
                            }
                        }
                        made_changes = true;
                        
                    } else {
                        // No splitting needed, keep as-is
                        new_children.push_back(child);
                    }
                } else {
                    // Not a declaration, keep as-is
                    new_children.push_back(child);
                }
            }
            
            // Update the node's children if we made changes
            if (made_changes) {
                current->children = std::move(new_children);
                current->child_count = current->children.size();
            }
        }
        
        // Add children to processing stack
        for (int i = 0; i < current->child_count; ++i) {
            if (current->children[i]) {
                node_stack.push_back(current->children[i]);
            }
        }
    }
}


void normalize_ast(ASTNode *node) {
    if (!node) return;    

    for (int i = 0; i < node->child_count; i++) normalize_ast(node->children[i]);

    normalize_variable_declarations(node);
    
    for (int i = 0; i < node->child_count; ) {
        ASTNode* child = node->children[i];
          if (!child) {
            node->children.erase(node->children.begin() + i);
            node->child_count--;
        }
        else if (child->type == node->type && node->type != AST_IF) { // Merge same-type children (except IF nodes)    
            node->children.erase(node->children.begin() + i);
            node->children.insert(node->children.begin() + i, child->children.begin(), child->children.end());
            node->child_count = node->children.size();
            child->children.clear();
            redundant_nodes.push_back(child);
        }
        else if(child->type == AST_IF) {
            if (child->child_count < 2) break;
            ConditionValue cond = evaluate_condition(child->children[0]);
            if (cond == ALWAYS_TRUE) {
                // Replace with then branch
                node->children[i] = child->children[1];
                child->children.erase(child->children.begin() + 1);
                child->children.clear();
                redundant_nodes.push_back(child);
            } else {
                // Remove empty branches
                if (child->child_count >= 2 && is_empty_block(child->children[1])) {
                    redundant_nodes.push_back(child->children[1]);
                    child->children.erase(child->children.begin() + 1);
                    child->child_count--;
                }
                if (child->child_count >= 3 && is_empty_block(child->children[2])) {
                    redundant_nodes.push_back(child->children[2]);
                    child->children.erase(child->children.begin() + 2);
                    child->child_count--;
                }
                if (child->child_count < 2) remove_child_subtree(node, i);
                else i++ ;
            }
        }
        else i++; 
    }   
}

void cleanup_redundant_nodes() {
    for (ASTNode* node : redundant_nodes ) delete node ; 
    redundant_nodes.clear();
    if (empty_block_cache.size() > 1000) empty_block_cache.clear();
}

#endif