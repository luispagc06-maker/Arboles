#include "tree.h"
#include <iostream>

Tree::Tree() {
    root = 0;
}

Tree::~Tree() {
    delete root;
}

Node* Tree::getRoot() {
    return root;
}

Node* Tree::insert(Node* parent, int id, const std::string& nombre, NodeType tipo)
{
    Node* nuevo = new Node(id, nombre, tipo);
    nuevo->parent = parent;

    if (parent)
        parent->children.push_back(nuevo);
    else
        root = nuevo;

    return nuevo;
}

Node* Tree::findById(Node* actual, int id)
{
    if (!actual) return 0;
    if (actual->id == id) return actual;

    for (size_t i = 0; i < actual->children.size(); i++) {
        Node* r = findById(actual->children[i], id);
        if (r) return r;
    }
    return 0;
}

bool Tree::move(Node* nodo, Node* nuevoPadre)
{
    if (!nodo || !nuevoPadre || nodo == root) return false;

    Node* p = nodo->parent;
    for (size_t i = 0; i < p->children.size(); i++) {
        if (p->children[i] == nodo) {
            p->children.erase(p->children.begin() + i);
            break;
        }
    }

    nodo->parent = nuevoPadre;
    nuevoPadre->children.push_back(nodo);
    return true;
}

bool Tree::remove(Node* nodo)
{
    if (!nodo || nodo == root) return false;

    Node* p = nodo->parent;
    for (size_t i = 0; i < p->children.size(); i++) {
        if (p->children[i] == nodo) {
            p->children.erase(p->children.begin() + i);
            delete nodo;
            return true;
        }
    }
    return false;
}

bool Tree::rename(Node* nodo, const std::string& nuevo)
{
    if (!nodo) return false;
    nodo->nombre = nuevo;
    return true;
}

void Tree::preorden(Node* nodo, int nivel)
{
    if (!nodo) return;

    for (int i = 0; i < nivel; i++) std::cout << "  ";
    std::cout << nodo->nombre << std::endl;

    for (size_t i = 0; i < nodo->children.size(); i++)
        preorden(nodo->children[i], nivel + 1);
}
