#include "Alignment.hpp"
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>




#include "Alignment.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>

Alignment::Alignment(const std::string& seq_v, const std::string& seq_h)
    : seq_v(seq_v), seq_h(seq_h), 
      seq_v_size(seq_v.size()), seq_h_size(seq_h.size()), 
      computed(false) {
    initializeMatrices(0);
}

void Alignment::compute(int match, int mismatch, int gap, bool local_align) {
    if(seq_h.empty() && seq_v.empty()) {
        return;
    }

    initializeMatrices(local_align ? 0 : gap);
    computed = true;

    for(uint32_t i = 1; i <= seq_v_size; ++i) {
        for(uint32_t j = 1; j <= seq_h_size; ++j) {
            int matchValue = matchCheck(seq_v[i - 1], seq_h[j - 1], match, mismatch);
            int scoreDiagonal = matrix[(i - 1) * (seq_h_size + 1) + (j - 1)] + matchValue;
            int scoreUp = matrix[i * (seq_h_size + 1) + (j - 1)] + gap;
            int scoreLeft = matrix[(i - 1) * (seq_h_size + 1) + j] + gap;
            int maxScore = local_align ? std::max({0, scoreDiagonal, scoreUp, scoreLeft}) 
                                       : scoreCalculator(gap, matchValue, scoreDiagonal, scoreUp, scoreLeft);
            
            matrix[i * (seq_h_size + 1) + j] = maxScore;
            if (local_align) {
                if (maxScore == 0) traceback_matrix[i * (seq_h_size + 1) + j] = 0;
                else if (maxScore == scoreDiagonal) traceback_matrix[i * (seq_h_size + 1) + j] = 1;
                else if (maxScore == scoreUp) traceback_matrix[i * (seq_h_size + 1) + j] = 3;
                else traceback_matrix[i * (seq_h_size + 1) + j] = 2;
            } else {
                traceback_matrix[i * (seq_h_size + 1) + j] = tracebackScoreCalculator(gap, matchValue, scoreDiagonal, scoreUp, scoreLeft);
            }
        }
    }
}

int Alignment::getScore() const {
    if(!computed) {
        throw std::runtime_error("Alignment has not been computed yet.");
    }
    return matrix.empty() ? 0 : matrix.back();
}


int Alignment::matchCheck(char char_v, char char_h, int match, int mismatch) const {
    return char_v == char_h ? match : mismatch;
}

int Alignment::scoreCalculator(int gap, int matchValue, int diagonal, int left, int top) const {
    return std::max({matchValue + diagonal, left + gap, top + gap});
}

int Alignment::tracebackScoreCalculator(int gap, int matchValue, int diagonal, int left, int top) const {
    int option1 = matchValue + diagonal;
    int option2 = left + gap;
    int option3 = top + gap;
    if (option1 >= option2 && option1 >= option3) return 1;
    return option3 > option1 && option3 >= option2 ? 3 : 2;
}

void Alignment::initializeMatrices(int gap) {
    matrix.clear();
    traceback_matrix.clear();
    matrix.resize((seq_v_size + 1) * (seq_h_size + 1), 0);
    traceback_matrix.resize((seq_v_size + 1) * (seq_h_size + 1), 0);
    for (uint32_t i = 0; i <= seq_v_size; ++i) {
        matrix[i * (seq_h_size + 1)] = gap * i;
    }
    for (uint32_t j = 0; j <= seq_h_size; ++j) {
        matrix[j] = gap * j;
    }
}






 /// Output alignment 
void Alignment::getAlignment(std::string& a1, std::string& gaps, std::string& a2) const 
{
  if(this->computed == false)    throw std::invalid_argument("erst compute!");
  else
  {
     a1.clear();
     a2.clear();
     gaps.clear();
		
     if(matrix.empty())
     {
	  a1 += "";
	  a2 += "";
	  gaps += "";
      }
      else
      {
	size_t counter{matrix.size()-1}; 
  	while(traceback_matrix[counter] != 0)
  	{	
  	  if(traceback_matrix[counter] == 1)
  	   {
  	      a2 += this -> seq_h[(counter%(this -> seq_h_size+1))-1];  
  	      a1 += this -> seq_v[counter / (this -> seq_h_size+1)-1]; 
           }	
  	   if(seq_h[(counter%(this -> seq_h_size+1))-1] == this->seq_v[counter / (this -> seq_h_size+1)-1])	
	           { gaps += "|";}
  	   else    { gaps += " ";
	   } 
  	   counter = counter - this -> seq_h_size - 2; //diagonal
  	  }
  	  if(traceback_matrix[counter] == 2)
           {
  	     a2 += this -> seq_h[(counter%(this -> seq_h_size+1))-1];  
             a1 += "-"; 
  	     gaps += " ";
  	     counter--; //left
  	    }
  	  if(traceback_matrix[counter] == 3)
            {
  	      a2 += "-"; //clean divide 
              a1 += this -> seq_v[counter / (this -> seq_h_size+1)-1]; 
  	      gaps += " ";
  	      counter = counter - this -> seq_h_size - 1; //up
  	     }
	  }
	 std::reverse(a1.begin(),a1.end());
	 std::reverse(a2.begin(),a2.end());
	 std::reverse(gaps.begin(),gaps.end());
 }  
}
