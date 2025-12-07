#include "tree.h"

Tree::Tree() {
    // Nodo raíz del sistema de archivos
    root = new Node(0, "/", NodeType::CARPETA);
    nextId = 1;
}
