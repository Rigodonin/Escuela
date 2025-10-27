#include <iostream>
using namespace std;

char tablero[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

// Función para mostrar el tablero
void mostrarTablero() {
    cout << "\n";
    cout << " " << tablero[0][0] << " | " << tablero[0][1] << " | " << tablero[0][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << tablero[1][0] << " | " << tablero[1][1] << " | " << tablero[1][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << tablero[2][0] << " | " << tablero[2][1] << " | " << tablero[2][2] << "\n";
    cout << "\n";
}

// Función que coloca una marca en el tablero
bool marcarCasilla(char turno, int eleccion) {
    // Recorre el tablero buscando la casilla elegida
    for (int i = 0; i < 3; i++) { // Recorre filas
        for (int j = 0; j < 3; j++) { // Recorre columnas
            if (tablero[i][j] == eleccion + '0') { // Si la casilla coincide con el número elegido
                tablero[i][j] = turno; // Coloca la marca (X o O)
                return true; // Indica que la jugada fue válida
            }
        }
    }
    return false; // Si no se encontró la casilla, jugada inválida
}

int main() {
    char turno = 'X'; // Comienza el jugador X
    int eleccion; // Variable para guardar el número elegido

    // Bucle infinito para permitir varias jugadas
    while (true) {
        mostrarTablero(); // Muestra el tablero
        cout << "Turno del jugador " << turno << ". Elige una casilla (1-9): ";
        cin >> eleccion; // Recibe la casilla

        // Valida si la jugada es válida
        if (!marcarCasilla(turno, eleccion)) {
            cout << "Casilla inválida. Intenta de nuevo.\n"; // Mensaje de error
            continue; // Vuelve a pedir la jugada
        }

        // Cambia el turno
        turno = (turno == 'X') ? 'O' : 'X';
    }

    return 0;
}
