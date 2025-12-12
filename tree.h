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
    void setRoot(Node* r);

    Node* findById(Node* actual, int id);

    Node* insert(Node* parent, int id, const std::string& nombre, NodeType tipo);
    bool remove(Node* nodo);
    bool move(Node* nodo, Node* nuevoPadre);
    bool rename(Node* nodo, const std::string& nuevoNombre);

    void printPreorden(Node* n);
};

#endif
