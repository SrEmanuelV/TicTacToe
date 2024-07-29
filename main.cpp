#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para imprimir el tablero sin colores
void printBoard(const vector<vector<char>>& board) {
    cout << "    1   2   3" << endl;
    cout << "  +---+---+---+" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << " | ";
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 'X') {
                cout << "X"; // Rojo (sin color)
            } else if (board[i][j] == 'O') {
                cout << "O"; // Azul (sin color)
            } else {
                cout << " ";
            }
            if (j < 2) {
                cout << " | ";
            }
        }
        cout << " |" << endl;
        cout << "  +---+---+---+" << endl;
    }
}

// Función para verificar si alguien ganó
bool checkWin(const vector<vector<char>>& board, char player) {
    // Verificar filas y columnas
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Verificar diagonales
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

// Función para manejar el turno de un jugador
bool makeMove(vector<vector<char>>& board, char player) {
    int row, col;
    while (true) {
        cout << "Jugador " << player << ", elija la fila (1-3) y columna (1-3): ";
        if (cin >> row >> col) {
            if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && board[row-1][col-1] == ' ') {
                board[row-1][col-1] = player;
                return true;
            } else {
                cout << "Movimiento invalido. Intente de nuevo." << endl;
            }
        } else {
            cin.clear(); // Limpiar el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar la entrada incorrecta
            cout << "Entrada invalida. Intente de nuevo." << endl;
        }
    }
}

// Función para manejar el turno de la máquina (movimiento aleatorio)
void makeMachineMove(vector<vector<char>>& board) {
    srand(static_cast<unsigned>(time(0)));
    int row, col;
    while (true) {
        row = rand() % 3;
        col = rand() % 3;
        if (board[row][col] == ' ') {
            board[row][col] = 'O';
            break;
        }
    }
}

// Función para mostrar el tiempo transcurrido
void displayElapsedTime(const steady_clock::time_point& start) {
    auto now = steady_clock::now();
    auto elapsed = duration_cast<seconds>(now - start);
    cout << "Tiempo jugado: " << elapsed.count() << " segundos" << endl;
}

// Función para jugar contra la máquina
void playAgainstMachine() {
    vector<vector<char>> board(3, vector<char>(3, ' ')); // Tablero 3x3 inicializado con espacios
    char currentPlayer = 'X';
    bool gameOver = false;

    // Iniciar temporizador
    auto start = steady_clock::now();

    while (!gameOver) {
        printBoard(board);
        displayElapsedTime(start);

        if (currentPlayer == 'X') {
            // Turno del jugador
            if (!makeMove(board, currentPlayer)) {
                continue;
            }
        } else {
            // Turno de la máquina
            makeMachineMove(board);
        }

        // Verificar si hay ganador
        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            displayElapsedTime(start);
            cout << "Jugador " << currentPlayer << " ha ganado!" << endl;
            gameOver = true;
        } else {
            // Cambiar jugador
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

            // Verificar si hay empate
            bool fullBoard = true;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == ' ') {
                        fullBoard = false;
                        break;
                    }
                }
                if (!fullBoard) break;
            }
            if (fullBoard) {
                printBoard(board);
                displayElapsedTime(start);
                cout << "Empate!" << endl;
                gameOver = true;
            }
        }
    }
}

// Función para imprimir el menú principal
void printMenu() {
    cout << "Bienvenido al juego de Tic-Tac-Toe!" << endl;
    cout << "1. Jugar contra la inteligencia artificial" << endl;
    cout << "2. Jugar entre dos jugadores" << endl;
    cout << "3. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

// Función para jugar entre dos jugadores
void playTwoPlayers() {
    vector<vector<char>> board(3, vector<char>(3, ' ')); // Tablero 3x3 inicializado con espacios
    char currentPlayer = 'X';
    bool gameOver = false;

    // Iniciar temporizador
    auto start = steady_clock::now();

    while (!gameOver) {
        printBoard(board);
        displayElapsedTime(start);

        // Turno del jugador
        if (!makeMove(board, currentPlayer)) {
            continue;
        }

        // Verificar si hay ganador
        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            displayElapsedTime(start);
            cout << "Jugador " << currentPlayer << " ha ganado!" << endl;
            gameOver = true;
        } else {
            // Cambiar jugador
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

            // Verificar si hay empate
            bool fullBoard = true;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == ' ') {
                        fullBoard = false;
                        break;
                    }
                }
                if (!fullBoard) break;
            }
            if (fullBoard) {
                printBoard(board);
                displayElapsedTime(start);
                cout << "Empate!" << endl;
                gameOver = true;
            }
        }
    }
}

int main() {
    int choice;

    while (true) {
        printMenu();
        cin >> choice;

        if (choice == 1) {
            // Jugar contra la máquina
            playAgainstMachine();
        } else if (choice == 2) {
            // Jugar entre dos jugadores
            playTwoPlayers();
        } else if (choice == 3) {
            cout << "Gracias por jugar. Hasta la proxima!" << endl;
            break;
        } else {
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    }

    return 0;
}
