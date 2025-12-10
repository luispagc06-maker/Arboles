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
    void collect(TrieNode* node, std::string prefix, std::vector<std::string>& out);

public:
    Trie();
    ~Trie();
    void insert(const std::string& word);
    std::vector<std::string> autocomplete(const std::string& prefix);
    void clear(); // libera memoria
};

#endif
