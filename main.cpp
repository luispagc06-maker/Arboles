#include <iostream>
#include "tree.h"
#include "trie.h"
#include "json_manager.h"

int main()
{
    Tree tree;
    Trie trie;

    Node* root = tree.insert(0, 1, "root", CARPETA);
    Node* docs = tree.insert(root, 2, "docs", CARPETA);
    tree.insert(docs, 3, "tarea.txt", ARCHIVO);
    tree.insert(root, 4, "imagenes", CARPETA);

    trie.insertar("docs");
    trie.insertar("imagenes");
    trie.insertar("tarea.txt");

    std::cout << "=== DEMO PROYECTO ARBOLES ===\n\n";
    std::cout << "Recorrido Preorden:\n";
    tree.preorden(tree.getRoot(), 0);

    std::cout << "\nAutocompletado 'ta':\n";
    std::vector<std::string> res = trie.autocompletar("ta");
    for (size_t i = 0; i < res.size(); i++)
        std::cout << res[i] << std::endl;

    JSONManager::guardar("arbol.json", tree);
    std::cout << "\nJSON generado.\n";

    return 0;
}
