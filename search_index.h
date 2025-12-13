#ifndef SEARCH_INDEX_H
#define SEARCH_INDEX_H

#include <map>
#include <string>

class SearchIndex {
private:
    std::map<std::string, int> tabla;

public:
    void add(const std::string& nombre, int id);
    int find(const std::string& nombre);
};

#endif
