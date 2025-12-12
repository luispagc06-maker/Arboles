
#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <map>
#include <vector>

class Trie {
private:
    struct NodoTrie {
        bool fin;
        std::map<char, NodoTrie*> hijos;
        std::vector<int> ids;

        NodoTrie() : fin(false) {}
    };

    NodoTrie* root;

    void autoRecorrer(NodoTrie* nodo, std::string prefijo, std::vector<std::string>& out);

public:
    Trie();
    ~Trie();

    void insertar(const std::string& palabra, int id);
    std::vector<std::string> autocompletar(const std::string& prefijo);
};

#endif
