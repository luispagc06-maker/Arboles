#ifndef SEARCH_INDEX_H
#define SEARCH_INDEX_H

#include <unordered_map>
#include <string>
#include <vector>
#include "node.h"
#include "trie.h"

class SearchIndex {
private:
    std::unordered_map<std::string, Node*> mapa;
    Trie trie;

    void indexRec(Node* n);

public:
    SearchIndex();
    void clear();
    void build(Node* root); // construir índice desde root
    Node* findExact(const std::string& name);
    std::vector<std::string> autocomplete(const std::string& prefix);
};

#endif

