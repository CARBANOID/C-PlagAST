#ifndef VISUALIZE_HPP
#define VISUALIZE_HPP
#include "c_parser.h"
#include <iostream>
#include <fstream>
#include <functional>

// ---------------Functions for AST visualization and export-----------------

// DOT file generation for AST visualization
void generate_dot_file_recursive(ASTNode *node, std::ofstream &file, int &node_id) {
    if (!node) return;
    
    int current_id = node_id++;
    std::string node_label = ast_node_type_to_string(node->type);
      // Add value to label if it exists
    if (!node->value.empty()) {
        // Escape special characters for DOT format
        std::string escaped_value = node->value;
        size_t pos = 0;
        
        // Escape quotes
        while ((pos = escaped_value.find("\"", pos)) != std::string::npos) {
            escaped_value.replace(pos, 1, "\\\"");
            pos += 2;
        }
        
        // Escape newlines
        pos = 0;
        while ((pos = escaped_value.find("\n", pos)) != std::string::npos) {
            escaped_value.replace(pos, 1, "\\n");
            pos += 2;
        }
        
        // Escape angle brackets which can cause issues
        pos = 0;
        while ((pos = escaped_value.find("<", pos)) != std::string::npos) {
            escaped_value.replace(pos, 1, "&lt;");
            pos += 4;
        }
        pos = 0;
        while ((pos = escaped_value.find(">", pos)) != std::string::npos) {
            escaped_value.replace(pos, 1, "&gt;");
            pos += 4;
        }
        
        node_label += "\\n[" + escaped_value + "]";
    }
    
    // Define node style based on node type
    std::string node_style = "shape=box, style=filled";
    std::string color = "lightblue";
    
    // Color coding for different node types
    switch (node->type) {
        case AST_TRANS:
            color = "lightgreen";
            break;
        case AST_FUNCTION_DEF:
            color = "orange";
            break;
        case AST_COMPOUND_STMT:
        case AST_BLOCK:
            color = "lightyellow";
            break;
        case AST_IF:
        case AST_ITERATION_STMT:
            color = "lightcoral";
            break;
        case AST_DECLARATION:
            color = "lightgray";
            break;
        case AST_IDENTIFIER:
            color = "lightcyan";
            break;
        case AST_NUMBER:
        case AST_LITERAL:
            color = "lightpink";
            break;
        case AST_FUNCTION_CALL:
            color = "gold";
            break;
        case AST_RETURN:
            color = "thistle";
            break;
        default:
            color = "lightblue";
            break;
    }
    
    file << "  node" << current_id << " [label=\"" << node_label << "\", " 
         << node_style << ", fillcolor=" << color << "];\n";
    
    for (int i = 0; i < node->child_count; i++) {
        if (node->children[i]) {
            int child_id = node_id;
            generate_dot_file_recursive(node->children[i], file, node_id);
            file << "  node" << current_id << " -> node" << child_id << ";\n";
        }
    }
}

void generate_dot_file(ASTNode *node, const char *filename) {
    if (!node) {
        std::cerr << "Error: Cannot generate DOT file for null AST node\n";
        return;
    }
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << " for writing\n";
        return;
    }
    
    std::cout << "Generating DOT file: " << filename << std::endl;
    
    // Write DOT file header
    file << "digraph AST {\n";
    file << "  rankdir=TB;\n";  // Top to bottom layout
    file << "  node [fontname=\"Arial\", fontsize=10];\n";
    file << "  edge [fontname=\"Arial\", fontsize=8];\n";
    file << "  bgcolor=\"white\";\n";
    file << "  label=\"Abstract Syntax Tree Visualization\";\n";
    file << "  labelloc=\"t\";\n";
    file << "  fontsize=16;\n";
    file << "  fontname=\"Arial Bold\";\n\n";
    
    // Generate the tree recursively
    int node_id = 0;
    generate_dot_file_recursive(node, file, node_id);
    
    // Write DOT file footer
    file << "}\n";
    
    file.close();
    std::cout << "DOT file generated successfully: " << filename << std::endl;
    std::cout << "To generate image, run: dot -Tpng " << filename << " -o ast_visualization.png" << std::endl;
    std::cout << "Or run: dot -Tsvg " << filename << " -o ast_visualization.svg" << std::endl;
}


void export_ast_to_json(ASTNode *node, const char *json_filename) {
    if (!node) return;
    
    std::ofstream file(json_filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << json_filename << " for writing\n";
        return;
    }
    
    std::function<void(ASTNode*, int)> write_json = [&](ASTNode* n, int indent) {
        if (!n) {
            file << "null";
            return;
        }
        
        std::string indent_str(indent * 2, ' ');
        file << "{\n";
        file << indent_str << "  \"type\": \"" << ast_node_type_to_string(n->type) << "\",\n";
        file << indent_str << "  \"value\": \"" << n->value << "\",\n";
        file << indent_str << "  \"children\": [";
        
        if (n->child_count > 0) {
            file << "\n";
            for (int i = 0; i < n->child_count; i++) {
                file << indent_str << "    ";
                write_json(n->children[i], indent + 2);
                if (i < n->child_count - 1) file << ",";
                file << "\n";
            }
            file << indent_str << "  ";
        }
        
        file << "]\n";
        file << indent_str << "}";
    };
    
    write_json(node, 0);
    file.close();
    std::cout << "AST exported to JSON: " << json_filename << std::endl;
}

#endif 