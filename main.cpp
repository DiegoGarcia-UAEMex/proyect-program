#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <conio.h>
using namespace std;
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
// Listas de Productos


void siguiente(int &i) {
    if(i < 4) {
        i++;
    } else {
        cout << "You are in the end of the array." << endl;
    }
    
}

void anterior(int &i){
    if(i > 0) {
        i--;
    } else {
        cout << "You are in the start of the array" << endl;
    }
}
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
// Función para mostrar los Productos disponibles
void mover(int &i, int &j, vector<Producto> productos[], void (*direction)(int &i), int input) {
    if(input == UP_ARROW || input == DOWN_ARROW) {

        direction(i);
        cout << "nivel: " << i+1 << endl;
    } else if (input == LEFT_ARROW || input == RIGHT_ARROW) {
        direction(j);
    }
    cout << "- " << Productos[i][j].id << " " << Productos[i][j].nombre << " ($" << Productos[i][j].precio << ")" << endl;
}

int main() {
    double sumaTotal=0;
    cout << "Bienvenido al sistema de compra de Productos." << endl;
    int i = 0;
    int j = 0;
    cout << "Usa las flechas para navegar, Enter para seleccionar, ESC para salir:" << endl;
    cout << "- " << Productos[i][j].id << " " << Productos[i][j].nombre << " ($" << Productos[i][j].precio << ")" << endl;
    
    while(true){
        int input = _getch(); // Get a character from the console without echoing it
        switch (input) {
            case ENTER:
                if(Productos[i][j].precio >= 0){
                    sumaTotal += Productos[i][j].precio;
                    cout << "Monto actual: $" << sumaTotal << endl;
                }
                break;
            case ESC:
            case 3:
                cout << "Gracias por usar el sistema de compra de Productos." << endl;
                cout << "Total a pagar: $" << sumaTotal << endl;
                return 0; // Salir de la función
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