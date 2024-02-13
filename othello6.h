//Beatriz Ceschin Antunes
//December 1st, 2022

#ifndef OTHELLO_H_INCLUDED
#define OTHELLO_H_INCLUDED
#endif // OTHELLO_H_INCLUDED

// macros a.k.a. global constants
#define TRUE 1
#define FALSE 0
#define NAME 20
#define ROW 8
#define COL 8
#define SPACE ' '
#define PLAYER_X 1
#define PLAYER_O 2
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define INVALID -1
#define MIN 0
#define MAX 7
#define EIGHT 8
//new macro
#define SQUARES 64


//struct Player definition
struct Player {
    int playerNum;
    char playerName[NAME];
    int discCount;
    char playChar;
};

// function prototypes
void welcomeScreen ();
void displayExplicitBoard();
void clearScreen();
void playGame();
void initializeBoard(char board[ROW][COL]);
void displayBoard(char board[ROW][COL]);
void makeMove(struct Player *player, char board[ROW][COL]);
int isValid(char move[THREE], char board[ROW][COL], struct Player *player);
int getMoveRow(char move[TWO]);
int getMoveCol(char move[TWO]);
int isOpen(char move[TWO], char board[ROW][COL]);
void displayStats(struct Player player);
int isOutFlank(char move[THREE], char board[ROW][COL], char playerChar);
int checkHorizontal(int row, int col, char board[ROW][COL], char playerChar);
int checkVertical(int row, int col, char board[ROW][COL], char playerChar);
int checkDiagonal(int row, int col, char board[ROW][COL], char playerChar);
void updateBoard(char move[TWO], char board[ROW][COL], struct Player *player);
void updateHorizontal(int row, int col, char board[ROW][COL], struct Player *player);
void updateVertical(int row, int col, char board[ROW][COL], struct Player *player);
void updateDiagonal(int row, int col, char board[ROW][COL], struct Player *player);
void updateDiscCount(char board[ROW][COL], struct Player *player);
//new function declarations
int isEndGame(char board[ROW][COL]);
int getDiscCount(char board[ROW][COL]);
int validMoveExists(char board[ROW][COL], char playerChar);
void gameOver(char board[ROW][COL], struct Player playerX, struct Player playerO);
void setFullBoard(char board[ROW][COL]);
void setNoMoveBoard(char board[ROW][COL]);
