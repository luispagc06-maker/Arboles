#ifndef SEARCH_INDEX_H
#define SEARCH_INDEX_H

#include "node.h"
#include "trie.h"
#include <unordered_map>
#include <string>
#include <vector>

class SearchIndex {
private:
    std::unordered_map<std::string, Node*> map;
    Trie trie;

    void indexRec(Node* n);

public:
    void build(Node* root);
    Node* findExact(const std::string& name);
    std::vector<std::string> suggest(const std::string& prefix);
};

#endif
