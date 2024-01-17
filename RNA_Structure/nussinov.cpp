#include "nussinov.hpp"

Nussinov::Nussinov(const std::string& sequence) : 
                                sequence(sequence), 
                                length(sequence.size()), 
                                score_matrix(length, 
                                std::vector<int>(length, 0))  {}

void Nussinov::fillScoreMatrix() {
    for (int i = 0; i < length; i++) {
        for (int j = i; j < length; j++) {
            if (i == j) {
                score_matrix[i][j] = 0;} 
            else if (sequence[i] == sequence[j] && i + 1 == j) {
                score_matrix[i][j] = 1;} 
            else if (sequence[i] == sequence[j]) {
                score_matrix[i][j] = std::max(score_matrix[i + 1][j - 1] + 1, std::max(score_matrix[i][j - 1], score_matrix[i + 1][j]));} 
            else {
                score_matrix[i][j] = std::max(score_matrix[i + 1][j], score_matrix[i][j - 1]); }}}
}

std::string Nussinov::traceback(int i, int j){
    if (i == j) { return ".";} 
    else if (score_matrix[i][j] == score_matrix[i + 1][j]) 
            { return traceback(i + 1, j);} 
    else if (score_matrix[i][j] == score_matrix[i][j - 1]) 
            {return traceback(i, j - 1);} else {
    return "(" + traceback(i + 1, j - 1) + ")";}
}

std::string Nussinov::calculateStructure() {
    fillScoreMatrix();
    std::string structure = "";
    for (int i = 0; i < length; i++) {
        structure += traceback(0, length - 1 - i);}
    
    return structure;
}
