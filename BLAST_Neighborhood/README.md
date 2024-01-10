<img src="blob:chrome-untrusted://media-app/86e979e4-2d29-4ed7-a215-6c8fb7dc89a4" alt="blast.png"/>![image](https://github.com/kris96tian/dsa_cpp/assets/92834350/c7a1c8ca-6b94-4ca0-923a-da7385ecdc19)

# BLAST Neighborhood Generator
## Overview

The BLAST Neighborhood Generator is a tool designed to analyze sequences of amino acids. This tool helps in identifying similar sequences, or 'neighborhoods', based on a given input sequence and specific scoring criteria for understanding protein functions and relationships.

## Requirements

A C++ compiler with C++17 support (e.g., g++)
OpenMP for parallel processing (optional but recommended for performance)


## Compilation

Compile the program using the provided Makefile in the project directory by:

bash make blastMain

## Usage

./blastMain SEQUENCE SCORE_MATRIX WORD_SIZE THRESHOLD THREADS

## Example
./blastMain AGTCG blosum62 3 5 1

## Output
The program outputs the neighborhoods for each subsequence (infix) of the input sequence, showing similar sequences and their scores.
