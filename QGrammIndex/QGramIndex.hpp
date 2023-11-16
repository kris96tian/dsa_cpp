#pragma once
#include "a5_util.hpp"
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <omp.h>
#include <math.h>
#include <stdexcept>
#include <cmath>

/*
   The Q-Gram-Index implementation using Counting Sort for SA Construction
   assuming DNA alphabet (|Sigma| = 4).  
   The text may be up to 2^32 in length, i.e. uint32_t is used internally for suffix array and q-gram index.
   The maximal supported value for q is 13.
*/
class QGramIndex 
{
public:
    /**
     @brief Constructor: build up a q-gram index from @p text.
     Internally, @p text is stored as const reference (const std::string& )  
     The index is build immediately.
     @param text The sequence (genome, ...) to be indexed
     @param q Length of q-gram (from 1 to 13).
     @throws std::invalid_argument("Invalid q!") unless: 1 <= q <= 13
    */
    QGramIndex(const std::string& text, const uint8_t q);

    /**
      @brief Returns the text.
      @return the full text
    */
    const std::string& getText() const;
    
    /**
      @brief Returns a vector of indices into text, where the q-gram with hash @p h occurs.     
      The vector might be empty, if the q-gram does not exist, i.e. empty range within the suffix array.
      The hash value must be within [0...|SIGMA|^q), otherwise an exception is thrown.
      @param h Hash value of the q-gram
      @return Vector of hits (indices into text)
      @throws std::invalid_argument("Invalid hash!"); if h is outside of valid hash values
    */
    std::vector<uint32_t> getHits(const uint32_t h) const;
    
    /**
      @brief Get the length of q-grams, i.e. 'q'.
    */
    uint8_t getQ() const;
    
    /**
      @brief Compute a full hash for a given q-gram.
      @param qgram A q-gram; must have size 'q'
      @return hash value of @p qgram
      @throws std::invalid_argument("Invalid q-gram. Wrong length!"); if qgram.size() != q
    */
    uint32_t hash(const std::string& qgram) const;
    
    /**
       @brief Returns the next rolling hash for given new character and previous hash (of previous q-gram).
       The first character going out-of-scope is removed internally by bitmasking.     
       @param prev_hash Previous hash value
       @param new_pos new character (last position of current q-gram)
       @return The updated hash value
    */
    uint32_t hashNext(const uint32_t prev_hash, const char new_pos) const;
const std::vector<uint32_t>& getSA() const;

private:
	std::vector<uint32_t> countingSort(std::vector<uint32_t>& dir, const std::string& text);
	void updateSuffixArray(std::vector<uint32_t>& dir, std::vector<uint32_t>& sa, uint32_t hash_value, uint32_t position);
	const std::string& text_;
	const uint8_t q_;
	std::vector<std::vector<uint32_t>> qgi_;
	std::vector<uint32_t> sa_;
	std::vector<uint32_t> dir_;
	uint32_t bitmask_;
	uint8_t indcopy;
};

