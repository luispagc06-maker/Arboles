#include "json_manager.h"
#include <fstream>

bool JSONManager::guardar(const std::string& archivo, Tree&)
{
    std::ofstream out(archivo.c_str());
    if (!out) return false;
    out << "{ \"estado\": \"guardado\" }";
    return true;
}
