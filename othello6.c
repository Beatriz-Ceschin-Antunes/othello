//Beatriz Ceschin Antunes
//December 1st, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "othello6.h"

// main function
int main()
{
    // call function welcomeScreen
    welcomeScreen();
    // call function clearScreen
    clearScreen();

    // call function playGame
    playGame();

    // program executed successfully
    return 0;
}

// welcomeScreen function displays the Othello logo and rules of the game
void welcomeScreen ()
{
	printf ("\t\t OOOO  TTTTTT HH  HH EEEEEE LL      LL      OOOO  \n");
	printf ("\t\tOO  OO   TT   HH  HH EE     LL      LL     OO  OO \n");
	printf ("\t\tOO  OO   TT   HHHHHH EEEE   LL      LL     OO  OO \n");
	printf ("\t\tOO  OO   TT   HH  HH EE     LL      LL     OO  OO \n");
	printf ("\t\t OOOO    TT   HH  HH EEEEEE LLLLLLL LLLLLL  OOOO  \n");
	printf ("\n\n");//
	printf ("OTHELLO GAME RULES:\n");
    printf("\t1. A square 8 x 8 board\n");
    printf("\t2. 64 discs colored black (X) on one side and white (O) on the opposite side.\n");
    printf("\t3. The board will start with 2 black discs (X) and 2 white discs (O) at the center of the board.\n");
    printf("\t4. They are arranged with black (X) forming a North-East to South-West direction. White (O) is forming a North-West to South-East direction\n");
    printf("\t5. The goal is to get the majority of color discs on the board at the end of the game.\n");
    printf("\t6. Each player gets 32 discs and black (X) always starts the game.\n");
    printf("\t7. The game alternates between white (O) and black (X) until one player can not make a valid move to outflank the opponent or both players have no valid moves.\n");
    printf("\t8. When a player has no valid moves, they pass their turn and the opponent continues.\n");
    printf("\t9. A player cannot voluntarily forfeit their turn.\n");
    printf("\t10. When both players can not make a valid move the game ends.\n");
}

// function displayExplicitBoard displays a hardcoded version of an Othello board
void displayExplicitBoard()
{
    printf("|-----------------------------------------------------|\n");
    printf("|     |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  1  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  2  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  3  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  4  |     |     |     |  O  |  X  |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  5  |     |     |     |  X  |  O  |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  6  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  7  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
    printf("|  8  |     |     |     |     |     |     |     |     |\n");
    printf("|-----------------------------------------------------|\n");
 }

// function clearScreen clears the screen for display purposes
void clearScreen()
{
    printf("\n\t\t\t\tHit <ENTER> to continue!\n");

	char enter;
	scanf("%c", &enter );

	// send the clear screen command Windows
    system("cls");
    // send the clear screen command for UNIX flavor operating systems
//    system("clear");
}

void playGame()
{

    // declare variable for each player as a struct
    struct Player playerX;
    struct Player playerO;

    // Othello board
    char board[ROW][COL]; // this is really a memory location of board[0][0]
    // black (X) always goes first
    int currentPlayer = PLAYER_X;
    //int loop = ZERO;

    printf("Player X, please enter your name\n");
    scanf("%s", playerX.playerName);
    playerX.playerNum = PLAYER_X;
    playerX.discCount = TWO;
    playerX.playChar = 'X';

    printf("Player O, please enter your name\n");
    scanf("%s", playerO.playerName);
    playerO.playerNum = PLAYER_O;
    playerO.discCount = TWO;
    playerO.playChar = 'O';

    printf("%s and %s, let's play Othello!\n", playerX.playerName, playerO.playerName);

    // call function initializeBoard
    initializeBoard(board);

    //declaration of local variable
    int endGame = FALSE;

    while(endGame == FALSE)
    {
        endGame = isEndGame(board);


        //if endGame is true, game over
        if(endGame == TRUE)
        {
            gameOver(board, playerX, playerO);
            break;
        }

        // call function displayBoard
        displayBoard(board);

        // request the player's move
        if(currentPlayer == PLAYER_X)
        {
            //makeMove(&playerX, board);
            //currentPlayer = PLAYER_O;
            if (validMoveExists(board, playerX.playChar) == TRUE)
            {
                makeMove(&playerX, board);
                //switches players
                currentPlayer == PLAYER_O;
            }
            else
            {
                //switches players
                currentPlayer == PLAYER_O;
            }
        }


        else if(currentPlayer == PLAYER_O)
        {
            //makeMove(&playerO, board);
            //currentPlayer = PLAYER_X;
            if(validMoveExists(board,playerO.playChar) == TRUE)
            {
                makeMove(&playerO, board);
                //switches players
                currentPlayer == PLAYER_X;
            }
            else
            {
                //switches players
                currentPlayer == PLAYER_X;
            }
        }

        updateDiscCount(board, &playerX);
        updateDiscCount(board, &playerO);

        displayStats(playerX);
        displayStats(playerO);

        //loop++;
    }

    //displayBoard(board);

    //updateDiscCount(board, &playerX);
    //updateDiscCount(board, &playerO);

    //displayStats(playerX);
    //displayStats(playerO);
}

void initializeBoard(char board[ROW][COL])
{
    for(int row = 0; row < ROW; row++)
    {
        for(int col = 0; col < COL; col++)
        {
            if((row == THREE && col == THREE) || (row == FOUR && col == FOUR))
                board[row][col] = 'O';
            else if((row == THREE && col == FOUR) || row == FOUR && col == THREE)
                board[row][col] = 'X';
            else
                board[row][col] = SPACE;
        }
    }
}

void displayBoard(char board[ROW][COL])
{
    printf("|-----------------------------------------------------|\n");
    printf("|     |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |\n");

    for(int row = 0; row < ROW; row++)
    {
        printf("|-----------------------------------------------------|\n");
        printf("|  %d  |", (row + 1));

        for(int col = 0; col < COL; col++)
        {
            printf("  %c  |", board[row][col]);
        }

        printf("\n");
    }

    printf("|-----------------------------------------------------|\n");
}

void makeMove(struct Player *player, char board[ROW][COL])
{
    char move[THREE];
    int valid = FALSE;

    // loop until the player enters a valid move
    while(valid == FALSE)
    {
        printf("%s, enter your move location (e.g. B6)\n", player->playerName);
        scanf("%s", move);
        printf("%s, you entered %s\n", player->playerName, move);

        // check for the correct number of characters
        int length = (int)strlen(move);

        if(length == TWO)
            valid = TRUE;
        else
            valid = FALSE;

        // do other data validation
        if(valid == FALSE)
            printf("Invalid move, try again\n\n");
        else
            valid = isValid(move, board, player);

        if(valid == FALSE)
            printf("Invalid move, try again\n\n");
        else
            printf("Selected move is valid!\n\n");
    }
}

int isValid(char move[THREE], char board[ROW][COL], struct Player *player)
{
    int valid = FALSE;

    // check if the square is open
    valid = isOpen(move, board);

    // if the square is not open, return FALSE, no need to check the out flank
    if(valid == FALSE)
        return valid;
    else
        valid = isOutFlank(move, board, player->playChar);

    if(valid)
        updateBoard(move, board, player);

    return valid;
}

int isOpen(char move[THREE], char board[ROW][COL])
{
    int open = FALSE;

    // get the indexes for the board row and column to check the array
    int rowInt = getMoveRow(move);
    int colInt = getMoveCol(move);

    if( (rowInt != INVALID) && (colInt != INVALID) &&
        (board[rowInt][colInt] == SPACE))
    {
        open = TRUE;
    }
    else
        open = FALSE;

    return open;
}

int getMoveCol(char move[THREE])
{
    // initialize to an invalid value
    int colInt = INVALID;
    // use the array to get the index value for the board array row
    //              0    1    2    3    4    5    6    7
    char cols[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    for(int col = 0; col < COL; col++)
    {
        // convert the first character to upper case
        if(toupper(move[ZERO]) == cols[col])
            colInt = col;
    }

    return colInt;
}

int getMoveRow(char move[THREE])
{
    // initialize to an invalid value
    int rowInt = INVALID;
    // use the array to get the index value for the board array column
    //              0    1    2    3    4    5    6    7
    char rows[] = {'1', '2', '3', '4', '5', '6', '7', '8'};

    for(int row = 0; row < ROW; row++)
    {
        // the second character in the move array is the column
        if(move[ONE] == rows[row])
            rowInt = row;
    }

    return rowInt;
}

void displayStats(struct Player player)
{
    printf("Player name:   %s\n", player.playerName);
    printf("Player number: %d\n", player.playerNum);
    printf("Player character: %c\n", player.playChar);
    printf("Player discs:  %d\n\n", player.discCount);
}

int isOutFlank(char move[THREE], char board[ROW][COL], char playerChar)
{
    int flank = FALSE;

    // get the indexes for the board row and column to check the array
    int rowInt = getMoveRow(move);
    int colInt = getMoveCol(move);

    if(checkHorizontal(rowInt, colInt, board, playerChar) > ZERO ||
       checkVertical(rowInt, colInt, board, playerChar) > ZERO ||
       checkDiagonal(rowInt, colInt, board, playerChar) > ZERO)
        flank = TRUE;
    else
        flank = FALSE;

    return flank;
}

int checkHorizontal(int row, int col, char board[ROW][COL], char playerChar)
{
    int count = 0;
    int c = col;
    int found = FALSE;

    // check left of location
    // start at the square to the left of the row selected
    c--;

    while(c >= MIN)
    {
        // if the square to the left is a space, stop checking
        // if the square to the left is the same character as the player, stop checking
        // if the square to the left is the opposite letter, count
        if(board[row][c] == SPACE)
        {
            break;
        }
        else
        {
            if(board[row][c] != playerChar)
                count++;
            else
            {
                found = TRUE;
                break;
            }
        }

        c--;
    }

    // check right of location
    // start at the square to the right of the row selected
    c = col;
    c++;

    while(c <= MAX)
    {
        // if the square to the left is a space, stop checking
        // if the square to the left is the same character as the player, stop checking
        // if the square to the left is the opposite letter, count
        if(board[row][c] == SPACE)
        {
            break;
        }
        else
        {
            if(board[row][c] != playerChar)
                count++;
            else
            {
                found = TRUE;
                break;
            }
        }

        c++;
    }

    if(count > ZERO && found == TRUE)
        return count;
    else
        return ZERO;
}

int checkVertical(int row, int col, char board[ROW][COL], char playerChar)
{
    int count = 0;
    int r = row;
    int found = FALSE;

    // check up of location
    r--;

    while(r >= MIN)
    {
        if(board[r][col] == SPACE)
        {
            break;
        }
        else
        {
            if(board[r][col] != playerChar)
                count++;
            else
            {
                found = TRUE;
                break;
            }
        }

        r--;
    }

    // check bottom of location
    // start at the square to the below of the row selected
    r = row;
    r++;

    while(r <= MAX)
    {
        // if the square to the left is a space, stop checking
        // if the square to the left is the same character as the player, stop checking
        // if the square to the left is the opposite letter, count
        if(board[r][col] == SPACE)
        {
            break;
        }
        else
        {
            if(board[r][col] != playerChar)
                count++;
            else
            {
                found = TRUE;
                break;
            }
        }

        r++;
    }

    if(count > ZERO && found == TRUE)
        return count;
    else
        return ZERO;
}

int checkDiagonal(int row, int col, char board[ROW][COL], char playerChar)
{
    int count = 0;
    int flank = FALSE;
    int r = row;
    int c = col;
    int found = FALSE;

    // check up and left of location
    r--;
    c--;

    while(r >= MIN && c >= MIN)
    {
        if(board[r][col] == SPACE && board[row][c] == SPACE)
        {
            break;
        }
        else if (board[row][c] == playerChar && board[r][col] == playerChar)
        {
            flank = TRUE;
            break;
        }
        else
        {
            if(board[row][c] != playerChar && board[r][col] != playerChar)
                count++;
            else
            {
                found = TRUE;
                break;
            }
        }

        r--;
        c--;
    }


    // check down and left of location
    // start at the square to the below of the row selected
    r = row;
    c = col;
    r++;
    c--;

    while(r <= MAX && c >= MIN)
    {
        if(board[r][col] == SPACE && board[row][c] == SPACE)
        {
            break;
        }
        else if (board[r][col] == playerChar && board[row][c] == playerChar)
        {
            flank = TRUE;
            break;
        }
        else
        {
            if(board[r][col] != playerChar && board[row][c] != playerChar)
                count++;
            else
            {
                found = TRUE;
                break;
            }
        }
        r++;
        c--;
    }

    //check up and right of location
    r = row;
    c = col;
    r--;
    c++;

    while(r >= MIN && c <= MAX)
    {
        if(board[r][col] == SPACE && board[row][c] == SPACE)
        {
            break;
        }
        else if (board[r][col] == playerChar && board[row][c] == playerChar)
        {
            flank = TRUE;
            break;
        }
        else
        {
            if(board[r][col] != playerChar && board[row][c] != playerChar)
                count++;
            else
            {
                found = TRUE;
                break;
            }
        }

        r--;
        c++;
    }


    //check down and right of location
    r = row;
    c = col;
    r++;
    c++;

    while(r <= MAX && c <= MAX)
    {
        if(board[r][col] == SPACE && board[row][c] == SPACE)
        {
            break;
        }
        else if (board[r][col] == playerChar && board[row][c] == playerChar)
        {
            flank = TRUE;
            break;
        }
        else
        {
            if(board[r][col] != playerChar && board[row][c] != playerChar)
                count++;
            else
            {
                found = TRUE;
                break;
            }
        }

        r++;
        c++;
    }

    if(count > ZERO && found == TRUE)
        return count;
    else
        return ZERO;
}

void updateBoard(char move[TWO], char board[ROW][COL], struct Player *player)
{
    int rowInt = getMoveRow(move);
    int colInt = getMoveCol(move);

    if(checkHorizontal(rowInt, colInt, board, player->playChar) > ZERO)
    {
        updateHorizontal(rowInt, colInt, board, player);
    }

    if(checkVertical(rowInt, colInt, board, player->playChar) > ZERO)
    {
        updateVertical(rowInt, colInt, board, player);
    }

    if(checkDiagonal(rowInt, colInt, board, player->playChar) > ZERO)
    {
        updateDiagonal(rowInt, colInt, board, player);
    }
}

void updateHorizontal(int row, int col, char board[ROW][COL], struct Player *player)
{
    int c = col;

    // update the actual location first
    board[row][col] = player->playChar;

    // go left
    c--;
    while(c >= MIN)
    {
        if(board[row][c] == SPACE)
        {
            break;
        }
        else
        {
            if(board[row][c] != player->playChar)
                board[row][c] = player->playChar;
            else
            {
                break;
            }
        }

        c--;
    }

    // go right
    c = col;
    c++;
    while(c <= MAX)
    {
        if(board[row][c] == SPACE)
        {
            break;
        }
        else
        {
            if(board[row][c] != player->playChar)
                board[row][c] = player->playChar;
            else
            {
                break;
            }
        }

        c++;
    }
}

void updateVertical(int row, int col, char board[ROW][COL], struct Player *player)
{
    // update the actual location first
    board[row][col] = player->playChar;

    int r = row;

    // check up of location
    r--;
    while(r >= MIN)
    {
        if(board[r][col] == SPACE)
        {
            break;
        }
        else
        {
            if(board[r][col] != player->playChar)
            {
                board[r][col] = player->playChar;
            }
            else
            {
                break;
            }
        }

        r--;
    }

    // check right of location
    // start at the square to the right of the row selected
    r = row;
    r++;

    while(r <= MAX)
    {
        if(board[r][col] == SPACE)
        {
            break;
        }
        else
        {
            if(board[r][col] != player->playChar)
            {
                board[r][col]= player->playChar;
            }
            else
            {
                break;
            }
        }

        r++;
    }
}

void updateDiagonal(int row, int col, char board[ROW][COL], struct Player *player)
{
    int c = col;
    int r = row;


    //flip discs up and left towards [row][col] (i.e., [0][0])
    r--;
    c--;

    while(r >= MIN && c >= MIN)
    {
        if(board[r][col] == SPACE && board[row][c] == SPACE)
        {
            break;
        }
        else if (board[r][col] == player->playChar && board[row][c] == player->playChar)
        {
            break;
        }
        else
        {
            if(board[r][col] != player->playChar && board[row][c] != player->playChar)
            {
                board[r][col] = player->playChar;
                board[row][c] = player->playChar;
            }
            else
            {
                break;
            }
        }

        r--;
        c--;
    }

    //flip discs down and left towards [row][col] (i.e., [7][0])
    r = row;
    c = col;
    r++;
    c--;

    while(r <= MAX && c >= MIN)
    {
        if(board[r][col] == SPACE && board[row][c] == SPACE)
        {
            break;
        }
        else if (board[r][col] == player->playChar && board[row][c] == player->playChar)
        {
            break;
        }
        else
        {
            if(board[r][col] != player->playChar && board[row][c] != player->playChar)
            {
                board[r][col] = player->playChar;
                board[row][c] = player->playChar;
            }
            else
            {
                break;
            }
        }

        r++;
        c--;
    }
    //flip discs up and right towards [row][col] (i.e., [0][7])
    c = col;
    r = row;
    r--;
    c++;

    while(r >= MIN && c <= MAX)
    {
        if(board[r][col] == SPACE && board[row][c] == SPACE)
        {
            break;
        }
        else if (board[r][col] == player->playChar && board[row][c] == player->playChar)
        {
            break;
        }
        else
        {
            if(board[r][col] != player->playChar && board[row][c] != player->playChar)
            {
                board[r][col] = player->playChar;
                board[row][c] = player->playChar;
            }
            else
            {
                break;
            }
        }

        r--;
        c++;
    }

    //flip discs down and right towards [row][col] (i.e., [7][7])
    c = col;
    r = row;
    r++;
    c++;

    while(r <= MAX && c <= MAX)
    {
        if(board[r][col] == SPACE && board[row][c] == SPACE)
        {
            break;
        }
        else if (board[r][col] == player->playChar && board[row][c] == player->playChar)
        {
            break;
        }
        else
        {
            if(board[r][col] != player->playChar && board[row][c] != player->playChar)
            {
                board[r][col] = player->playChar;
                board[row][c] = player->playChar;
            }
            else
            {
                break;
            }
        }

        r++;
        c++;
    }
}

void updateDiscCount(char board[ROW][COL], struct Player *player)
{
    int disc = 0;

    for(int row = 0; row <= MAX; row++)
        for(int col = 0; col <= MAX; col++)
            if(board[row][col] == player->playChar)
                disc++;

    player->discCount = disc;
}

//new isEndGame function
int isEndGame(char board[ROW][COL])
{
    int result = ZERO;
//setFullBoard(board);
//displayBoard(board);
//  system("pause");


    //if the board is full
    if(getDiscCount(board) == SQUARES)
    {
        return TRUE;
    }

//no move scenario
    //setNoMoveBoard(board);
    //displayBoard(board);
    //system("pause");

//no valid moves left scenario
    if (validMoveExists(board, 'X') == FALSE &&
        validMoveExists(board, 'O') == FALSE)
    {
        return TRUE;
    }
    else
        return FALSE;
}

//new function getDiscCount
int getDiscCount(char board[ROW][COL])
{
    int disc = ZERO;

    //iterates through the board array
    for(int row = 0; row <= MAX; row++)
        for(int col = 0; col <= MAX; col++)
            if(board[row][col] != SPACE)
        {
            disc++;
        }

    return disc;
}

//new function validMoveExists
int validMoveExists(char board[ROW][COL], char playerChar)
{
    int spaces = ZERO;
    int result = FALSE;

    //iterates through the board array
    for(int row = 0; row <= MAX; row++)
    {
        for(int col = 0; col <= MAX; col++)
        {
            if(board[row][col] == SPACE)
            {
                spaces++;
            }
            else if (spaces > ZERO)
            {
                if (checkHorizontal(row, col, board, playerChar) == ZERO &&
                    checkVertical(row, col, board, playerChar) == ZERO &&
                    checkDiagonal(row, col, board, playerChar) == ZERO)
                {
                    result = FALSE;
                }
                else
                    result = TRUE;
                    break;
            }
        }

        if (result == TRUE)
        {
            break;
        }
    }

    return result;
}


//new function gameOver
void gameOver(char board[ROW][COL], struct Player playerX, struct Player playerO)
{
    //displays end game banner
    printf("*******************************************************************\n");
    printf("*************************  GAME OVER  *****************************\n");
    printf("*******************************************************************\n");

    displayBoard(board);

    updateDiscCount(board, &playerX);
    updateDiscCount(board, &playerO);

    displayStats(playerX);
    displayStats(playerO);
}

// test end game support function
void setFullBoard(char board[ROW][COL])
{
    for(int row = ZERO; row < ROW; row++)
    {
        for(int col = ZERO; col < COL; col++)
        {
            if(row % TWO == ZERO && col % TWO == ZERO)
                board[row][col] = 'X';
            else
                board[row][col] = 'O';
        }
    }
}


// test end game support function
void setNoMoveBoard(char board[ROW][COL])
{
    // row 0
    // {'X','X','X','X','X','O','X','O'}
    board[0][0] = 'X';
    board[0][1] = 'X';
    board[0][2] = 'X';
    board[0][3] = 'X';
    board[0][4] = 'X';
    board[0][5] = 'O';
    board[0][6] = 'X';
    board[0][7] = 'O';

    // row 1
    // {'O','X','X','O','O','O','X','O'}
    board[1][0] = 'O';
    board[1][1] = 'X';
    board[1][2] = 'X';
    board[1][3] = 'O';
    board[1][4] = 'O';
    board[1][5] = 'O';
    board[1][6] = 'X';
    board[1][7] = 'O';

    // row 2
    // {'X','X','X','X','X','X','X','O'}
    board[2][0] = 'X';
    board[2][1] = 'X';
    board[2][2] = 'X';
    board[2][3] = 'X';
    board[2][4] = 'X';
    board[2][5] = 'X';
    board[2][6] = 'X';
    board[2][7] = 'O';

    // row 3
    // {'X','X','X','X','X','X','X','O'}
    board[3][0] = 'X';
    board[3][1] = 'X';
    board[3][2] = 'X';
    board[3][3] = 'X';
    board[3][4] = 'X';
    board[3][5] = 'X';
    board[3][6] = 'X';
    board[3][7] = 'O';

    // row 4
    // {'O','X','X','O','X','X','X','O'}
    board[4][0] = 'O';
    board[4][1] = 'X';
    board[4][2] = 'X';
    board[4][3] = 'O';
    board[4][4] = 'X';
    board[4][5] = 'X';
    board[4][6] = 'X';
    board[4][7] = 'O';

    // row 5
    // {'O','O','X','O','O','X','X','O'}
    board[5][0] = 'O';
    board[5][1] = 'O';
    board[5][2] = 'X';
    board[5][3] = 'O';
    board[5][4] = 'O';
    board[5][5] = 'X';
    board[5][6] = 'X';
    board[5][7] = 'O';

    // row 6
    // {'O','O','X','X','O','O','X','O'}
    board[6][0] = 'O';
    board[6][1] = 'O';
    board[6][2] = 'X';
    board[6][3] = 'x';
    board[6][4] = 'O';
    board[6][5] = 'O';
    board[6][6] = 'X';
    board[6][7] = 'O';

    // row 7
    // {'O','O','O','O','O','O','O',' '}
    board[7][0] = 'O';
    board[7][1] = 'O';
    board[7][2] = 'O';
    board[7][3] = 'O';
    board[7][4] = 'O';
    board[7][5] = 'O';
    board[7][6] = 'O';
    board[7][7] = ' ';
}
