#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <vector>

class Tree {
private:
    Node* root;

    Node* insertar(Node* actual, int id, const std::string& nombre);
    void inOrden(Node* actual) const;
    Node* buscar(Node* actual, int id);
    Node* eliminar(Node* actual, int id);
    Node* nodoMinimo(Node* actual);

    void serializar(Node* actual, std::vector<std::pair<int,std::string>>& datos);

public:
    Tree();

    void insertar(int id, const std::string& nombre);
    void mostrar() const;
    Node* buscar(int id);
    void eliminar(int id);

    // JSON
    std::vector<std::pair<int,std::string>> exportar();
    void importar(const std::vector<std::pair<int,std::string>>& datos);
};

#endif
