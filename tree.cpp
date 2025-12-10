#include "tree.h"
#include <sstream>
#include <algorithm>
#include <iostream>

// ---------------- constructor / destructor ----------------
Tree::Tree() {
    root = new Node(0, "/", NodeType::CARPETA);
    nextId = 1;
}

Tree::~Tree() {
    deleteSubtree(root);
}

void Tree::deleteSubtree(Node* n) {
    if (!n) return;
    for (Node* c : n->children) deleteSubtree(c);
    n->children.clear();
    delete n;
}

int Tree::computeMaxId(Node* n) {
    if (!n) return -1;
    int mx = n->id;
    for (Node* c : n->children) mx = std::max(mx, computeMaxId(c));
    return mx;
}

Node* Tree::getRoot() const { return root; }
int Tree::getNextId() const { return nextId; }

void Tree::setRoot(Node* r) {
    // borra viejo
    if (root) deleteSubtree(root);
    // asigna nuevo
    if (!r) {
        root = new Node(0, "/", NodeType::CARPETA);
        nextId = 1;
        return;
    }
    root = r;
    root->parent = nullptr;
    int mx = computeMaxId(root);
    nextId = (mx >= 0) ? mx + 1 : 1;
}

// ---------------- util split ----------------
std::vector<std::string> Tree::splitPath(const std::string& path) {
    std::vector<std::string> tokens;
    std::stringstream ss(path);
    std::string item;
    while (std::getline(ss, item, '/')) {
        if (!item.empty()) tokens.push_back(item);
    }
    return tokens;
}

// ---------------- findByPath ----------------
Node* Tree::findByPath(const std::string& path) {
    if (path.empty() || path == "/") return root;
    auto tokens = splitPath(path);
    Node* cur = root;
    for (auto &t : tokens) {
        Node* nxt = cur->findChildByName(t);
        if (!nxt) return nullptr;
        cur = nxt;
    }
    return cur;
}

// ---------------- insertNode (mkdir / touch) ----------------
bool Tree::insertNode(const std::string& parentPath, const std::string& name, NodeType tipo) {
    Node* padre = findByPath(parentPath);
    if (!padre) return false;
    if (padre->tipo != NodeType::CARPETA) return false;
    // evitar nombre duplicado
    if (padre->findChildByName(name)) return false;
    Node* nuevo = new Node(nextId++, name, tipo);
    padre->addChild(nuevo);
    return true;
}

// ---------------- moveNode (mv) ----------------
bool Tree::moveNode(const std::string& origenPath, const std::string& destPath) {
    Node* nodo = findByPath(origenPath);
    Node* dest = findByPath(destPath);
    if (!nodo || !dest) return false;
    if (nodo == root) return false;
    if (dest->tipo != NodeType::CARPETA) return false;
    // evitar mover dentro de sí mismo
    Node* t = dest;
    while (t) { if (t == nodo) return false; t = t->parent; }
    // quitar del padre
    nodo->parent->removeChild(nodo);
    dest->addChild(nodo);
    return true;
}

// ---------------- renameNode ----------------
bool Tree::renameNode(const std::string& path, const std::string& nuevoNombre) {
    Node* n = findByPath(path);
    if (!n) return false;
    if (n == root) return false;
    // verificar duplicado entre hermanos
    Node* p = n->parent;
    for (Node* c : p->children) if (c->nombre == nuevoNombre) return false;
    n->nombre = nuevoNombre;
    return true;
}

// ---------------- trash management ----------------
Node* Tree::ensureTrash() {
    Node* trash = findByPath("/.trash");
    if (trash) return trash;
    // crear carpeta .trash en root
    Node* t = new Node(nextId++, ".trash", NodeType::CARPETA);
    root->addChild(t);
    return t;
}

// mover nodo a papelera (no borra)
bool Tree::removeToTrash(const std::string& path) {
    Node* n = findByPath(path);
    if (!n || n == root) return false;
    Node* trash = ensureTrash();
    // quitar del padre y agregar a trash
    n->parent->removeChild(n);
    trash->addChild(n);
    return true;
}

// restaurar desde papelera por id
bool Tree::restoreFromTrash(int id, const std::string& destPath) {
    Node* trash = findByPath("/.trash");
    if (!trash) return false;
    Node* target = nullptr;
    for (Node* c : trash->children) if (c->id == id) { target = c; break; }
    if (!target) return false;
    Node* dest = findByPath(destPath);
    if (!dest || dest->tipo != NodeType::CARPETA) return false;
    // mover
    trash->removeChild(target);
    dest->addChild(target);
    return true;
}

// borrar definitivo (usa path, puede usarse para limpiar papelera)
bool Tree::permanentDelete(const std::string& path) {
    Node* n = findByPath(path);
    if (!n || n == root) return false;
    Node* p = n->parent;
    if (!p) return false;
    p->removeChild(n);
    deleteSubtree(n);
    return true;
}

// ---------------- listChildren (ls) ----------------
std::vector<Node*> Tree::listChildren(const std::string& path) {
    std::vector<Node*> out;
    Node* n = findByPath(path);
    if (!n) return out;
    for (Node* c : n->children) out.push_back(c);
    return out;
}

// ---------------- getFullPath (pwd) ----------------
std::string Tree::getFullPath(Node* nodo) {
    if (!nodo) return "";
    if (nodo == root) return "/";
    std::vector<std::string> parts;
    Node* cur = nodo;
    while (cur && cur != root) {
        parts.push_back(cur->nombre);
        cur = cur->parent;
    }
    std::string path;
    for (int i = (int)parts.size()-1; i >= 0; --i) {
        path += "/" + parts[i];
    }
    if (path.empty()) path = "/";
    return path;
}

// ---------------- preorder export ----------------
static void preorderRec(Node* n, std::vector<Node*>& out) {
    if (!n) return;
    out.push_back(n);
    for (Node* c : n->children) preorderRec(c, out);
}
std::vector<Node*> Tree::preorder() {
    std::vector<Node*> out;
    preorderRec(root, out);
    return out;
}
