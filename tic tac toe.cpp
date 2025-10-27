#include <iostream>
using namespace std;

// Matriz del tablero
char tablero[3][3];

// Reinicia el tablero a su estado inicial
void reiniciarTablero() {
    char contador = '1'; // Empieza desde el número 1
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tablero[i][j] = contador++; // Llena las casillas del 1 al 9
}

// Muestra el tablero
void mostrarTablero() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " " << tablero[i][0] << " | " << tablero[i][1] << " | " << tablero[i][2] << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

// Marca una casilla
bool marcarCasilla(char turno, int eleccion) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i][j] == eleccion + '0') {
                tablero[i][j] = turno;
                return true;
            }
    return false;
}

// Verifica si hay ganador o empate
char verificarGanador() {
    for (int i = 0; i < 3; i++)
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2])
            return tablero[i][0];

    for (int j = 0; j < 3; j++)
        if (tablero[0][j] == tablero[1][j] && tablero[1][j] == tablero[2][j])
            return tablero[0][j];

    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2])
        return tablero[0][0];
    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0])
        return tablero[0][2];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i][j] != 'X' && tablero[i][j] != 'O')
                return ' ';

    return 'E';
}

int main() {
    char turno, resultado, opcion;
    int eleccion;

    do {
        reiniciarTablero(); // Inicia el tablero limpio
        turno = 'X'; // Empieza el jugador X
        resultado = ' ';

        while (resultado == ' ') {
            mostrarTablero();
            cout << "Turno del jugador " << turno << ". Elige una casilla (1-9): ";
            cin >> eleccion;

            if (!marcarCasilla(turno, eleccion)) {
                cout << "Casilla inválida. Intenta de nuevo.\n";
                continue;
            }

            resultado = verificarGanador();

            if (resultado == ' ')
                turno = (turno == 'X') ? 'O' : 'X';
        }

        mostrarTablero();

        if (resultado == 'E')
            cout << "¡Empate!\n";
        else
            cout << "¡El jugador " << resultado << " ha ganado!\n";

        cout << "¿Deseas jugar otra vez? (s/n): ";
        cin >> opcion;

    } while (opcion == 's' || opcion == 'S');

    cout << "Gracias por jugar. ¡Hasta pronto!\n";
    return 0;
}
