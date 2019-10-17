
#include <stdio.h>
#include <stdbool.h>

/*Declare your function definitions in the section below*/
/*Mandatory Options : 1-DisplayMenu 2- RegularGame 3-AnvilGame 4-CheckConnect 5-PrintBoard*/
/*You may add other functions if needed*/
/*********************************************************/
void regularGame();
void anvilGame();
bool checkHor(int coordX, int coordY, char board[6][7]); //check for horizontal connection. 
bool checkVer(int coordX, int coordY, char board[6][7]); //check for veritcal connection.
bool checkDiag(int coordX, int coordY, char board[6][7]); //check for diagonal connection
bool checkAll(int coordX, int coordY, char board[6][7]); //check for all connection.
void checkAnvil(int *aturn1, int *aturn2, int *turn, char *anvil, char board[6][7]);
void fullCoord(int coordY, int *turn);
void printColor(char piece); //set and print color for each piece "X" and "O"
void printBoard(char board[6][7]); //print the entire game board.
void checkTurn(int coordX, char player, int *coordY, char board[6][7]); //check and assign coordinate for each piece


/*********************************************************/

/*Declare your global variables below (if any)*/
/**************************************************/
const int row = 6;
const int col = 7;


/**************************************************/

/*Colors (you can add or remove from this list*/
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\x1b[0m"

/*Main function*/
int main(int argc, char** argv) 
{
    	char type; // type of game
	char replay = 'y';
    	
	while (replay == 'y')
	{
    		printf(KYEL "\n        Welcome to Connect 4 Game: EECS 22 HW1\n\n" RESET);
    		printf("1-{R) Regular\n");
    		printf("2-(R) ANVIL Variation\n");
    		printf("Enter 'R' or 'A': ");
    		scanf(" %c", &type);

    		if (type == 'A')
    		{
        		printf("ANVIL mode selected\n");
			anvilGame();
    		}	
    		else if (type == 'R' || type == 'r')
    		{
        		printf("Regular mode selected\n");
			regularGame();
    		}
	
		printf("\n\nPlay Again (y/n): ");
		scanf(" %c", &replay);
	}

    	return 0;
}

void regularGame()
{
 	int coord = 1; //coordinate
    	char *player = "XO"; // game pieces.
    	char  board[row][col];
    	for (int i = 0; i < row; i++) // set a default game board.
		for (int j = 0; j <= col; j++)
 	            	board[i][j] = '-';


    	printf(KRED "\n\n    ****Connect");
    	printf(KBLU "Four**** \n\n" RESET);
    	printBoard(board);

    	bool win = false; //condition for winning the game.
    	int turn = 2; //keeping track of player's turn.
    	int coordY = 0; // coordinate for row in the 2d array
    	while (win == false && turn <44)
    	{
        	 printf("\nPlayer (%c):", player[turn%2]);
        	 printf("\nEnter number coordinate: ");
        	 scanf("%i", &coord);
         	 printf("\n");
	
        	 checkTurn(coord, player[turn%2], &coordY,  board);
        	 fullCoord(coordY, &turn);
         	 printBoard(board);
        	 win = checkAll(coord, coordY, board);
    	}

   	if (turn == 44)//check if the board are full.
        	 printf("\nPlayer (%c) won\n", player[(turn)%2]);
    	else
		 printf("\nPlayer (%c) won\n", player[(turn-1)%2]);
}

void anvilGame()
{
    	int coord = 1; //coordinate
    	char *player = "XO"; // game pieces.
    	char  board[row][col];
    	for (int i = 0; i < row; i++) // set a default game board.
        	for (int j = 0; j <= col; j++)
        	     	board[i][j] = '-';
	

    	printf(KRED "\n\n    ****Connect");
    	printf(KBLU "Four**** \n\n" RESET);
    	printBoard(board);

    	bool win = false; //condition for winning the game.
    	int turn = 2; //keeping track of player's turn.
    	int coordY = 0; // coordinate for row in the 2d array
    	int aturn1 = 0; // turn that player allow anvil in the game.
    	int aturn2 = 0;
    	while (win == false)
    	{
	 	char anvil = 'n'; //default condition, reset at the begining of the loop.
         	printf("\nPlayer (%c):", player[turn%2]);

	 	if (turn % 2 == 0 && aturn1 == 0) // condition that make sure thar each player can only use anvil once per game. 
	 	{
 		 	checkAnvil(&aturn1, &aturn2, &turn, &anvil, board);   
	 	}
       	 	if (turn % 2 == 1 && aturn2 == 0)
	 	{
		 	checkAnvil(&aturn1, &aturn2, &turn, &anvil, board);
	 	}
	 	if (anvil == 'y')
	 	{
		 	printBoard(board);
		 	++turn;
	 	}
	 	else
	 	{
		 	printf("\nEnter number coordinate: ");
  		 	scanf("%i", &coord);	 
		 	checkTurn(coord, player[turn%2], &coordY,  board);
		 	fullCoord(coordY, &turn);	 
        	 	printBoard(board);
        	 	win = checkAll(coord, coordY, board);
	 	}	
	 
     	}
     	printf("\nPlayer (%c) won\n", player[(turn-1)%2]);

}
void printBoard(char board[row][col])
{
    	for (int i = 0; i < row; i++)
    	{
        	for (int j = 0; j < col; j++)
               		printColor(board[i][j]);
        	printf("|");
        	printf("\n-----------------------------\n");
    	}
    	printf("  1   2   3   4   5   6   7\n");
}

void checkTurn(int coordX, char player, int *coordY, char board[row][col])
{
     	for (int i = row - 1; i >= 0; i--)
     	{
         	if (board[i][coordX-1] == '-')
         	{
             		board[i][coordX-1] = player;
             		*coordY = i; //update coordinate Y (row index in 2d array).
             		break; // stop the loop and fill in the empty spot on the board with a piece.
         	}
     	}	
}


bool checkHor(int coordX, int coordY, char board[row][col])
{
	coordX--;

	int check = 0; // check for connection.
	int i = 1;
	int j = 1;
	while (check != 3) // stop the loop and return true when all four pieces is connected.
	{
		if (board[coordY][coordX] == board[coordY][coordX+i]) // compare each piece horizontally.
		{
			++check;
			++i; // update the coordinate of the piece to right of the board.
		}
		else if (board[coordY][coordX] == board[coordY][coordX-j])
		{
			++check;
			++j; // update the coordinate of the piece to the left of the board.
		}
		else
			return false;
	}
	return true;
}

bool checkVer(int coordX, int coordY, char board[row][col]) // same implementation as in checkHor except checking for vertical connection.
{ 
	coordX--;
	
	int check = 0;
	int i = 1;
	while (check != 3)
	{
		if (board[coordY][coordX] == board[coordY+i][coordX]) 
		{
			++check;
			++i;
		}
		else
			return false;
	}
	return true;
}

bool checkDiag(int coordX, int coordY, char board[row][col])
{
	// need to account for all the direction of diagonal connection.(4 direction)
	coordX--;

        int check = 0;
	int check2 = 0;
        int i = 1; 
	int j = 1;
	int g = 1;
	int k = 1;
        while (check != 3 && check2 != 3)
        {
		 // 4 if-else condtion for  all 4 directions.
                if (board[coordY][coordX] == board[coordY-i][coordX+i])
                {
                        ++check;
                        ++i;
                }
                else if (board[coordY][coordX] == board[coordY+j][coordX-j])
                {
                        ++check;
                        ++j;
                }
		else if (board[coordY][coordX] == board[coordY-g][coordX-g])
                {
                       ++check2;
                       ++g;
                }
		else if (board[coordY][coordX] == board[coordY+k][coordX+k])
        	{
                       ++check2;
                       ++k;
                }
                else
                        return false;
        }
        return true;
}

bool checkAll(int coordX, int coordY, char board[row][col])
{
	// return true if either one of the checking conditons is met.
	if (checkHor(coordX, coordY, board) || checkVer(coordX, coordY, board) || checkDiag(coordX, coordY, board))
		return true;
	return false;
}

void checkAnvil(int *aturn1, int *aturn2, int *turn, char *anvil, char board[row][col])
{
	char ask;
	int coordA;

	printf("\nUse Anvil? (y/n): ");
	scanf(" %c", &ask);
	if (ask == 'y')
	{
		printf("Please choose Anvil's coordinate: ");
		scanf("%i", &coordA);		
	
		if (*turn %  2 == 0)
	
			++(*aturn1);
		else
			++(*aturn2);
		
		board[row - 1][coordA - 1] = '@';
                for (int i = row - 2; i > 0; i--)// drop anvil down at the bottom of the stack and empty the rest.
                        board[i][coordA - 1] = '-';

		*anvil = 'y';
	}
} 

void fullCoord(int coordY, int *turn)
{
	if (coordY !=  0)
		++(*turn);
	else
		printf("This coordinate is full. Choose a different coordinate.\n");
}

void printColor(char piece)
{
	if (piece == 'X')
	{
		printf("| ");
		printf(KRED "X " RESET);		
	}
	else if (piece == 'O')
	{
		printf("| ");
		printf(KBLU "O " RESET);
	}
	else if (piece == '@')
	{
		printf("| ");
		printf(KYEL "@ " RESET);
	}
	else if (piece == '-')
	{
		printf("| ");
		printf("- ");
	}
}
