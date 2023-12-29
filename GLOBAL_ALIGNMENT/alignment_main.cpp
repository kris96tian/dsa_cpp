#include <iostream>
#include "Alignment.hpp"

int main(int argc, char* argv[]) 
{

    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " seq1 seq2 [match] [mismatch] [gap]\n";
        return 1; 
    }

    std::string seq_v = argv[1];
    std::string seq_h = argv[2];


    Alignment alignment(seq_v, seq_h);
    int match = (argc > 3 ? std::stoi(argv[3]) : 1);
    int mismatch = (argc > 4 ? std::stoi(argv[4]) : 1);
    int gap = (argc > 5 ? std::stoi(argv[5]) : 1);

    alignment.compute(match, mismatch, gap);
    int score = alignment.getScore();
    std::cout << "Alignment score: " << score << std::endl;

    // Get the aligned sequences
    std::string a1, gaps, a2;
    alignment.getAlignment(a1, gaps, a2);
    std::cout << "Aligned sequences:" << std::endl;
    std::cout << a1 << std::endl;
    std::cout << gaps << std::endl;
    std::cout << a2 << std::endl;

    return 0;
}
