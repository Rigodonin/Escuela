// conecta4_vA_part4.cpp
// Versión A - Parte 4
// Añade detección diagonal ascendente y descendente.

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

// Diagonal descendente (\) - desde arriba izquierda hacia abajo derecha
bool hay4DiagDesc(const std::vector<std::vector<char>>& board, char ficha) {
    for (int r = 0; r <= ROWS - 4; ++r) {
        for (int c = 0; c <= COLS - 4; ++c) {
            bool ok = true;
            for (int k = 0; k < 4; ++k) {
                if (board[r + k][c + k] != ficha) { ok = false; break; }
            }
            if (ok) return true;
        }
    }
    return false;
}

// Diagonal ascendente (/) - desde abajo izquierda hacia arriba derecha
bool hay4DiagAsc(const std::vector<std::vector<char>>& board, char ficha) {
    for (int r = 3; r < ROWS; ++r) {
        for (int c = 0; c <= COLS - 4; ++c) {
            bool ok = true;
            for (int k = 0; k < 4; ++k) {
                if (board[r - k][c + k] != ficha) { ok = false; break; }
            }
            if (ok) return true;
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

        // Comprobar todas las direcciones
        if (hay4Horizontal(board, simbolos[turno]) ||
            hay4Vertical(board, simbolos[turno]) ||
            hay4DiagDesc(board, simbolos[turno]) ||
            hay4DiagAsc(board, simbolos[turno])) {
            dibujarTablero(board);
            std::cout << "¡Jugador " << (turno+1) << " (" << simbolos[turno] << ") gana!\n";
            break;
        }

        if (tableroLleno(board)) {
            dibujarTablero(board);
            std::cout << "Empate. Tablero lleno.\n";
            break;
        }

        turno = 1 - turno;
    }

    return 0;
}
