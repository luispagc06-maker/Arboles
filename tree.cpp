#include "tree.h"
#include <iostream>

Tree::Tree() {
    root = nullptr;
}

Node* Tree::insertar(Node* actual, int id, const std::string& nombre) {
    if (!actual) return new Node(id, nombre);
    if (id < actual->id) actual->left = insertar(actual->left, id, nombre);
    else actual->right = insertar(actual->right, id, nombre);
    return actual;
}

void Tree::insertar(int id, const std::string& nombre) {
    root = insertar(root, id, nombre);
}

void Tree::inOrden(Node* actual) const {
    if (!actual) return;
    inOrden(actual->left);
    std::cout << "[" << actual->id << "] " << actual->nombre << "\n";
    inOrden(actual->right);
}

void Tree::mostrar() const {
    if (!root) {
        std::cout << "Árbol vacío.\n";
        return;
    }
    inOrden(root);
}

Node* Tree::buscar(Node* actual, int id) {
    if (!actual) return nullptr;
    if (id == actual->id) return actual;
    if (id < actual->id) return buscar(actual->left, id);
    return buscar(actual->right, id);
}

Node* Tree::buscar(int id) {
    return buscar(root, id);
}

Node* Tree::nodoMinimo(Node* actual) {
    while (actual && actual->left)
        actual = actual->left;
    return actual;
}

Node* Tree::eliminar(Node* actual, int id) {
    if (!actual) return nullptr;

    if (id < actual->id) actual->left = eliminar(actual->left, id);
    else if (id > actual->id) actual->right = eliminar(actual->right, id);
    else {
        if (!actual->left) {
            Node* temp = actual->right;
            delete actual;
            return temp;
        }
        else if (!actual->right) {
            Node* temp = actual->left;
            delete actual;
            return temp;
        }

        Node* temp = nodoMinimo(actual->right);
        actual->id = temp->id;
        actual->nombre = temp->nombre;
        actual->right = eliminar(actual->right, temp->id);
    }
    return actual;
}

void Tree::eliminar(int id) {
    root = eliminar(root, id);
}

void Tree::serializar(Node* actual, std::vector<std::pair<int,std::string>>& datos) {
    if (!actual) return;
    serializar(actual->left, datos);
    datos.push_back({actual->id, actual->nombre});
    serializar(actual->right, datos);
}

std::vector<std::pair<int,std::string>> Tree::exportar() {
    std::vector<std::pair<int,std::string>> datos;
    serializar(root, datos);
    return datos;
}

void Tree::importar(const std::vector<std::pair<int,std::string>>& datos) {
    root = nullptr;
    for (auto& d : datos)
        insertar(d.first, d.second);
}
