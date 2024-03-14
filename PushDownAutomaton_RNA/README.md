# Pushdown Automaton for RNA-Structure Parsing
This repository contains a C++ PDA that can parse RNA sequences and check if they match formal language models defined by context-free grammars.

## Context-Free Grammars
Context-free grammars are able to generate languages like palindromes that cannot be recognized by regular expressions. A CFG defines a set of production rules to derive strings in a language.

The PDA construction and transition rules effectively encode the CFGs for the HAIRPIN and BRACKETS languages. This allows these structures, which require context-sensitive parsing, to be recognized.

## Implementation
The PDA class defines the automaton by maintaining:

- An internal state
- A stack
- Transitions defined by production rules

- It supports two languages - HAIRPIN and BRACKETS - by initializing with different rules.
   
The rules define the CFG productions.

Transitions simulate rewriting the string according to these rules.

## Usage

To run:
```bash
git clone https://github.com/kris96tian/dsa_cpp
cd dsa_cpp/PushDownAutomaton_RNA 
make
./pda_main <rna_sequence>
```
It will parse the input using the HAIRPIN language by default.

Specify the language as the second argument:

```bash
./pda_main <sequence> BRACKETS
```
It will print "ACCEPT" if parsing succeeds or "FAIL" if it fails.

## Acknowledgments
This implementation was developed based on foundational works in formal language and automata theory by Chomsky, Hopcroft, and others. Many key insights and examples were drawn from their texts on context-free grammars and pushdown automata.
