#pragma once 
#include <string>
#include <vector>

/// Build suffix array from text.
/// @param sa The text (might be empty)
/// @param text A suffix array (sorted). The variable 'sa' is cleared before it's filled and returned.
void construct(std::vector<uint32_t>& sa, const std::string& text);

/// Search a query string in a text via suffix array, which was constructed before using 'construct()'. If the query is empty, return empty hits.
/// @param query The pattern we look for 
/// @param sa A suffix array previously build from 'text'
/// @param text The text that 'sa' is build from
/// @param[out] hits Indices of hits for 'query' in 'text' (sorted ascending by position in text!). The variable is cleared before its filled and returned
void find(const std::string& query, const std::vector<uint32_t>& sa, const std::string& text, std::vector<uint32_t>& hits);



/// Construct the Burrows-Wheeler Transform (BWT) of a text using a given suffix array.
/// The BWT is created from the original text and stored in the 'BW' variable.
/// Additionally, the corresponding suffix array for the BWT is computed and stored in 'sa_bwt'.
/// @param sa The suffix array of the input text (constructed beforehand using 'construct()')
/// @param input_text The original text from which 'sa' was built
/// @param[out] BW The resulting Burrows-Wheeler Transform of 'input_text'
/// @param[out] sa_bwt The suffix array of the BWT of 'input_text'
void construct_BWT(const std::vector<uint32_t>& sa, const std::string& input_text, std::string& BW, std::vector<uint32_t>& sa_bwt);


/// Reconstruct the original text from the Burrows-Wheeler Transform (BWT) using the given suffix array.
/// The original text is stored in the 'text' variable.
/// @param sa The suffix array of the original text
/// @param BWT The Burrows-Wheeler Transform of the original text
/// @param[out] text The reconstructed original text from the BWT
void sa_to_text(const std::vector<uint32_t>& sa, const std::string& BWT, std::string& text);


/// Given the original text, its Burrows-Wheeler Transform (BWT), and the suffix array of the BWT,
/// compute and store the suffix array of the original text in the 'sa' variable.
/// @param input_text The original text from which the BWT was constructed
/// @param BWT The Burrows-Wheeler Transform of 'input_text'
/// @param sa_bwt The suffix array of the BWT of 'input_text'
/// @param[out] sa The resulting suffix array of the original text
void text_to_sa(const std::string& input_text, const std::string& BWT, const std::vector<uint32_t>& sa_bwt, std::vector<uint32_t>& sa);
