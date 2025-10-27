#include <iostream>
using namespace std;

char tablero[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

// Muestra el tablero en pantalla
void mostrarTablero() {
    cout << "\n";
    for (int i = 0; i < 3; i++) { // Recorre filas
        cout << " " << tablero[i][0] << " | " << tablero[i][1] << " | " << tablero[i][2] << "\n"; // Muestra la fila
        if (i < 2) cout << "---|---|---\n"; // Línea divisoria
    }
    cout << "\n";
}

// Marca una casilla con X o O si es válida
bool marcarCasilla(char turno, int eleccion) {
    for (int i = 0; i < 3; i++) { // Recorre filas
        for (int j = 0; j < 3; j++) { // Recorre columnas
            if (tablero[i][j] == eleccion + '0') { // Si el número coincide
                tablero[i][j] = turno; // Coloca la marca
                return true; // Jugada válida
            }
        }
    }
    return false; // Jugada inválida
}

// Verifica si hay un ganador o empate
char verificarGanador() {
    // Verifica filas
    for (int i = 0; i < 3; i++)
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2])
            return tablero[i][0]; // Devuelve el ganador

    // Verifica columnas
    for (int j = 0; j < 3; j++)
        if (tablero[0][j] == tablero[1][j] && tablero[1][j] == tablero[2][j])
            return tablero[0][j];

    // Verifica diagonales
    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2])
        return tablero[0][0];
    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0])
        return tablero[0][2];

    // Verifica empate (si todas las casillas están ocupadas)
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i][j] != 'X' && tablero[i][j] != 'O')
                return ' '; // Aún hay espacios

    return 'E'; // Empate
}

int main() {
    char turno = 'X'; // Inicia el jugador X
    int eleccion; // Guarda la casilla elegida
    char resultado = ' '; // Guarda el resultado del juego

    while (resultado == ' ') { // Mientras no haya ganador ni empate
        mostrarTablero(); // Muestra el tablero
        cout << "Turno del jugador " << turno << ". Elige una casilla (1-9): ";
        cin >> eleccion; // Pide la jugada

        if (!marcarCasilla(turno, eleccion)) { // Si la jugada no es válida
            cout << "Casilla inválida. Intenta de nuevo.\n"; // Mensaje
            continue; // Vuelve a pedir jugada
        }

        resultado = verificarGanador(); // Comprueba si hay ganador

        // Cambia el turno si no ha terminado
        if (resultado == ' ')
            turno = (turno == 'X') ? 'O' : 'X';
    }

    mostrarTablero(); // Muestra el tablero final

    // Muestra el resultado final
    if (resultado == 'E')
        cout << "¡Empate!\n";
    else
        cout << "¡Felicidades! El jugador " << resultado << " ha ganado.\n";

    return 0;
}
