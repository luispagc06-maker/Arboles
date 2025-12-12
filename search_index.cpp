#include "search_index.h"

void SearchIndex::indexRec(Node* n) {
    map[n->nombre] = n;
    trie.insert(n->nombre);
    for (Node* c : n->children)
        indexRec(c);
}

void SearchIndex::build(Node* root) {
    map.clear();
    trie.clear();
    if (root) indexRec(root);
}

Node* SearchIndex::findExact(const std::string& name) {
    auto it = map.find(name);
    return it == map.end() ? nullptr : it->second;
}

std::vector<std::string> SearchIndex::suggest(const std::string& prefix) {
    return trie.autocomplete(prefix);
}
