#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class PDA
{
public:
    enum class Language {
      HAIRPIN, 
      BRACKETS 
    };

    enum class State {
      IN_PROGRESS = 0, 
      SUCCESS = 1,     ///< currently in accepting state, i.e. stack is empty after reading final $ symbol
      FAIL = 2         ///< sequence is not in language
    };

    /// Constructor, which specifies which language to check (HAIRPIN by default) and internally builds up the production rules
    PDA(const Language l = Language::HAIRPIN);
    
    /// Read the next symbol and internally traverse states
    /// If a fail state was reached in the previous call, the fail state will be maintained
    /// @param a The symbol to read
    /// @return current state of PDA
    State next(const char a);
    
    /// Reset the automaton to a state as if newly constructed
    /// I.e. init stack and set state to s0 (IN_PROGRESS).
    void reset();
	 
protected:
  struct Rule
  {
    char input;
    PDA::State state;
    char top_stack;
    PDA::State new_state;
    std::string add;
  };
  
  std::string stack;
  State machine_State;
  std::vector<Rule> grammar;

  //get letter, current machine_state, top of the stack, and grammar
  // return true if grammar works out 
  bool lookup(const char a, State machine_state, const char top, Rule rule);

};

