#include "JSONManager.h"
#include <fstream>
#include <sstream>

bool JSONManager::guardar(const std::string& ruta, const std::vector<std::pair<int,std::string>>& datos) {
    std::ofstream archivo(ruta);
    if (!archivo.is_open()) return false;

    archivo << "[\n";
    for (size_t i = 0; i < datos.size(); i++) {
        archivo << "  {\"id\": " << datos[i].first
                << ", \"nombre\": \"" << datos[i].second << "\"}";
        if (i < datos.size() - 1) archivo << ",";
        archivo << "\n";
    }
    archivo << "]\n";

    archivo.close();
    return true;
}

std::vector<std::pair<int,std::string>> JSONManager::cargar(const std::string& ruta) {
    std::ifstream archivo(ruta);
    std::vector<std::pair<int,std::string>> datos;

    if (!archivo.is_open()) return datos;

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.find("\"id\"") != std::string::npos) {
            int id;
            std::string nombre;

            // Extraer id
            size_t pos = linea.find(":");
            id = std::stoi(linea.substr(pos + 1));

            // Extraer nombre
            std::getline(archivo, linea);
            pos = linea.find(":");
            size_t inicio = linea.find("\"", pos);
            size_t fin = linea.find("\"", inicio + 1);
            nombre = linea.substr(inicio + 1, fin - inicio - 1);

            datos.push_back({id, nombre});
        }
    }

    archivo.close();
    return datos;
}
