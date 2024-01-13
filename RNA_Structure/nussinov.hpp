#ifndef NUSSINOV_HPP
#define NUSSINOV_HPP

#include <iostream>
#include <vector>
#include <string>

class Nussinov {
public:
    Nussinov(const std::string& sequence);
    void fillScoreMatrix();
    std::string traceback(int i, int j);
    std::string calculateStructure();

private:
    std::string sequence;
    int length;
    std::vector<std::vector<int>> score_matrix;
};

#endif // NUSSINOV_HPP