# Nussinov RNA Folding

A C++ implementation of the Nussinov algorithm for RNA secondary structure prediction. The Nussinov algorithm is a dynamic programming approach for predicting the minimum free energy structure of an RNA molecule.

## Building and Running

To build the code, first install the required dependencies:

- A C++ compiler (e.g., g++)
- The Boost library ([http://www.boost.org/](http://www.boost.org/))

Then, compile the code with the following command:

```bash
g++ -o main main.cpp nussinov.cpp -lboost_program_options

./main [RNA_SEQUENCE]

//If you do not provide an RNA sequence as a command-line argument, the program will prompt you to enter one.
```

## Usage
The program takes an RNA sequence as input and outputs the predicted minimum free energy structure. The input RNA sequence must consist of only the characters A, C, G, and U, representing the nucleotides adenine, cytosine, guanine, and uracil, respectively.

Here's an example of how to use the program:

```bash
./main GCGCGC

// Output:
Sequence: GCGCGC
Structure: ((..))
```
In this example, the input RNA sequence is GCGCGC, and the predicted RNA Point-Bracket structure is ((..)).

## Implementation

The implementation of the Nussinov algorithm is contained in the nussinov.cpp and nussinov.hpp files. The Nussinov class takes an RNA sequence as input and calculates the minimum free energy structure using dynamic programming.

The calculateStructure function returns the predicted minimum free energy structure as a string of parentheses, where each pair of parentheses represents a base pair in the structure.


## Acknowledgments
This implementation of the Nussinov algorithm is based on the description in the following paper:

Nussinov, R., & Jacobson, J. W. (1980). Fast folding of RNA sequences into secondary structures. Nucleic acids research, 8(20), 4877-4888.
