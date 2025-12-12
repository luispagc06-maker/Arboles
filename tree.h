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
    int findMaxId(Node* n);
    std::vector<std::string> split(const std::string& path);

public:
    Tree();
    ~Tree();

    Node* getRoot();
    int getNextId() const;

    Node* find(const std::string& path);
    bool insert(const std::string& parent, const std::string& name, NodeType tipo);
    bool renameNode(const std::string& path, const std::string& nuevo);
    bool move(const std::string& origen, const std::string& destino);
    bool removeToTrash(const std::string& path);
    bool permanentDelete(const std::string& path);
    bool restore(int id, const std::string& destino);

    std::vector<Node*> preorder();
};

#endif
