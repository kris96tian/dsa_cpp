#include "PDA.hpp"

PDA::PDA(const Language l)
{
  if(l == Language::HAIRPIN)
  {
     this -> stack = "%$";
     this -> machine_State = State::IN_PROGRESS;
     this -> grammar =  {       {'a', State::IN_PROGRESS, '$', State::IN_PROGRESS, "uX"},
			        {'u', State::IN_PROGRESS, '$', State::IN_PROGRESS, "aX"},
			        {'g', State::IN_PROGRESS, '$', State::IN_PROGRESS, "cX"},
			        {'c', State::IN_PROGRESS, '$', State::IN_PROGRESS, "gX"},    		
			        {'a', State::IN_PROGRESS, 'X', State::IN_PROGRESS, "uY"},
			        {'u', State::IN_PROGRESS, 'X', State::IN_PROGRESS, "aY"},  
			        {'g', State::IN_PROGRESS, 'X', State::IN_PROGRESS, "cY"},  
			        {'c', State::IN_PROGRESS, 'X', State::IN_PROGRESS, "gY"},		
			        {'a', State::IN_PROGRESS, 'Y', State::IN_PROGRESS, "uZg"},
			        {'u', State::IN_PROGRESS, 'Y', State::IN_PROGRESS, "aZg"},
			        {'g', State::IN_PROGRESS, 'Y', State::IN_PROGRESS, "cZg"},
			        {'c', State::IN_PROGRESS, 'Y', State::IN_PROGRESS, "gZg"},	
			        {'a', State::IN_PROGRESS, 'Z', State::IN_PROGRESS, "aa"},
			        {'c', State::IN_PROGRESS, 'Z', State::IN_PROGRESS, "aa"},	
			        {'a', State::IN_PROGRESS, 'a', State::IN_PROGRESS, ""},
			        {'u', State::IN_PROGRESS, 'u', State::IN_PROGRESS, ""},
			        {'g', State::IN_PROGRESS, 'g', State::IN_PROGRESS, ""},
			        {'c', State::IN_PROGRESS, 'c', State::IN_PROGRESS, ""},
			        {'$', State::IN_PROGRESS, '%', State::SUCCESS, ""}  };
  }
  if(l == Language::BRACKETS)
  {
      this -> stack = "%$";
      this -> machine_State = State::IN_PROGRESS;
      this -> grammar = {       {'(', State::IN_PROGRESS, '$', State::IN_PROGRESS, ")"},
			        {'(', State::IN_PROGRESS, '%', State::IN_PROGRESS, "%)"},
			        {'(', State::IN_PROGRESS, ')', State::IN_PROGRESS, "))"},
			        {')', State::IN_PROGRESS, ')', State::IN_PROGRESS, ""},
			        {'$', State::IN_PROGRESS, '%', State::SUCCESS, ""} };
   }
}

bool PDA::lookup(const char a, PDA::State machine_state, const char top, PDA::Rule rule)
{
  if(a == rule.input && machine_state == rule.state && top == rule.top_stack) return true;
  return false;
}

PDA::State PDA::next(const char a)
{
  char top = stack.back();
  for(auto rule : grammar)
  {
    if(lookup(a, machine_State, top, rule))
    {
      this -> machine_State = rule.new_state;
      stack.pop_back();
      this -> stack += rule.add;
      return machine_State;
    }
  }
 this -> machine_State = State::FAIL;
 return machine_State;
}

void PDA::reset()
{
  this -> machine_State = State::IN_PROGRESS;
  this -> stack = "%$";
}
