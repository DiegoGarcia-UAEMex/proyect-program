#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <conio.h>
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
void sumarPrecio(float precio) {
    if(precio >= 0){
        sumaTotal += precio;
        cout << "Monto actual: $" << sumaTotal << endl;
    }
}
#define ENTER 13
#define ESC 27
#define UP_ARROW 72
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define DOWN_ARROW 80
char tipoDeProducto;

void moverAdelante(int &i, const vector<Producto>& productos) {
    if(i < productos.size() - 1) {
        i++;
    } else {
        cout << "You are in the end of the array." << endl;
    }
    cout << "- " << productos[i].id << " " << productos[i].nombre << " ($" << productos[i].precio << ")" << endl;
}

int moverAtras(int i, const vector<Producto>& productos){
    if(i > 0) {
        i--;
    } else {
        cout << "You are in the start of the array" << endl;
    }
    cout << "- " << productos[i].id << " " << productos[i].nombre << " ($" << productos[i].precio << ")" << endl;
    return i;
}
    
// Función para mostrar los productos disponibles
void mostrarProductos(const vector<Producto>& productos) {
    int i = 0;
    cout << "Usa las flechas para navegar, Enter para seleccionar, ESC para salir:" << endl;
    cout << "- " << productos[i].id << " " << productos[i].nombre << " ($" << productos[i].precio << ")" << endl;
    
    while(true){
        int input = _getch(); // Get a character from the console without echoing it
        switch (input) {
            case ENTER:
                sumarPrecio(productos[i].precio);
                return; // Salir de la función
            case ESC:
            case 3:
                cout << "exiting..." << endl;
                return; // Salir de la función
            case DOWN_ARROW:
            case RIGHT_ARROW:
                moverAdelante(i, productos);
                break;
            
            case UP_ARROW:
            case LEFT_ARROW:
                i = moverAtras(i, productos);
                break;
        }
    }
}

int main() {
    cout << "Bienvenido al sistema de compra de productos." << endl;
    while (true)
    {
        char tipoDeProducto;
        cout << "Que tipo de productos desea ver (F para frutas, V para verduras): ";
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
        cout << "\nPresione cualquier tecla para continuar, ESC o Ctrl-C para salir: \n";
        int opc=_getch();
        if (opc == 3|| opc == ESC) {
            cout << "Gracias por usar el sistema. Total a pagar: $" << sumaTotal << endl;
            return 0; // Salir del bucle y finalizar el programa
        }
    }
    
    return 0;
}