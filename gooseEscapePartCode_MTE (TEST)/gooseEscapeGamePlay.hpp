/*
Start of file - gooseEscapeGamePlay.hpp
*/



#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
	
// Going further:  Learn how to use an enum for these values
const int EMPTY = 0;
const int SHALL_NOT_PASS = 1;
const int WINNER = 2;
const int FENCE = 3;//added value for where a fence is placed 

//display characters
const int PLAYER_CHAR = int('@');
const int MONSTER_CHAR = int('G');
const int WALL_CHAR = int('o');
const int WIN_CHAR = int('%');
const int FENCE_CHAR = int('+');//character for fences
const int NOTHING_CHAR = int(' ');//empty character

// print the game board function protype
int printGameBoard(int gameWorld[MAX_BOARD_X][MAX_BOARD_Y], ifstream & levels);

/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/

//captured function
bool captured(Actor & player, Actor & monster);

//moving player function
void movePlayer(int key, Actor & player, 
				int gameWorld[MAX_BOARD_X][MAX_BOARD_Y]);

//goose chasing player function
void chase(Actor & player, Actor & monster, Actor & win, 
		   int gameWorld[MAX_BOARD_X][MAX_BOARD_Y]);

//placing electric fences function
int electricFencePlacement(int gameWorld[MAX_BOARD_X][MAX_BOARD_Y], 
						   Actor & player);

//placing walls function
int wallPlacement(int gameWorld[MAX_BOARD_X][MAX_BOARD_Y], Actor & player);

//win game function
bool won_game(Actor & player, Actor & win);

/*
Does same thing as captured function, except the
name is better suited for its purpose. 
*/

#endif

/*
End of file - gooseEscapeGamePlay.hpp
*/
