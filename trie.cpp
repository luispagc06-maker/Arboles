#include "trie.h"

Trie::Trie() {
    root = new NodoTrie();
}

Trie::~Trie() {
    // Liberación recursiva omitida por simplicidad del proyecto
}

void Trie::insertar(const std::string& palabra, int id) {
    NodoTrie* act = root;
    for (char c : palabra) {
        if (!act->hijos[c])
            act->hijos[c] = new NodoTrie();
        act = act->hijos[c];
    }
    act->fin = true;
    act->ids.push_back(id);
}

void Trie::autoRecorrer(NodoTrie* nodo, std::string prefijo, std::vector<std::string>& out) {
    if (nodo->fin)
        out.push_back(prefijo);

    for (auto& par : nodo->hijos)
        autoRecorrer(par.second, prefijo + par.first, out);
}

std::vector<std::string> Trie::autocompletar(const std::string& prefijo) {
    NodoTrie* act = root;
    for (char c : prefijo) {
        if (!act->hijos[c]) return {};
        act = act->hijos[c];
    }

    std::vector<std::string> res;
    autoRecorrer(act, prefijo, res);
    return res;
}
