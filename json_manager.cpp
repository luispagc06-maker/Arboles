#include "json_manager.h"
#include <fstream>

bool JSONManager::guardar(const std::string& archivo, Tree& tree)
{
    std::ofstream out(archivo.c_str());
    if (!out) return false;

    out << "{ \"demo\": \"arbol guardado\" }";
    out.close();
    return true;
}
