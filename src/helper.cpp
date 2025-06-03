#include "AST_Normalization.hpp"

ASTNode *root = nullptr; // Root node of the AST

// Create a new AST node or Non-Terminal node(according to grammar) with variable number of children
ASTNode *create_ast_node(ASTNodeType type, int n, ...) {  
    va_list args;
    va_start(args, n);
    ASTNode *ret = new ASTNode(type,0,"",n,std::vector<ASTNode*>(n));
    for (int i = 0; i < n; i++) ret->children[i] = va_arg(args, ASTNode *);
    va_end(args);
    return ret;
}

// Create a leaf node or Terminal node(according to grammar) with a string value
ASTNode *create_leaf_node(ASTNodeType type, const char *val) {  
    ASTNode *ret = new ASTNode(type,0,val,0,std::vector<ASTNode*>(0));       
    return ret;
}

void delete_ast(ASTNode *node) {
    if (!node) return;
    for (int i = 0; i < node->child_count; i++) delete_ast(node->children[i]);    
    delete node;
}


std::string ast_node_type_to_string(ASTNodeType type) {
    switch (type) {
        case AST_FUNCTION_DEF:            return "FunctionDef";
        case AST_PARAM_LIST:              return "ParamList";
        case AST_PARAM:                   return "Param";
        case AST_DECLARATION:             return "Declaration";
        case AST_INIT_DECLARATOR:         return "InitDeclarator";
        case AST_ASSIGNMENT:              return "Assignment";
        case AST_FUNCTION_PROTOTYPE:      return "FunctionPrototype";
        case AST_PREPROCESSOR:            return "Preprocessor";
        case AST_PLUS:                    return "Plus";
        case AST_MINUS:                   return "Minus";
        case AST_MUL:                     return "Multiply";
        case AST_DIV:                     return "Divide";
        case AST_MOD:                     return "Modulo";        
        case AST_LT:                      return "LessThan";
        case AST_GT:                      return "GreaterThan";
        case AST_LE:                      return "LessEqual";
        case AST_GE:                      return "GreaterEqual";
        case AST_EQUALS:                  return "Equals";
        case AST_NOT_EQUALS:              return "NotEquals";
        case AST_FUNCTION_CALL:           return "FunctionCall";
        case AST_FUNCTION_DECLARATOR:     return "FunctionDeclarator";
        case AST_IDENTIFIER:              return "Identifier";
        case AST_LITERAL:                 return "Literal";
        case AST_NUMBER:                  return "Number";
        case AST_RETURN:                  return "Return";
        case AST_IF:                      return "If";
        case AST_ELSE:                    return "Else";
        case AST_ITERATION_STMT:          return "IterationStmt";
        case AST_COMPOUND_STMT:           return "CompoundStmt";
        case AST_ARRAY_ACCESS:            return "ArrayAccess";
        case AST_STRUCT_DECL:             return "StructDecl";
        case AST_TYPEDEF:                 return "Typedef";
        case AST_INIT_LIST:               return "InitList";
        case AST_POINTER_DEREF:           return "PointerDeref";
        case AST_ADDRESS_OF:              return "AddressOf";
        case AST_BREAK:                   return "Break";
        case AST_CONTINUE:                return "Continue";
        case AST_SIZEOF:                  return "Sizeof";
        case AST_POINTER:                 return "Pointer";
        case AST_TYPE_QUALIFIER:          return "TypeQualifier";
        case AST_TYPE_SPECIFIER:          return "TypeSpecifier";
        case AST_FUNCTION_SPECIFIER:      return "FunctionSpecifier";
        case AST_TRANS:                   return "TranslationUnit";
        case AST_LIST:                    return "List";
        case AST_BLOCK:                   return "Block";
        case AST_ALIGNMENT_SPECIFIER:     return "AlignmentSpecifier";
        case AST_STORAGE_CLASS_SPECIFIER: return "StorageClassSpecifier";
        case AST_DECLARATOR:              return "Declarator";
        case AST_ENUM:                    return "EnumSpecifier";
        case AST_TYPE_NAME:               return "TypeName";
        case AST_MEMBER_ACCESS:           return "MemberAccess";
        case AST_PTR_MEMBER_ACCESS:       return "PtrMemberAccess";
        case AST_POST_INCREMENT:          return "PostIncrement";
        case AST_POST_DECREMENT :         return "PostDecrement";
        case AST_PLUS_ASSIGN:             return "PlusAssign";
        case AST_MINUS_ASSIGN:            return "MinusAssign";
        case AST_MUL_ASSIGN:              return "MultiplyAssign";
        case AST_DIV_ASSIGN:              return "DivideAssign";
        case AST_MOD_ASSIGN:              return "ModuloAssign";
        case AST_BIT_AND_ASSIGN:          return "BitAndAssign";
        case AST_BIT_OR_ASSIGN:           return "BitOrAssign";
        case AST_BIT_XOR_ASSIGN:          return "BitXorAssign";
        case AST_SHIFT_LEFT_ASSIGN:       return "ShiftLeftAssign";
        case AST_SHIFT_RIGHT_ASSIGN:      return "ShiftRightAssign";
        case AST_SWITCH :                 return "AST_SWITCH" ;
        case AST_CASE :                   return "AST_CASE" ;
        case AST_DEFAULT :                return "AST_DEFAULT" ;
        case AST_UNARY_PLUS:              return "UnaryPlus";
        case AST_UNARY_MINUS:             return "UnaryMinus";
        case AST_TRANSLATION_UNIT:        return "TranslationUnit";
        case AST_GOTO_STMT:               return "GotoStmt";
        case AST_LABELED_STMT:            return "LabeledStmt";
        case AST_BIT_NOT:                 return "BitNot";
        case AST_LOGICAL_NOT:             return "LogicalNot";
        case AST_SHIFT_LEFT:              return "ShiftLeft";
        case AST_SHIFT_RIGHT:             return "ShiftRight";
        case AST_BIT_AND:                 return "BitAnd";
        case AST_BIT_XOR:                 return "BitXor";
        case AST_BIT_OR:                  return "BitOr";
        case AST_LOGICAL_AND:             return "LogicalAnd";
        case AST_LOGICAL_OR:              return "LogicalOr";
        case AST_CONDITIONAL:             return "Conditional";
        case AST_COMMA:                   return "Comma";
        default:                          return "Unknown";
    }
}

void print_ast(ASTNode *node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) std::cout << " ";
    std::cout << ast_node_type_to_string(node->type);
    if (!node->value.empty()) std::cout << "(" << node->value << ")";
    std::cout << std::endl;
    for (int i = 0; i < node->child_count; i++) print_ast(node->children[i], depth + 2);
}

void print_ast_side_by_side(ASTNode *originalNode, ASTNode *suspectedNode) {
    std::function<std::string(ASTNode*, int)> capture = [&](ASTNode *node, int depth) -> std::string {
        if (!node) return "";
        std::string result = std::string(depth, ' ') + ast_node_type_to_string(node->type) + 
        (node->value.empty() ? "" : "(" + node->value + ")") + "\n";
        for (int i = 0; i < node->child_count; i++) result += capture(node->children[i], depth + 2);
        return result;
    };
    
    auto split = [](const std::string& str) {
        std::vector<std::string> lines ; std::stringstream ss(str) ; std::string line ;
        while (std::getline(ss, line)) lines.push_back(line);
        return lines;
    };
    
    auto originalLines = split(capture(originalNode, 0));
    auto suspectedLines = split(capture(suspectedNode, 0));
    
    const int width = 45, sep = 5;
    std::cout << std::left << std::setw(width) << "Original File" << std::string(sep, ' ') << "Suspected File\n"
              << std::string(width, '-') << std::string(sep, ' ') << std::string(45, '-') << "\n";
    
    for (size_t i = 0; i < std::max(originalLines.size(), suspectedLines.size()); i++) {
        std::string left = (i < originalLines.size()) ? originalLines[i] : "";
        std::string right = (i < suspectedLines.size()) ? suspectedLines[i] : "";
        if (left.length() > width) left = left.substr(0, width - 3) + "...";
        std::cout << std::left << std::setw(width) << left << std::string(sep, ' ') << right << "\n";
    }
}

ASTNode* extract_ast_element(ASTNode* node, ASTNodeType target_type, int child_index) {
    if (!node) return nullptr;
    if (node->type == target_type) {
        if (child_index == -1 || child_index == 0) {
            return node;
        } else if (child_index > 0 && child_index < node->child_count) {
            return node->children[child_index];
        }
    }
    for (int i = 0; i < node->child_count; ++i) {
        if (node->children[i]) {
            ASTNode* result = extract_ast_element(node->children[i], target_type, child_index);
            if (result) return result;
        }
    }
    return nullptr;
}

bool is_function_prototype(ASTNode *node) noexcept {
    if (!node) return false;
    if (node->type == AST_FUNCTION_DECLARATOR) return true;
    
    std::vector<ASTNode*> queue;
    queue.reserve(16);
    queue.push_back(node);
    
    for (size_t i = 0; i < queue.size(); ++i) {
        ASTNode* current = queue[i];
        if (!current) continue;
        if (current->type == AST_FUNCTION_DECLARATOR) return true;

        for (int j = 0; j < current->child_count; ++j) {
            if (current->children[j]) {
                queue.push_back(current->children[j]);
            }
        }
    }
    return false;
}


void yyerror(const char *s) {
    extern int yylineno;  
    fprintf(stderr, "Error at line %d: %s\n", yylineno, s);
}
