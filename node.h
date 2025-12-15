#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

enum NodeType { CARPETA, ARCHIVO };

class Node {
public:
    int id;
    std::string nombre;
    NodeType tipo;

    Node* parent;
    std::vector<Node*> children;

    Node(int id, const std::string& nombre, NodeType tipo);
    ~Node();
};

#endif
