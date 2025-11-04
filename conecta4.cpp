// conecta4_vA_part1.cpp
// Versión A - Parte 1
// Muestra un tablero vacío y alterna turnos sin colocar fichas (base mínima).

#include <iostream>
#include <vector>

const int ROWS = 6;
const int COLS = 7;

// Dibuja el tablero en consola
void dibujarTablero(const std::vector<std::vector<char>>& board) {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            std::cout << board[r][c] << ' ';
        }
        std::cout << '\n';
    }
    // mostrar indices de columna
    for (int c = 1; c <= COLS; ++c) std::cout << c << ' ';
    std::cout << "\n\n";
}

int main() {
    // Inicializar tablero con '.'
    std::vector<std::vector<char>> board(ROWS, std::vector<char>(COLS, '.'));

    int turno = 0; // 0 -> Jugador 1 (X), 1 -> Jugador 2 (O)
    char simbolos[2] = {'X', 'O'};

    std::cout << "Conecta 4 - \n";
    // Mostrar tablero inicial
    dibujarTablero(board);

    // Ciclo mínimo: solo alterna turnos y muestra quien juega (sin colocar)
    for (int i = 0; i < 4; ++i) { // solo algunas iteraciones de ejemplo
        std::cout << "Turno jugador " << (turno+1) << " (" << simbolos[turno] << ")\n";
        // En esta parte solo mostramos el turno y el tablero (sin entrada de columna aún)
        dibujarTablero(board);
        turno = 1 - turno;
    }

    
    return 0;
}
