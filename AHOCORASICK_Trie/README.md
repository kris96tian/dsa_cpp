# Aho-Corasick Algorithm Implementation

A C++ implementation the Aho-Corasick algorithm, a string-searching algorithm (in bioinformatics) that efficiently searches for multiple patterns in a given text.

## Overview

The Aho-Corasick algorithm consists of three main steps:

1. **Insertion**: Build a trie data structure that represents the set of patterns to be searched.
2. **Failure Function Construction**: Calculate a failure function for efficient transition between trie nodes.
3. **Pattern Search**: Perform the actual search for patterns in the given text using the constructed trie and failure function.

## Code Structure

The code is organized into the following components:

- **TrieNode Structure**: Represents a node in the trie, containing output patterns, children nodes, and a fail pointer.

- **createNode Function**: Creates a new trie node with proper initialization.

- **insert Function**: Inserts a pattern into the trie.

- **buildFailTransitions Function**: Constructs the failure function for efficient transitions between trie nodes.

- **AhoCorasickSearch Function**: Performs the pattern search in a given text using the constructed trie and failure function.

- **Main Function**: Demonstrates the usage of the Aho-Corasick algorithm by searching for multiple patterns in a random text.

## Usage

Compile the C++ program:

```bash
g++ -o ahocorasick ahocorasick.cpp 
```
Then add the input text to be searched and the pattern(s) as command line arguments:
```bash
./ahocorasick <text> <pattern1> <pattern2> ...
```
The program outputs the positions where each pattern is found in the text.

## Example
Input:
```bash
./ahocorasick abcdefgh ab bc cf def
```

Output:
```plaintext
Pattern "ab" found at Position 0
Pattern "bc" found at Position 1
Pattern "cf" found at Position 5
Pattern "def" found at Position 3
```

## References
This implementation is based on the Aho-Corasick algorithm described in the following paper:
Aho, Alfred V., and Corasick, Margaret J. "Efficient string matching: An aid to bibliographic search." Communications of the ACM 18.6 (1975): 333-340.
