## Global Alignment Algorithm in C++

Implementation of the Needleman-Wunsch global alignment algorithm in C++. The global alignment algorithm is widely used in bioinformatics to compare two sequences and identify similarities and differences between them.

### Files

1. **Alignment.hpp**: This header file defines the `Alignment` class, which is responsible for performing the global alignment of sequences. It includes methods to compute the alignment score and generate the aligned sequences.

2. **Alignment.cpp**: This file contains the implementation of the `Alignment` class methods. It includes the `compute` method to calculate the alignment score and generate the aligned sequences based on the given match, mismatch, and gap penalties.

3. **main.cpp**: This file contains the main function that reads sequences from input files, performs global alignment using the `Alignment` class, and writes the alignment results to an output file.

### Usage

To use this program, follow these steps:

1. Compile the source files using a C++ compiler.
   
2. Run the compiled executable with the following command-line arguments:

```bash
./executable file1 file2 [match] [mismatch] [gap]
```


- `file1` and `file2` are the paths to the input files in `fasta format` containing sequences to be aligned.

- `match`, `mismatch`, and `gap` (optional) are the match, mismatch, and gap penalties, respectively. If not provided, default values of `3`, `-1`, and `-2` are used.

### Example

```bash
./alignment_executable sequences1.fasta sequences2.fasta
```


This command aligns the sequences from `sequences1.fasta` and `sequences2.fasta` using match, mismatch, and gap penalties of `3`, `-1`, and `-2`, respectively, and saves the alignment results to an output file.

### Output

The alignment results are saved to a text file named "results_DATE_TIME.txt", where DATE_TIME represents the current date and time. Each alignment score and the corresponding aligned sequences are written to the output file.

![Example output file](<img src="blob:chrome-untrusted://media-app/16c03f3d-d130-4f4a-ba82-0a9b0bb0123c" alt="Screenshot 2024-04-04 18.18.20.png"/>![image](https://github.com/kris96tian/dsa_cpp/assets/92834350/3ca67755-718f-4814-be5e-9ee0ce26786f)
)

