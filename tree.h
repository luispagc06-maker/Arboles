#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <string>

class Tree {
private:
    Node* root;

public:
    Tree();
    ~Tree();

    Node* getRoot();
    Node* insert(Node* parent, int id, const std::string& nombre, NodeType tipo);
    Node* findById(Node* actual, int id);

    bool move(Node* nodo, Node* nuevoPadre);
    bool remove(Node* nodo);
    bool rename(Node* nodo, const std::string& nuevo);

    void preorden(Node* nodo, int nivel);
};

#endif

