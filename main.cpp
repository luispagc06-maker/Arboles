#include <iostream>
#include "tree.h"
#include "json_manager.h"
#include "search_index.h"

int main() {
    Tree t;
    SearchIndex idx;

    t.insert("/", "docs", NodeType::CARPETA);
    t.insert("/docs", "archivo1", NodeType::ARCHIVO);
    t.insert("/", "imagenes", NodeType::CARPETA);

    idx.build(t.getRoot());

    std::cout << "Contenido árbol (preorder):\n";
    for (Node* n : t.preorder())
        std::cout << n->id << " - " << n->nombre << "\n";

    auto sug = idx.suggest("a");
    std::cout << "\nSugerencias para 'a':\n";
    for (auto& s : sug) std::cout << s << "\n";

    JSONManager::save("arbol.json", t);

    return 0;
}
