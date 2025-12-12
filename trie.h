#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <vector>
#include <string>

class TrieNode {
public:
    bool end;
    std::unordered_map<char, TrieNode*> next;

    TrieNode(): end(false) {}
};

class Trie {
private:
    TrieNode* root;
    void clearNode(TrieNode* n);
    void collect(TrieNode* n, std::string pref, std::vector<std::string>& out);

public:
    Trie();
    ~Trie();
    void clear();
    void insert(const std::string& word);
    std::vector<std::string> autocomplete(const std::string& prefix);
};

#endif
