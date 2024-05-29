# Checkers Game in C

This repository contains the source code for a Checkers game implemented in the C programming language. The game was developed as a part of a university project during my first year.

## Game Overview

The game is designed to be played on either an 8x8 or a 10x10 board. The board size can be chosen by the user at the start of the game. The game follows the standard rules of Checkers, with the additional feature of promoting a soldier to a queen when it reaches the end of the board.

## Features

- **Recursive Enemy Checking**: The game uses recursion to check for any enemies in the path of a checker. This feature allows a checker to capture multiple enemy pieces in a single move if they are lined up diagonally.
- **Queen Promotion**: A soldier is promoted to a queen when it reaches the end of the board. Queens have the ability to move and capture pieces over any number of squares diagonally.
- **Win Condition Checking**: The game checks for win conditions after every move. A player wins when all the opponent's pieces have been captured or blocked.

## Code Structure

The code is structured into several functions, each responsible for a specific aspect of the game:

- `startGame()`: Runs the game, taking inputs for moves and applying other functions to run the game.
- `checkDiagonalEnemy()`: Checks if there is an enemy in the way and eats it. It uses recursion to check all the steps between the soldier and the destination, diagonally.
- `movePlayer()`: Moves a soldier to its required coordinates.
- `checkDiagonal()`: Checks if the movement is a diagonal.
- `checkQueen()`: Checks if the player moved to a block that will turn soldier into queen.
- `checkOutofBound()`: Checks if the move is inside the board.
- `checkEmpty()`: Checks if the block is empty.
- `checkWin()`: Checks if one of the players doesn't have any soldiers left.
- `checkMovement()`: Checks if players soldiers are blocked.
- `freeBoard()`: Frees all allocated memory.
- `allocateBoard()`: Allocates memory for the matrix and builds the board.
- `printBoard()`: Prints the board.

## How to Run

To run the game, simply execute the provided binary file. The game will prompt you to enter the dimensions of the board and the coordinates of your moves.

## Disclaimer

This project was developed for educational purposes and is not intended for use in a production environment.
