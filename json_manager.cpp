#include "json_manager.h"
#include <fstream>

bool JSONManager::guardar(const std::string& filename, Tree& tree)
{
    std::ofstream f(filename.c_str());
    if (!f) return false;

    Node* r = tree.getRoot();
    if (!r) {
        f << "{}";
        return true;
    }

    f << "{\n";
    f << "  \"id\": " << r->id << ",\n";
    f << "  \"nombre\": \"" << r->nombre << "\"\n";
    f << "}\n";

    return true;
}

bool JSONManager::cargar(const std::string& filename, Tree& tree)
{
    // NO requerido para día 12
    return true;
}
