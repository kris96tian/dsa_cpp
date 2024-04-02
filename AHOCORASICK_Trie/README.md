# Aho-Corasick Algorithm Implementation

A C++ implementation the Aho-Corasick algorithm, a string-searching algorithm (in bioinformatics) that efficiently searches for multiple patterns in a given text.

## Reuirements

C++ compiler with C++11 support



## Usage

Compile the C++ program:

```bash
g++ -o ahocorasick ahocorasick.cpp 
```
Run the compiled program with the following command:

```bash
./aho_corasick <text_file_or_string> <pattern1> <pattern2> ...
```

Replace <text_file_or_string> with the path to a text file or the text itself and <pattern1> <pattern2> ... with the patterns you want to search for in the text.

## Example
```bash
./aho_corasick input.txt pattern1 pattern2
```

## Description
The program consists of the following components:

TrieNode: Represents a node in the trie data structure used for efficient string matching.


insert: Inserts a pattern into the trie.


buildFailTransitions: Builds failure transitions in the trie to efficiently handle non-matching characters.


AhoCorasickSearch: Performs the Aho-Corasick string search algorithm on the input text using the constructed trie.

## References
This implementation is based on the Aho-Corasick algorithm described in the following paper:
Aho, Alfred V., and Corasick, Margaret J. "Efficient string matching: An aid to bibliographic search." Communications of the ACM 18.6 (1975): 333-340.
