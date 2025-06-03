#include "AST_CC.hpp"
#include "c_parser.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

bool isDescendant(const ASTNodeInfo& potential_child, const ASTNodeInfo& potential_ancestor) {
    if (potential_child.Node == potential_ancestor.Node) return false;   
    if (potential_child.Parent == potential_ancestor.Node) return true;
    if (potential_child.Parent && potential_ancestor.Parent && 
        potential_child.subtree_size < potential_ancestor.subtree_size &&
        potential_child.Parent == potential_ancestor.Parent) {
        return true;
    } 
    return false;
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


    if (score > 0 && !matchingSubtrees.empty()) {
        std::cout << "\n=== Matching Code Pieces ===\n";

        std::vector<MatchingSubtree> filteredMatches;
        std::vector<MatchingSubtree> &sortedMatches = matchingSubtrees;

        std::sort(
            sortedMatches.begin(), sortedMatches.end(), 
            [](const MatchingSubtree& a, const MatchingSubtree& b) {
                return a.originalNode.subtree_size > b.originalNode.subtree_size;
            }
        );
        
        for (const auto& match : sortedMatches) {
            bool shouldInclude = true;
            
            if (match.originalNode.subtree_size < 3) shouldInclude = false;
            
            if (shouldInclude) {
                for (const auto& existingMatch : filteredMatches) {
                    if (isDescendant(match.originalNode, existingMatch.originalNode) &&
                        isDescendant(match.suspectedNode, existingMatch.suspectedNode)) {
                        shouldInclude = false;
                        break;
                    }
                }
            }
            
            if (shouldInclude && match.originalNode.subtree_size >= 5) {
                int similarCount = 0;
                for (const auto& otherMatch : sortedMatches) {
                    if (otherMatch.originalNode.subtree_size == match.originalNode.subtree_size &&
                        otherMatch.originalNode.subtree_hash == match.originalNode.subtree_hash) {
                        similarCount++;
                    }
                }
                if (similarCount >= 3) {
                    std::cout << "⚠️  SUSPICIOUS PATTERN DETECTED: " << similarCount 
                    << " identical subtrees of size " << match.originalNode.subtree_size
                    << " found - Strong indication of code copying!\n";
                }
            }
            if (shouldInclude) filteredMatches.push_back(match);
        }
        
        std::cout << "Found " << filteredMatches.size() << " unique matching subtrees (filtered from " 
                  << matchingSubtrees.size() << " total matches):\n\n";
        
        int displayCount = 0;
        int maxDisplay = filteredMatches.size();

        for (const auto& match : filteredMatches) {

            if (displayCount >= maxDisplay) break;
            displayCount++;

            std::cout << "Match #" << displayCount << " - " << match.nodeDescription 
            << " (Size: " << match.originalNode.subtree_size << " nodes)\n\n";
            
            print_ast_side_by_side(match.originalNode.Node, match.suspectedNode.Node);
            
            std::cout << "\n" << std::string(50,'=') << "\n\n";        }
        
        if (filteredMatches.size() > static_cast<size_t>(maxDisplay)) {
            std::cout << "... and " << (filteredMatches.size() - maxDisplay) 
                      << " more matches not shown.\n\n";
        }
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