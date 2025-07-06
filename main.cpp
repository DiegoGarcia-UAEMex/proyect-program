#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <conio.h>
using namespace std;

//Variables
struct Producto
    {
        int id;
        string nombre;
        float precio;
    };

#define ENTER 13
#define ESC 27
#define UP_ARROW 72
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define DOWN_ARROW 80
#define DELETE 8

// Productos
vector<Producto> Productos[] = {
    {
        {1,"Manzana", 0.5},
        {2,"Banana", 0.3},
        {3,"Naranja", 0.4},
        {4,"Fresa", 0.6},
        {5,"Uva", 0.8}
    },
    {
        {1,"Zanahoria", 0.2},
        {2,"Brócoli", 0.7},
        {3,"Espinaca", 0.5},
        {4,"Lechuga", 0.4},
        {5,"Pepino", 0.3}
    },
    {
        {1, "Lentejas", 0.9},
        {2, "Arroz", 0.6},
        {3, "Frijoles", 0.8},
        {4, "Garbanzos", 1.0},
        {5, "Quinoa", 1.2}
    },
    {
        {1, "Pollo", 2.5},
        {2, "Carne de res", 3.0},
        {3, "Pescado", 4.0},
        {4, "Cerdo", 2.8},
        {5, "Pavo", 3.5}
    },
    {
        {1, "Leche", 1.0},
        {2, "Yogur", 0.8},
        {3, "Queso", 1.5},
        {4, "Mantequilla", 1.2},
        {5, "Helado", 2.0}
    }
};
string nombreProductos[]={"Frutas", "Verduras", "Legumbres", "Carnes", "Lacteos"};

// Funciones para navegar por los Productos
void siguiente(int &i) {
    if(i < 4) {
        i++;
    } else {
        i = 0;
    }
    
}

void anterior(int &i){
    if(i > 0) {
        i--;
    } else {
        i = 4;
    }
}


// Función para mostrar los Productos disponibles
void mover(int &i, int &j, vector<Producto> productos[], void (*direction)(int &i), int input) {
    if(input == UP_ARROW || input == DOWN_ARROW) {
        direction(i);
        cout << nombreProductos[i] << endl;
    } else if (input == LEFT_ARROW || input == RIGHT_ARROW) {
        direction(j);
    }
    cout << "- " << Productos[i][j].id << " " << Productos[i][j].nombre << " ($" << Productos[i][j].precio << ")" << endl;
}

int main() {
    double sumaTotal=0;

    // mensaje de bienvenida
    cout << "Bienvenido al sistema de compra de Productos." << endl;
    int i = 0;
    int j = 0;
    cout << "Usa las flechas arriba y abajo para cambiar de categoria, las flechas izquierda y derecha para cambiar de producto en una misma categoria, Enter para seleccionar, Borrar para quitar la selección, ESC para salir:" << endl;
    cout << nombreProductos[i] << endl;
    cout << "- " << Productos[i][j].id << " " << Productos[i][j].nombre << " ($" << Productos[i][j].precio << ")" << endl;
    
    //Inicia la navegación por los Productos
    while(true){
        int input = _getch();
        switch (input) {
            case ENTER:
                if(Productos[i][j].precio >= 0){
                    sumaTotal += Productos[i][j].precio;
                    cout << "Monto actual: $" << sumaTotal << endl;
                }
                break;
            case DELETE:
                if(sumaTotal > 0) {
                    sumaTotal -= Productos[i][j].precio;
                    cout << "Monto actual: $" << sumaTotal << endl;
                } else {
                    cout << "No hay monto para eliminar." << endl;
                }
                break;
            case ESC:
            case 3:
                cout << "Gracias por usar el sistema de compra de Productos." << endl;
                cout << "Total a pagar: $" << sumaTotal << endl;
                return 0;
            case RIGHT_ARROW:
               mover(i, j, Productos, siguiente, input);
                break;
            case DOWN_ARROW:
                mover(i, j, Productos, siguiente, input);
                break;
            case LEFT_ARROW:
                mover(i, j, Productos, anterior, input);
                break;
            case UP_ARROW:
                mover(i, j, Productos, anterior, input);
                break;
        }
    }
    return 0;
}