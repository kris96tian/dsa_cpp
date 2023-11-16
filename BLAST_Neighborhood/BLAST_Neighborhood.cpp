#include "BLAST_Neighborhood.hpp"
#include <algorithm>
#include <omp.h> // Include for parallel processing

// Define other necessary includes and helper functions

std::vector<NHResult> BLAST_Neighborhood::generateNeighborhood(const std::string& query,
                                                              const ScoreMatrix& matrix,
                                                              const int word_size,
                                                              const int score_threshold,
                                                              const int threads) 
{
    // Check for valid thread count
    if (threads < 1) throw std::invalid_argument("Thread count must be at least 1");

    // Initialize result vector
    std::vector<NHResult> blast_neighborhood; 

    // Check for word size larger than query size
    if (static_cast<size_t>(word_size) > query.size()) {  
        return blast_neighborhood; 
    }

    // Generate permutations of amino acids
    std::vector<char> aminoacids = {'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 
                                    'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V'};
    std::vector<std::string> permutations = permute(word_size, aminoacids);

    // Parallel processing using OpenMP
    #pragma omp parallel for num_threads(threads) schedule(dynamic)
    for (size_t counter_query = 0; counter_query <= query.size() - word_size; ++counter_query) {
        std::string word_query = query.substr(counter_query, word_size);

        std::vector<std::pair<std::string, int>> neighbors;

        for (const std::string& permutation : permutations) {
            int score = 0;
            for (size_t i = 0; i < word_query.size(); ++i) {
                score += matrix.score(word_query[i], permutation[i]);
            }
            if (score >= score_threshold) {
                #pragma omp critical
                neighbors.emplace_back(permutation, score);
            }
        }

        // Sort neighbors
        std::sort(neighbors.begin(), neighbors.end());

        #pragma omp critical
        blast_neighborhood.push_back({word_query, neighbors});
    }

    return blast_neighborhood;
}
