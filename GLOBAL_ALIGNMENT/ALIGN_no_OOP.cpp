#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to calculate the maximum of three numbers
int max_of_three(int a, int b, int c) {
    return max(max(a, b), c);
}

// Needleman-Wunsch Algorithm
vector<vector<int>> needleman_wunsch(string seq1, string seq2, int gap_penalty, int match_score, int mismatch_penalty) {
    int m = seq1.length();
    int n = seq2.length();

    // Initialize the matrix
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Initialize the first row and column
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i * gap_penalty;
    }

    for (int j = 0; j <= n; j++) {
        dp[0][j] = j * gap_penalty;
    }

    // Fill the matrix
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int match = dp[i - 1][j - 1] + (seq1[i - 1] == seq2[j - 1] ? match_score : mismatch_penalty);
            int delete_gap = dp[i - 1][j] + gap_penalty;
            int insert_gap = dp[i][j - 1] + gap_penalty;

            dp[i][j] = max_of_three(match, delete_gap, insert_gap);
        }
    }

    return dp;
}

// Traceback function to generate the alignments
pair<string, string> traceback(vector<vector<int>>& dp, string seq1, string seq2, int gap_penalty, int match_score, int mismatch_penalty) {
    int i = seq1.length();
    int j = seq2.length();

    string aligned_seq1 = "";
    string aligned_seq2 = "";

    while (i > 0 || j > 0) {
        if (i > 0 && dp[i][j] == dp[i - 1][j] + gap_penalty) {
            aligned_seq1 = seq1[i - 1] + aligned_seq1;
            aligned_seq2 = "-" + aligned_seq2;
            i--;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + gap_penalty) {
            aligned_seq1 = "-" + aligned_seq1;
            aligned_seq2 = seq2[j - 1] + aligned_seq2;
            j--;
        } else {
            aligned_seq1 = seq1[i - 1] + aligned_seq1;
            aligned_seq2 = seq2[j - 1] + aligned_seq2;
            i--;
            j--;
        }
    }

    return make_pair(aligned_seq1, aligned_seq2);
}
int main() {
    string sequence1, sequence2;
    int gap_penalty, match_score, mismatch_penalty;

    // Prompting user for input
    cout << "Enter your first sequence: ";
    cin >> sequence1;

    cout << "Enter your second sequence: ";
    cin >> sequence2;

    cout << "Enter the gap penalty: ";
    cin >> gap_penalty;

    cout << "Enter match score: ";
    cin >> match_score;

    cout << "Enter mismatch score: ";
    cin >> mismatch_penalty;
    cout <<"\n";
    vector<vector<int>> alignment_matrix = needleman_wunsch(sequence1, sequence2, gap_penalty, match_score, mismatch_penalty);

    // Perform traceback
    pair<string, string> alignment = traceback(alignment_matrix, sequence1, sequence2, gap_penalty, match_score, mismatch_penalty);

    // Output the alignments and the calculated alignment score
    cout << "First Sequence : " << alignment.first << endl;
    cout << "Second Sequenca: " << alignment.second << endl;
    cout << "Alignment Score: " << alignment_matrix[sequence1.length()][sequence2.length()] << endl;

    return 0;
}
