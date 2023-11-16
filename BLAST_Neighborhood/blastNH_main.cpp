#include "a4_util.h"
#include "BLAST_Neighborhood.hpp"
#include <omp.h>
#include <iostream>
#include <stdexcept>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 6) {
        cerr << "Usage: " << argv[0] << " <SEQ> <SCORE_MATRIX> <WORD_SIZE> <THRESHOLD> <THREADS>" << endl;
        return 1;
    }

    try 
    {
        string query = argv[1];
        int word_size = stoi(argv[3]);
        int score_threshold = stoi(argv[4]);
        int threads = stoi(argv[5]);

        ScoreMatrix scoreMatrix;
        scoreMatrix.load(argv[2]);
        BLAST_Neighborhood blast;
        double start = omp_get_wtime();

        vector<NHResult> blast_results = blast.generateNeighborhood(query, scoreMatrix, word_size, score_threshold, threads);
        double end = omp_get_wtime();

        for (const NHResult& blast_result : blast_results) {
            cout << blast_result.infix << ": ";
            for (const auto& [neighbor, score] : blast_result.neighbors) {
                cout << "(" << neighbor << ", " << score << ") ";
            }
            cout << endl;
        }
        cout << "Time: " << end - start << "s" << endl;
    }
    catch (const exception& e) 
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

/*
Usage after compile (make):
./blastNH_main   <SEQ>  <SCORE_MATRIX>  <WORD_SIZE>  <THRESHOLD>  <THREADS>
 <SEQ> - An amino acid sequence.
 <SCORE_MATRIX> - filename of scoring matrix, like  'blosum62'
<WORD_SIZE> - The length of the words to be generated.
<THRESHOLD> - The limit for which a neighboring word is included in the list.
<THREADS> - Threads number for parallel processing. Currently works only with '1'.
*/