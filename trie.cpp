#include "trie.h"

Trie::Trie() { root = new Nodo(); }

void Trie::insertar(const std::string& palabra)
{
    Nodo* a = root;
    for (size_t i = 0; i < palabra.size(); i++) {
        char c = palabra[i];
        if (!a->hijos[c]) a->hijos[c] = new Nodo();
        a = a->hijos[c];
    }
    a->fin = true;
}

void Trie::recolectar(Nodo* n, std::string pref, std::vector<std::string>& r)
{
    if (n->fin) r.push_back(pref);
    for (std::map<char, Nodo*>::iterator it = n->hijos.begin(); it != n->hijos.end(); ++it)
        recolectar(it->second, pref + it->first, r);
}

std::vector<std::string> Trie::autocompletar(const std::string& pref)
{
    Nodo* a = root;
    for (size_t i = 0; i < pref.size(); i++) {
        if (!a->hijos[pref[i]]) return std::vector<std::string>();
        a = a->hijos[pref[i]];
    }
    std::vector<std::string> r;
    recolectar(a, pref, r);
    return r;
}
