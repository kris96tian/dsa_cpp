# QGramm Index Data Structure in C++

This repository contains the implementation of QGramm Index, a data structure used for efficient text search and retrieval. The implementation is in C++.

## What is a QGramm Index?

A QGramm Index is a text indexing data structure that breaks down words into smaller components called Q-grams. These Q-grams are then used to index the words, allowing for efficient text search and retrieval.

## Implementation

The QGramm Index implementation consists of a Trie data structure. Each node in the Trie represents a Q-gram. The children of a node represent the Q-grams that follow the current Q-gram in the Trie.

Here is an example of how the implementation works:

```cpp
QGrammIndex qindex(3); // create a QGramm Index with q = 3

qindex.insert("example"); // insert the word "example" into the QGramm Index

auto result = qindex.search("example"); // search for the word "example" in the QGramm Index

if (result.size() > 0) {
    std::cout << "Word found: " << result[0] << std::endl; // output: "Word found: example"
} else {
    std::cout << "Word not found" << std::endl;
}
```
In this example, the word "example" is inserted into the QGramm Index. Then, a search is performed for the word "example". The search function returns a vector of strings containing all the words that match the search query. In this case, the result vector contains the word "example".
