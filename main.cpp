#include <iostream>
#include "tree.h"
#include "json_manager.h"

using namespace std;

int main() {
    Tree tree;

    // árbol inicial
    Node* root = new Node(1, "root", NodeType::CARPETA);
    tree.setRoot(root);

    int op;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Agregar nodo\n";
        cout << "2. Guardar JSON\n";
        cout << "3. Cargar JSON\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        if (op == 1) {
            int idPadre, id;
            string nombre;
            int tipoInt;

            cout << "ID del padre: ";
            cin >> idPadre;

            Node* padre = tree.buscarPorID(tree.getRoot(), idPadre);
            if (!padre) {
                cout << "Padre no encontrado\n";
                continue;
            }

            cout << "Nuevo ID: ";
            cin >> id;
            cout << "Nombre: ";
            cin >> nombre;
            cout << "Tipo (0 carpeta / 1 archivo): ";
            cin >> tipoInt;

            NodeType t = (tipoInt == 0) ? NodeType::CARPETA : NodeType::ARCHIVO;

            padre->addChild(new Node(id, nombre, t));

            cout << "Nodo creado.\n";
        }

        else if (op == 2) {
            if (JSONManager::guardar("arbol.json", tree))
                cout << "Guardado correctamente.\n";
            else
                cout << "ERROR al guardar.\n";
        }

        else if (op == 3) {
            if (JSONManager::cargar("arbol.json", tree))
                cout << "Cargado correctamente.\n";
            else
                cout << "ERROR al cargar.\n";
        }

    } while (op != 0);

    return 0;
}
