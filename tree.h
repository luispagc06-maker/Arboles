#ifndef TREE_H
#define TREE_H

#include "node.h"

class Tree {
private:
    Node* root;
    int nextId;

public:
    Tree();

    Node* getRoot() const { return root; }
};

#endif
