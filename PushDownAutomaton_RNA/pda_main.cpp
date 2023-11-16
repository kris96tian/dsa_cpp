#include "PDA.hpp"
using namespace std;

int main(int argc, const char* argv[])
{
   PDA::Language l;
    if (argc != 2)
    { 
      if (argc == 3)
      {
        l = PDA::Language::BRACKETS; 
	PDA instanz = PDA(l);
        string input_seq  {argv[1]};
	PDA::State state = PDA::State::IN_PROGRESS;	 
	for(size_t counter = 0; counter < input_seq.size(); counter++)
	{
          char letter = input_seq[counter];
          if(letter == '(' || letter == ')')    
	     state = instanz.next(letter);
        }
        if(state == PDA::State::SUCCESS)
	{
          cout << "ACCEPT" << '\n';
          return 0;
	} 
        if(state == PDA::State::FAIL)
	{
          cout << "FAIL" << '\n'; //string kein elem dieser sprache
          return 1;
	}
        } 
        else { throw invalid_argument("zu wenig Argumente");}
    }
    
	 
    l = {PDA::Language::HAIRPIN};
    PDA instanz = PDA(l);
    string input_seq  {argv[1]};
    PDA::State state = PDA::State::IN_PROGRESS;
    for(size_t counter = 0; counter < input_seq.size(); counter++)
    {
      char letter = input_seq[counter];
      state = instanz.next(letter);
    }
    if(state == PDA::State::SUCCESS)
    {  
      cout << "ACCEPT" << '\n'; /* PDA hat alle phasen durchlaufen , stack leer*/
      return 0;
    } 
    if(state == PDA::State::FAIL)
    {
      cout << "FAIL" << '\n'; /* Basenabfolge stellt keine hairpin strucktur dar*/
      return 1;
    }
}
