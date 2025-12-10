#include "trie.h"
#include <stack>

Trie::Trie() { root = new TrieNode(); }

Trie::~Trie() { clear(); }

void Trie::clear() {
    if (!root) return;
    // eliminar recursivamente
    std::stack<TrieNode*> st;
    st.push(root);
    while (!st.empty()) {
        TrieNode* t = st.top(); st.pop();
        for (auto &p : t->next) st.push(p.second);
        delete t;
    }
    root = new TrieNode();
}

void Trie::insert(const std::string& word) {
    TrieNode* cur = root;
    for (char ch : word) {
        if (!cur->next[ch]) cur->next[ch] = new TrieNode();
        cur = cur->next[ch];
    }
    cur->end = true;
}

void Trie::collect(TrieNode* node, std::string prefix, std::vector<std::string>& out) {
    if (!node) return;
    if (node->end) out.push_back(prefix);
    for (auto &p : node->next) collect(p.second, prefix + p.first, out);
}

std::vector<std::string> Trie::autocomplete(const std::string& prefix) {
    std::vector<std::string> out;
    TrieNode* cur = root;
    for (char ch : prefix) {
        if (!cur->next[ch]) return out;
        cur = cur->next[ch];
    }
    collect(cur, prefix, out);
    return out;
}
