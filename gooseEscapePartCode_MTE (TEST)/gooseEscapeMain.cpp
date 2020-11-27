/* 

Begining of file - gooseEscapeMain.cpp

*/

#include <BearLibTerminal.h>
#include <cmath>
#include <ctime> //for the random seed
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

//set up the console.   Don't modify this line!
Console out;

int main()
{
	//putting in the random seed-the starting point for random numbers
	srand((unsigned) time(0));

/*
    The code below provides a skeleton of the game play.  You will need to
    write code for setting up the game board, and playing the game itself.
    You can modify the code given as needed.
    
    Call the functions that you have written in the game play file, and that
    you have added to the Actor class.
*/
	const int NUM_LEVELS = 2;
	int player_lives = 3; //to keep track even as levels change
 	
 	//following constructors generate random position
    for(int level_num = 1; level_num <= NUM_LEVELS; level_num++)
	{
		terminal_open();
  		terminal_set(SETUP_MESSAGE);
	  
	  	//make the player
		Actor player(PLAYER_CHAR, player_lives);//start player in a random set of coordinates
			
		//make the monster
		Actor monster(MONSTER_CHAR);//start goose in a random set of coordinates
		
		//make win point
		Actor win(WIN_CHAR);//start the win point in a random set of coordinates
		
		//declare the array that will hold the game board "map"
	    int gameWorld[MAX_BOARD_X][MAX_BOARD_Y] = {EMPTY};
		
		//declare constants to limit amount of fence and walls placed
		const int MAX_FENCE = 2;
		const int MAX_WALL = 1;
		
		//declare variables to limit amount of fence and walls placed
		int totalFence = 0;
		int totalWall = 0;
		
		/*
		the text files for the levels are named
		levelA.txt, where A is 1, 2, 3, etc. 
		Each time the loop goes around, the next level is called
		*/
		//index of thing to be changed
		const int CHANGE_NUM = 5;
		const char CONVERT_ASCII = '0';
		const int FILE_NAME_SIZE = 10;
		//could not use a string as ifstream does not accept a string
		char file_name[] = "level0.txt";
		//this changes the file name at the correct index
		//int+'0' equals the ASCII for the specific number
		file_name[CHANGE_NUM] = level_num+CONVERT_ASCII;
		
	  	ifstream levels(file_name);
	  	
	  	//checks if file is open
	  	if(!levels)
	  	{
	  		cout << "file not opened" << endl;
	  		return EXIT_FAILURE;
		}
	  	
	/*
	    Initiallize locations in the game board to have game features.  What if you
	    have many things to add to the game board?  Should you use a loop?  Does it
	    make sense to store this information in a file?  Should this code be a
	    function as well?
	*/
	  	
	
		// Printing the instructions
	    out.writeLine("Escape the Goose! If won level, close window");
		out.writeLine("Move w/ arrow keys. Lives (^) on bottom left");
		out.writeLine("Caught=lose life. 3 lives. 0 lives=lose");
		out.writeLine("Press Z=electric fence. X=wall");
	
	/*
	    This is the main game loop.  It continues to let the player give input
	    as long as they do not press escape or close, they are not captured by
	    the goose, and they didn't reach the win tile
	*/
	/*
	    All key presses start with "TK_" then the character.  So "TK_A" is the "a"
	    key being pressed.
	*/
	    int keyEntered = TK_A; // can be any valid value that is not ESCAPE or CLOSE
	        
	    // Call the function to print the game board
	  	printGameBoard(gameWorld, levels);
	        
	    //check if player has been captured, won or pressed a certain key
	    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
	        	&& !captured(player,monster) && !won_game(player, win))
		{
			//shows player lives on bottom left
			player.display_lives();
			
		    //get player key press
		    keyEntered = terminal_read();
	
	        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
	        {
	            //call the player's move function
	    	    movePlayer(keyEntered,player, gameWorld); // moves the player
	
	            //call the goose's chase function
	            chase(player, monster, win, gameWorld);// moves the goose	    
	        }
	        
	        //limits the amount of electric fences you can use
	        if(totalFence < 2 && keyEntered == TK_Z)
	        {
	        	totalFence += electricFencePlacement(gameWorld, player);
			}
			
			//limits the number of walls you can use
			if(totalWall < 1 && keyEntered == TK_X)
	        {	
	        	totalWall += wallPlacement(gameWorld, player);
			}
			
	  	}
	
	    if (keyEntered != TK_CLOSE)
        {
            //once we're out of the loop, the game is over
            out.writeLine("Game has ended");

            //outputs whether the player reached the win point or was captured
            if(captured(player,monster))
            {
                out.writeLine("You were CAPTURED!");
            }
            else if(won_game(player, win))
            {
                out.writeLine("You WIN!");
            }

            // Wait until user closes the window
            while (terminal_read() != TK_CLOSE);
        }

        player_lives = player.lives_left();

        //close the file
        levels.close();    

        //game is done, close it  
        terminal_close();
    }
	
}

/* 

End of file - gooseEscapeMain.cpp

*/
