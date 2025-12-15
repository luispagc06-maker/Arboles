#include "node.h"

Node::Node(int id_, const std::string& nombre_, NodeType tipo_)
{
    id = id_;
    nombre = nombre_;
    tipo = tipo_;
    parent = 0;
}

Node::~Node()
{
    for (size_t i = 0; i < children.size(); i++)
        delete children[i];
}
