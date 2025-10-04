 #include <stdio.h>
#include <stdlib.h>

void initBoard(char **board, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = ' ';
}

void displayBoard(char **board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf(" %c ", board[i][j]);
            if (j < n - 1) printf("|");
        }
        printf("\n");
        if (i < n - 1) {
            for (int j = 0; j < n; j++) printf("---");
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
        for (int j = 0; j < n; j++) fprintf(fp, "%c ", board[i][j]);
        fprintf(fp, "\n");
    }
    fflush(fp);
}

int main() {
    int n;
    printf("Enter board size (3-10): ");
    scanf("%d", &n);

    // Dynamic memory allocation
    char **board = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
        board[i] = (char *)malloc(n * sizeof(char));

    initBoard(board, n);

    FILE *fp = fopen("tictactoe_log.txt", "w");

    int turn = 0; // 0 = Player X, 1 = Player O
    char players[2] = {'X', 'O'};
    int row, col;

    while (1) {
        displayBoard(board, n);
        printf("Player %c's turn. Enter row and column: ", players[turn]);
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
        turn = 1 - turn; // Switch player
    }

    fclose(fp);
    for (int i = 0; i < n; i++) free(board[i]);
    free(board);
    return 0;
}
