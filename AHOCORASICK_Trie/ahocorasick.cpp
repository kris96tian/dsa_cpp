#include <cctype>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// const int ALPHABET_SIZE = 128;

struct TrieNode 
{
  int *output = nullptr;
  size_t output_size = 0;
  size_t output_capacity = 0;
  std::unordered_map<char, std::shared_ptr<TrieNode>> children;
  std::shared_ptr<TrieNode> fail = nullptr;

  ~TrieNode() { delete[] output; }

  void add_output(int index) 
 {
    if (output_size == output_capacity)
    {
          output_capacity = (output_capacity == 0) ? 1 : output_capacity * 2;
          int *new_output = new int[output_capacity];
          for (size_t i = 0; i < output_size; ++i) 
          {
            new_output[i] = output[i];
          }
          delete[] output;
          output = new_output;
    }
    output[output_size++] = index;
  }
};

std::shared_ptr<TrieNode> root = std::make_shared<TrieNode>();


void insert(const std::string &pattern, int index) {
  std::shared_ptr<TrieNode> current = root;
  for (char c : pattern) 
  {
    char idx = std::tolower(c);
    if (current->children.count(idx) == 0) {
      current->children[idx] = std::make_shared<TrieNode>();
    }
    current = current->children[idx];
  }
  current->add_output(index);
}

void buildFailTransitions() {
  std::vector<std::shared_ptr<TrieNode>> q;
    
  for (auto &entry : root->children) {
    entry.second->fail = root;
    q.push_back(entry.second);
  }

  while (!q.empty()) 
  {
    std::shared_ptr<TrieNode> current = q.back();
    q.pop_back();

    for (auto &entry : current->children) 
    {
          char c = entry.first;
          std::shared_ptr<TrieNode> child = entry.second;
    
          std::shared_ptr<TrieNode> temp = current->fail;
          while (temp != nullptr && temp->children.count(c) == 0) 
          {
            temp = temp->fail;
          }
          child->fail = (temp == nullptr) ? root : temp->children[c];
          q.push_back(child);
     }
  }
}

void AhoCorasickSearch(const std::string &text, const std::vector<std::string> &all_patterns){
  std::shared_ptr<TrieNode> current = root;

  for (size_t i = 0; i < text.length(); ++i) 
  {
        char idx = std::tolower(text[i]);
          
        while (current != root && current->children.count(idx) == 0) 
             { current = current->fail; }  
        if (current->children.count(idx) != 0) {  current = current->children[idx];   } 
        else { current = root; }
    
        std::shared_ptr<TrieNode> temp = current;
          
        while (temp != root) 
        {
              for (size_t j = 0; j < temp->output_size; ++j) 
              {
                int index = temp->output[j];
                std::string pattern = all_patterns[index];
                size_t pos = i - pattern.length() + 1;
                std::cout << "Pattern \"" << pattern << "\" found at Position " << pos << std::endl;
              }
          temp = temp->fail;
        }
  }
}


//// MAIN /////////////////////////////////////////////////////////
int main(int argc, char *argv[]) 
{
  if (argc < 3) {
    std::cout << "Usage: " << argv[0]
              << " <text_file_or_string> <pattern1> <pattern2> ..."
              << std::endl;
    return 1;
  }

  std::string input_text;
  if (std::ifstream(argv[1]).good()) 
  {
    std::ifstream file(argv[1]);
    std::getline(file, input_text, '\0');
  } else {
    input_text = argv[1];
  }

    
  std::vector<std::string> patterns;
  for (int i = 2; i < argc; ++i) {
    patterns.push_back(argv[i]);
  }

  for (int i = 0; i < patterns.size(); ++i) {
    insert(patterns[i], i);
  }

  buildFailTransitions();
  AhoCorasickSearch(input_text, patterns);

  return 0;
}
