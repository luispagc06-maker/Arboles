#include <iostream>
#include "tree.h"
#include "JSONManager.h"

int main() {
    Tree arbol;

    int opcion;
    do {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Insertar\n";
        std::cout << "2. Mostrar\n";
        std::cout << "3. Buscar\n";
        std::cout << "4. Eliminar\n";
        std::cout << "5. Guardar JSON\n";
        std::cout << "6. Cargar JSON\n";
        std::cout << "0. Salir\n> ";
        std::cin >> opcion;

        if (opcion == 1) {
            int id; std::string nombre;
            std::cout << "ID: "; std::cin >> id;
            std::cout << "Nombre: "; std::cin >> nombre;
            arbol.insertar(id, nombre);
        }
        else if (opcion == 2) {
            arbol.mostrar();
        }
        else if (opcion == 3) {
            int id;
            std::cout << "ID a buscar: ";
            std::cin >> id;
            Node* n = arbol.buscar(id);
            if (n) std::cout << "Encontrado: " << n->nombre << "\n";
            else std::cout << "No existe.\n";
        }
        else if (opcion == 4) {
            int id;
            std::cout << "ID a eliminar: ";
            std::cin >> id;
            arbol.eliminar(id);
        }
        else if (opcion == 5) {
            if (JSONManager::guardar("arbol.json", arbol.exportar()))
                std::cout << "Guardado correctamente.\n";
            else
                std::cout << "Error guardando JSON.\n";
        }
        else if (opcion == 6) {
            auto datos = JSONManager::cargar("arbol.json");
            arbol.importar(datos);
            std::cout << "Cargado correctamente.\n";
        }

    } while (opcion != 0);

    return 0;
}
