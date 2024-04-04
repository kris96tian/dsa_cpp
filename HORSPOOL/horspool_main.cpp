#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "horspool.h"

std::string readFasta(const std::string& filename) {
    std::ifstream file(filename);
    std::string sequence;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '>') {
            continue;
        }
        sequence += line;
    }
    return sequence;
}

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        std::cout << argv[0] << " <TEXT_OR_FASTA_FILE> <PATTERN>" << std::endl;
        return 1;
    }

    std::string sequence;
    std::string filename = argv[1];
    if (filename.size() >= 5 && (filename.substr(filename.size() - 5) == ".fasta" || filename.substr(filename.size() - 3) == ".fa")) {
        // Argument is a FASTA file
        sequence = readFasta(filename);
        if (sequence.empty()) {
            std::cerr << "Error: Failed to read sequence from file: " << filename << std::endl;
            return 1;
        }
    } else {
        // Argument is a string
        sequence = filename;
    }

    Horspool h;
    h.setPattern(argv[2]);
    auto hits = h.getHitsFromSequence(sequence);
    
    std::cout << "Horspool search:\n\n-- Hits: --\n";
    for (const auto hit : hits) {
        std::cout << "Pattern found at position: " << hit << std::endl;      
    }
  
    return 0;
}
