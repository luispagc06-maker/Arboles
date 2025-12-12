#include "tree.h"
#include <iostream>

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    delete root;
}

Node* Tree::getRoot() { return root; }
void Tree::setRoot(Node* r) { root = r; }

Node* Tree::findById(Node* actual, int id) {
    if (!actual) return nullptr;
    if (actual->id == id) return actual;

    for (Node* h : actual->children) {
        Node* f = findById(h, id);
        if (f) return f;
    }
    return nullptr;
}

Node* Tree::insert(Node* parent, int id, const std::string& nombre, NodeType tipo) {
    Node* nuevo = new Node(id, nombre, tipo);
    nuevo->parent = parent;

    if (parent)
        parent->children.push_back(nuevo);
    else
        root = nuevo;

    return nuevo;
}

bool Tree::remove(Node* nodo) {
    if (!nodo || nodo == root) return false;

    Node* p = nodo->parent;
    for (int i = 0; i < p->children.size(); i++) {
        if (p->children[i] == nodo) {
            p->children.erase(p->children.begin() + i);
            delete nodo;
            return true;
        }
    }
    return false;
}

bool Tree::move(Node* nodo, Node* nuevoPadre) {
    if (!nodo || nodo == root) return false;

    Node* p = nodo->parent;
    for (int i = 0; i < p->children.size(); i++) {
        if (p->children[i] == nodo) {
            p->children.erase(p->children.begin() + i);
            break;
        }
    }

    nodo->parent = nuevoPadre;
    nuevoPadre->children.push_back(nodo);

    return true;
}

bool Tree::rename(Node* nodo, const std::string& nuevoNombre) {
    if (!nodo) return false;
    nodo->nombre = nuevoNombre;
    return true;
}

void Tree::printPreorden(Node* n) {
    if (!n) return;

    std::cout << n->id << " - " << n->nombre << std::endl;

    for (Node* h : n->children)
        printPreorden(h);
}
