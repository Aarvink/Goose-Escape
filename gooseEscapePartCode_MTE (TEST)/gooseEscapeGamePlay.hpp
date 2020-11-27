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
const int FENCE = 3;
//display characters
const int PLAYER_CHAR = int('@');
const int MONSTER_CHAR = int('G');
const int WALL_CHAR = int('o');
const int WIN_CHAR = int('%');
const int FENCE_CHAR = int('+');
const int NOTHING_CHAR = int(' ');
const int 

// print the game board function protype
int printGameBoard(int gameWorld[MAX_BOARD_X][MAX_BOARD_Y], ifstream & levels);

/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/
bool captured(Actor & player, Actor & monster);

void movePlayer(int key, Actor & player, 

int gameWorld[MAX_BOARD_X][MAX_BOARD_Y]);

//added win to the chase, so that goose will not be able to move over it. 
void chase(Actor & player, Actor & monster, Actor & win, 
int gameWorld[MAX_BOARD_X][MAX_BOARD_Y]);

int electricFencePlacement(int gameWorld[MAX_BOARD_X][MAX_BOARD_Y], Actor & player);


/*
Does same thing as captured function, except the
name is better suited for its purpose. 
*/
bool won_game(Actor & player, Actor & win, ifstream & winScreen);


#endif

/*
End of file - gooseEscapeGamePlay.hpp
*/
