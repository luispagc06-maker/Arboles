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
    std::string contenido;

    Node* parent;
    std::vector<Node*> children;

    Node(int _id, const std::string& _nombre, NodeType _tipo);
    ~Node();
};

#endif
