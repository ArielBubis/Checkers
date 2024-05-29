/*HW5_Ariel*/
#include <stdio.h>
#include <stdlib.h>
#define W 1
#define B 2
#define Q 3
#define q 4
/***************************************/
int brdSize;
int i,j;
char** board;
int brdSizeX,brdSizeY;
int player = W;
int x,y,moveToX,moveToY;
int blokdW,blokdB;
int gameOver = 0;
int wCount = 0, bCount = 0;
int flagEnemy = 0;
char playerColor, playerQueen;
int winner = 0;
int soldierCount=0;
char row = '0';
/***************************************/
/*explanation about each function is presented in the code below*/
void startGame();
int checkDiagonalEnemy(int,int,int,int,int );
void movePlayer(int,int,int,int,int );
int checkDiagonal(int,int,int,int );
void checkQueen(int,int, int );
int checkOutofBound(int,int);
int checkEmpty(int,int);
int checkWin();
int checkMovement(int, int, int);
void freeBoard();
void allocateBoard(int, int );
void printBoard();
int checkMovementFix(int, int, int);
/***************************************/

int main()
{

    printf("Enter the dimensions of the board: \n(For 8x8- Choose 8|For 10x10- Choose 10):");
    if(scanf("%d",&brdSizeX)==1)/*check if the input is number*/
    {
        if(brdSizeX == 8 || brdSizeX == 10)/*if the input is 8X8 or 10X10 build the board*/
        {
            brdSize = brdSizeX;
            brdSizeY = brdSizeX;
            printf("\nInstructions:\nTo move a soldier, first enter the 'y' coordinate of the soldier, followed by the 'x' coordinate.\nNext, provide the 'y' and 'x' coordinates of the new location where you wish to move the soldier.");
            if(brdSize == 8){
                printf("\nFor example: 2 1 3 0");
            }else{
                printf("\nFor example: 3 8 4 7");
            }
            allocateBoard(brdSizeX,brdSizeX);/*function to allocate memory for the matrix and build the board */
            printBoard();/*function to print board*/
            startGame();/*Function to run the game*/
            freeBoard();/*Function to free the board*/
        }
        else
        {
            printf("\nInput Error!");
            return 1;
        }
    }
    else
    {
        printf("\nInput Error!");
        return 1;
    }
    return 0;
}

/***************************************/
/*function that runs the game, it has input for the moves and applies other functions to run the game*/
/*This function has a while loop that keeps the game running until someone loses or gets a tie*/
/*using if function it know which of the players is playing, while Whits is player=1, and Black is player=2*/
void startGame()
{
    while(gameOver == 0)/*check game over*/
    {
        /**player 1 (White soldiers)**/
        if(player == W)
        {
            printf("\nThe turn of W, type your move: ");
            if(scanf("%d%d%d%d",&y,&x,&moveToY,&moveToX)!= 4 || checkOutofBound(moveToY,moveToX)== 0)/*check if input is numbers and inside of board*/
            {
                printf("\nInput Error!");
                return;
            }

            else
            {
                if(checkEmpty(moveToY,moveToX) == 2 )/*check the player chose an empty block*/
                {
                    if ((*(*(board+y)+ x) == 'W'))/*check if there is a white soldier on the coordinate*/
                    {
                        if(moveToY == y+1 && (moveToX == x+1 || moveToX == x-1))/*if player wants to move one block*/
                        {
                            movePlayer(y,x,moveToY,moveToX,W);/*function to move soldier*/
                            checkQueen(moveToY,moveToX,player);/*check if need to upgrade soldier to queen*/
                            printBoard();
                            gameOver = checkWin();
                        }
                        else
                        {
                            if(moveToY == y+2 && (moveToX == x+2 || moveToX == x-2))/*if player wants to move two blocks only possible if he wants to eat an enemy*/
                            {
                                if (checkDiagonalEnemy(y,x,moveToY,moveToX,player) == -1)/*check if there is an enemy in the way*/
                                {
                                    printf("\nThis move is not possible!");
                                }
                                else
                                {

                                    movePlayer(y,x,moveToY,moveToX,W);/*function to move soldier*/
                                    checkQueen(moveToY,moveToX,player);/*check if need to upgrade soldier to queen*/
                                    printBoard();
                                    gameOver = checkWin();
                                }
                            }
                            else
                            {
                                printf("\nThis move is not possible!");
                            }
                        }
                    }
                    else
                    {
                        if((*(*(board+y)+ x) == 'Q'))/*check if there is a white queen on the coordinate*/
                        {
                            /*The next "if" checks that the input is correct (in a diagonal line) and goes to checkDiagonalEnemy to see if the move is possible to make*/
                            if(checkDiagonal(y,x,moveToY,moveToX) == 2 && checkDiagonalEnemy(y,x,moveToY,moveToX,player) != -1)
                            {
                                movePlayer(y,x,moveToY,moveToX,Q);/*function to move soldier*/
                                printBoard();
                                gameOver = checkWin();

                            }
                            else
                            {
                                printf("\nThis move is not possible!");
                            }
                        }
                        else
                        {
                            printf("\nThis move is not possible!");
                        }
                    }
                }
                else
                {
                    printf("\nThis move is not possible!");
                }
            }
            flagEnemy = 0;
            player = B;
        }
        /**player 2 (Black soldiers)**/
        if (player == B)
        {
            printf("\nThe turn of B, type your move: ");
            if(scanf("%d%d%d%d",&y,&x,&moveToY,&moveToX)!= 4 || checkOutofBound(moveToY,moveToX) == 0)/*check if input is numbers and inside of board*/
            {
                printf("\nInput Error!");
                return;
            }
            else
            {
                if(checkEmpty(moveToY,moveToX) == 2)/*check the player chose an empty block*/
                {
                    if(*(*(board+y)+ x) == 'B')/*check if there is a black soldier on the coordinate*/
                    {
                        if(moveToY == y-1 && (moveToX == x+1 || moveToX == x-1))/*if player wants to move one block*/
                        {
                            movePlayer(y,x,moveToY,moveToX,B);/*function to move soldier*/
                            checkQueen(moveToY,moveToX,player);/*check if need to upgrade soldier to queen*/
                            printBoard();
                            gameOver = checkWin();
                        }
                        else
                        {
                            if(moveToY == y-2 && (moveToX == x+2 || moveToX == x-2))/*if player wants to move two blocks only possible if he wants to eat an enemy*/
                            {
                                if (checkDiagonalEnemy(y,x,moveToY,moveToX,player) == -1)/*check if there is an enemy in the way*/
                                {
                                    printBoard();
                                }
                                else
                                {
                                    movePlayer(y,x,moveToY,moveToX,B);/*function to move soldier*/
                                    checkQueen(moveToY,moveToX,player);/*check if need to upgrade soldier to queen*/
                                    printBoard();
                                    gameOver = checkWin();

                                }
                            }
                            else
                            {
                                printf("\nThis move is not possible!");
                            }
                        }

                    }
                    else
                    {
                        if(*(*(board+y)+ x) == 'q')/*check if there is a black queen on the coordinate*/

                        {
                            /*the next "if" checks that the input is correct (in a diagonal line) and goes to checkDiagonalEnemy to see if the move is possible to make*/
                            if(checkDiagonal(y,x,moveToY,moveToX) == 2 && checkDiagonalEnemy(y,x,moveToY,moveToX,player) != -1)
                            {
                                movePlayer(y,x,moveToY,moveToX,q);/*function to move soldier*/
                                printBoard();
                                gameOver = checkWin();
                            }
                            else
                            {
                                printf("\nThis move is not possible!");
                            }
                        }

                        else
                        {
                            printf("\nThis move is not possible!");
                        }
                    }
                }
                else
                {
                    printf("\nThis move is not possible!");
                }
            }
            flagEnemy = 0;
            player = W;
        }
        /***********Check if game over*************/
        if(gameOver == 1)/*white win*/
        {
            printf("\nThe winner is: WHITE!");
        }
        if(gameOver == 2)/*black win*/
        {
            printf("\nThe winner is: BLACK!");

        }
        if(gameOver == 3)/*tie*/
        {
            printf("\nThere is a tie!");
        }
    }
    return;
}

/***************************************/
/*check if there is an enemy in the way and eat it*/
/*The way it works is that using recursion the functions checks all the steps between the soldier and the destination, diagonally, and if possible eats the enemy soldiers on the way*/
/*every recursion takes the pointers one diagnosed block back from the destination until it gets to the original soldier */
/*if there is an enemy on the diagonal line of the soldier it will remove it (only queen)*/
int checkDiagonalEnemy(int y,int x,int moveToY,int moveToX,int player) /*returns -1 and prints a message if the move is impossible*/
{
    char playerColor, playerQueen;
    /*check soldier color*/
    if(player == W)/*white*/
    {
        playerColor = 'W';
        playerQueen = 'Q';

    }
    else/*black*/
    {
        playerColor = 'B';
        playerQueen = 'q';
    }

    if(checkOutofBound(moveToY,moveToX) !=2 || moveToY == y || moveToX == x)/*exit the function*/
    {
        return flagEnemy;
    }
    else
    {
        if(*(*(board+moveToY)+moveToX) == playerColor)/*check if the block doesn't have a friendly soldier*/
        {

            flagEnemy =-1;
            return flagEnemy;
        }
        if(*(*(board+moveToY)+moveToX) != playerColor && *(*(board+moveToY)+moveToX) != playerQueen)/*check if any enemy soldier on block */
        {
            if(x>moveToX)/*going left*/
            {
                if(y>moveToY)/*going up the board*/
                {
                    if(*(*(board+moveToY)+moveToX) == *(*(board+(moveToY+1))+ (moveToX+1))&& *(*(board+moveToY)+moveToX) != '_')/*check if two enemies one after the other blocking and if the block is not empty*/
                    {
                        printf("\ntest2");

                        printf("\nThis move is not possible!");
                        flagEnemy =-1;
                        return flagEnemy;
                    }
                    else
                    {

                        *(*(board + moveToY)+ moveToX) = '_';/*eat the enemy in the coordinate*/
                        return checkDiagonalEnemy(y,x,moveToY+1,moveToX+1,player);/*move recursion to the next step */
                    }
                }
                else/*going down the board*/
                {
                    if(*(*(board+(moveToY))+(moveToX)) == *(*(board+(moveToY-1))+ (moveToX+1)) && *(*(board+moveToY)+moveToX) != '_' )/*check if two enemies one after the other blocking and if the block is not empty*/
                    {

                        printf("\nThis move is not possible!");
                        flagEnemy =-1;
                        return flagEnemy;
                    }
                    else
                    {

                        *(*(board + moveToY)+ moveToX)='_';/*eat the enemy in the coordinate*/
                        return checkDiagonalEnemy(y,x,moveToY-1,moveToX+1,player);/*move recursion to the next step */
                    }
                }
            }
            else/*going right*/
            {
                if(y>moveToY)/*going up the board*/
                {
                    if(*(*(board+moveToY)+moveToX) == *(*(board+(moveToY+1))+(moveToX-1))&& *(*(board+moveToY)+moveToX) != '_')/*check if two enemies one after the other blocking and if the block is not empty*/
                    {

                        printf("\nThis move is not possible!");
                        flagEnemy =-1;
                        return flagEnemy;
                    }
                    else
                    {

                        *(*(board + moveToY)+ moveToX)='_';/*eat the enemy in the coordinate*/
                        return checkDiagonalEnemy(y,x,moveToY+1,moveToX-1,player);/*move recursion to the next step */
                    }
                }
                else/*going down the board*/
                {
                    if(*(*(board+moveToY)+moveToX) == *(*(board+(moveToY-1))+(moveToX-1))&& *(*(board+moveToY)+moveToX) != '_')/*check if two enemies one after the other blocking and if the block is not empty*/
                    {
                        printf("\nThis move is not possible!");
                        flagEnemy =-1;
                        return flagEnemy;
                    }
                    else
                    {

                        *(*(board + moveToY)+ moveToX) = '_';/*eat the enemy in the coordinate*/
                        return checkDiagonalEnemy(y,x,moveToY-1,moveToX-1,player);/*move recursion to the next step */
                    }
                }
            }
        }
        else
        {
            if(*(*(board + moveToY)+ moveToX) == '_')/*if the block is empty continue the recursion*/
            {
                if(x>moveToX)/*going left*/
                {
                    if(y>moveToY)/*going down the board*/
                    {

                        return checkDiagonalEnemy(y,x,moveToY-1,moveToX+1,player);/*move recursion to the next step */
                    }
                    else/*going up the board*/
                    {

                        return checkDiagonalEnemy(y,x,moveToY+1,moveToX+1,player);/*move recursion to the next step */
                    }
                }
                else/*going right*/
                {
                    if(y>moveToY)/*going down the board*/
                    {

                        return checkDiagonalEnemy(y,x,moveToY-1,moveToX-1,player);/*move recursion to the next step */
                    }
                    else/*going up the board*/
                    {
                        return checkDiagonalEnemy(y,x,moveToY+1,moveToX-1,player);/*move recursion to the next step */
                    }
                }

            }
        }
    }
}

/***************************************/
/*this function moves a soldier to it's required coordinates */
void movePlayer(int y,int x,int moveToY,int moveToX,int piece)
{
    switch(piece)
    {
    case 1:/*white soldier*/
        playerColor = 'W';

        break;
    case 2:/*black soldier*/
        playerColor = 'B';

        break;
    case 3:/*white queen*/
        playerColor = 'Q';

        break;
    case 4:/*black queen*/
        playerColor = 'q';

        break;
    }
    (*(*(board+y)+ x))='_';/*clean the original coordinate*/
    (*(*(board+moveToY)+ moveToX))= playerColor ;/*move the soldier to the given coordinate*/
}

/***************************************/
/*function to check if the movement is a diagonal*/
int checkDiagonal(int y,int x,int moveToY,int moveToX)
{
    if(abs(moveToY-y)==abs(moveToX-x))/*check if the movement is a diagonal using abs function because I only need to check the both values in a positive*/
    {
        return 2;
    }
    else
    {
        return -1;
    }
}

/***************************************/
/*check if the player moved to a block that will turn soldier into queen*/
void checkQueen(int moveToY,int moveToX, int player)
{
    if(player == W)/*white player*/
    {
        if(moveToY == brdSize-1)/*check if white soldier reach the end of the board*/
        {
            (*(*(board+moveToY)+ moveToX)) = 'Q';/*upgrade white soldier to queen*/
        }
        else
        {
            return;
        }
    }
    else/*black player*/
    {
        if(moveToY == 0)/*check if black soldier reach the end of the board*/
        {
            (*(*(board+moveToY)+ moveToX)) = 'q';/*upgrade black soldier to queen*/
        }
        else
        {
            return;
        }
    }
}


/***************************************/
/*check if the move is inside the board*/
int checkOutofBound(int moveToY,int moveToX)
{
    if(moveToY >= 0 && moveToX >= 0 && moveToY < brdSize && moveToX < brdSize)/*move is in bounds of the board*/
    {
        return 2;
    }
    else
    {

        return 0;
    }
}
/***************************************/
/*check if the block is empty*/
int checkEmpty(int moveToY,int moveToX)
{
    if(*(*(board+moveToY)+ moveToX) == '_')
    {
        return 2;
    }
    else
    {
        return -1;
    }

}

/***************************************/
/*check if one of the players doesn't have any soldiers left*/
/*I used two for loops to run on every block on the matrix and count how many soldier each player got*/
/*In this function I also used checkMovement function to check if the soldier has no option to move*/
int checkWin()/*return 0 if no winner, 2 if black wins, 1 if white wins, 3 if tie*/
{
    wCount = 0;
    bCount = 0;
    blokdW= -1;
    blokdB = -1;
    /*two loops to count number of soldiers left for each player*/
    for(i=0; i<brdSize; i++)
    {
        for(j=0; j<brdSize; j++)
        {
            if((*(*(board + i)+j)) == 'W' || (*(*(board + i)+j)) == 'Q')
            {
                if(checkMovement(j,i,W)==2)/*sends coordinate checkMovement to if checkMovement returns 2 soldier is not stuck*/
                {
                    wCount++;/*number of movable white soldiers*/
                }
            }
            if((*(*(board + i)+j)) == 'B'|| (*(*(board + i)+j)) == 'q')
            {
                if(checkMovement(j,i,B)==2)/*sends coordinate checkMovement to if checkMovement returns 2 soldier is not stuck*/
                {
                    bCount++;/*number of movable black soldiers*/
                }
            }
        }
    }
    if(bCount == 0 && wCount == 0)/*in case of tie*/
    {
        winner = 3;
        return winner;
    }
    if(wCount == 0)/*no more white soldiers, black wins*/
    {
        winner = 2;
        return winner;
    }
    if(bCount == 0)/*no more black soldiers,white wins*/
    {
        winner = 1;
        return winner;
    }
    return winner;
}

/***************************************/
/*check if players soldiers are blocked*/
/*this function checks it the player is stuck, using the coordinates from the checkWin function(When the function checkWin finds a soldier it send it's coordinates here)
this function check placement of soldier and the possible moves he has, if he can't move it returns 1 else 2*/
int checkMovement(int x, int y, int player)
{
    if(player == W)/*white*/
    {
        if(y == brdSize-1)/*Queen move check*/
        {
            /*This "if" check the possible moves of the soldier, by comparing the next move possible moves if checking if the block is empty*/
            if (((*(*(board+(y-1))+(x+1))) != '_') && (*(*(board+(y-1))+(x-1))) != '_'
                    && ((*(*(board+(y-2))+(x+2))) != '_') && (*(*(board+(y-2))+(x-2))) != '_')
            {
                return 1;/*soldier is stuck*/
            }
            else
            {

                return 2;/*not stuck*/
            }
        }
        else
        {
            if(y == brdSize-2)/*close to border move check*/
            {
                /*This "if" check the possible moves of the soldier, by comparing the next move possible moves if checking if the block is empty*/
                if(((*(*(board+(y+1))+(x+1))) != '_') && (*(*(board+(y+1))+(x-1))) != '_')
                {
                    return 1;/*soldier is stuck*/
                }
                else
                {

                    return 2;/*not stuck*/
                }
            }
            else
            {
                /*This "if" check the possible moves of the soldier, by comparing the next move possible moves if checking if the block is empty*/
                if ( ((*(*(board+(y+1))+(x+1))) != '_') && (*(*(board+(y+1))+(x-1))) != '_'
                        &&  ((*(*(board+(y+2))+(x+2))) != '_') && (*(*(board+(y+2))+(x-2))) != '_')
                {

                    return 1;/*soldier is stuck*/
                }
                else
                {

                    return 2;/*not stuck*/
                }
            }
        }


    }
    else/*black*/
    {
        if(y == 0)/*queen move check*/
        {
            /*This "if" check the possible moves of the soldier, by comparing the next move possible moves if checking if the block is empty*/
            if (checkOutofBound(y+1,x+1) == 2 && checkOutofBound(y+1,x-1) == 2 && ((*(*(board+(y+1))+(x+1))) != '_') && (*(*(board+(y+1))+(x-1))) != '_'
                    && checkOutofBound(y+2,x+2) == 2 && checkOutofBound(y+2,x-2) == 2 && ((*(*(board+(y+2))+(x+2))) != '_') && (*(*(board+(y+2))+(x-2))) != '_')
            {

                return 1;/*soldier is stuck*/
            }
            else
            {

                return 2;/*not stuck*/

            }
        }
        else
        {
            if(y == 1)/*close to border move check*/
            {
                /*This "if" check the possible moves of the soldier, by comparing the next move possible moves if checking if the block is empty*/
                if (checkOutofBound(y+1,x+1) == 2 && checkOutofBound(y+1,x-1) == 2 && ((*(*(board+(y+1))+(x+1))) != '_') && (*(*(board+(y+1))+(x-1))) != '_')
                {

                    return 1;/*soldier is stuck*/
                }
                else
                {

                    return 2;/*not stuck*/

                }
            }
            /*This "if" check the possible moves of the soldier, by comparing the next move possible moves if checking if the block is empty*/
            else if (checkOutofBound(y-1,x+1) == 2 && checkOutofBound(y-1,x-1) == 2 && ((*(*(board+(y-1))+(x+1))) != '_') && (*(*(board+(y-1))+(x-1))) != '_'
                     && checkOutofBound(y+2,x+2) == 2 && checkOutofBound(y+2,x-2) == 2 && ((*(*(board+(y-2))+(x+2))) != '_') && (*(*(board+(y-2))+(x-2))) != '_')
            {

                return 1;/*soldier is stuck*/
            }
            else
            {

                return 2;/*not stuck*/

            }
        }
    }

}

/***************************************/
/*function to free allucated memory*/
void freeBoard()
{
    int i=0;
    while(i<brdSize)
    {
        free(*(board+i));
        i++;
    }
    free(board);
    return;
}

/***************************************/
/*function to allocate memory for the matrix and build the board */
/*building the board using modulo function  to put the soldiers on the right place using the logic that on each row the soldiers are or even blocks or odd blocks etc'*/
void allocateBoard(int brdSizeX, int brdSizeY)
{
    brdSize = brdSizeY;
    board = (char**)malloc(brdSize*sizeof(char*));
    if(board==NULL)
    {
        printf("Allocation failed\n");
        return;
    }
    for (i=0 ; i < brdSize ; i++)
    {
        *(board+i) = (char*)malloc(brdSize*sizeof(char*));
        if(*(board+i)==NULL)
        {
            printf("Allocation failed\n");
            return;
        }
    }
    /***********8x8 board************/
    if(brdSize == 8)/*8x8 board*/
    {
        for(i=0; i<brdSize; i++)
        {
            for(j=0; j<brdSize; j++)
            {
                if(i<3)
                {
                    if(i%2==0)
                    {
                        if(j%2==0)
                        {
                            *(*(board + i)+j)='_';
                        }
                        else
                        {
                            *(*(board + i)+j)='W';
                        }
                    }
                    else
                    {
                        if(j%2==0)
                        {
                            *(*(board + i)+j)='W';
                        }
                        else
                        {
                            *(*(board + i)+j)='_';
                        }
                    }

                }
                if(i>=3 && i<=4)
                {
                    *(*(board + i)+j)='_';
                }
                if(i>4)
                {
                    if(i%2==0)
                    {
                        if(j%2==0)
                        {
                            *(*(board + i)+j)='_';
                        }
                        else
                        {
                            *(*(board + i)+j)='B';
                        }
                    }
                    else
                    {
                        if(j%2==0)
                        {
                            *(*(board + i)+j)='B';
                        }
                        else
                        {
                            *(*(board + i)+j)='_';
                        }
                    }
                }
            }
        }
    }
    /***********10x10 board************/
    if(brdSize == 10)/*10x10 board*/
    {
        for(i=0; i<brdSize; i++)
        {
            for(j=0; j<brdSize; j++)
            {
                if(i<4)
                {
                    if(i%2==0)
                    {
                        if(j%2==0)
                        {
                            *(*(board + i)+j)='_';
                        }
                        else
                        {
                            *(*(board + i)+j)='W';
                        }
                    }
                    else
                    {
                        if(j%2==0)
                        {
                            *(*(board + i)+j)='W';
                        }
                        else
                        {
                            *(*(board + i)+j)='_';
                        }
                    }

                }
                if(i>=4 && i<=5)
                {
                    *(*(board + i)+j)='_';
                }
                if(i>5)
                {
                    if(i%2==0)
                    {
                        if(j%2==0)
                        {
                            *(*(board + i)+j)='_';
                        }
                        else
                        {
                            *(*(board + i)+j)='B';
                        }
                    }
                    else
                    {
                        if(j%2==0)
                        {
                            *(*(board + i)+j)='B';
                        }
                        else
                        {
                            *(*(board + i)+j)='_';
                        }
                    }
                }
            }
        }
    }
}

/***************************************/
/*function to print the board*/
void printBoard()
{
    row = '0';
    for(i=0; i<brdSize; i++)
    {
        printf("\n%c ",row);
        row++;
        for(j=0; j<brdSize; j++)
        {
            printf("[%c] ",*(*(board + i)+j));
        }
    }
    return;
}
