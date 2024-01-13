#include <iostream>
#include <string>
#include <vector>
#include <queue>

const int ALPHABET_SIZE = 26;
using namespace std;


struct TrieNode 
{
    vector<int>         output;
    vector<TrieNode*>   children;
    TrieNode*           fail;
};


// Funktion to create a new Node
TrieNode* createNode() 
{
    TrieNode* newNode = new TrieNode();
    newNode->children.assign(ALPHABET_SIZE, nullptr);
    newNode->fail = nullptr;
    return newNode;
}


// Insert-Funktion with params(root_node, pattern, index)
void insert(TrieNode* root, const string& pattern, int index) 
{
    TrieNode* current = root;
    for (char c : pattern) 
    {
        int idx = c - 'a';
        if (!current->children[idx])
            current->children[idx] = createNode();
        current = current->children[idx];
    }
    current->output.push_back(index);
}


void buildFailTransitions(TrieNode* root) 
{
    std::queue<TrieNode*> q;
    
    for (int i = 0; i < ALPHABET_SIZE; ++i) 
    {
        if (root->children[i]) 
        {
            root->children[i]->fail = root;
            q.push(root->children[i]);
        }
    }


    while (!q.empty()) 
    {
        TrieNode* current = q.front();
        q.pop();

        for (int i = 0; i < ALPHABET_SIZE; ++i) 
        {
            if (current->children[i]) 
            {
                TrieNode* temp = current->fail;
                while (temp && !temp->children[i])
                    temp = temp->fail;

                if (temp)
                    current->children[i]->fail = temp->children[i];
                else
                    current->children[i]->fail = root;

                q.push(current->children[i]);
            }
        }
    }
}


// The searching Fkt.
void AhoCorasickSearch(const string& text, TrieNode* root, const vector< string >& all_patterns) 
{
    TrieNode* current = root;

    for (char c : text) 
    {
        int idx = c - 'a';
        while (current && !current->children[idx])
            current = current->fail;

        if (current)
            current = current->children[idx];
        else
            current = root;

        for (int index : current->output)
            cout << "Pattern \"" << all_patterns[index] << "\" found at Position " << index << endl;
    }
}



// 
//   Execution in the Main_Funktion:
//
int main() 
{

    string random_text = "abcdefgh";
    vector<string> some_patterns = {"ab", "bc", "cf", "def"};
    TrieNode* root_node = createNode();


    for (int i = 0; i < some_patterns.size(); ++i)

        insert(root_node, some_patterns[i], i);

        buildFailTransitions(root_node);
        
        AhoCorasickSearch(random_text, root_node, some_patterns);

    return 0;
}
