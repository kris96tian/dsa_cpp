#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector> 
#include <string>
#include "sa_bwt.hpp"
 
void construct(std::vector<uint32_t>& sa, const std::string& text)
{
  if (text.empty())       { sa.clear(); return; }	
  sa.clear();
  sa.resize(text.size());
  for (uint32_t i = 0; i < text.size(); ++i)   { sa[i] = i; }

  std::sort(sa.begin(), sa.end(), [&text](uint32_t i, uint32_t j) {
     uint32_t n = text.size();
     while (i < n && j < n && text[i] == text[j]) { ++i;   ++j; }
     return (i == n || j == n) ? i > j : text[i] < text[j];
     });
}


void find(const std::string& query, const std::vector<uint32_t>& sa, const std::string& text, std::vector<uint32_t>& hits)
{ 
  hits.clear();
  if (query.empty())    {  return; }
  
  auto left = std::lower_bound(sa.begin(), sa.end(), query, 
	[&text](uint32_t i, const std::string& q) 
        {return text.compare(i, std::string::npos, q)  < 0;
  });

  
  auto right = std::upper_bound(sa.begin(), sa.end(), query, 
	[&text](const std::string& q, uint32_t i) 
	{return text.compare(i, std::string::npos, q)  > 0;
   });
 
  //loop iter. über  range von gefundenen ,
  // also vom erstenbis zum letzten Occ. der query ^ fügt sie in vec hits:
  for (auto it = left; it != right; ++it)    { hits.push_back(*it); }
}


void construct_BWT(const std::vector<uint32_t>& sa, const std::string& input_text, std::string& BW
  , std::vector<uint32_t>& sa_bwt)
{// Konstruiere BWT-Text durch Ablesen des letzten Zeichens jedes Suffix im sortierten Suffix-Array
  BW.clear();
  sa_bwt.clear();
  for (uint32_t i = 0; i < sa.size(); ++i) 
   {
      if (sa[i] == 0) 
        {
          sa_bwt.push_back(BW.size());
          BW.push_back(input_text[input_text.size() - 1]);
         }
       else 
         {
          sa_bwt.push_back(BW.size());
          BW.push_back(input_text[sa[i] - 1]);
         }
    }
}

void sa_to_text(const std::vector<uint32_t>& sa, const std::string& BWT, std::string& text)
{
  text.clear();
  text.resize(BWT.size());
  uint32_t idx = sa[0];
  text[BWT.size() - 1] = BWT[idx];
	
  for (uint32_t i = 1; i < sa.size(); ++i) 
  { // folge im BWT-Text der Permutation im Suffix-Array
     idx = sa[idx];
     text[BWT.size() - i - 1] = BWT[idx];
  }
}

void text_to_sa(const std::string& input_text, const std::string& BWT, const std::vector<uint32_t>& sa_bwt, std::vector<uint32_t>& sa)
{
  std::vector<uint32_t> rank(256, 0);
  for (char c : BWT)   { ++rank[c]; }
	
  // kumulative Summe von rank
  std::partial_sum(rank.begin(), rank.end(), rank.begin());
  // Init sa mit Rangsumme v. 1 Vorkommen jedes Zeichens im BWT-Text
  std::vector<uint32_t> first_occ(256, 0);
  std::copy(rank.begin(), rank.end() - 1, first_occ.begin());

  for (uint32_t i = 0; i < sa_bwt.size(); ++i) 
   {
      char c = BWT[i];
      sa[first_occ[c]] = i;
      ++first_occ[c];
   }
   // Bestimme den Rang des Suffixes mit Index 0 im Suffix-Array
   uint32_t rank0 = 0;
   for (uint32_t i = 0; i < sa_bwt.size(); ++i) 
   {
      if (sa[i] == 0)  { rank0 = i;   break; }
   }
    //Indizes der restlichen Suffixe durch iteratives Verfolgen der Permutationen im BWT-Text
    for (uint32_t i = 0; i < sa_bwt.size(); ++i) 
    {
      char c = BWT[i];
      sa[rank[c]] = i;
      ++rank[c];
    }	
    sa.erase(sa.begin() + rank0);
    sa.insert(sa.begin(), 0);
}
