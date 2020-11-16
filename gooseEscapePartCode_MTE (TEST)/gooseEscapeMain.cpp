#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

//set up the console.   Don't modify this line!
Console out;

int main()
{
	//Set up the window.  Don't edit these two lines
    terminal_open();
  	terminal_set(SETUP_MESSAGE);

/*
    The code below provides a skeleton of the game play.  You will need to
    write code for setting up the game board, and playing the game itself.
    You can modify the code given as needed.
    
    Call the functions that you have written in the game play file, and that
    you have added to the Actor class.
*/
 	
    //make the player
	Actor player(PLAYER_CHAR, 70,10);  // you probably don't want to start in the same place each time
	
	//make the monster
	Actor monster(MONSTER_CHAR, 70,20);
	
	//make win point
	Actor win(WIN_CHAR, 4,4);
	
    int gameWorld[MAX_BOARD_X][MAX_BOARD_Y];// Declare the array that will hold the game board "map"
  	
/*
    Initiallize locations in the game board to have game features.  What if you
    have man things to add to the game board?  Should you use a loop?  Does it
    make sense to store this information in a file?  Should this code be a
    function as well?
*/
    gameWorld[1][1] = SHALL_NOT_PASS;
    gameWorld[4][4] = WINNER;
  	
    // Call the function to print the game board
  	
	// Printing the instructions
    out.writeLine("Escape the Goose! " + monster.get_location_string());
	out.writeLine("Use the arrow keys to move");
	out.writeLine("If the goose catches you, you lose!");
	out.writeLine("Be careful! Sometimes the goose can jump through walls!");

/*
    This is the main game loop.  It continues to let the player give input
    as long as they do not press escape or close, they are not captured by
    the goose, and they didn't reach the win tile
*/
/*
    All key presses start with "TK_" then the character.  So "TK_A" is the "a"
    key being pressed.
*/
    int keyEntered = TK_A;  // can be any valid value that is not ESCAPE or CLOSE
    
    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
        	&& !captured(player,monster) && !(player.get_x() == 4 
         	&& player.get_y() == 4))
	{
	    // get player key press
	    keyEntered = terminal_read();

        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
        {
            // move the player, you can modify this function
    	    movePlayer(keyEntered,player, gameWorld/* game board array and maybe other parameters*/);

            // call the goose's chase function
            chase(player, monster, gameWorld);

            // call other functions to do stuff?	    
        }
  	}

    if (keyEntered != TK_CLOSE)
    {
      	//once we're out of the loop, the game is over
        out.writeLine("Game has ended");
    
        // output why:  did the goose get us, or did we get to the win location?
        // Outputs whether the player reached the win point or was captured
		if(captured(player,monster))
		{
			out.writeLine("You were CAPTURED!");
		}
		else if(player.get_x() == 4 && player.get_y() == 4)
		{
			out.writeLine("You WIN!");
		}
    	// Wait until user closes the window
        while (terminal_read() != TK_CLOSE);
    }

	//game is done, close it  
    terminal_close();
}
