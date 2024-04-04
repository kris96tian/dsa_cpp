#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime> 

#include "Alignment.hpp"

std::string getCurrentDateTime() {
    time_t now = time(0);
    struct tm timeinfo;
    char buffer[80];
    localtime_r(&now, &timeinfo);
    strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", &timeinfo);
    return std::string(buffer);
}

int main(int argc, char* argv[]) 
{
    int match, mismatch, gap;

    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " file1 file2 [match] [mismatch] [gap]\n";
        return 1;
    }

    std::string file1 = argv[1];
    std::string file2 = argv[2];

    if (argc == 3) {
        match = 3;
        mismatch = -1;
        gap = -2;
    } else {
        match = std::stoi(argv[3]);
        mismatch = std::stoi(argv[4]);
        gap = std::stoi(argv[5]);
    }

    // Read sequences from files
    std::ifstream infile1(file1);
    std::ifstream infile2(file2);

    if (!infile1 || !infile2) {
        std::cerr << "Error: Unable to open input files." << std::endl;
        return 1;
    }

    std::vector<std::string> seqs_v, seqs_h;
    std::string line;

    // Read sequences from file1
    while (std::getline(infile1, line)) {
        if (line.empty() || line[0] != '>') continue;
        seqs_v.emplace_back();
        std::getline(infile1, seqs_v.back());
    }

    // Read sequences from file2
    while (std::getline(infile2, line)) {
        if (line.empty() || line[0] != '>') continue;
        seqs_h.emplace_back();
        std::getline(infile2, seqs_h.back());
    }

    infile1.close();
    infile2.close();

    std::string outputFileName = "results_" + getCurrentDateTime() + ".txt";

    // Open output file to save results
    std::ofstream outfile(outputFileName);
    if (!outfile) {
        std::cerr << "Error: Unable to create output file." << std::endl;
        return 1;
    }

    // Align sequences and write results to the output file
    for (size_t i = 0; i < std::min(seqs_v.size(), seqs_h.size()); ++i) {
        Alignment alignment(seqs_v[i], seqs_h[i]);
        alignment.compute(match, mismatch, gap);
        int score = alignment.getScore();
        outfile << "Alignment score for sequence " << i + 1 << ": " << score << std::endl;

        // Get the aligned sequences
        std::string a1, gaps, a2;
        alignment.getAlignment(a1, gaps, a2);
        outfile << "Aligned sequences:" << std::endl;
        outfile << a1 << std::endl;
        outfile << gaps << std::endl;
        outfile << a2 << std::endl;
        outfile << std::endl;
    }

    outfile.close();

    std::cout << "Alignment results have been saved to " << outputFileName << std::endl;

    return 0;
}
