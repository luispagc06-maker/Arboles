#include "search_index.h"

void SearchIndex::add(const std::string& nombre, int id) {
    tabla[nombre] = id;
}

int SearchIndex::buscar(const std::string& nombre) {
    if (tabla.count(nombre)) return tabla[nombre];
    return -1;
}
