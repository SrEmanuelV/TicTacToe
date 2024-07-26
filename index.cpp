#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define SIZE 3


int victoriasX = 0;
int victoriasO = 0;

void imprimirTablero(char tablero[SIZE][SIZE], int fila, int columna) {
    system("cls");
    printf("Bienvenido a Triqui en C\n\n");
    printf("Historial de victorias:\n");
    printf("Jugador X: %d | Jugador O: %d\n\n", victoriasX, victoriasO);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == fila && j == columna) {
                printf("\033[1;33m[%c]\033[0m", tablero[i][j]); 
            } else {
                if (tablero[i][j] == 'X') {
                    printf(" \033[1;31m%c\033[0m ", tablero[i][j]); 
                } else if (tablero[i][j] == 'O') {
                    printf(" \033[1;34m%c\033[0m ", tablero[i][j]); 
                } else {
                    printf(" %c ", tablero[i][j]);
                }
            }
            if (j < SIZE - 1) printf("\033[1;33m|\033[0m"); 
        }
        printf("\n");
        if (i < SIZE - 1) printf("\033[1;33m---+---+---\033[0m\n"); 
    }
    printf("\n");
}

int verificarGanador(char tablero[SIZE][SIZE], char jugador) {
    for (int i = 0; i < SIZE; i++) {
        if ((tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) ||
            (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador)) {
            return 1;
        }
    }
    return (tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) ||
           (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador);
}

int esEmpate(char tablero[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (tablero[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void movimientoComputadora(char tablero[SIZE][SIZE], char jugador) {
    int fila, columna;
    do {
        fila = rand() % SIZE;
        columna = rand() % SIZE;
    } while (tablero[fila][columna] != ' ');

    tablero[fila][columna] = jugador;
}

void iniciarJuego(int contraComputadora) {
    char tablero[SIZE][SIZE] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    char jugadorActual = 'X';
    int fila = 0, columna = 0;

    while (1) {
        imprimirTablero(tablero, fila, columna);
        if (contraComputadora && jugadorActual == 'O') {
            printf("Turno de la computadora...\n");
            movimientoComputadora(tablero, 'O');
            if (verificarGanador(tablero, 'O')) {
                imprimirTablero(tablero, fila, columna);
                printf("¡La computadora ha ganado!\n");
                victoriasO++;
                break;
            }
            if (esEmpate(tablero)) {
                imprimirTablero(tablero, fila, columna);
                printf("¡Empate!\n");
                break;
            }
            jugadorActual = 'X'; 
        } else {
            printf("Turno del jugador %c. Usa 'w', 'a', 's', 'd' para moverte y 'Enter' para seleccionar.\n", jugadorActual);

            char tecla = _getch();

            if (tecla == 'w' && fila > 0) fila--;
            else if (tecla == 's' && fila < SIZE - 1) fila++;
            else if (tecla == 'a' && columna > 0) columna--;
            else if (tecla == 'd' && columna < SIZE - 1) columna++;
            else if (tecla == 13) { 
                if (tablero[fila][columna] == ' ') {
                    tablero[fila][columna] = jugadorActual;

                    if (verificarGanador(tablero, jugadorActual)) {
                        imprimirTablero(tablero, fila, columna);
                        printf("¡El jugador %c ha ganado!\n", jugadorActual);
                        if (jugadorActual == 'X') victoriasX++;
                        else victoriasO++;
                        break;
                    }

                    if (esEmpate(tablero)) {
                        imprimirTablero(tablero, fila, columna);
                        printf("¡Empate!\n");
                        break;
                    }

                    jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
                } else {
                    printf("Movimiento inválido. Inténtalo de nuevo.\n");
                    _getch(); 
                }
            }
        }
    }

  
    printf("¿Quieres jugar de nuevo? (s/n): ");
    char respuesta = _getch();
    if (respuesta == 's' || respuesta == 'S') {
        system("cls"); 
        
    }
}

void mostrarIntroduccion() {
    system("cls");
    printf("Bienvenido a Triqui (Tic-Tac-Toe) en C\n\n");
    printf("Instrucciones del juego:\n");
    printf("1. El objetivo del juego es alinear tres de tus símbolos (X o O) en fila, columna o diagonal.\n");
    printf("2. Puedes jugar contra otro jugador o contra la computadora.\n");
    printf("3. Usa las teclas 'w', 'a', 's', 'd' para moverte por el tablero.\n");
    printf("4. Presiona 'Enter' para seleccionar la celda donde quieres colocar tu símbolo.\n");
    printf("5. El juego termina cuando un jugador gana o el tablero se llena y no hay ganadores.\n");
    printf("\nPresiona cualquier tecla para continuar...\n");
    _getch(); 
}

int main() {
    srand(time(NULL)); 

    mostrarIntroduccion(); 

    while (1) {
        printf("Selecciona el modo de juego:\n");
        printf("1. Jugar contra otro jugador (1vs1)\n");
        printf("2. Jugar contra la computadora\n");
        char opcion = _getch();

        if (opcion == '2') {
            iniciarJuego(1); 
        } else if (opcion == '1') {
            iniciarJuego(0); 
        } else {
            printf("Opción inválida. Intenta nuevamente.\n");
            _getch(); 
        }
    }

    return 0;
}
