#include "node.h"

Node::Node(int id, const std::string& nombre) {
    this->id = id;
    this->nombre = nombre;
    left = nullptr;
    right = nullptr;
}
