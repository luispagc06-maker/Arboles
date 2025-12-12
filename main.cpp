#include <iostream>
#include "tree.h"
#include "trie.h"
#include "json_manager.h"
#include "search_index.h"

int main() {
    Tree tree;

    Node* root = tree.insert(nullptr, 1, "root", CARPETA);
    tree.insert(root, 2, "docs", CARPETA);
    tree.insert(root, 3, "readme.txt", ARCHIVO);

    std::cout << "Arbol en preorden:\n";
    tree.printPreorden(tree.getRoot());

    JSONManager::guardar("arbol.json", tree);

    std::cout << "\nArchivo JSON generado.\n";
    return 0;
}
