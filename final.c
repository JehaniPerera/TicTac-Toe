#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"

void initBoard(char **board, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = ' ';
}

void displayBoard(char **board, int n) {
    printf("   ");
    for (int j = 0; j < n; j++)
        printf("%d   ", j);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", i );
        for (int j = 0; j < n; j++) {
            printf(" %c ", board[i][j]);
            if (j < n - 1) printf("|");
        }
        printf("\n");
        if (i < n - 1) {
            printf("  ");
            for (int j = 0; j < n; j++) printf("----");
            printf("\n");
        }
    }
}

int isValidMove(char **board, int n, int row, int col) {
    return (row >= 0 && row < n && col >= 0 && col < n && board[row][col] == ' ');
}

int checkWin(char **board, int n, char symbol) {
    // Check rows & columns
    for (int i = 0; i < n; i++) {
        int rowWin = 1, colWin = 1;
        for (int j = 0; j < n; j++) {
            if (board[i][j] != symbol) rowWin = 0;
            if (board[j][i] != symbol) colWin = 0;
        }
        if (rowWin || colWin) return 1;
    }

    // Check diagonals
    int diag1 = 1, diag2 = 1;
    for (int i = 0; i < n; i++) {
        if (board[i][i] != symbol) diag1 = 0;
        if (board[i][n - i - 1] != symbol) diag2 = 0;
    }
    return diag1 || diag2;
}

int checkDraw(char **board, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

void logMove(FILE *fp, char **board, int n) {
    fprintf(fp, "\nCurrent Board:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            fprintf(fp, "%c ", board[i][j]);
        fprintf(fp, "\n");
    }
    fflush(fp);
}

void computerMove(char **board, int n, char symbol) {
    int row, col;
    do {
        row = rand() % n;
        col = rand() % n;
    } while (board[row][col] != ' ');
    board[row][col] = symbol;
    printf("Computer (%c) placed at (%d, %d)\n", symbol, row, col);
}

// Main Function

int main() {
    int n, choice;
    srand(time(0)); 
    printf("Enter board size N (3 <= N <= 10): ");
    scanf("%d", &n);

    // Allocate memory for dynamic 2D array
    char **board = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
        board[i] = (char *)malloc(n * sizeof(char));

    initBoard(board, n);
    FILE *fp = fopen("tictactoe_log.txt", "w");

    printf("\nSelect Game Mode:\n");
    printf("1. Two Players (User vs User)\n");
    printf("2. User vs Computer\n");
    printf("3. Three Players\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &choice);

    // Mode 1 Two players (User vs User)
    if (choice == 1) {
        int turn = 0;
        char players[2] = {'X', 'O'};
        int row, col;
        while (1) {
            displayBoard(board, n);
            printf("Player %c, enter row and col (0..%d): ", players[turn], n - 1);
            scanf("%d %d", &row, &col);

            if (!isValidMove(board, n, row, col)) {
                printf("Invalid move! Try again.\n");
                continue;
            }

            board[row][col] = players[turn];
            logMove(fp, board, n);

            if (checkWin(board, n, players[turn])) {
                displayBoard(board, n);
                printf("Player %c wins!\n", players[turn]);
                break;
            }
            if (checkDraw(board, n)) {
                displayBoard(board, n);
                printf("Game is a draw!\n");
                break;
            }
            turn = 1 - turn;
        }
    }

    // Mode 2 User vs Computer
    else if (choice == 2) {
        int row, col;
        while (1) {
            displayBoard(board, n);
            printf("Your turn (X). Enter row and col (0..%d): ", n - 1);
            scanf("%d %d", &row, &col);

            if (!isValidMove(board, n, row, col)) {
                printf("Invalid move! Try again.\n");
                continue;
            }
            board[row][col] = 'X';
            logMove(fp, board, n);

            if (checkWin(board, n, 'X')) {
                displayBoard(board, n);
                printf("You win!\n");
                break;
            }
            if (checkDraw(board, n)) {
                displayBoard(board, n);
                printf("Game is a draw!\n");
                break;
            }

            computerMove(board, n, 'O');
            logMove(fp, board, n);

            if (checkWin(board, n, 'O')) {
                displayBoard(board, n);
                printf("Computer wins!\n");
                break;
            }
            if (checkDraw(board, n)) {
                displayBoard(board, n);
                printf("Game is a draw!\n");
                break;
            }
        }
    }

    // Mode 3 Three Players
    else if (choice == 3) {
        char players[3] = {'X', 'O', 'Z'};
        int isHuman[3];
        printf("Define players (1=Human, 0=Computer,2=third player):\n");
        for (int i = 0; i < 3; i++) {
            printf("Player %c: ", players[i]);
            scanf("%d", &isHuman[i]);
        }

        int turn = 0, row, col;
        while (1) {
            displayBoard(board, n);
            if (isHuman[turn]) {
                printf("Player %c, enter row and col (0..%d): ", players[turn], n - 1);
                scanf("%d %d", &row, &col);
                if (!isValidMove(board, n, row, col)) {
                    printf("Invalid move! Try again.\n");
                    continue;
                }
                board[row][col] = players[turn];
            } else {
                computerMove(board, n, players[turn]);
            }

            logMove(fp, board, n);

            if (checkWin(board, n, players[turn])) {
                displayBoard(board, n);
                printf("Player %c wins!\n", players[turn]);
                break;
            }
            if (checkDraw(board, n)) {
                displayBoard(board, n);
                printf("Game is a draw!\n");
                break;
            }
            turn = (turn + 1) % 3;
        }
    }

    else {
        printf("Invalid choice! Exiting.\n");
    }

    fclose(fp);
    for (int i = 0; i < n; i++) free(board[i]);
    free(board);
    return 0;
}
	

