#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

#include "tree.h"
#include <string>

class JSONManager {
public:
    static bool guardar(const std::string& filename, Tree& tree);
    static bool cargar(const std::string& filename, Tree& tree);

private:
    static void escribirNodo(std::ofstream& file, Node* nodo, int tab);
    static Node* leerNodo(std::istream& in);
};

#endif
