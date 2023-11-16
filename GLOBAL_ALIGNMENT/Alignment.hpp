#pragma once
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
#include <iostream>

class Alignment
{
public:
  
  Alignment() = delete;  
  
  /// Constructor with two sequences
  /// Makes an internal copy of the sequences.
  Alignment(const std::string& seq_v, const std::string& seq_h);
  
  /// Compute the aligment (i.e. score and traceback)
  /// given the three alignment parameters match, mismatch and gap.
  void compute(const int match, const int mismatch, const int gap, const bool local_align = false);
  
  /// Return the score of the alignment;
  int getScore() const;
  
  void getAlignment(std::string& a1, std::string& gaps, std::string& a2) const; //ausgabe
    
  private:
    std::string seq_v;
    std::string seq_h;
    uint32_t seq_v_size;
    uint32_t seq_h_size;
    std::vector<int> matrix;
    std::vector<int> traceback_matrix;
    bool computed{false};

    int matchCheck(char char_v, char char_h, int match, int mismatch) const;
    int scoreCalculator(int gap, int matchValue, int diagonal, int left, int top) const;
    int tracebackScoreCalculator(int gap, int matchValue, int diagonal, int left, int top) const;
    void initializeMatrices(int gap);
};