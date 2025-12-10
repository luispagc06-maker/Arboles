#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

#include <string>
#include <vector>
#include <utility>

class JSONManager {
public:
    static bool guardar(const std::string& ruta, const std::vector<std::pair<int,std::string>>& datos);
    static std::vector<std::pair<int,std::string>> cargar(const std::string& ruta);
};

#endif
