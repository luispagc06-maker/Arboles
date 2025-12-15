#include "search_index.h"

SearchIndex::SearchIndex()
{
    // constructor vacío
}

void SearchIndex::add(const std::string& nombre, int id)
{
    tabla[nombre] = id;
}

void SearchIndex::remove(const std::string& nombre)
{
    if (tabla.count(nombre))
        tabla.erase(nombre);
}

int SearchIndex::find(const std::string& nombre)
{
    if (tabla.count(nombre))
        return tabla[nombre];
    return -1;
}
