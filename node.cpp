#include "node.h"

Node::Node(int id, const std::string& n, NodeType t)
    : id(id), nombre(n), tipo(t), parent(nullptr), contenido("") {}

void Node::addChild(Node* n) {
    n->parent = this;
    children.push_back(n);
}
