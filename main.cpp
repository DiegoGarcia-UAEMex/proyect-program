#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <thread>
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

void delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// Función para borrar texto y color en un área rectangular
void clearLineAndPosition(int y) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(handle, &csbi);
    
    COORD coord = {0, y};
    DWORD written;
    
    // Borrar toda la línea
    FillConsoleOutputCharacter(handle, ' ', csbi.dwSize.X, coord, &written);
    // Restaurar color normal
    FillConsoleOutputAttribute(handle, NORMAL, csbi.dwSize.X, coord, &written);
    // Posicionar el cursor al inicio de la línea borrada
    SetConsoleCursorPosition(handle, coord);
}

// Función alternativa para borrar solo una línea completa
void clearLine(int y) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(handle, &csbi);
    
    COORD coord = {0, y};
    DWORD written;
    
    // Borrar toda la línea
    FillConsoleOutputCharacter(handle, ' ', csbi.dwSize.X, coord, &written);
}
// Función para borrar un área rectangular de texto y restaurar el color normal
void clearTextAreaAndPosition(int y0, int y1) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    
    // Borrar cada fila del área especificada
    for(int y = y0; y <= y1; y++) {
        COORD coord = {0, y};
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(handle, &csbi);
        // Llenar con espacios en blanco para borrar el texto
        FillConsoleOutputCharacter(handle, ' ', csbi.dwSize.X, coord, &written);
        // Restaurar el color normal
        FillConsoleOutputAttribute(handle, NORMAL, csbi.dwSize.X, coord, &written);
    }
    
    // Posicionar el cursor al inicio del área borrada
    COORD newPos = {0, y0};
    SetConsoleCursorPosition(handle, newPos);
}
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
    }
    
}

void anterior(int &i){
    if(i > 0) {
        i--;
    } else {
        i=Productos[i].size() - 1;
    }
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

// Función para mostrar los Productos disponibles
void mover(int &i, int &j, vector<Producto> productos[], void (*direction)(int &i), int input) {
    if(input == UP_ARROW || input == DOWN_ARROW) {
        direction(j);
        if(j==0){
            //clearBackgroundArea(0, 4, 40, 4);
            clearBackgroundArea(0, 4, 40, getCurrentCursorY()-1);
        }
        if(j==Productos[i].size()-1){
            clearBackgroundArea(0, 4, 40, getCurrentCursorY()-1);
        }
        setBackgroundAt(4, j+4, Productos[i][j].nombre.size(), YELLOW);
    } else if (input == LEFT_ARROW || input == RIGHT_ARROW) {
        direction(i);
        if(i==0){
            clearBackgroundArea(0, 3, 40, 3);
        }
        if(i==Productos[i].size()-1){
            clearBackgroundArea(0, 3, 6, 3);
        }
        clearTextAreaAndPosition(4,getCurrentCursorY()-1);
        j = 0; // Reset product index when changing category
        for(int k = 0; k < 5; k++) {
            cout <<"- "<< productos[i][k].id << " " << productos[i][k].nombre << " ($" << productos[i][k].precio << ")\n";
        }
        setBackgroundAt(4, 4, Productos[i][j].nombre.size(), YELLOW);
    }
}

void mostrarEnColumna(int x, int y, string categoria) {
    cout << categoria << " ";
}

int main() {
    double sumaTotal=0;
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
    for(int k = 0; k < 5; k++) {
        cout << "- " << Productos[0][k].id << " " << Productos[0][k].nombre << " ($" << Productos[0][k].precio << ")" << endl;
    }
    setBackgroundAt(0, 3, menu[i].pos_X, LIGHT_GRAY_BLACK);
    setBackgroundAt(4, 4, Productos[0][0].nombre.size(), YELLOW);
    //Inicia la navegación por los Productos
    while(true){
        int input = _getch();
        switch (input) {
            case ENTER:
                if(Productos[i][j].precio >= 0){
                    sumaTotal += Productos[i][j].precio;
                    cout << "Monto actual: $" << sumaTotal << endl;
                    delay(1000); // Pausa de 1 segundo para que el usuario vea el mensaje
                    clearLineAndPosition(getCurrentCursorY()-1);
                }
                break;
            case DELETEKEY:
                if(sumaTotal > 0) {
                    sumaTotal -= Productos[i][j].precio;
                    cout << "Monto actual: $" << sumaTotal << endl;
                    delay(1000); // Pausa de 1 segundo para que el usuario vea el mensaje
                    clearLineAndPosition(getCurrentCursorY()-1);
                } else {
                    cout << "No hay monto para eliminar." << endl;
                    delay(1000); // Pausa de 1 segundo para que el usuario vea el mensaje
                    clearLineAndPosition(getCurrentCursorY()-1);
                }
                break;
            case ESC:
            case 3:
                clearBackgroundArea(0, 0, 100, getCurrentCursorY());
                cout << "Gracias por usar el sistema de compra de Productos." << endl;
                cout << "Total a pagar: $" << sumaTotal << endl;
                return 0;
            case RIGHT_ARROW:
                mover(i, j, Productos, siguiente, input);
                setBackgroundAt(0, 3, menu[i].pos_X, LIGHT_GRAY_BLACK);
                clearBackgroundArea(0, 3, menu[i-1].pos_X, 3);
                break;
            case DOWN_ARROW:
                mover(i, j, Productos, siguiente, input);
                clearBackgroundArea(4, j+3, 100, j+3);
                break;
            case LEFT_ARROW:
                mover(i, j, Productos, anterior, input);
                setBackgroundAt(menu[i-1].pos_X+1, 3, menu[i].pos_X, LIGHT_GRAY_BLACK);
                clearBackgroundArea(menu[i].pos_X, 3, menu[5].pos_X, 3);
                setBackgroundAt(4, 4, Productos[i][j].nombre.size(), YELLOW);
                break;
            case UP_ARROW:
                mover(i, j, Productos, anterior, input);
                clearBackgroundArea(4, j+5, 100, j+5);
                break;
        }
    }
    return 0;
}