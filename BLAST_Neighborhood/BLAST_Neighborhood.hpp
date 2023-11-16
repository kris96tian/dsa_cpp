#pragma once 
#include <string>
#include <vector>
#include <omp.h>
#include "a4_util.h"

struct NHResult
{

  /**
   Neighborhood Result data for a single infix
   e.g. infix: "AHI" 
         neighbors: (AHI, 16); (AHL, 14); (AHV, 15)
    Members in structs are public by default.
              So they can be initialized and used like this:
      std::vector< std::pair <std::string, int> > my_vec;
      my_vec.push_back(make_pair("AGT", 23));
      my_vec.emplace_back("ATT", 21);
      NHResult r{"AAA", my_vec};
      NHResult other_r;
      other_r.infix = "BLA";
      other_r.neighbors = my_vec;
 */
  std::string infix;
  std::vector<std::pair<std::string, int>> neighbors;
};

class BLAST_Neighborhood
{
  public:
  /**
     Die BLAST Nachbarschaft fuer eine Query wird berechnet.
    
     @param query           Die Eingabesequenz, welche in Infixe der Länge @p word_size zerlegt wird
     @param matrix          Die Scoring-Matrix fuer das Berechnen der Nachbarschaft
     @param word_size       Die zu verwendende Wortgroesse
     @param score_threshold Der minimale Score den ein Wort haben muss um zur Nachbarschaft zugehoeren
     @param threads         Die Anzahl der Threads die verwendet werden sollen
     @return Die Nachbarschaften der Query-Infixe, sortiert nach Position der Infixe in Query (d.h. 1. Infix, 2. Infix, ...).
	         Die Nachbarschaft jedes Infixes ist alphabetisch sortiert.
    */
    std::vector<NHResult> generateNeighborhood(const std::string& query,
                                               const ScoreMatrix& matrix,
                                               const int word_size,
                                               const int score_threshold,
                                               const int threads);
    
    // Inline helper functions
    inline std::vector<std::string> permute(const int word_size, const std::vector<char>& aminoacids);
    inline std::vector<std::string> permute_recursion(const int pos, std::string& place_holder, 
                                                      const std::vector<std::string>& intermediate, 
                                                      const std::vector<char>& aminoacids);
};




// Implementations of helper functions
inline std::vector<std::string> BLAST_Neighborhood::permute(const int word_size, const std::vector<char>& aminoacids) {
    std::string place_holder(word_size, '_');
    std::vector<std::string> permutations = {place_holder};
    for (int pos = 0; pos < word_size; ++pos) {
        permutations = permute_recursion(pos, place_holder, permutations, aminoacids);
    }
    return permutations;
}

inline std::vector<std::string> BLAST_Neighborhood::permute_recursion(const int pos, std::string& place_holder, 
                                                               const std::vector<std::string>& intermediate, 
                                                               const std::vector<char>& aminoacids) {
    std::vector<std::string> intermediate_sol;
    for (const auto& interm : intermediate) {
        place_holder = interm;
        for (char aminoacid : aminoacids) {
            place_holder[pos] = aminoacid;
            intermediate_sol.push_back(place_holder);
        }
    }
    return intermediate_sol;
}
