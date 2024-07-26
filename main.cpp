#include <iostream>
#include <vector>

using namespace std;

// Prototipos de funciones
void printBoard(const vector<char>& board);
bool isMoveValid(const vector<char>& board, int move);
bool checkWin(const vector<char>& board, char player);
bool isBoardFull(const vector<char>& board);
void updateBoard(vector<char>& board, int move, char player);
void playGame(int& player1Wins, int& player2Wins);
void printStatistics(int gamesPlayed, int player1Wins, int player2Wins);
void clearScreen();

int main() {
    char playAgain;
    int gamesPlayed = 0;
    int player1Wins = 0;
    int player2Wins = 0;

    do {
        playGame(player1Wins, player2Wins);
        gamesPlayed++;
        printStatistics(gamesPlayed, player1Wins, player2Wins);
        cout << "¿Quieres jugar otra vez? (s/n): ";
        cin >> playAgain;
    } while (playAgain == 's' || playAgain == 'S');

    return 0;
}

void printBoard(const vector<char>& board) {
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << " \n";
}

bool isMoveValid(const vector<char>& board, int move) {
    return move >= 1 && move <= 9 && board[move - 1] != 'X' && board[move - 1] != 'O';
}

bool checkWin(const vector<char>& board, char player) {
    vector<vector<int>> winningCombinations = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Filas
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columnas
        {0, 4, 8}, {2, 4, 6} // Diagonales
    };

    for (const auto& combination : winningCombinations) {
        if (board[combination[0]] == player && board[combination[1]] == player && board[combination[2]] == player) {
            return true;
        }
    }

    return false;
}

bool isBoardFull(const vector<char>& board) {
    for (char cell : board) {
        if (cell != 'X' && cell != 'O') {
            return false;
        }
    }
    return true;
}

void updateBoard(vector<char>& board, int move, char player) {
    board[move - 1] = player;
}

void playGame(int& player1Wins, int& player2Wins) {
    vector<char> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int move;
    char currentPlayer = 'X';

    while (true) {
        clearScreen();
        printBoard(board);
        cout << "Jugador " << currentPlayer << ", ingresa tu movimiento (1-9): ";
        cin >> move;

        if (isMoveValid(board, move)) {
            updateBoard(board, move, currentPlayer);
        } else {
            cout << "Movimiento inválido. Intenta de nuevo." << endl;
            continue;
        }

        if (checkWin(board, currentPlayer)) {
            clearScreen();
            printBoard(board);
            cout << "¡Jugador " << currentPlayer << " gana!" << endl;
            if (currentPlayer == 'X') {
                player1Wins++;
            } else {
                player2Wins++;
            }
            return;
        }

        if (isBoardFull(board)) {
            clearScreen();
            printBoard(board);
            cout << "¡Es un empate!" << endl;
            return;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

void printStatistics(int gamesPlayed, int player1Wins, int player2Wins) {
    cout << "Estadísticas del juego:\n";
    cout << "Partidas jugadas: " << gamesPlayed << endl;
    cout << "Victorias del Jugador 1 (X): " << player1Wins << endl;
    cout << "Victorias del Jugador 2 (O): " << player2Wins << endl;
}

// Función para limpiar la pantalla
void clearScreen() {
    // Para sistemas POSIX (como Linux y macOS)
    cout << "\033[2J\033[1;1H";
    // Para Windows (puedes comentar esto si no estás en Windows)
    // system("CLS");
}
