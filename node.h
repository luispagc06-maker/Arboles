#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <algorithm>

enum class NodeType { CARPETA, ARCHIVO };

class Node {
public:
    int id;
    std::string nombre;
    NodeType tipo;
    std::string contenido;
    Node* parent;
    std::vector<Node*> children;

    Node(int _id = -1,
         const std::string& _nombre = std::string(),
         NodeType _tipo = NodeType::CARPETA)
        : id(_id), nombre(_nombre), tipo(_tipo), contenido(), parent(nullptr), children()
    {}

    void addChild(Node* hijo) {
        if (!hijo) return;
        hijo->parent = this;
        children.push_back(hijo);
    }

    bool removeChild(Node* hijo) {
        if (!hijo) return false;
        auto it = std::find(children.begin(), children.end(), hijo);
        if (it == children.end()) return false;
        children.erase(it);
        hijo->parent = nullptr;
        return true;
    }

    Node* findChildByName(const std::string& n) {
        for (Node* c : children) if (c && c->nombre == n) return c;
        return nullptr;
    }

    ~Node() = default; // Tree gestiona borrado recursivo
};

#endif // NODE_H
