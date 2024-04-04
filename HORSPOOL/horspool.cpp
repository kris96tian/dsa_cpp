#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "horspool.h"

void Horspool::setPattern(const std::string& pat) {
    pat = pat;
    uint32_t indec{0}; //idx. counter
    
    // inserting vals
    for (char element : pat) {    
        if (tabelle.find(element) != tabelle.end()) {
            if (indec != pat.length() - 1) {
                tabelle.erase(element);
                tabelle.insert({element, (pat.length() - indec - 1)});
            }
        } else {
            if (indec == pat.length() - 1) {
                tabelle.insert({element, pat.length()});
            } else {
                tabelle.insert({element, (pat.length() - indec - 1)});
            }
        }
        indec += 1;
    }
}

const std::string& Horspool::getPattern() const { return pat; }
 
uint32_t Horspool::getShift_(const char last_char) const {
    if (tabelle.find(last_char) != tabelle.end()) {
        return tabelle.find(last_char)->second;
    }
    return pat.length();
}

std::vector<size_t> Horspool::getHits(const std::string& text) const {
    if (text.length() < pat.length() || pat.empty()) {
        return std::vector<size_t>();
    }
    
    std::vector<size_t> sol{}; 
    size_t pos{0}; //index
    
    while (pos <= text.length() - pat.length()) {
        //comparitive index
        size_t comin{pat.length()};
        while (comin > 0 && (text[pos + comin - 1] == pat[comin - 1])) {
            comin--;
        }
        if (comin == 0) { sol.push_back(pos); }
        
        alignCheck_(pos);
        pos += getShift_(text[pos + pat.length() - 1]);
    }
    return sol;
}
