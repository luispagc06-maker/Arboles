#include "json_manager.h"
#include <fstream>
#include <sstream>
#include <iostream>

static std::string tabs(int n) {
    return std::string(n, ' ');
}

bool JSONManager::guardar(const std::string& filename, Tree& tree) {
    std::ofstream file(filename);
    if (!file) return false;

    file << "{\n";
    file << "\"root\": ";
    escribirNodo(file, tree.getRoot(), 0);
    file << "\n}\n";

    return true;
}

void JSONManager::escribirNodo(std::ofstream& file, Node* nodo, int tab) {
    file << "{\n";

    file << tabs(tab+2) << "\"id\": " << nodo->id << ",\n";
    file << tabs(tab+2) << "\"nombre\": \"" << nodo->nombre << "\",\n";
    file << tabs(tab+2) << "\"tipo\": \""
         << (nodo->tipo == NodeType::CARPETA ? "carpeta" : "archivo")
         << "\",\n";
    file << tabs(tab+2) << "\"contenido\": \"" << nodo->contenido << "\",\n";

    file << tabs(tab+2) << "\"children\": [";
    if (!nodo->children.empty()) file << "\n";

    for (size_t i = 0; i < nodo->children.size(); i++) {
        file << tabs(tab+4);
        escribirNodo(file, nodo->children[i], tab+4);
        if (i < nodo->children.size() - 1) file << ",";
        file << "\n";
    }

    file << tabs(tab+2) << "]";
    file << "\n" << tabs(tab) << "}";
}

bool JSONManager::cargar(const std::string& filename, Tree& tree) {
    std::ifstream file(filename);
    if (!file) return false;

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    size_t pos = text.find("\"root\"");
    if (pos == std::string::npos) return false;

    pos = text.find("{", pos);
    if (pos == std::string::npos) return false;

    std::string obj = text.substr(pos);

    std::istringstream in(obj);
    Node* newRoot = leerNodo(in);

    if (!newRoot) return false;

    tree.setRoot(newRoot);
    return true;
}

Node* JSONManager::leerNodo(std::istream& in) {
    std::string token;
    in >> token; // "{"
    if (token != "{") return nullptr;

    int id;
    std::string nombre, tipoStr, contenido;

    in >> token; // "id":
    in >> id;
    in >> token; // ,

    in >> token; // "nombre":
    std::getline(in, token, '"');
    std::getline(in, nombre, '"');
    in >> token; // ,

    in >> token; // "tipo":
    std::getline(in, token, '"');
    std::getline(in, tipoStr, '"');
    in >> token; // ,

    in >> token; // "contenido":
    std::getline(in, token, '"');
    std::getline(in, contenido, '"');
    in >> token; // ,

    in >> token; // "children":
    in >> token; // [

    Node* nodo = new Node(id, nombre, tipoStr == "carpeta" ? NodeType::CARPETA : NodeType::ARCHIVO);
    nodo->contenido = contenido;

    while (true) {
        in >> token;
        if (token == "]") break;

        if (token == "{") {
            in.putback('{');
            Node* child = leerNodo(in);
            nodo->addChild(child);

            in >> token; // coma o ]
        }
    }

    in >> token; // "}"

    return nodo;
}
