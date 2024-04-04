#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// lookup table
std::vector<int> buildShiftTable(const std::string& pattern) {
    const int alphabetSize = 256;
    std::vector<int> shiftTable(alphabetSize, pattern.length());
    for (int i = 0; i < pattern.length() - 1; ++i) {
        shiftTable[pattern[i]] = pattern.length() - 1 - i;
    }
    return shiftTable;
}

// Horspool alg.
std::vector<int> horspool(const std::string& text, const std::string& pattern) {
    std::vector<int> shifts = buildShiftTable(pattern);
    std::vector<int> matches;

    int textLength = text.length();
    int patternLength = pattern.length();
    int i = patternLength - 1;

    while (i < textLength) {
        int k = 0;
        while (k < patternLength && pattern[patternLength - 1 - k] == text[i - k]) {
            ++k;
        }
        if (k == patternLength) {
            matches.push_back(i - patternLength + 1);
        }
        i += shifts[text[i]];
    }

    return matches;
}



// MAIN FUNCTION
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <input_file> <pattern>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cout << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    std::string line, text;
    bool isFirstLine = true;
    while (std::getline(inputFile, line)) {
        if (line[0] != '>') { // Skip fasta header line
            text += line;
        }
    }
    inputFile.close();

    std::string pattern = argv[2];

    std::vector<int> matches = horspool(text, pattern);

    if (matches.empty()) {
        std::cout << "Pattern not found." << std::endl;
    } else {
        std::cout << "Pattern found at positions: ";
        for (int pos : matches) {
            std::cout << pos + 1 << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
