#include "node.h"

Node::Node(int _id, const std::string& _nombre, NodeType _tipo)
{
    id = _id;
    nombre = _nombre;
    tipo = _tipo;
    parent = nullptr;
    contenido = "";
}

Node::~Node()
{
    for (Node* h : children)
        delete h;
}
