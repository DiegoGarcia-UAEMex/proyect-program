#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;
double sumaTotal=0;
struct Producto
    {
        int id;
        string nombre;
        float precio;
    };
// Listas de productos
vector<Producto> Frutas = {
        {1,"Manzana", 0.5},
        {2,"Banana", 0.3},
        {3,"Naranja", 0.4},
        {4,"Fresa", 0.6},
        {5,"Uva", 0.8}
    };
vector<Producto> Verduras = {
    {1,"Zanahoria", 0.2},
    {2,"Brócoli", 0.7},
    {3,"Espinaca", 0.5},
    {4,"Lechuga", 0.4},
    {5,"Pepino", 0.3}
};

char tipoDeProducto;
    
// Función para mostrar los productos disponibles
void mostrarProductos(const vector<Producto>& Productos) {
    for (const auto& Producto : Productos) {
        cout << "- " << Producto.id << " " << Producto.nombre << " ($" << Producto.precio << ")" << endl;
    }
}

void listarProductos() {
    char opc;
    do {
        char tipoDeProducto;
        cout << "Ingrese el tipo de producto (F para frutas, V para verduras): ";
        cin>>tipoDeProducto;
        tipoDeProducto=toupper(tipoDeProducto);
        switch (tipoDeProducto) {
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
        cout << "¿Desea ver más productos? (S para salir, cualquier otra tecla para continuar): ";
        cin >> opc;
        opc = toupper(opc);
    } while (opc!='S');
}

float buscarProducto(const vector<Producto>& Productos, const int& id) {
    int mitadProductos = ceil(Productos.size() / 2.0) - 1;
    int i=mitadProductos;
    for(int j=0; j<Productos.size(); j++) {
        if (Productos[i].id == id) {
            cout << "Producto encontrado: " << Productos[i].nombre << " - $" << Productos[i].precio << endl;
            return Productos[i].precio;
        }
        if (Productos[i].id < id) {
            i++;
        } else {
            i--;
        }
        if (i < 0 || i >= Productos.size()) {
            break; // Evitar desbordamiento de índice
        }
    
    }
    cout << "Producto no encontrado." << endl;
    return 0.0;
}

void realizarCompra(const vector<Producto>& Productos) {
    char continuar;
    // cout << "Productos disponibles para comprar:" << endl;
    // mostrarProductos(Productos);
    do {
        int id;
        cout << "Ingrese el ID del producto que desea comprar: ";
        cin >> id;
        if(cin.fail() || id < 1 || id > Productos.size()) {
            cout << "ID no válido. Por favor, ingrese un ID entre 1 y " << Productos.size() << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        float precio = buscarProducto(Productos, id);
        if (precio > 0) {
            sumaTotal += precio;
            cout << "Producto agregado al carrito. Total actual: $" << sumaTotal << endl;
        }
        cout << "¿Desea agregar otro producto? (S para salir, cualquier otra tecla para continuar): ";
        cin >> continuar;
    } while (toupper(continuar) != 'S');
}

int main() {
    cout << "Bienvenido al sistema de compra de productos." << endl;
    char opc;
    do {
        cout << "Que desea hacer? 1. Ver productos disponibles 2. Realizar una compra" << endl;
        int opcion;
        cin >> opcion;
        if(cin.fail() || (opcion != 1 && opcion != 2)) {
            cout << "Opción no válida. Por favor, ingrese 1 o 2." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Volver a solicitar la opción
        }
        switch (opcion) {
            case 1:
                listarProductos();
                break;
            case 2:
                cout << "Seleccione el tipo de producto para comprar (F para frutas, V para verduras): ";
                cin >> tipoDeProducto;
                tipoDeProducto = toupper(tipoDeProducto);
                switch (tipoDeProducto) {
                    case 'F':
                        realizarCompra(Frutas);
                        break;
                    case 'V':
                        realizarCompra(Verduras);
                        break;
                    default:
                        cout << "Opción no válida. Por favor, ingrese 'F' para frutas o 'V' para verduras." << endl;
                        break;
                }
                break;
            default:
                cout << "Opción no válida. Por favor, ingrese 1, 2 o 3." << endl;
                break;
        }
        cout << "¿Desea realizar otra operación? cualquier tecla para continuar, 3. salir: ";
        cin >> opc;
    } while (opc != '3');
    return 0;
}