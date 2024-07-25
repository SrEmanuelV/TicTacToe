#include <iostream>
#include <vector>
#include <climits>
#include <unistd.h> // Librería para usleep en Unix/Linux

using namespace std;

const char HUMAN_PLAYER = 'X';
const char AI_PLAYER = 'O';

// Prototipos de funciones
char checkWinner(const vector<char>& board);
void drawBoard(const vector<char>& board);
bool gameOver(const vector<char>& board);
vector<int> getValidMoves(const vector<char>& board);
int minimax(vector<char> board, bool isMaximizing, int alpha, int beta);
int getAIMove(const vector<char>& board);

// Función para limpiar la consola y dibujar el tablero
void clearScreenAndDraw(const vector<char>& board) {
    // Limpiar la consola usando ANSI escape codes
    cout << "\033[2J\033[H";
    drawBoard(board);
}

// Función para dibujar el tablero
void drawBoard(const vector<char>& board) {
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "---+---+---" << endl;
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "---+---+---" << endl;
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
}

// Función para verificar si hay un ganador o si es empate
bool gameOver(const vector<char>& board) {
    // Verificar si hay un ganador
    for (int i = 0; i < 3; ++i) {
        // Filas
        if (board[i*3] != ' ' && board[i*3] == board[i*3+1] && board[i*3] == board[i*3+2]) {
            return true;
        }
        // Columnas
        if (board[i] != ' ' && board[i] == board[i+3] && board[i] == board[i+6]) {
            return true;
        }
    }
    // Diagonales
    if (board[0] != ' ' && board[0] == board[4] && board[0] == board[8]) {
        return true;
    }
    if (board[2] != ' ' && board[2] == board[4] && board[2] == board[6]) {
        return true;
    }

    // Verificar si es empate
    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ') {
            return false;
        }
    }
    return true;
}

// Función para obtener los movimientos válidos
vector<int> getValidMoves(const vector<char>& board) {
    vector<int> validMoves;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ') {
            validMoves.push_back(i);
        }
    }
    return validMoves;
}

// Función Minimax con Alfa-Beta Pruning
int minimax(vector<char> board, bool isMaximizing, int alpha, int beta);

// Función para que la IA elija un movimiento utilizando Minimax con Alfa-Beta Pruning
int getAIMove(const vector<char>& board) {
    int bestScore = INT_MIN;
    int bestMove = -1;
    int alpha = INT_MIN;
    int beta = INT_MAX;

    vector<int> validMoves = getValidMoves(board);

    for (int move : validMoves) {
        vector<char> newBoard = board;
        newBoard[move] = AI_PLAYER;
        int score = minimax(newBoard, false, alpha, beta);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}

// Función Minimax con Alfa-Beta Pruning
int minimax(vector<char> board, bool isMaximizing, int alpha, int beta) {
    // Evaluar el estado actual del tablero
    if (gameOver(board)) {
        // Si el juego ha terminado, devolver el valor de la utilidad
        if (checkWinner(board) == AI_PLAYER) {
            return 10; // AI gana
        } else if (checkWinner(board) == HUMAN_PLAYER) {
            return -10; // Humano gana
        } else {
            return 0; // Empate
        }
    }

    // Obtener movimientos válidos
    vector<int> validMoves = getValidMoves(board);

    // Maximizar o minimizar el valor
    if (isMaximizing) {
        int bestScore = INT_MIN;
        for (int move : validMoves) {
            board[move] = AI_PLAYER;
            int score = minimax(board, false, alpha, beta);
            board[move] = ' ';
            bestScore = max(bestScore, score);
            alpha = max(alpha, bestScore);
            if (beta <= alpha) {
                break;
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for (int move : validMoves) {
            board[move] = HUMAN_PLAYER;
            int score = minimax(board, true, alpha, beta);
            board[move] = ' ';
            bestScore = min(bestScore, score);
            beta = min(beta, bestScore);
            if (beta <= alpha) {
                break;
            }
        }
        return bestScore;
    }
}

// Implementación de la función checkWinner
char checkWinner(const vector<char>& board) {
    // Verificar si hay un ganador
    for (int i = 0; i < 3; ++i) {
        // Filas
        if (board[i*3] != ' ' && board[i*3] == board[i*3+1] && board[i*3] == board[i*3+2]) {
            return board[i*3];
        }
        // Columnas
        if (board[i] != ' ' && board[i] == board[i+3] && board[i] == board[i+6]) {
            return board[i];
        }
    }
    // Diagonales
    if (board[0] != ' ' && board[0] == board[4] && board[0] == board[8]) {
        return board[0];
    }
    if (board[2] != ' ' && board[2] == board[4] && board[2] == board[6]) {
        return board[2];
    }

    // Si no hay ganador
    return ' ';
}

int main() {
    int totalGames = 0;
    int playerWins = 0;
    int aiWins = 0;

    while (true) {
        vector<char> board(9, ' '); // Tablero vacío
        bool playerTurn = true;     // True: turno del jugador, False: turno de la IA
        totalGames++;

        cout << "Bienvenido al juego Tic Tac Toe! Partida #" << totalGames << endl;

        // Dibujar el tablero por primera vez
        clearScreenAndDraw(board);

        // Bucle principal del juego
        while (true) {
            if (playerTurn) {
                // Turno del jugador
                int move;
                cout << "Es tu turno. Ingresa un número del 1 al 9 para hacer tu movimiento (0 para salir): ";
                cin >> move;

                if (move == 0) {
                    cout << "Gracias por jugar. Saliendo del juego." << endl;
                    return 0;
                }

                // Convertir el movimiento a índice (1-9) a (0-8)
                move--;

                if (move < 0 || move >= 9 || board[move] != ' ') {
                    cout << "Movimiento inválido. Intenta de nuevo." << endl;
                    continue;
                }

                board[move] = HUMAN_PLAYER;
            } else {
                // Turno de la IA
                cout << "Turno de la IA..." << endl;
                usleep(1000000); // Esperar un segundo (1000000 microsegundos) para simular el pensamiento de la IA
                int aimove = getAIMove(board);
                board[aimove] = AI_PLAYER;
            }

            // Limpiar la consola y dibujar el tablero actualizado
            clearScreenAndDraw(board);

            // Verificar si hay un ganador o empate
            if (gameOver(board)) {
                if (checkWinner(board) == HUMAN_PLAYER) {
                    cout << "¡Felicidades! ¡Has ganado!" << endl;
                    playerWins++;
                } else if (checkWinner(board) == AI_PLAYER) {
                    cout << "¡La IA ha ganado!" << endl;
                    aiWins++;
                } else {
                    cout << "¡Es un empate!" << endl;
                }
                break;
            }

            // Cambiar turno
            playerTurn = !playerTurn;
        }

        // Mostrar estadísticas después de cada partida
        cout << "Estadísticas: " << endl;
        cout << "- Partidas jugadas: " << totalGames << endl;
        cout << "- Victorias del jugador: " << playerWins << endl;
        cout << "- Victorias de la IA: " << aiWins << endl;

        // Preguntar si desea jugar otra partida
        cout << "¿Quieres jugar otra partida? (s/n): ";
        char choice;
        cin >> choice;
        if (choice != 's' && choice != 'S') {
            cout << "Gracias por jugar. Saliendo del juego." << endl;
            break;
        }
    }

    return 0;
}
