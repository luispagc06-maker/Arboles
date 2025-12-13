#include "trie.h"

Trie::Trie() {
    root = new Nodo();
}

void Trie::insertar(const std::string& palabra)
{
    Nodo* act = root;
    for (size_t i = 0; i < palabra.size(); i++) {
        char c = palabra[i];
        if (!act->hijos[c])
            act->hijos[c] = new Nodo();
        act = act->hijos[c];
    }
    act->fin = true;
}

void Trie::recolectar(Nodo* n, std::string pref, std::vector<std::string>& res)
{
    if (n->fin) res.push_back(pref);
    for (std::map<char, Nodo*>::iterator it = n->hijos.begin(); it != n->hijos.end(); ++it)
        recolectar(it->second, pref + it->first, res);
}

std::vector<std::string> Trie::autocompletar(const std::string& prefijo)
{
    Nodo* act = root;
    for (size_t i = 0; i < prefijo.size(); i++) {
        char c = prefijo[i];
        if (!act->hijos[c]) return std::vector<std::string>();
        act = act->hijos[c];
    }

    std::vector<std::string> res;
    recolectar(act, prefijo, res);
    return res;
}
