#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <conio.h>
#include <windows.h>
using namespace std;

//Variables
struct Producto
    {
        int id;
        string nombre;
        float precio;
    };

//Teclas
#define ENTER 13
#define ESC 27
#define UP_ARROW 72
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define DOWN_ARROW 80
#define DELETEKEY 8

//Colores
#define DARK_BLUE 31
//#define DARK_GREEN_BLACK 32
#define RED 64
#define YELLOW 224
#define LIGHT_GRAY_BLACK 112
//#define LIGHT_GRAY_GREEN 112
//#define DARK_GRAY 128
#define GREEN_BLACK 160
#define LIGHT_GREEN 176
#define WHITE 240
#define NORMAL 7  // Color normal (blanco sobre negro)

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

struct Menu {
	string categoria;
	int pos_X;	
};

// Estructura para el menú
struct Menu menu[] = {
    {"Frutas", 6},
    {"Verduras", 15},
    {"Legumbres", 25},
    {"Carnes", 32},
    {"Lacteos", 40}
};

// Función para limpiar color de fondo en un área rectangular
void clearBackgroundArea(int x0, int y0, int x1, int y1) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    
    int width = x1 - x0 + 1;
    
    // Limpiar cada fila restaurando color normal
    for(int y = y0; y <= y1; y++) {
        COORD coord = {x0, y};
        FillConsoleOutputAttribute(handle, NORMAL, width, coord, &written);
    }
}
// Función para establecer color de fondo sin mover el cursor
void setBackgroundAt(int x, int y, int width, int backgroundColor) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    DWORD written;
    
    // Solo cambia el color de fondo, no mueve el cursor
    FillConsoleOutputAttribute(handle, backgroundColor, width, coord, &written);
}
// Funciones para navegar por los Productos
void siguiente(int &i) {
    if(i < 4) {
        i++;
    } else {
        i = 0;
        clearBackgroundArea(0, 3, 40, 3);
    }
    
}

void anterior(int &i){
    if(i > 0) {
        i--;
    } else {
        i=Productos[i].size() - 1;
        clearBackgroundArea(0, 3, 6, 3);
    }
}


// Función para mostrar los Productos disponibles
void mover(int &i, int &j, vector<Producto> productos[], void (*direction)(int &i), int input) {
    if(input == UP_ARROW || input == DOWN_ARROW) {
        direction(i);
        j = 0; // Reset product index when changing category
    } else if (input == LEFT_ARROW || input == RIGHT_ARROW) {
        direction(j);
    }
    cout << "- " << Productos[i][j].id << " " << Productos[i][j].nombre << " ($" << Productos[i][j].precio << ")" << endl;
}
// Función para mover el cursor a una posición específica en la consola
void gotoxy(int x, int y, int width, int backgroundColor = LIGHT_GRAY_BLACK) {
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    DWORD written;
    // Fill with background color
    FillConsoleOutputAttribute(handle, backgroundColor, width, coord, &written);
    SetConsoleCursorPosition(handle, coord);
}

void mostrarProducto(int i, int j, vector<Producto> productos[]) {
    gotoxy(0, 0,0);
}

void mostrarEnColumna(int x, int y, string categoria) {
    cout << categoria << " ";
}

// Función para obtener la posición actual del cursor
COORD getCurrentCursorPosition() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(handle, &csbi);
    return csbi.dwCursorPosition;
}

// Función para obtener solo la coordenada Y del cursor
int getCurrentCursorY() {
    COORD pos = getCurrentCursorPosition();
    return pos.Y;
}


int main() {
    double sumaTotal=0;
    int yESC=2;
    int y=3;
    system("cls");
    // mensaje de bienvenida
    cout << "Bienvenido al sistema de compra de Productos." << endl;
    int i = 0;
    int j = 0;
    cout << "Usa las flechas arriba y abajo para cambiar de categoria, las flechas izquierda y derecha para cambiar de producto en una misma categoria, Enter para seleccionar, Borrar para quitar la selección, ESC para salir:" << endl;
    for(int k = 0; k < 5; k++) {
        mostrarEnColumna(menu[k].pos_X, 4, menu[k].categoria);
    }
    cout << endl;
    cout << "- " << Productos[i][j].id << " " << Productos[i][j].nombre << " ($" << Productos[i][j].precio << ")" << endl;
    setBackgroundAt(0, 3, menu[i].pos_X, LIGHT_GRAY_BLACK);
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
            case DELETEKEY:
                if(sumaTotal > 0) {
                    sumaTotal -= Productos[i][j].precio;
                    cout << "Monto actual: $" << sumaTotal << endl;
                } else {
                    cout << "No hay monto para eliminar." << endl;
                }
                break;
            case ESC:
            case 3:
                clearBackgroundArea(0, getCurrentCursorY()-yESC, menu[i].pos_X, getCurrentCursorY()-yESC);
                cout << "Gracias por usar el sistema de compra de Productos." << endl;
                cout << "Total a pagar: $" << sumaTotal << endl;
                return 0;
            case RIGHT_ARROW:
               mover(i, j, Productos, siguiente, input);
                break;
            case DOWN_ARROW:
                mover(i, j, Productos, siguiente, input);
                setBackgroundAt(0, 3, menu[i].pos_X, LIGHT_GRAY_BLACK);
                clearBackgroundArea(0, getCurrentCursorY()-y, menu[i-1].pos_X, getCurrentCursorY()-y);
                y++;
                yESC++;
                break;
            case LEFT_ARROW:
                mover(i, j, Productos, anterior, input);
                break;
            case UP_ARROW:
                mover(i, j, Productos, anterior, input);
                setBackgroundAt(menu[i-1].pos_X+1, 3, menu[i].pos_X, LIGHT_GRAY_BLACK);
                clearBackgroundArea(menu[i].pos_X, getCurrentCursorY()-y, menu[5].pos_X, getCurrentCursorY()-y);
                y++;
                yESC++;
                break;
        }
    }
    return 0;
}