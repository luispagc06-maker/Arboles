#include <iostream>
#include <sstream>
#include <vector>

#include "tree.h"
#include "trie.h"
#include "json_manager.h"
#include "search_index.h"

void mostrarHelp()
{
    std::cout << "\n=== AYUDA DEL SISTEMA ===\n";
    std::cout << "help                     - Mostrar esta ayuda\n";
    std::cout << "mkdir <nombre>           - Crear una carpeta\n";
    std::cout << "touch <nombre>           - Crear un archivo\n";
    std::cout << "ls                       - Listar contenido del directorio actual\n";
    std::cout << "cd <carpeta>             - Entrar a una carpeta\n";
    std::cout << "rm <id>                  - Eliminar nodo por ID\n";
    std::cout << "rename <id> <nuevo>      - Renombrar nodo\n";
    std::cout << "preorden                 - Mostrar el árbol completo\n";
    std::cout << "search <prefijo>         - Autocompletar nombres\n";
    std::cout << "save                     - Guardar árbol en JSON\n";
    std::cout << "exit                     - Salir del programa\n";
    std::cout << "=========================\n\n";
}

int main()
{
    Tree tree;
    Trie trie;
    SearchIndex index;

    Node* actual = tree.getRoot();
    std::string linea;

    std::cout << "=== SISTEMA DE ARCHIVOS (DIA 14) ===\n";
    std::cout << "Escribe 'help' para ver los comandos disponibles.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, linea);

        std::stringstream ss(linea);
        std::string cmd;
        ss >> cmd;

        if (cmd == "exit") {
            break;
        }

        else if (cmd == "help") {
            mostrarHelp();
        }

        else if (cmd == "mkdir") {
            std::string nombre;
            ss >> nombre;
            if (nombre == "") {
                std::cout << "Uso: mkdir <nombre>\n";
                continue;
            }
            Node* n = tree.mkdir(actual, nombre);
            trie.insertar(nombre);
            index.add(nombre, n->id);
        }

        else if (cmd == "touch") {
            std::string nombre;
            ss >> nombre;
            if (nombre == "") {
                std::cout << "Uso: touch <nombre>\n";
                continue;
            }
            Node* n = tree.touch(actual, nombre);
            trie.insertar(nombre);
            index.add(nombre, n->id);
        }

        else if (cmd == "ls") {
            for (size_t i = 0; i < actual->children.size(); i++) {
                Node* n = actual->children[i];
                std::cout << n->id << " - " << n->nombre;
                if (n->tipo == CARPETA) std::cout << " [DIR]";
                std::cout << std::endl;
            }
        }

        else if (cmd == "cd") {
            std::string nombre;
            ss >> nombre;
            bool encontrado = false;

            if (nombre == "..") {
                if (actual->parent)
                    actual = actual->parent;
                continue;
            }

            for (size_t i = 0; i < actual->children.size(); i++) {
                if (actual->children[i]->nombre == nombre &&
                    actual->children[i]->tipo == CARPETA) {
                    actual = actual->children[i];
                    encontrado = true;
                    break;
                }
            }

            if (!encontrado)
                std::cout << "Carpeta no encontrada\n";
        }

        else if (cmd == "rm") {
            int id;
            ss >> id;
            Node* n = tree.findById(tree.getRoot(), id);
            if (!n) {
                std::cout << "ID no encontrado\n";
                continue;
            }
            index.remove(n->nombre);
            tree.remove(n);
        }

        else if (cmd == "rename") {
            int id;
            std::string nuevo;
            ss >> id >> nuevo;

            Node* n = tree.findById(tree.getRoot(), id);
            if (!n) {
                std::cout << "ID no encontrado\n";
                continue;
            }
            index.remove(n->nombre);
            tree.rename(n, nuevo);
            index.add(nuevo, id);
            trie.insertar(nuevo);
        }

        else if (cmd == "preorden") {
            tree.preorden(tree.getRoot(), 0);
        }

        else if (cmd == "search") {
            std::string pref;
            ss >> pref;
            std::vector<std::string> r = trie.autocompletar(pref);
            if (r.empty()) {
                std::cout << "Sin coincidencias\n";
            }
            for (size_t i = 0; i < r.size(); i++)
                std::cout << r[i] << std::endl;
        }

        else if (cmd == "save") {
            JSONManager::guardar("arbol.json", tree);
            std::cout << "Árbol guardado en arbol.json\n";
        }

        else {
            std::cout << "Comando desconocido. Escribe 'help'.\n";
        }
    }

    return 0;
}
