#ifndef SEARCH_INDEX_H
#define SEARCH_INDEX_H

#include <map>
#include <string>

class SearchIndex {
private:
    std::map<std::string, int> tabla;

public:
    void add(const std::string& nombre, int id);
    int buscar(const std::string& nombre);
};

#endif
