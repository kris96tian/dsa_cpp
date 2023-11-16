#include "QGramIndex.hpp"
#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <omp.h>


const uint8_t DNA_ALPHABET_SIZE = 4;
const uint8_t MAX_Q = 13;

//////////_________KONSTRUKTOR_______////////////////////////////
QGramIndex::QGramIndex(const std::string& text, const uint8_t q)
    : text_(text), q_(q), qgi_(1 << (2 * q_)), sa_(text.size()), dir_(pow(4, q), 0)
{
    if (q > MAX_Q || q < 1)
    {
        throw std::invalid_argument("Error: q is too long!");
    }

    // bitmask:
    uint32_t bitmask = 3 << 2 * (q_ - 1);
    QGramIndex::bitmask_ = ~bitmask << 2;

    // nutze countingSort um den Suffix Array zu erstellen
    QGramIndex::sa_ = QGramIndex::countingSort(dir_, text);
}
///////////////////////////////////////////////////////////////////////////



////////////________COUNTING_SORT______//////////////////////////////////////
std::vector<uint32_t> QGramIndex::countingSort(std::vector<uint32_t>& dir, const std::string& text)
{
    // hash value des ersten q-gram im test wird berechnet
    uint32_t first_qgram_hash = hash(text.substr(0, q_));

    //Demzufolge wird das index element inkrementiert, welches dem hash Wert in "dir" entspricht
    dir[first_qgram_hash]++;

    // Es wird über qgrame im Text iteriert, ab dem 2.en beginnend
    for (auto i = 1u; i <= text.size() - q_; ++i)
    {
        //  hash value vom nächsten q-gram 
        uint32_t next_qgram_hash = hashNext(first_qgram_hash, text[i + q_ - 1]);

        // wieder index in "dir" inkrementieren . .
        dir[next_qgram_hash]++;

        // update hash val entsprechend 
        first_qgram_hash = next_qgram_hash;
    }

    // Kumulative Summe der Elemente in  "dir"
    for (auto j = 1u; j < dir.size(); j++)
       {
        dir[j] += dir[j - 1];
    }


    // suffix array wird mit 0en , aber mit angemessener Größe initialisiert:
    std::vector<uint32_t> sa(dir.back(), 0);

    // hash value vom 1.en q-gram im Text wird berechnet
    first_qgram_hash = hash(text.substr(0, q_));

    // for- Schleife iteriert über alle qgrame im Text, beginnend beim zweiten
    for (auto i = 1u; i <= text.size() - q_; ++i)
    {
        // Update SA mit dem jeweiligen position im text
        updateSuffixArray(dir, sa, first_qgram_hash, i - 1);

        //  nächst. hash value  wird berechnet
        uint32_t next_qgram_hash = hashNext(first_qgram_hash, text[i + q_ - 1]);

        // Update entsprechend..
        first_qgram_hash = next_qgram_hash;
    }

    // Update SA mit letz. Pos. im text
    updateSuffixArray(dir, sa, first_qgram_hash, text.size() - q_);

    //Return nun den sortierten SuffixArray
    return sa;
}
//////////////////////////////////////////////////////////////////////////





///////////////////___METHODEN___//////////////////////////////
///////////////////////////////////////////////////////////////
void QGramIndex::updateSuffixArray(std::vector<uint32_t>& dir, 
                                   std::vector<uint32_t>& sa, 
                                   uint32_t hash_value, uint32_t position){
    dir[hash_value]--;
    sa[dir[hash_value]] = position;
}




/*
   ______HASH________
 
*/
uint32_t QGramIndex::hash(const std::string& qgram) const{
    if (qgram.size() != QGramIndex::q_)
    {
        throw std::invalid_argument("Falsche QGram Eingabe!");
    }

    // init hash_value mit 0
    uint32_t hash_value = 0;

    // for-Schl. über die characters in qgram
    for (uint32_t i = 0; i < QGramIndex::q_; ++i)
    {
        // character_value  = integer Wert des aktuellen characters
        uint8_t character_value = ordValue(qgram[i]);

        // Shifte hash value 2 bits nach links
        hash_value <<= 2;

        // (akt. hash value) OR (character_value),um letzte 2 bits zu setzten
        hash_value |= character_value;
    }

    return hash_value;
}

/*
   ___________HASHNEXT_________________
 
*/
uint32_t QGramIndex::hashNext(const uint32_t prev_hash, const char new_pos) const{
    // Shifte prev_hash  2 bits nach links
    uint32_t shifted_hash = prev_hash << 2;

    // prev_hash OR 3 , um letzte zwei bits auf 1 zu setzen
    uint32_t hash_with_last_two_bits_set = shifted_hash | 3;

    // Get Value von new_pos 
    uint8_t new_pos_value = ordValue(new_pos);

    //  mask OR n_pos um korrekte bits zu setzen
    uint32_t mask = QGramIndex::bitmask_ | new_pos_value;

    // hash_with_last_two_bits_set AND mask , um nur sichere bits zu behalten
    uint32_t result = hash_with_last_two_bits_set & mask;

    return result;
}
///////////////////////////////////////////////////////////////////





////////////_______GETTERS_______///////////////////////////////////
const std::vector<uint32_t>& QGramIndex::getSA() const{
    return sa_;
    }

const std::string& QGramIndex::getText() const{
    return text_;
    }

uint8_t QGramIndex::getQ() const{
    return q_;
    }



std::vector<uint32_t> QGramIndex::getHits(const uint32_t h) const
{   
    if(h >= dir_.size())  // Check if h is out of range
        throw std::invalid_argument("Error, wrong hash!");
    
    std::vector<uint32_t> hits;
    uint32_t nextQGram = 0;
    if(h == dir_.size()-1) 
        nextQGram = sa_.size();
    else nextQGram = dir_[h+1];

    for(uint32_t i = dir_[h]; i < nextQGram; ++i)
    {
        hits.push_back(sa_[i]);
    }
    return hits;
}