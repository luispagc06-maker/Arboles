#ifndef TREE_H
#define TREE_H

#include "node.h"

class Tree {
private:
    Node* root;

public:
    Tree();

    void setRoot(Node* r);
    Node* getRoot();

    Node* buscarPorID(Node* actual, int id);
};

#endif
