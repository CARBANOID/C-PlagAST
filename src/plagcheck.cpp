#include "AST_CC.hpp"
#include "c_parser.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>

void isDescendant(const ASTNode* node, std::unordered_map<ASTNode*,MatchingSubtree*>&potentialchilds) {
    if(node == nullptr) return  ;
    if(potentialchilds.find(const_cast<ASTNode*>(node)) != potentialchilds.end()) 
        potentialchilds.erase(const_cast<ASTNode*>(node)) ;
    for(auto child : node->children) isDescendant(child, potentialchilds) ;
}

void clear_data() {
    HashListArray.clear();
    childsASTInfo.clear();
    root = nullptr;
    setMoore() ;
    clear_dead_function_tracking();  
}

std::pair<SubtreeInfo, ASTNodeInfo*> original_info ;
std::vector<ASTNodeInfo> originalHashListArray ;
long original_size ;


int check_plagarism(const char* original_file, const char* suspected_file) {

    clear_data();
    std::cout << "\nProcessing suspected file: " << suspected_file << std::endl;
    parse_file(suspected_file);  
    
    std::pair<SubtreeInfo, ASTNodeInfo*> suspected_info = getChildsSubtreeInfo(root);
    std::vector<ASTNodeInfo> suspectedHashListArray = HashListArray;
    long suspected_size = suspected_info.first.first;
    
    int score = ast_cc_similarity_score(originalHashListArray, suspectedHashListArray);
    
    std::cout << "\n=== Similarity Analysis ===\n";
    std::cout << "Original file: " << original_file << "\n";
    std::cout << "Suspected file: " << suspected_file << "\n";
    std::cout << "Original AST size: " << original_size << " nodes\n";
    std::cout << "Suspected AST size: " << suspected_size << " nodes\n";
    std::cout << "AST-CC Similarity score: " << score << "%\n";

    sort(matchingSubtrees.begin(), matchingSubtrees.end(), []
    (MatchingSubtree &A, MatchingSubtree &B) {
        return A.originalNode.subtree_size > B.originalNode.subtree_size;
    });

    std::unordered_map<ASTNode*,MatchingSubtree*> potentialchilds ; 

    for(int i = 0 ; i < matchingSubtrees.size() ; i++){ 
        if(matchingSubtrees[i].originalNode.subtree_size < 3) continue ; // skip small subtrees // comment this if you want to see all small matches also
        potentialchilds[matchingSubtrees[i].originalNode.Node] = &matchingSubtrees[i] ;
    }

    for(int i = 0 ; i< matchingSubtrees.size() ; i++) {
        ASTNode* node = matchingSubtrees[i].originalNode.Node ;
        if(potentialchilds.find(node) != potentialchilds.end()) {
           for(auto child : node->children) isDescendant(child, potentialchilds) ;
        }
    }
        
    std::cout << "Found " << potentialchilds.size() << " unique matching subtrees (filtered from " 
              << matchingSubtrees.size() << " total matches):\n\n";
        
    int displayCount = 0;
    int maxDisplay = potentialchilds.size();

    for (const auto& match : potentialchilds) {
        if (displayCount >= maxDisplay) break;
        displayCount++;

        std::cout << "Match #" << displayCount << " - " << match.second->nodeDescription 
        << " (Size: " << match.second->originalNode.subtree_size << " nodes)\n\n";
            
        print_ast_side_by_side(match.second->originalNode.Node, match.second->originalNode.Node);
        std::cout << "\n" << std::string(50,'=') << "\n\n";        }
        
        if (potentialchilds.size() > static_cast<size_t>(maxDisplay)) {
            std::cout << "... and " << (potentialchilds.size() - maxDisplay) << " more matches not shown.\n\n";
        }
    
    std::cout << "=========================\n";
    return score;
}

extern "C" int Run_AST_CC(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <original_file> --ast-cc-test <suspected_file1> [<suspected_file2> ...]\n";
        return 1;
    }

    const char* original_file = argv[1];  
    std::cout << "\nProcessing original file: " << original_file << std::endl;
    parse_file(original_file); 

    original_info = getChildsSubtreeInfo(root);
    originalHashListArray = HashListArray;
    original_size = original_info.first.first;

    for (int i = 3 ; i < argc; i++) {
        const char* suspected_file = argv[i];
        check_plagarism(original_file, suspected_file);   
    }

    return 0;
} 
