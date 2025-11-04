// conecta4_vA_part2.cpp
// Versión A - Parte 2
// Añade ingreso por teclado, colocación de ficha que "cae" al fondo, validación de columna.

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
    for (int c = 1; c <= COLS; ++c) std::cout << c << ' ';
    std::cout << "\n\n";
}

// Intenta colocar una ficha en la columna (1..7). Retorna true si se colocó.
bool colocarFicha(std::vector<std::vector<char>>& board, int columna, char ficha) {
    int col = columna - 1;
    if (col < 0 || col >= COLS) return false;
    // buscar desde abajo hacia arriba la primera celda vacía
    for (int r = ROWS - 1; r >= 0; --r) {
        if (board[r][col] == '.') {
            board[r][col] = ficha;
            return true;
        }
    }
    return false; // columna llena
}

int main() {
    std::vector<std::vector<char>> board(ROWS, std::vector<char>(COLS, '.'));
    int turno = 0;
    char simbolos[2] = {'X', 'O'};

    std::cout << "Conecta 4 \n";

    while (true) {
        dibujarTablero(board);
        std::cout << "Turno jugador " << (turno+1) << " (" << simbolos[turno] << "). Elige columna (1-7): ";
        int col;
        std::cin >> col;
        if (!std::cin) { // manejo básico de entrada no numérica
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Entrada invalida. Intenta de nuevo.\n";
            continue;
        }
        if (!colocarFicha(board, col, simbolos[turno])) {
            std::cout << "Columna invalida o llena. Intenta otra.\n";
            continue;
        }
        // Alternar turno
        turno = 1 - turno;
        // Nota: aún no se comprueba ganador ni empate
    }

    return 0;
}
