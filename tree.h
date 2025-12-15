#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <string>

class Tree {
private:
    Node* root;
    int nextId;

public:
    Tree();
    ~Tree();

    Node* getRoot();
    Node* findById(Node* n, int id);

    Node* mkdir(Node* parent, const std::string& nombre);
    Node* touch(Node* parent, const std::string& nombre);

    bool remove(Node* nodo);
    bool move(Node* nodo, Node* nuevoPadre);
    bool rename(Node* nodo, const std::string& nuevoNombre);

    void preorden(Node* n, int nivel);
};

#endif
