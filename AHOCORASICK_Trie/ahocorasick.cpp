#include <iostream>
#include <string>
#include <vector>
#include <queue>

const int ALPHABET_SIZE = 26;
using namespace std;

struct TrieNode {
    vector<int> output;
    vector<TrieNode*> children;
    TrieNode* fail;
};

TrieNode* createNode() {
    TrieNode* newNode = new TrieNode();
    newNode->children.assign(ALPHABET_SIZE, nullptr);
    newNode->fail = nullptr;
    return newNode;
}

void insert(TrieNode* root, const string& pattern, int index) {
    TrieNode* current = root;
    for (char c : pattern) {
        int idx = c - 'a';
        if (!current->children[idx])
            current->children[idx] = createNode();
        current = current->children[idx];
    }
    current->output.push_back(index);
}

void buildFailTransitions(TrieNode* root) {
    queue<TrieNode*> q;

    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (root->children[i]) {
            root->children[i]->fail = root;
            q.push(root->children[i]);
        }
    }

    while (!q.empty()) {
        TrieNode* current = q.front();
        q.pop();

        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (current->children[i]) {
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

void AhoCorasickSearch(const string& text, TrieNode* root, const vector<string>& all_patterns) {
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


/*          M A I N 
*//////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) 
{
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <text> <pattern1> <pattern2> ..." << endl;
        return 1;}

    string random_text = argv[1];
    vector<string> some_patterns;
    
    for (int i = 2; i < argc; ++i)
        some_patterns.push_back(argv[i]);

    TrieNode* root_node = createNode();

    for (int i = 0; i < some_patterns.size(); ++i)
        insert(root_node, some_patterns[i], i);

    buildFailTransitions(root_node);
    AhoCorasickSearch(random_text, root_node, some_patterns);

    return 0;
}

 /*
           E X A M P L E    U S A G E :
    
Input:
    ./ahocorasick abcdefgh ab bc cf def

Output:
    Pattern "ab" found at Position 0
    Pattern "bc" found at Position 1
    Pattern "def" found at Position 3*/
