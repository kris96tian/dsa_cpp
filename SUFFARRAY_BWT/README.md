# SUFFARRAY_BWT
This repository contains a C++ implementation of the Suffix Array and Burrows-Wheeler Transform (BWT) algorithms. The implementation is designed to handle inputs of large size, making it suitable for handling genomic data.

## Getting Started
To get started, clone the repository and navigate to the SUFFARRAY_BWT directory:

```bash
git clone https://github.com/kris96tian/dsa_cpp.git
cd dsa_cpp/SUFFARRAY_BWT
```

## Usage
To build the project, run the following command:

```bash
mkdir build && cd build
cmake ..
make
```
This will create an executable named suffarray_bwt. To use the program, run it and provide the input file as a command-line argument:

```bash

./suffarray_bwt input.txt
The output will be written to a file named output.txt.
```
The program accepts two command-line arguments:

-i or --input: The input file.
-o or --output: The output file.
For example, to specify a custom output file, run:

```bash
./suffarray_bwt -i input.txt -o output.txt
```
The input file should contain a single string, which will be processed by the Suffix Array and Burrows-Wheeler Transform algorithms.

## Acknowledgments
The Suffix Array and Burrows-Wheeler Transform algorithms are based on the following resources:
Suffix Array Construction by Induced Sorting by Maxime Crochemore, Stefano Lonardi, and Gabriele Ponty.
The Burrows-Wheeler Transform and Its Applications by Michael Burrows and David Wheeler.

