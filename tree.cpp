#include "tree.h"

Tree::Tree() : root(nullptr) {}

void Tree::setRoot(Node* r) {
    root = r;
}

Node* Tree::getRoot() {
    return root;
}

Node* Tree::buscarPorID(Node* actual, int id) {
    if (!actual) return nullptr;
    if (actual->id == id) return actual;

    for (auto h : actual->children) {
        Node* encontrado = buscarPorID(h, id);
        if (encontrado) return encontrado;
    }
    return nullptr;
}
