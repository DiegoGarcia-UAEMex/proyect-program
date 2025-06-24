#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Producto
    {
        string nombre;
        float precio;
    };
    
// Función para mostrar los productos disponibles
void mostrarProductos(const vector<Producto>& Productos) {
    for (const auto& Producto : Productos) {
        cout << "- " << Producto.nombre << " ($" << Producto.precio << ")" << endl;
    }
}


int main() {
    char opc;

    vector<Producto> Frutas = {
        {"Manzana", 0.5},
        {"Banana", 0.3},
        {"Naranja", 0.4},
        {"Fresa", 0.6},
        {"Uva", 0.8}
    };
    vector<Producto> Verduras = {
        {"Zanahoria", 0.2},
        {"Brócoli", 0.7},
        {"Espinaca", 0.5},
        {"Lechuga", 0.4},
        {"Pepino", 0.3}
    };
    do {
        char producto;
        cout << "Ingrese el tipo de producto (F para frutas, V para verduras): ";
        cin>>producto;
        producto=toupper(producto);
        switch (producto) {
            case 'F':
                cout << "Frutas disponibles:\n";
                mostrarProductos(Frutas);
                break;
            case 'V':
                cout << "Verduras disponibles:\n";
                mostrarProductos(Verduras);
                break;
            default:
                cout << "Opción no válida. Por favor, ingrese 'F' para frutas o 'V' para verduras." << endl;
        }
        cout << "¿Desea ver más productos? (S para continuar, cualquier otra tecla para salir): ";
        cin >> opc;
        opc = toupper(opc); // Convertir a mayúscula para evitar problemas con minúsculas
        if (opc != 'S'|| !opc) {
            cout << "Saliendo del programa." << endl;
            return 0;
        }
} while (opc=='S');
    
}