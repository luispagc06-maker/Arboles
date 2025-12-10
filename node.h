#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
public:
    int id;
    std::string nombre;
    Node* left;
    Node* right;

    Node(int id, const std::string& nombre);
};

#endif
