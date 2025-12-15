#include "tree.h"
#include <iostream>

Tree::Tree()
{
    root = new Node(0, "root", CARPETA);
    nextId = 1;
}

Tree::~Tree()
{
    delete root;
}

Node* Tree::getRoot() { return root; }

Node* Tree::findById(Node* n, int id)
{
    if (!n) return 0;
    if (n->id == id) return n;

    for (size_t i = 0; i < n->children.size(); i++) {
        Node* r = findById(n->children[i], id);
        if (r) return r;
    }
    return 0;
}

Node* Tree::mkdir(Node* parent, const std::string& nombre)
{
    Node* n = new Node(nextId++, nombre, CARPETA);
    n->parent = parent;
    parent->children.push_back(n);
    return n;
}

Node* Tree::touch(Node* parent, const std::string& nombre)
{
    Node* n = new Node(nextId++, nombre, ARCHIVO);
    n->parent = parent;
    parent->children.push_back(n);
    return n;
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

bool Tree::move(Node* nodo, Node* nuevoPadre)
{
    if (!nodo || nodo == root) return false;

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

bool Tree::rename(Node* nodo, const std::string& nuevoNombre)
{
    if (!nodo) return false;
    nodo->nombre = nuevoNombre;
    return true;
}

void Tree::preorden(Node* n, int nivel)
{
    for (int i = 0; i < nivel; i++) std::cout << "  ";
    std::cout << n->id << " - " << n->nombre << std::endl;

    for (size_t i = 0; i < n->children.size(); i++)
        preorden(n->children[i], nivel + 1);
}
