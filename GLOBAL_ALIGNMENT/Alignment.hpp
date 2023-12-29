#pragma once
#include <string>
#include <vector>
#include <iostream>

class Alignment {
public:
  // Constructor (Deleted) to prevent default initialization
  Alignment() = delete;

  // Constructor to initialize the sequence strings
  Alignment(const std::string& seq_v, const std::string& seq_h);

  // Method to compute the alignment score and generate the alignment strings
  void compute(const int match, const int mismatch, const int gap, const bool local_align = false);

  // Method to retrieve the alignment score
  int getScore() const;

  // Method to retrieve the alignment strings (aligned sequences, gaps, and directions)
  void getAlignment(std::string& a1, std::string& gaps, std::string& a2) const;

private:
  // Private member variables to store alignment data
  std::string seq_v;  // Vertical sequence
  std::string seq_h;  // Horizontal sequence

  // Score of the alignment
  int score;

  // Aligned sequences
  std::string a1;
  std::string gaps; 
  std::string a2;
};
