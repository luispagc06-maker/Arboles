#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

enum class NodeType { CARPETA, ARCHIVO };

class Node {
public:
    int id;
    std::string nombre;
    NodeType tipo;
    std::string contenido;
    Node* parent;
    std::vector<Node*> children;

    Node(int id, const std::string& n, NodeType t);

    void addChild(Node* n);
};

#endif
