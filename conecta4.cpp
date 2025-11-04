// conecta4_vA_part3.cpp
// Versión A - Parte 3
// Añade comprobación de victoria horizontal y vertical, y detección de tablero lleno (empate).

#include <iostream>
#include <vector>

const int ROWS = 6;
const int COLS = 7;

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

bool colocarFicha(std::vector<std::vector<char>>& board, int columna, char ficha) {
    int col = columna - 1;
    if (col < 0 || col >= COLS) return false;
    for (int r = ROWS - 1; r >= 0; --r) {
        if (board[r][col] == '.') {
            board[r][col] = ficha;
            return true;
        }
    }
    return false;
}

// Comprueba si hay 4 en línea horizontalmente
bool hay4Horizontal(const std::vector<std::vector<char>>& board, char ficha) {
    for (int r = 0; r < ROWS; ++r) {
        int conteo = 0;
        for (int c = 0; c < COLS; ++c) {
            conteo = (board[r][c] == ficha) ? conteo + 1 : 0;
            if (conteo >= 4) return true;
        }
    }
    return false;
}

// Comprueba si hay 4 en línea verticalmente
bool hay4Vertical(const std::vector<std::vector<char>>& board, char ficha) {
    for (int c = 0; c < COLS; ++c) {
        int conteo = 0;
        for (int r = 0; r < ROWS; ++r) {
            conteo = (board[r][c] == ficha) ? conteo + 1 : 0;
            if (conteo >= 4) return true;
        }
    }
    return false;
}

bool tableroLleno(const std::vector<std::vector<char>>& board) {
    for (int c = 0; c < COLS; ++c) {
        if (board[0][c] == '.') return false;
    }
    return true;
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
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Entrada invalida.\n";
            continue;
        }
        if (!colocarFicha(board, col, simbolos[turno])) {
            std::cout << "Columna invalida o llena. Intenta otra.\n";
            continue;
        }

        // Comprobaciones de victoria
        if (hay4Horizontal(board, simbolos[turno]) || hay4Vertical(board, simbolos[turno])) {
            dibujarTablero(board);
            std::cout << "¡Jugador " << (turno+1) << " (" << simbolos[turno] << ") gana!\n";
            break;
        }

        // Empate
        if (tableroLleno(board)) {
            dibujarTablero(board);
            std::cout << "Empate. Tablero lleno.\n";
            break;
        }

        turno = 1 - turno;
    }

    return 0;
}
