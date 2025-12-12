#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

#include "tree.h"
#include <string>

class JSONManager {
public:
    static bool guardar(const std::string& filename, Tree& tree);
    static bool cargar(const std::string& filename, Tree& tree);
};

#endif
