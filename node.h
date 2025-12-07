#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

enum class NodeType {
    CARPETA,
    ARCHIVO
};

class Node {
public:
    int id;
    std::string nombre;
    NodeType tipo;
    std::string contenido;
    std::vector<Node*> children;
    Node* parent;

    Node(int _id, const std::string& _nombre, NodeType _tipo)
        : id(_id), nombre(_nombre), tipo(_tipo), parent(nullptr) {}

};

#endif
