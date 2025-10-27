#include <iostream> // Incluye la librería estándar para entrada y salida de datos
using namespace std; // Permite usar cout, cin, etc. sin escribir std::

// Declaramos una matriz 3x3 que representará el tablero del juego
char tablero[3][3] = {
    {'1', '2', '3'}, // Fila 1
    {'4', '5', '6'}, // Fila 2
    {'7', '8', '9'}  // Fila 3
};

// Función que muestra el tablero actual en consola
void mostrarTablero() {
    cout << "\n";
    cout << " " << tablero[0][0] << " | " << tablero[0][1] << " | " << tablero[0][2] << "\n"; // Muestra fila 1
    cout << "---|---|---\n"; // Línea divisoria
    cout << " " << tablero[1][0] << " | " << tablero[1][1] << " | " << tablero[1][2] << "\n"; // Muestra fila 2
    cout << "---|---|---\n"; // Línea divisoria
    cout << " " << tablero[2][0] << " | " << tablero[2][1] << " | " << tablero[2][2] << "\n"; // Muestra fila 3
    cout << "\n";
}

int main() {
    mostrarTablero(); // Llama a la función para mostrar el tablero inicial
    return 0; // Termina el programa correctamente
}
