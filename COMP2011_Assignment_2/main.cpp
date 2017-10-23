/*
 * 2017F COMP2011 PA2
 * skeleton.cpp
 *
 *  Created on: Sep 20, 2017
 *      Author: Kevin Wang
 */

#include <iostream>



using namespace std;



/**
 * You should use the following const and enum whenever necessary. Do not hard code
 * the size of game board, the char of an EMPTY spot and the char of an OCCUPIED spot.
 *
 */
const int BOARD_SIZE = 4; // we will assign BOARD_SIZE to
// different values (>=3) to test your program.
const char EMPTY = '.';  // symbol that represents an EMPTY spot
const char OCCUPIED = 'x'; // symbol that represents an OCCUPIED spot
enum direction {DOWN, RIGHT}; //a block is placed to right (RIGHT)  or downward (DOWN).
/**
 * Given function. To print the game board.
 * It is already completed. Do not modify it.
 */
void printBoard(const char board[BOARD_SIZE][BOARD_SIZE]) {
    cout << "* ";
    for (int j = 0; j < BOARD_SIZE; j++)
        cout << (j % 10) << " ";
    cout << "* " << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << (i % 10) << " ";
        for (int j = 0; j < BOARD_SIZE; j++)
            cout << board[i][j] << ' ';
        cout << "*" << endl;
    }
    for (int j = 0; j < BOARD_SIZE + 2; j++)
        cout << "* ";
    cout << endl;
}

/**
 * Given function, to initialize a game board
 * It is already completed. Do not modify it.
 */
void initBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = EMPTY;

}

/**
 * @TODO function
 *
 * You need to return the smallest block available to use from an input array.
 * This function takes two parameters:
 * 1) blocks - an array storing the number of blocks remains for each block size. For instance, blocks[0]
 * should store how many 'Size 1' blocks are remaining and blocks[4] should store how many 'Size 5' blocks are remaining.
 * 2) size - a variable that may be useful when constructing your recursion.
 *
 * When this function is called in the main program, the variable "size" is always set as BOARD_SIZE.
 *
 * //UPDATED HERE @ 18/10/2017
 * Example, assume the blocks array is {0, 1, 0, 2}; this should return 2;
 *                 the blocks array is {2, 0, 0, 1}; this should return 1;
 *                 the blocks array is {0, 0, 1, 2}; this should return 3; etc.
 *
 * Note, if the blocks array contains only 0s (all blocks are used), this should return BOARD_SIZE + 1.
 *
 */
int getSmallestBlock(const int blocks[], int size) {
    if (size < 1) {
        return BOARD_SIZE + 1;
    }

    if (blocks[BOARD_SIZE - size] <= 0) {
        return getSmallestBlock(blocks, size - 1);
    } else {
        return BOARD_SIZE - size + 1;
    }
}

void chngaxTestGetSmallestBlock() {
    int test0[4] = {0,1,0,2};
    int test1[4] = {2,0,0,1};
    int test2[4] = {0,0,1,2};
    cout << "Test 1 {0,1,0,2} Expected 2 Returns " << getSmallestBlock(test0, 4) << endl;
    cout << "Test 2 {2,0,0,1} Expected 1 Returns " << getSmallestBlock(test1, 4) << endl;
    cout << "Test 3 {0,0,1,2} Expected 3 Returns " << getSmallestBlock(test2, 4) << endl;
}


/**
 * @TODO function.
 *
 * This function takes the following parameters
 * 1) char board[BOARD_SIZE][BOARD_SIZE] - a game board
 * 2) int row, int col - the top-left corner of the position that you want to put a block
 * 3) direction d, the direction you want to put a block, either downward (DOWN) or towards right (RIGHT)
 * 4) the size of a block
 *
 * If there is enough empty spot to place the block, the function shall fill the locations of the board with
 * OCCUPIED (x) and it should return true to its caller.
 * If there is not enough empty spot to place the block, or some part of the block is placed out of the game
 * board, the function shall not modify the board array and return false to its caller.
 *
 * You need to complete this function with recursion.
 */
bool placeBlock(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, direction d, int size) {
    // base case
    if (size <= 0) {
        return true;
    }

    if (d == RIGHT) {
        if (col + size <= BOARD_SIZE) {
            if (board[row][col + size - 1] == EMPTY) {
                board[row][col + size - 1] = OCCUPIED;
                if (placeBlock(board, row, col, d, size - 1)) {
                    return true;
                } else {
                    board[row][col + size - 1] = EMPTY;
                }
            }
        }
    } else if (d == DOWN) {
        if (row + size <= BOARD_SIZE) {
            if (board[row + size - 1][col] == EMPTY) {
                board[row + size - 1][col] = OCCUPIED;
                if (placeBlock(board, row, col, d, size - 1)) {
                    return true;
                } else {
                    board[row + size - 1][col] = EMPTY;
                }
            }
        }
    }

    return false;
}


/**
 * @TODO function.
 *
 * You need to check if a player have any possible way to fit a block to the board.
 * This function takes the input
 * 1) board - the 2D array representing the board
 * 2) row, col - two variables that may be useful to construct your recursion
 * 3) size - the size of a block
 *
 * The function shall return true if there is NO anyway to fit a block to the board
 * and return false if there is one or more than one way to fit a block into the board.
 *
 * When this function is called from the main program, we always fill the variable row
 * and col as 0. But when you implement this function, these two parameter may be useful
 * to construct your recursion.
 *
 */

bool cannotFitThisBlockHorizontally (char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size, int current) {
    if (current >= size) { // base case
        return false;
    }
    if (row >= BOARD_SIZE) { // all rows tried
        return true;
    }
    if (col + size > BOARD_SIZE) { // go to next row if block out of bounds
        return cannotFitThisBlockHorizontally(board, row + 1, 0, size, 0);
    }
//    cout << "horizontal checking (" << row << "," << col + current << ")...";
    if (board[row][col + current] == EMPTY) { // test for current start point
//        cout << "empty" << endl;
        if (!cannotFitThisBlockHorizontally(board, row, col, size, current + 1)) { // recursion
//            cout << "possible horizontal start point: (" << row << "," << col << ") size: "<< size << " current: " << current << endl;
            return false; // current start point can fit block, return false
        } else {
            return cannotFitThisBlockHorizontally(board, row, col + 1, size, 0); // try next start point
        }
    } else {
//        cout << "filled" << endl;
        if (current == 0) {
            return cannotFitThisBlockHorizontally(board, row, col + 1, size, 0); // try next start point
        } else {
            return true;
        }
    }
}

bool cannotFitThisBlockVertically (char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size, int current) {
    if (current >= size) { // base case
        return false;
    }
    if (col >= BOARD_SIZE) { // all cols tried
        return true;
    }
    if (row + size > BOARD_SIZE) { // go to next col if block out of bounds
        return cannotFitThisBlockVertically(board, 0, col + 1, size, 0);
    }
//    cout << "vertical checking (" << row + current << "," << col << ")... ";
    if (board[row + current][col] == EMPTY) { // test for current start point
//        cout << "empty" << endl;
        if (!cannotFitThisBlockVertically(board, row, col, size, current + 1)) { // recursion
//            cout << "possible vertical start point: (" << row << "," << col << ") size: "<< size << " current: " << current << endl;
            return false; // current start point can fit block, return false
        } else {
            return cannotFitThisBlockVertically(board, row + 1, col, size, 0); // try next start point
        }
    } else {
//        cout << "filled" << endl;
        if (current == 0) {
            return cannotFitThisBlockVertically(board, row + 1, col, size, 0); // try next start point
        } else {
            return true;
        }
    }
}


bool cannotFitThisBlock (char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int size) {
    return cannotFitThisBlockVertically(board, row, col, size, 0) && cannotFitThisBlockHorizontally(board, row, col, size, 0);
}


/**
 * @TODO
 *
 * This function should determine if there is any "checkmate move". A checkmate move is a valid move that
 * if a player makes that move, his opponent will lose the game immediately. If there is such case, the
 * function should return true and assign that move to the variables row, col, direction, size. If there is no
 * "checkmate move" the function should return false and the reference variables should not be modified.
 *
 * Similar to the above functions, row and col should be representing the top-left corner of the position
 * of the block and direction should be either RIGHT or DOWN that represents towards right or downward.
 * The variable size is the size of the block and it is required there are still unused blocks of that size
 * available, that is, blocks[size - 1] > 0.
 *
 * This function requires the status of board and the remaining number of blocks and they are supplied in the
 * array board and blocks respectively. You can assume the size of these two arrays are always "correct" when
 * it is tested. That is, you don't need to worry about if board or blocks have insufficient sizes and leading
 * array out of bound.
 *
 * When this function is called in the main program or our testing code, the variables will be set as:
 * row = 0, col = 0, direction = RIGHT, size = 1
 *
 * Note, it is possible to have more than one checkmate move. In this case you are required to assign ANY ONE
 * of the checkmate moves into the variables row, col, direction, size.
 */

void copyBoard(char from[BOARD_SIZE][BOARD_SIZE], char to[BOARD_SIZE][BOARD_SIZE], int i = 0){
    if (i >= BOARD_SIZE * BOARD_SIZE) {
        return;
    }
    to[i/BOARD_SIZE][i%BOARD_SIZE] = from[i/BOARD_SIZE][i%BOARD_SIZE];
    return copyBoard(from, to, i + 1);
}

void copyBlocks(int from[BOARD_SIZE], int to[BOARD_SIZE], int i = 0) {
    if (i >= BOARD_SIZE) {
        return;
    }
    to[i] = from[i];
    return copyBlocks(from, to, i + 1);
}

bool tryPlaceBlock(char board[BOARD_SIZE][BOARD_SIZE], int& row, int& col, direction d, int size) {
    if (d == RIGHT) {
        if (row >= BOARD_SIZE) { // base case
            return false;
        }
        if (col >= BOARD_SIZE) {
            row += col/BOARD_SIZE;
            col %= BOARD_SIZE;
            return tryPlaceBlock(board, row, col, d, size);
        }
        if (placeBlock(board, row, col, d, size)) {
            return true;
        } else {
            col += 1;
            return tryPlaceBlock(board, row, col, d, size);
        }
    } else {
        if (col >= BOARD_SIZE) { // base case
            return false;
        }
        if (row >= BOARD_SIZE) {
            col += row/BOARD_SIZE;
            row %= BOARD_SIZE;
            return tryPlaceBlock(board, row, col, d, size);
        }
        if (placeBlock(board, row, col, d, size)) {
            return true;
        } else {
            row += 1;
            return tryPlaceBlock(board, row, col, d, size);
        }
    }
}

bool tryCheckMate (char board[BOARD_SIZE][BOARD_SIZE], int& row, int& col, direction& d, int blocks[BOARD_SIZE], int& size) {
    if (d == DOWN && col >= BOARD_SIZE) {
        return false;
    }
    if (d == RIGHT && row >= BOARD_SIZE) {
        row = 0;
        col = 0;
        d = DOWN;
        return tryCheckMate(board, row, col, d, blocks, size);
    }
    char tempBoard[BOARD_SIZE][BOARD_SIZE] = {};
    copyBoard(board, tempBoard);
    int tempBlocks[BOARD_SIZE] = {};
    copyBlocks(blocks, tempBlocks);
    if (tryPlaceBlock(tempBoard, row, col, d, size)) {
        tempBlocks[size - 1] -= 1;
        if (cannotFitThisBlock(tempBoard, 0, 0, getSmallestBlock(tempBlocks, BOARD_SIZE))) {
            return true;
        } else {
            if (d == RIGHT) {
                col += 1;
            } else {
                row += 1;
            }
            return tryCheckMate(board, row, col, d, blocks, size);
        }
    } else {
        if (d == RIGHT) {
            row = 0;
            col = 0;
            d = DOWN;
            return tryCheckMate(board, row, col, d, blocks, size);
        } else {
            return false;
        }
    }
}

bool checkMate (char board[BOARD_SIZE][BOARD_SIZE], int& row, int& col, direction& d, int blocks[BOARD_SIZE], int& size) {
    char tempBoard[BOARD_SIZE][BOARD_SIZE] = {};
    copyBoard(board, tempBoard);
    int tempBlocks[BOARD_SIZE] = {};
    copyBlocks(blocks, tempBlocks);
    int tempRow = row;
    int tempCol = col;
    direction tempD = RIGHT;
    int tempSize = getSmallestBlock(tempBlocks, BOARD_SIZE);
    if (tryCheckMate(tempBoard, tempRow, tempCol, tempD, tempBlocks, tempSize)) {
        row = tempRow;
        col = tempCol;
        d = tempD;
        size = tempSize;
        return true;
    } else {
        return false;
    }
}

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    int blocks[BOARD_SIZE];
    int turn = 0; // 0 for player 1; 1 for player 2;

    //initialize game board
    initBoard(board);

    //initialize number blocks
    for (int i = 0; i < BOARD_SIZE - 1; i++) {
        blocks[i] = 2;
    }
    blocks[BOARD_SIZE - 1] = 1;


    do {
        cout << "It is your turn, player " << (turn + 1) << endl;
        printBoard(board);
        cout << "Remaining Blocks" << endl;
        for (int i = 0; i < BOARD_SIZE; i++)
            cout << (i+1) << " ";
        cout << endl;
        for (int i = 0; i < BOARD_SIZE; i++)
            cout << blocks[i] << " ";
        cout << endl;

        int row = 0, col = 0;
        int size = 1;
        int d = 0;

        direction dir = RIGHT;
        if (checkMate(board, row, col, dir, blocks, size)) {
            cout << "There is check mate move: (" << row << ", " << col << "), place size " << size <<
            ((dir == RIGHT)? " to right": " down") << endl;
        }

        while (1) {
            cout << "Please enter the coordinate: row col" << endl;
            cin >> row >> col;
            if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
                break;
            cout << "Invalid input" << endl;
        }

        while (1) {
            cout << "Please enter the size of the block: (1 to "<< BOARD_SIZE <<")" << endl;
            cin >> size;
            if (size > 0 && size <= BOARD_SIZE && blocks[size - 1] != 0)
                break;
            cout << "Invalid input or block of that size are used up." << endl;
        }

        while (1) {
            cout << "Direction? 1 for Right, 0 for Down: " << endl;
            cin >> d;
            if (d == 0 || d == 1)
                break;
            cout << "Invalid input" << endl;
        }


        if (!placeBlock(board, row, col, static_cast<direction>(d) , size))
            cout << "Cannot place the block, please try again" << endl;
        else {
            turn = (turn + 1) % 2 ;
            blocks[size - 1]--;
        }
        if (getSmallestBlock(blocks, BOARD_SIZE) > BOARD_SIZE) {
            printBoard(board);
            cout << "Game over. Block completed. " << endl;
        }

    }  while(!cannotFitThisBlock (board, 0, 0, getSmallestBlock(blocks, BOARD_SIZE)));
    printBoard(board);
    cout << "Player " << (turn + 1) << ":no more move, game over!" << endl;

}
