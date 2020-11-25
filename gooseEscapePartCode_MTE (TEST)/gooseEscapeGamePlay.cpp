/* 

Begining of file - gooseEscapeGamePlay.cpp

*/

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

extern Console out;
/*
With graphics, screens are given an x,y coordinate system with the origin
in the upper left corner.  So it means the coordinate axes are:
---------------->   x direction
|
|
|
|
|
V

y direction 
*/
	
/*
    Print the game world
    
    The functions should draw characters to present features of the game
    board, e.g. win location, obstacles, power ups
*/

//print the game board function
int printGameBoard(int gameWorld[MAX_BOARD_X][MAX_BOARD_Y], ifstream & levels)
{	
    //create a vertical wall of 10 tiles on the game board
//    for(int count = 0; count < 10; count++)
//    {
//    	gameWorld[40][8 + count] = SHALL_NOT_PASS;
//    	terminal_put(40, 8 + count, WALL_CHAR);
//    	
//	}
	
	string line_in;
	
	int x_pos = 0, y_pos = 0;
		
	for(int newlines = 0; newlines < MAX_BOARD_Y; newlines++)
	{
		x_pos = 0;
		getline(levels, line_in);
		
		if(!(line_in[0] == 0))
		{
			for(int iter_str = 0; iter_str < line_in.size(); iter_str++)
			{
				if(line_in[iter_str] == WALL_CHAR && x_pos < MAX_BOARD_X && y_pos < MAX_BOARD_Y && x_pos > MIN_BOARD_X && y_pos > MIN_BOARD_Y)
				{
					gameWorld[x_pos][y_pos] = SHALL_NOT_PASS;
					terminal_put(x_pos, y_pos, WALL_CHAR);
				}
				x_pos++;
			}
			y_pos++;
		}
	}
	
	terminal_refresh();
}

/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/

//function that allows the goose to capture the player
bool captured(Actor & player, Actor & monster)
{
	
	if((player.get_x() == monster.get_x() 
        && player.get_y() == monster.get_y())){
		if(player.lives_left()){
			player.caught();
			//cout << player.lives_left();
			return 0;
		}else
			return 1;
	}
	
	return 0;
}

/*
    Move the player to a new location based on the user input.  You may want
    to modify this if there are extra controls you want to add.
    
    All key presses start with "TK_" then the character.  So "TK_A" is the a
    key being pressed.
    
    A look-up table might be useful.
    You could decide to learn about switch statements and use them here.
*/
// function that allows the player to move
void movePlayer(int key, Actor & player, int gameWorld[MAX_BOARD_X][MAX_BOARD_Y])
{
	//checks for button pressed
    int yMove = 0, xMove = 0;
    if (key == TK_UP)
        yMove = -1;
    else if (key == TK_DOWN)
        yMove = 1;
    else if (key == TK_LEFT)
        xMove = -1;
    else if (key == TK_RIGHT)
        xMove = 1;
    
    //determines the new location of the player based on the givin input
    int deltax = player.get_x() + xMove;
    int deltay = player.get_y() + yMove;
    
    //checks to see if it is a valid location to move to
    if (player.can_move(xMove, yMove) 
      	&& gameWorld[deltax][deltay] != SHALL_NOT_PASS)
        player.update_location(xMove, yMove);
}

// Function that allows the goose to chase the player 
void chase(Actor & player, Actor & monster, Actor & win, 
			int gameWorld[MAX_BOARD_X][MAX_BOARD_Y])
{
    int yMove = 0, xMove = 0;
    
    int newY = 0, newX = 0;
    
    //checks if the goose's y-coordinate is not the same as the player's
    if(player.get_y() != monster.get_y())
    {
    	//moves either up or down, depending which gets closer to the player
	    if (player.get_y() > monster.get_y())
	        yMove = 1;
	    else if (player.get_y() < monster.get_y())
	        yMove = -1;
	    
	    //checks if the new location to move to is valid
	    int newY = monster.get_y() + yMove;
	    if(monster.can_move(0, yMove) && 
			gameWorld[monster.get_x()][newY] != SHALL_NOT_PASS && 
			!(monster.get_x() == win.get_x() && newY == win.get_y()))
	    	monster.update_location(0, yMove);
	
	}
	//checks if the goose's y-coordinate is not the same as the player's
	if(player.get_x() != monster.get_x())
	{
		//moves either left or right, depending which gets closer to the player
		if (player.get_x() > monster.get_x())
	        xMove = 1;
	    else if (player.get_x() < monster.get_x())
	        xMove = -1;
	    
	    //checks if the new goose location to move to is valid
	    int newX = monster.get_x() + xMove;
	    if(monster.can_move(xMove, 0) && 
			gameWorld[newX][monster.get_y()] != SHALL_NOT_PASS && 
			!(newX == win.get_x() && monster.get_y() == win.get_y()))
	    	monster.update_location(xMove, 0);
	}


}

//function that allows the player to win
bool won_game(Actor & player, Actor & win)
{
	//checks to see if the player's location is the same as the win point
	if(player.get_x() == win.get_x() && player.get_y() == win.get_y())
		return 1;
	else
		return 0;
}

/*
    What other functions do you need to make the game work?  What can you
    add to the basic functionality to make it more fun to play?
*/

/* 

End of file - gooseEscapeGamePlay.cpp

*/
