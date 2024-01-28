#include "sa_bwt.hpp"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, const char* argv[]){
  if (argc == 2){

   string input_text {argv[1]};
   vector<uint32_t> sa = {};
   construct(sa, input_text);
   vector<uint32_t> result(sa.size());
   uint32_t max =*max_element(sa.begin(), 
sa.end());
   
   // (-) 1 f. e. el.& store in result
        
    for (uint32_t j = 0; j < sa.size(); j++) {
       result[j] = sa[j] == 0 ? max : sa[j] - 1;
        }

   // Construct BWT from s.a.
   string bwt(input_text.size(), ' ');
   
    for (uint32_t i = 0; i < sa.size(); i++){
     if (sa[i] == 0){
        
         bwt[i] = input_text.back();}
     else {
         bwt[i] = input_text[sa[i] - 1];}}

    cout << "The suffix array: ";
    for (uint32_t member : sa){
        cout  << member << " ";}
        cout << endl;

        cout << "The Burrows-Wheeler Transform: " << bwt << endl;}
      else{
      cout << "Please provide one argument, the input text." << endl;}
    
return 0;
}
