#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Function prototypes
void initBoard(char **board, int n);
void displayBoard(char **board, int n);
int isValidMove(char **board, int n, int row, int col);
int checkWin(char **board, int n, char symbol);
int checkDraw(char **board, int n);
void logMove(FILE *fp, char **board, int n);
void computerMove(char **board, int n, char symbol);

#endif

