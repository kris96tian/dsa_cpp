#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <omp.h>
#include <fstream>
#include "QGramIndex.hpp"
#include "a5_util.hpp"
#include <stdexcept>

int main(int argc, char* argv[])
{
    /*
    if (argc == 4) {
        uint32_t numThread = std::stoul(argv[3]);
        omp_set_num_threads(numThread);
    } else */
    if (argc != 3) {
        std::cerr << "Error! Input should be: <GENOME_FILE> <QUERY>\n";
        return 1;
    }

    std::string query = argv[2];
    std::string text;
    std::ifstream file(argv[1]);

    if (!file) {
        std::cerr << "Error opening file: " << argv[1] << "\n";
        return 1;
    }

    std::string line;
    while (getline(file, line)) {
        text += line;
    }
    file.close();

    QGramIndex instanz(text, query.size());

    // Calculate hash for the query
    uint32_t query_hash = instanz.hash(query);

    // Get positions where query occurs in text
    std::vector<uint32_t> hits = instanz.getHits(query_hash);
    std::cout << query << ": ";
    for (uint32_t i : hits) {
        std::cout << i << " ";
    }
    std::cout << '\n';

    return 0;
}
