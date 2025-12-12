#include "tree.h"
#include <sstream>
#include <algorithm>

Tree::Tree() {
    root = new Node(0, "/", NodeType::CARPETA);
    nextId = 1;
}

Tree::~Tree() {
    deleteSubtree(root);
}

void Tree::deleteSubtree(Node* n) {
    for (Node* c : n->children)
        deleteSubtree(c);
    delete n;
}

int Tree::findMaxId(Node* n) {
    int m = n->id;
    for (Node* c : n->children)
        m = std::max(m, findMaxId(c));
    return m;
}

Node* Tree::getRoot() { return root; }
int Tree::getNextId() const { return nextId; }

std::vector<std::string> Tree::split(const std::string& p) {
    std::vector<std::string> r;
    std::stringstream ss(p);
    std::string tok;
    while (getline(ss, tok, '/'))
        if (!tok.empty()) r.push_back(tok);
    return r;
}

Node* Tree::find(const std::string& path) {
    if (path == "/" || path.empty()) return root;
    auto tokens = split(path);
    Node* cur = root;
    for (auto& t : tokens) {
        cur = cur->findChild(t);
        if (!cur) return nullptr;
    }
    return cur;
}

bool Tree::insert(const std::string& parent, const std::string& name, NodeType tipo) {
    Node* p = find(parent);
    if (!p) return false;
    if (p->findChild(name)) return false;
    Node* n = new Node(nextId++, name, tipo);
    p->addChild(n);
    return true;
}

bool Tree::renameNode(const std::string& path, const std::string& nuevo) {
    Node* n = find(path);
    if (!n || n == root) return false;
    if (n->parent->findChild(nuevo)) return false;
    n->nombre = nuevo;
    return true;
}

bool Tree::move(const std::string& origen, const std::string& destino) {
    Node* a = find(origen);
    Node* b = find(destino);
    if (!a || !b) return false;
    if (a == root) return false;
    if (b->tipo == NodeType::ARCHIVO) return false;
    a->parent->removeChild(a);
    b->addChild(a);
    return true;
}

bool Tree::removeToTrash(const std::string& path) {
    Node* n = find(path);
    if (!n || n == root) return false;

    Node* trash = find("/.trash");
    if (!trash) {
        trash = new Node(nextId++, ".trash", NodeType::CARPETA);
        root->addChild(trash);
    }
    n->parent->removeChild(n);
    trash->addChild(n);
    return true;
}

bool Tree::permanentDelete(const std::string& path) {
    Node* n = find(path);
    if (!n || n == root) return false;
    n->parent->removeChild(n);
    deleteSubtree(n);
    return true;
}

bool Tree::restore(int id, const std::string& destino) {
    Node* trash = find("/.trash");
    if (!trash) return false;
    Node* t = nullptr;

    for (Node* c : trash->children)
        if (c->id == id)
            t = c;

    if (!t) return false;

    Node* d = find(destino);
    if (!d) return false;

    trash->removeChild(t);
    d->addChild(t);
    return true;
}

static void preorderRec(Node* n, std::vector<Node*>& r) {
    r.push_back(n);
    for (Node* c : n->children)
        preorderRec(c, r);
}

std::vector<Node*> Tree::preorder() {
    std::vector<Node*> r;
    preorderRec(root, r);
    return r;
}
