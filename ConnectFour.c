/********DO NOT MODIFY THIS SECTION************
 * 
 * EECS 22 : Advanced C Programming
 * Fall 2018, Prof. Quoc-Viet Dang
 *  
 * HW1  : ConnectFour game
 * Template file : ConnectFour.c
 * 
 * Created on September 26, 2018, 12:06 AM by Ali Nickparsa <anickpar@uci.edu>
 */
/**********************************************

// Enter your name, last name and UCInet ID below://
 *
 *  ******************************
 *  First Name : Richard
 *  Last Name: Magdaluyo
 *  UCInet ID: 45993793
 *
 */

#include <stdio.h>
#include <stdbool.h>

/*Declare your function definitions in the section below*/
/*Mandatory Options : 1-DisplayMenu 2- RegularGame 3-AnvilGame 4-CheckConnect 5-
 * PrintBoard*/
/*You may add other functions if needed*/
/*********************************************************/


/*********************************************************/

/*Declare your global variables below (if any)*/
/**************************************************/
int turn = 0, inRow = 0, inCol = 0;
int playerOneAnvil = 1, playerTwoAnvil = 1;
char board[6][7];
char playerChar;
char gameMode;
bool win = false; 

/**************************************************/
void printBoard(){
    for(int j=0; j<7; j++)
        printf("%d ", j);
    printf("\n");    
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            printf("%c ",  board[i][j]);    
        }
        printf("\n");
    }
}

void dropAnvil(char playerChar){
    printf("Please select a column (0 to 6) to clear.\n");
    scanf("%d", &inCol);

    int temp = 0;
    while(temp < 5){
        //checks if there's another anvil placed beneath
        if(board[temp+1][inCol] == 'A'){
            board[temp][inCol] = 'A';
            return;
        }

        board[temp][inCol] = '_';
        temp++;
    }

    board[temp][inCol] = 'A';

}
  
/*    if(playerOneAnvil != 1 || playerTwoAnvil != 1){
       printf("Sorry, you have already used your anvil. A regular piece will be placed instead.\n");
       playerMoveAnvil(turn);
       return;
   }
 
   if(playerChar == 'x')
       playerTwoAnvil = 0;
   else if(playerChar == 'o')
       playerOneAnvil = 0;
   

   printf("Please select a column (0 to 6) to clear.\n");
   scanf("%d", &inCol); 
   
   int temp = 0;
   while(temp < 5){
       //checks if there's another anvil placed beneath
       if(board[temp+1][inCol] == 'A'){
           board[temp][inCol] = 'A';
           return;
       }
       board[temp][inCol] = '_';
       temp++;
   }
   
   board[temp][inCol] = 'A';
}
*/
bool winChecker(){
    //is independent of the last input
    //simply looks at the condition of the entire board
    //after a player's turn
    
    /*left to right check*/
    for(int i=0; i<6; i++)
        for(int j=0; j<3; j++)
            if((board[i][j] != '_') && (board[i][j]) == board[i][j+1] && (board[i][j]) == board[i][j+2] && (board[i][j]) == board[i][j+3])
                win = true;
    
    /*up to down check*/
    for(int i=0; i<3; i++)
        for(int j=0; j<6; j++)
            if((board[i][j] != '_') && (board[i][j]) == board[i+1][j] && (board[i][j]) == board[i+2][j] && (board[i][j]) == board[i+3][j])
                win = true;
    
    /*diagonal (top-left to down-right) check*/
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if((board[i][j] != '_') && (board[i][j]) == board[i+1][j+1] && (board[i][j]) == board[i+2][j+2] && (board[i][j]) == board[i+3][j+3])
                win = true;
    
    /*diagonal (top-right to down-left) check*/
    for(int i=0; i<3; i++)
        for(int j=3; j<6; j++)
            if((board[i][j] != '_') && (board[i][j]) == board[i+1][j-1] && (board[i][j]) == board[i+2][j-2] && (board[i][j]) == board[i+3][j-3])
                win = true;

    return win;
}

int playerMove(int turn){
    if(turn % 2 == 0)
        playerChar = 'o';
    else
        playerChar = 'x';
        
    printf("Please select a column (between 0 and 6)\n");
    scanf("%d", &inCol);

    /*checks for first empty place in selected colum*/
    int inRow = 5;
    while(board[inRow][inCol] != '_'){
        inRow--;
    }
    board[inRow][inCol] = playerChar;
    
    return inRow;
}

int playerMoveAnvil(int turn){
    if(turn % 2 == 0)
        playerChar = 'o';
    else
        playerChar = 'x';
        
    printf("Please select a column (between 0 and 6). Enter '10' to drop your anvil.\n");
    scanf("%d", &inCol);

    if(inCol == 10){
        if(playerChar == 'o')
            playerOneAnvil = 0;
        else
            playerTwoAnvil = 0;

        if((playerOneAnvil == 1) || (playerTwoAnvil == 1))
            dropAnvil(playerChar);
        else{
            printf("Sorry you have already used your anvil. A regular piece will be placed instead.\n");
            playerMoveAnvil(turn); 
        }
    }
    else{ 
        /*checks for first empty place in selected colum*/
        int inRow = 5;
        while(board[inRow][inCol] != '_'){
            inRow--;
        }
        board[inRow][inCol] = playerChar;
    }

    return inRow;
}

void regularGame(){
    printf("Welcome to the regular version of Connect 4!\n");
    
    /*initializes contents of the board*/                
    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            board[i][j] = '_';
    
    printBoard(); 

    /*check for win condition*/
    while((turn < 42) && !winChecker()){
        playerMove(turn);
        turn++;
        printBoard();
    }
    
    /*have to switch from the determiners for x vs o because of do-while loop (turn increased before loop ended)*/
    if(turn == 42){
        printf("It was a tie! Board filled.");
        return;
    }    
    
    if(turn%2 != 0)
        printf("Player 1 (o) won!\n");
    else
        printf("Player 2 (x) won!\n");
}

void anvilGame(){
   printf("Welcome to the Anvil version of Connect 4!\n");

   /*initializes contents of the board*/                
   for(int i=0; i<6; i++)
       for(int j=0; j<7; j++)
           board[i][j] = '_';
    
   printBoard(); 

   /*check for win condition*/
   while(!winChecker()){
       playerMoveAnvil(turn);
       turn++;
       printBoard();
   }
    
   /*have to switch from the determiners for x vs o because of do-while loop (turn increased before loop ended)*/    
   if(turn%2 != 0)
       printf("Player 1 (o) won!\n");
   else
       printf("Player 2 (x) won!\n");
}

/*Colors (you can add or remove from this list*/
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

/*Main function*/
int main(int argc, char** argv) {
    printf("Hello! Please select a game mode! (R) for regular and (A) for Anvil.\n");
    scanf("%c", &gameMode);

    if(gameMode == 'R')
        regularGame();
    else
        anvilGame();
        
    return 0;
}
