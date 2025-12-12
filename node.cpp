#include "node.h"
#include <algorithm>

Node::Node(int _id, std::string _nombre, NodeType _tipo)
    : id(_id), nombre(_nombre), tipo(_tipo), contenido(""), parent(nullptr) {}

void Node::addChild(Node* hijo) {
    hijo->parent = this;
    children.push_back(hijo);
}

bool Node::removeChild(Node* hijo) {
    auto it = std::find(children.begin(), children.end(), hijo);
    if (it == children.end()) return false;
    children.erase(it);
    hijo->parent = nullptr;
    return true;
}

Node* Node::findChild(const std::string& name) {
    for (Node* x : children)
        if (x->nombre == name)
            return x;
    return nullptr;
}
