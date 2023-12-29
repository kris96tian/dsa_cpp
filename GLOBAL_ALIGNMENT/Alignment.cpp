#include "Alignment.hpp"
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>

Alignment::Alignment(const std::string& seq_v, const std::string& seq_h) 
    : seq_v(seq_v), seq_h(seq_h), score(0) 
    {}

void Alignment::compute(const int match, const int mismatch, const int gap, const bool local_align) {
    // Init DP table with zeros
    std::vector<std::vector<int>> dp(seq_v.size()+1, std::vector<int>(seq_h.size()+1, 0));

    // Fill DP table
    for (size_t i = 1; i <= seq_v.size(); i++) {
        for (size_t j = 1; j <= seq_h.size(); j++) {
            int matchScore = (seq_v[i-1] == seq_h[j-1] ? match : -mismatch) + dp[i-1][j-1];
            int gapScoreV = gap + dp[i-1][j];
            int gapScoreH = gap + dp[i][j-1];
            int maxScore = std::max({matchScore, gapScoreV, gapScoreH, 0});
            dp[i][j] = (local_align ? std::max(0, maxScore) : maxScore);
            if (dp[i][j] > score) {
                score = dp[i][j];
            }
        }
    }

    // Traceback 
    a1.clear();
    gaps.clear();
    a2.clear();
    size_t i = seq_v.size();
    size_t j = seq_h.size();
    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i-1][j-1] + (seq_v[i-1] == seq_h[j-1] ? match : -mismatch)) {
            a1.insert(a1.begin(), seq_v[i-1]);
            gaps.insert(gaps.begin(), (seq_v[i-1] == seq_h[j-1] ? '|' : ' '));
            a2.insert(a2.begin(), seq_h[j-1]);
            i--;
            j--;
        }
        else if (dp[i][j] == dp[i-1][j] + gap) {
            a1.insert(a1.begin(), seq_v[i-1]);
            gaps.insert(gaps.begin(), ' ');
            a2.insert(a2.begin(), '-');
            i--;
        }
        else {
            a1.insert(a1.begin(), '-');
            gaps.insert(gaps.begin(), ' ');
            a2.insert(a2.begin(), seq_h[j-1]);
            j--;
        }
    }
}

int Alignment::getScore() const {
    return score;
}

void Alignment::getAlignment(std::string& a1, std::string& gaps, std::string& a2) const {
    a1 = this->a1;
    gaps = this->gaps;
    a2 = this->a2;
}
