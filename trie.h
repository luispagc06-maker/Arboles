#ifndef TRIE_H
#define TRIE_H

#include <map>
#include <string>
#include <vector>

class Trie {
private:
    struct Nodo {
        bool fin;
        std::map<char, Nodo*> hijos;
        Nodo() : fin(false) {}
    };

    Nodo* root;
    void recolectar(Nodo* n, std::string pref, std::vector<std::string>& r);

public:
    Trie();
    void insertar(const std::string& palabra);
    std::vector<std::string> autocompletar(const std::string& pref);
};

#endif
