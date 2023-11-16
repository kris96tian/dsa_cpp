#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "horspool.h"
using namespace std;

void Horspool::setPattern(const string& pat)
{
	this -> pat = pat;
	this -> tabelle = tabelle; 	
	uint32_t indec{0}; //index counter
	
	// inserting values
	for(char element :  pat)
	{	
		if(tabelle.find(element) != tabelle.end())
		{
			if(indec != pat.length()-1)
			{
			tabelle.erase(element);
			tabelle.insert({element, (pat.length() - indec -1)});
			}	
		}else
		{
			if (indec == pat.length()-1)
			{
			  tabelle.insert({element, pat.length()});
			}else
			{
			 tabelle.insert({element, (pat.length() - indec -1)});
			}
		}
	  indec+=1;
	  }
	
}

const string& Horspool::getPattern() const
{
	return this -> pat;
}
 
uint32_t Horspool::getShift_(const char last_char) const
{
	
	if(tabelle.find(last_char) != tabelle.end())
	{
		return tabelle.find(last_char) -> second;
	}
	return (this -> pat).length();
}

vector<size_t> Horspool::getHits(const std::string& text) const
{
	if(text.length() < (this -> pat).length() || (this -> pat).empty()) 
	{
		return vector<size_t>();
	}
	
	vector<size_t> sol{}; //empty vector of solutions 
	size_t pos{0}; //index
	
	while(pos <= text.length() - (this -> pat).length())
	{
		//comparitive index
		size_t comin{(this -> pat).length()};
		while(comin > 0 && ((text[pos+comin-1] == (this -> pat)[comin-1])))
		{
		 comin--;
    }
		if(comin==0)
		{
		 sol.push_back(pos);
		}
    
		alignCheck_(pos);
		pos += getShift_(text[pos+pat.length()-1]);
	}
	return sol;
}
