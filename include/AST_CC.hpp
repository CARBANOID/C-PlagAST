#ifndef AST_CC_HPP
#define AST_CC_HPP
#include "c_parser.h"
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <iostream>
using SubtreeInfo = std::pair<long,long>;

class ASTNodeInfo {
    public :
    ASTNode* Node ;
    ASTNode *Parent ;
    long parent_hash_sum ;  // hash value of parent subtree
    long childs_hash_sum ; // hash value of childs subtree
    long subtree_hash ; // hash of this node / subtree made by this node
    long subtree_size ; // no of all child nodes in the subtree made by this node
    int line_number ;
    ASTNodeInfo(ASTNode* Node,ASTNode* Parent, long childs_hash_sum,long subtree_hash,long subtree_size) 
    : Node(Node),Parent(Parent), childs_hash_sum(childs_hash_sum),subtree_hash(subtree_hash),subtree_size(subtree_size) {
        parent_hash_sum = (Parent) ? Parent->type : 0  ; 
        line_number = 0 ;
    }    bool operator==(const ASTNodeInfo& other) const {
        return ((this->subtree_hash == other.subtree_hash) && (this->subtree_size == other.subtree_size )
        && (this->Node->type == other.Node->type) ) ;
    }

    bool operator<(const ASTNodeInfo& other) const {
        if (this->subtree_size != other.subtree_size) {
            return this->subtree_size < other.subtree_size;
        }
        return this->subtree_hash < other.subtree_hash ;
    }
};

std::vector<ASTNodeInfo> HashListArray;
std::vector<ASTNodeInfo*>childsASTInfo ; 

std::pair<SubtreeInfo,ASTNodeInfo*> getChildsSubtreeInfo(ASTNode* Node, ASTNode* Parent = nullptr) {  
    if(!Node)  return {{0,0},nullptr} ; 
    long subtree_hash_sum = 0 ; // hash value of all childs in the subtree
    long subtree_size = 0 ; // no of nodes in the subtree

    std::vector<ASTNodeInfo*>childsASTInfo ;
    for(auto child : Node->children) {
        std::pair<SubtreeInfo,ASTNodeInfo*>childsInfo = getChildsSubtreeInfo(child,Node) ;
        subtree_size += childsInfo.first.first ; 
        subtree_hash_sum += childsInfo.first.second ;    
        if(childsInfo.second)childsASTInfo.push_back(childsInfo.second) ;
    }

    subtree_size += 1 ; // include the current node itself
    long subtree_hash_value = Node->type + subtree_size * subtree_hash_sum;

    for(auto child : childsASTInfo) child->parent_hash_sum = subtree_hash_value ; 
    childsASTInfo.clear() ;

    HashListArray.push_back(ASTNodeInfo(Node,Parent,subtree_hash_sum,subtree_hash_value,subtree_size)) ;
    return {{subtree_size,subtree_hash_value},&HashListArray.back()}  ;
}

class MatchingSubtree {
    public:
    ASTNodeInfo originalNode;
    ASTNodeInfo suspectedNode;
    std::string nodeDescription;
    
    MatchingSubtree(const ASTNodeInfo& orig, const ASTNodeInfo& susp) 
        : originalNode(orig), suspectedNode(susp) {
        nodeDescription = ast_node_type_to_string(orig.Node->type);
        if (!orig.Node->value.empty()) {
            nodeDescription += "(" + orig.Node->value + ")";
        }
    }
};

std::vector<MatchingSubtree> matchingSubtrees;

// AST-CC Algorithm Implementation using Jaccard coefficient on multisets
std::pair<int, int> calculateJaccardComponents(
    std::vector<ASTNodeInfo>& OriginalHashListArray,
    std::vector<ASTNodeInfo>& SuspectedHashListArray) {
    
    matchingSubtrees.clear();   
    
    std::map<std::pair<long, long>, int> hashCountA; // (subtree_hash, subtree_size) -> count
    std::map<std::pair<long, long>, int> hashCountB;
    
    std::map<std::pair<long, long>, std::vector<ASTNodeInfo*>> sigToOriginalNodes;
    std::map<std::pair<long, long>, std::vector<ASTNodeInfo*>> sigToSuspectedNodes;
    
    for(auto& node : OriginalHashListArray) {
        std::pair<long, long> signature = std::make_pair(node.subtree_hash, node.subtree_size);
        hashCountA[signature]++ ;
        sigToOriginalNodes[signature].push_back(&node);
    }
    
    for(auto& node : SuspectedHashListArray) {
        std::pair<long, long> signature = std::make_pair(node.subtree_hash, node.subtree_size);
        hashCountB[signature]++;
        sigToSuspectedNodes[signature].push_back(&node);
    }
    
    int intersection_size = 0;
    int union_size = 0;
    
    std::set<std::pair<long, long>> allSignatures;
    for(const auto& pair : hashCountA) allSignatures.insert(pair.first);
    for(const auto& pair : hashCountB) allSignatures.insert(pair.first);
    
    
    for(const auto& signature : allSignatures) {
        int countA = hashCountA[signature];  // 0 if not found
        int countB = hashCountB[signature];  // 0 if not found
        
        intersection_size += std::min(countA, countB);
        union_size += std::max(countA, countB);
        
        // Collect matching pairs for display
        if(countA > 0 && countB > 0) {
            int matches_to_record = intersection_size ;
            auto& originalNodes = sigToOriginalNodes[signature];
            auto& suspectedNodes = sigToSuspectedNodes[signature];
            int limit = std::min(originalNodes.size(),suspectedNodes.size());   
            for(int i = 0; i < matches_to_record && i < limit ; i++) {
                matchingSubtrees.emplace_back(*originalNodes[i], *suspectedNodes[i]);
            }
        }
    } 
    return std::make_pair(intersection_size, union_size);
}

// AST-CC Similarity Score using Jaccard Coefficient
int ast_cc_similarity_score(std::vector<ASTNodeInfo>& OriginalHashListArray,std::vector<ASTNodeInfo>& SuspectedHashListArray) {
    if(OriginalHashListArray.empty() && SuspectedHashListArray.empty()) return 100; 
    if(OriginalHashListArray.empty() || SuspectedHashListArray.empty()) return 0 ;
    
    std::pair<int, int> jaccard_components = calculateJaccardComponents(OriginalHashListArray, SuspectedHashListArray);
    int intersection_size = jaccard_components.first;
    int union_size = jaccard_components.second;
    
    if(union_size == 0) return 0;
    
    // AST-CC similarity = |H_A ∩ H_B| / |H_A ∪ H_B|
    double similarity = (double)intersection_size / (double)union_size;
    int percentage = (int)(similarity * 100.0 + 0.5);
    return std::min(percentage, 100); // Cap at 100%
}

#endif
