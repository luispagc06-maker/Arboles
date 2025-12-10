#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "tree.h"
#include "json_manager.h"
#include "search_index.h"

using namespace std;

void help() {
    cout << "Comandos disponibles:\n";
    cout << "  mkdir <ruta> <nombre>       - crear carpeta dentro de ruta\n";
    cout << "  touch <ruta> <nombre>       - crear archivo dentro de ruta\n";
    cout << "  ls <ruta>                   - listar hijos\n";
    cout << "  pwd <ruta>                  - mostrar ruta completa del nodo\n";
    cout << "  mv <ruta_origen> <ruta_dest>- mover nodo (dest es carpeta)\n";
    cout << "  rm <ruta>                   - mover nodo a papelera /.trash\n";
    cout << "  restore <id> <ruta_dest>    - restaurar desde papelera por id a ruta_dest\n";
    cout << "  purge <ruta>                - eliminar definitivamente (cuidado)\n";
    cout << "  search <prefijo>            - autocompletar nombres\n";
    cout << "  find <nombre>               - búsqueda exacta por nombre\n";
    cout << "  export_preorder <archivo>   - exportar recorrido preorden (JSON)\n";
    cout << "  save <archivo>              - guardar árbol en JSON\n";
    cout << "  load <archivo>              - cargar árbol desde JSON\n";
    cout << "  help                        - esta ayuda\n";
    cout << "  exit                        - salir\n";
}

int main() {
    Tree tree;
    SearchIndex index;
    index.build(tree.getRoot());

    cout << "Proyecto Arbol - Dias 7-9 (arbol general). Escribe 'help' para ver comandos.\n";

    string line;
    while (true) {
        cout << "> ";
        if (!std::getline(cin, line)) break;
        if (line.empty()) continue;

        // parse command and args
        std::istringstream iss(line);
        string cmd;
        iss >> cmd;
        if (cmd == "exit") break;
        if (cmd == "help") { help(); continue; }

        if (cmd == "mkdir" || cmd == "touch") {
            string ruta, nombre;
            iss >> ruta >> ws;
            std::getline(iss, nombre);
            if (nombre.empty()) { cout << "Uso: " << cmd << " <ruta> <nombre>\n"; continue; }
            // trim possible leading spaces
            if (nombre.size()>0 && nombre[0]==' ') nombre = nombre.substr(1);

            bool ok = tree.insertNode(ruta, nombre, (cmd=="mkdir"?NodeType::CARPETA:NodeType::ARCHIVO));
            if (!ok) cout << "Error: no se pudo crear (ruta inválida o nombre duplicado).\n";
            else {
                index.build(tree.getRoot());
                cout << "Creado.\n";
            }
            continue;
        }

        if (cmd == "ls") {
            string ruta; iss >> ruta;
            if (ruta.empty()) ruta = "/";
            auto hijos = tree.listChildren(ruta);
            if (hijos.empty()) { cout << "(vacío)\n"; continue; }
            for (Node* c : hijos)
                cout << (c->tipo==NodeType::CARPETA? "[DIR] ":"[FIL] ") << c->nombre << " (id=" << c->id << ")\n";
            continue;
        }

        if (cmd == "pwd") {
            string ruta; iss >> ruta;
            Node* n = tree.findByPath(ruta);
            if (!n) { cout << "Ruta no encontrada.\n"; continue; }
            cout << tree.getFullPath(n) << "\n";
            continue;
        }

        if (cmd == "mv") {
            string origen, destino; iss >> origen >> destino;
            if (origen.empty() || destino.empty()) { cout << "Uso: mv <origen> <destino>\n"; continue; }
            bool ok = tree.moveNode(origen, destino);
            if (!ok) cout << "Error: no se pudo mover (verificar rutas y tipos).\n";
            else { index.build(tree.getRoot()); cout << "Movido.\n"; }
            continue;
        }

        if (cmd == "rm") {
            string ruta; iss >> ruta;
            if (ruta.empty()) { cout << "Uso: rm <ruta>\n"; continue; }
            bool ok = tree.removeToTrash(ruta);
            if (!ok) cout << "Error: no se pudo mover a papelera.\n";
            else { index.build(tree.getRoot()); cout << "Movido a /.trash\n"; }
            continue;
        }

        if (cmd == "restore") {
            int id; string destino; iss >> id >> destino;
            if (!id || destino.empty()) { cout << "Uso: restore <id> <ruta_dest>\n"; continue; }
            bool ok = tree.restoreFromTrash(id, destino);
            if (!ok) cout << "Error: no se pudo restaurar (id o ruta inválida).\n";
            else { index.build(tree.getRoot()); cout << "Restaurado.\n"; }
            continue;
        }

        if (cmd == "purge" || cmd == "permadelete") {
            string ruta; iss >> ruta;
            if (ruta.empty()) { cout << "Uso: purge <ruta>\n"; continue; }
            bool ok = tree.permanentDelete(ruta);
            if (!ok) cout << "Error: no se pudo eliminar.\n";
            else { index.build(tree.getRoot()); cout << "Eliminado definitivamente.\n"; }
            continue;
        }

        if (cmd == "search") {
            string pref; iss >> pref;
            if (pref.empty()) { cout << "Uso: search <prefijo>\n"; continue; }
            auto suggestions = index.autocomplete(pref);
            if (suggestions.empty()) cout << "(sin coincidencias)\n";
            else {
                for (auto &s : suggestions) cout << "- " << s << "\n";
            }
            continue;
        }

        if (cmd == "find") {
            string name; iss >> name;
            if (name.empty()) { cout << "Uso: find <nombre>\n"; continue; }
            Node* n = index.findExact(name);
            if (!n) cout << "No encontrado.\n";
            else cout << "Encontrado: " << name << " (id=" << n->id << "), ruta=" << tree.getFullPath(n) << "\n";
            continue;
        }

        if (cmd == "export_preorder") {
            string file; iss >> file;
            if (file.empty()) { cout << "Uso: export_preorder <archivo>\n"; continue; }
            auto nodes = tree.preorder();
            // guardamos simple JSON array con objetos mínimos (id,nombre,tipo)
            std::ofstream out(file);
            if (!out.is_open()) { cout << "Error abriendo archivo.\n"; continue; }
            out << "[\n";
            for (size_t i=0;i<nodes.size();++i) {
                Node* n = nodes[i];
                out << "  {\"id\":" << n->id << ",\"nombre\":\"" << n->nombre
                    << "\",\"tipo\":\"" << (n->tipo==NodeType::CARPETA?"carpeta":"archivo") << "\"}";
                if (i+1<nodes.size()) out << ",\n"; else out << "\n";
            }
            out << "]\n";
            out.close();
            cout << "Exportado a " << file << "\n";
            continue;
        }

        if (cmd == "save") {
            string filename; iss >> filename;
            if (filename.empty()) filename = "arbol.json";
            bool ok = JSONManager::save(filename, tree);
            cout << (ok ? "Guardado.\n" : "Error guardando.\n");
            continue;
        }

        if (cmd == "load") {
            string filename; iss >> filename;
            if (filename.empty()) filename = "arbol.json";
            bool ok = JSONManager::load(filename, tree);
            if (ok) {
                index.build(tree.getRoot());
                cout << "Cargado.\n";
            } else cout << "Error cargando.\n";
            continue;
        }

        cout << "Comando desconocido. Escribe 'help' para ver comandos.\n";
    }

    cout << "Saliendo...\n";
    return 0;
}
