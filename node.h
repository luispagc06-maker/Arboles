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

    Node(int _id = -1, std::string _nombre = "", NodeType _tipo = NodeType::CARPETA);

    void addChild(Node* hijo);
    bool removeChild(Node* hijo);
    Node* findChild(const std::string& name);
};

#endif
