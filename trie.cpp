#include "trie.h"

Trie::Trie() { root = new TrieNode(); }
Trie::~Trie() { clear(); delete root; }

void Trie::clearNode(TrieNode* n) {
    for (auto& p : n->next)
        clearNode(p.second);
    delete n;
}

void Trie::clear() {
    for (auto& p : root->next)
        clearNode(p.second);
    root->next.clear();
}

void Trie::insert(const std::string& word) {
    TrieNode* cur = root;
    for (char c : word) {
        if (!cur->next[c]) cur->next[c] = new TrieNode();
        cur = cur->next[c];
    }
    cur->end = true;
}

void Trie::collect(TrieNode* n, std::string pref, std::vector<std::string>& out) {
    if (n->end) out.push_back(pref);
    for (auto& p : n->next)
        collect(p.second, pref + p.first, out);
}

std::vector<std::string> Trie::autocomplete(const std::string& prefix) {
    TrieNode* cur = root;
    for (char c : prefix) {
        if (!cur->next[c]) return {};
        cur = cur->next[c];
    }
    std::vector<std::string> r;
    collect(cur, prefix, r);
    return r;
}
