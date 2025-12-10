#include "search_index.h"

SearchIndex::SearchIndex() { }

void SearchIndex::clear() {
    mapa.clear();
    trie.clear();
}

void SearchIndex::indexRec(Node* n) {
    if (!n) return;
    mapa[n->nombre] = n;
    trie.insert(n->nombre);
    for (Node* c : n->children) indexRec(c);
}

void SearchIndex::build(Node* root) {
    clear();
    if (!root) return;
    indexRec(root);
}

Node* SearchIndex::findExact(const std::string& name) {
    auto it = mapa.find(name);
    if (it == mapa.end()) return nullptr;
    return it->second;
}

std::vector<std::string> SearchIndex::autocomplete(const std::string& prefix) {
    return trie.autocomplete(prefix);
}
