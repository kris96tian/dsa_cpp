# WEB SEQ
## Overview
The WEB SEQ is a web application that provides various bioinformatics algorithms and techniques for analyzing DNA, RNA, and protein sequences. The application is built using the Python Flask framework and integrates C++ code for the computational-heavy tasks.

## Key Features

  Global Alignment: Performs global sequence alignment between two input FASTA files, allowing the user to specify match, mismatch, and gap penalty scores.
 
  Horspool Algorithm: Implements the Horspool exact pattern matching algorithm, allowing users to search for a pattern in a FASTA file.

  Aho-Corasick Search: Allows users to search for multiple patterns in a FASTA file using the Aho-Corasick algorithm.

  Q-Gram Index Search: Provides a Q-Gram index-based search mechanism, enabling users to search for a query in a FASTA genome file.

  BLAST Neighborhood Search: Implements a simplified version of the BLAST algorithm, allowing users to search for sequence similarities using a FASTA query, score matrix, word size, and score threshold.

  RNA Structure Prediction: Utilizes the Nussinov algorithm to predict the secondary structure of an RNA sequence provided in a FASTA file.

