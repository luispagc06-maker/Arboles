#include "node.h"

Node::Node(int _id, const std::string& _nombre, NodeType _tipo)
{
    id = _id;
    nombre = _nombre;
    tipo = _tipo;
    parent = 0;
}

Node::~Node()
{
    for (size_t i = 0; i < children.size(); i++)
        delete children[i];
}
