#include "Alignment.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, const char* argv[]) {
    if (argc != 7) {
        std::cerr << "Usage: " << argv[0] << " <seq1> <seq2> <match> <mismatch> <gap> <local_align>\n";
        return 1;
    }

    try {
        std::string seq1 = argv[1];
        std::string seq2 = argv[2];
        int match = std::atoi(argv[3]);
        int mismatch = std::atoi(argv[4]);
        int gap = std::atoi(argv[5]);
        bool local_align = std::atoi(argv[6]) != 0;

        Alignment alignment(seq1, seq2);
        alignment.compute(match, mismatch, gap, local_align);

        std::string a1, gaps, a2;
        alignment.getAlignment(a1, gaps, a2);
        std::cout << a1 << "\n" << gaps << "\n" << a2 << "\n";
        std::cout << "Score: " << alignment.getScore() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
