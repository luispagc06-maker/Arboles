#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <string>
#include <vector>

class Tree {
private:
    Node* root;
    int nextId;

    void deleteSubtree(Node* n);
    int computeMaxId(Node* n);
    std::vector<std::string> splitPath(const std::string& path);

public:
    Tree();
    ~Tree();

    Node* getRoot() const;
    int getNextId() const;

    // Core operations
    Node* findByPath(const std::string& path);           // "/a/b/c"
    bool insertNode(const std::string& parentPath, const std::string& name, NodeType tipo);
    bool moveNode(const std::string& origenPath, const std::string& destPath);
    bool renameNode(const std::string& path, const std::string& nuevoNombre);
    bool removeToTrash(const std::string& path);        // mueve a /.trash
    bool restoreFromTrash(int id, const std::string& destPath); // restaura por id desde /.trash
    bool permanentDelete(const std::string& path);      // borra definitivamente
    std::vector<Node*> listChildren(const std::string& path);
    std::string getFullPath(Node* nodo);
    std::vector<Node*> preorder();                      // export preorden

    // helpers: trash management
    Node* ensureTrash();                                // crea /.trash si no existe

    // persistence helpers (JSON manager usará getRoot / setRoot)
    void setRoot(Node* r); // toma ownership: borra anterior
};

#endif // TREE_H
