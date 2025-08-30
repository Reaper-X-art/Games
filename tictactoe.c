#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define SIZE 3

#define PLAYER 'X'
#define COMPUTER 'O'
#define EMPTY ' '

typedef struct {
    int row;
    int col;
} Move;

void initializeBoard(char board[SIZE][SIZE]);
void printBoard(char board[SIZE][SIZE]);
bool isMovesLeft(char board[SIZE][SIZE]);
int evaluate(char board[SIZE][SIZE]);
int minimax(char board[SIZE][SIZE], int depth, bool isMax, int alpha, int beta);
Move findBestMove(char board[SIZE][SIZE]);
bool checkWin(char board[SIZE][SIZE], char player);
void playerMove(char board[SIZE][SIZE]);
void computerMove(char board[SIZE][SIZE]);
void playGame();

int main() {
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("You are 'X', Computer is 'O'.\n");
    printf("Enter row and column numbers (0-2) to make your move.\n\n");
    
    char choice;
    do {
        playGame();
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &choice);
        printf("\n");
    } while (choice == 'y' || choice == 'Y');
    
    printf("Thanks for playing!\n");
    return 0;
}

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void printBoard(char board[SIZE][SIZE]) {
    printf("-------------\n");
    for (int i = 0; i < SIZE; i++) {
        printf("| ");
        for (int j = 0; j < SIZE; j++) {
            printf("%c | ", board[i][j]);
        }
        printf("\n-------------\n");
    }
    printf("\n");
}

bool isMovesLeft(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                return true;
            }
        }
    }
    return false;
}

int evaluate(char board[SIZE][SIZE]) {
    // Check rows for victory
    for (int row = 0; row < SIZE; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == COMPUTER) return 10;
            else if (board[row][0] == PLAYER) return -10;
        }
    }
    
    for (int col = 0; col < SIZE; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == COMPUTER) return 10;
            else if (board[0][col] == PLAYER) return -10;
        }
    }
    
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == COMPUTER) return 10;
        else if (board[0][0] == PLAYER) return -10;
    }
    
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == COMPUTER) return 10;
        else if (board[0][2] == PLAYER) return -10;
    }
    
    return 0;
}

int minimax(char board[SIZE][SIZE], int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);
    
    if (score == 10) return score - depth;
    
    if (score == -10) return score + depth;
    
    if (!isMovesLeft(board)) return 0;
    
    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    int val = minimax(board, depth + 1, false, alpha, beta);
                    board[i][j] = EMPTY;
                    best = (best > val) ? best : val;
                    alpha = (alpha > best) ? alpha : best;
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    int val = minimax(board, depth + 1, true, alpha, beta);
                    board[i][j] = EMPTY;
                    best = (best < val) ? best : val;
                    beta = (beta < best) ? beta : best;
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    }
}

Move findBestMove(char board[SIZE][SIZE]) {
    int bestVal = INT_MIN;
    Move bestMove = {-1, -1};
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER;
                int moveVal = minimax(board, 0, false, INT_MIN, INT_MAX);
                board[i][j] = EMPTY;
                
                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

bool checkWin(char board[SIZE][SIZE], char player) {
    for (int row = 0; row < SIZE; row++) {
        if (board[row][0] == player && board[row][1] == player && board[row][2] == player) return true;
    }
    for (int col = 0; col < SIZE; col++) {
        if (board[0][col] == player && board[1][col] == player && board[2][col] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

void playerMove(char board[SIZE][SIZE]) {
    int row, col;
    while (true) {
        printf("Your move (row col): ");
        scanf("%d %d", &row, &col);
        
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == EMPTY) {
            board[row][col] = PLAYER;
            break;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
}

void computerMove(char board[SIZE][SIZE]) {
    Move bestMove = findBestMove(board);
    board[bestMove.row][bestMove.col] = COMPUTER;
    printf("Computer moves to %d %d\n", bestMove.row, bestMove.col);
}

void playGame() {
    char board[SIZE][SIZE];
    initializeBoard(board);
    printBoard(board);
    
    bool playerTurn = rand() % 2 == 0;
    if (playerTurn) {
        printf("You start!\n");
    } else {
        printf("Computer starts!\n");
    }
    
    while (true) {
        if (playerTurn) {
            playerMove(board);
        } else {
            computerMove(board);
        }
        printBoard(board);
        
        if (checkWin(board, PLAYER)) {
            printf("You win!\n");
            break;
        } else if (checkWin(board, COMPUTER)) {
            printf("Computer wins!\n");
            break;
        } else if (!isMovesLeft(board)) {
            printf("It's a draw!\n");
            break;
        }
        
        playerTurn = !playerTurn;
    }
}
