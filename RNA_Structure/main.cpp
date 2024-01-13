#include <iostream>
#include "nussinov.hpp"

int main(int argc, char* argv[]) {
    std::string sequence;
    if (argc > 1) {
        sequence = argv[1];
    } else {
        std::cout << "Please enter the RNA sequence: ";
        std::cin >> sequence;
    }
    Nussinov nussinov(sequence);
    std::string structure = nussinov.calculateStructure();
    std::cout << "Sequence: " << sequence << std::endl;
    std::cout << "Structure: " << structure << std::endl;
    return 0;
}