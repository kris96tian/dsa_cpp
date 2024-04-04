# HORSPOOL Algorithm (Exact string matching in linear time)
This repository contains an implementation of the Horspool algorithm, a simple and efficient algorithm for exact string searching. The Horspool algorithm is an improvement over the naive string search algorithm, which has a worst-case time complexity of O(nm), where n is the length of the text and m is the length of the pattern. The Horspool algorithm has a worst-case time complexity of O(n), which makes it much more efficient for large inputs.

## Usage

To use the Horspool algorithm, follow these steps:

1. Clone the repository:
```bash
git clone https://github.com/kris96tian/dsa_cpp.git
```
2. Navigate to the HORSPOOL directory:
```bash
cd dsa_cpp/HORSPOOL
```
3. Compile the C++ program:
```bash
g++ -o horspool horspool.cpp horspool_main.cpp
```
This command will compile both the horspool.cpp and horspool_main.cpp files into an executable named horspool.
Alternatively just use the Makefile like 
```bash
~/dsa_cpp/HORSPOOL$ make
```
4. After compiling, you can run the program with the text and pattern as command line arguments:

```bash
./horspool "This is a test string." "test"
```

This will output the index of the first occurrence of the pattern in the text.

## Example Output:


```bash
./horspool "This is a test string." "test"
Horspool search:

-- Text is: --
This is a test string.
-- Hits: --
        test
In this example, the pattern "test" is found in the text "This is a test string." at index 8.
```

## Acknowledgments
The Horspool algorithm was invented by Robert Horspool and published in 1980. The implementation in this repository is based on the description in the book "Algorithms in C++, Parts 1-4: Fundamentals, Data Structures, Sorting, Searching" by Robert Sedgewick and Kevin Wayne.
