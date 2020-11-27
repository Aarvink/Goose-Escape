/*
Start of file - gooseEscapeActors.hpp
*/

#ifndef GOOSE_ESCAPE_ACTORS
#define GOOSE_ESCAPE_ACTORS
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"

/*
    Modify this class to contain more characteristics of the "actor".  Add
    functions that will be useful for playing the game that are specific to
    the Actor.
    
    Feel free to add additional Classes to your program.
*/

/* 
    Going further:  Learn the other syntax for implementing a class that is
    more appropriate for working with multiple files, and improve the class code.
*/

class Actor
{
  private:
    int actorChar;      
    int location_x, location_y;
    int lives; //the new data member

  public:
    Actor()
    {
    	lives = 3;
        actorChar = int('A');
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        put_actor();
    }

    Actor(char initPlayerChar, int x0, int y0)
    {
    	lives = 3;
        change_char(initPlayerChar);
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        update_location(x0,y0);
    }
    
    //new constructor-creates actor with random position
    //also can input number of lives actor has
    Actor(char initPlayerChar, int given_lives)
    {
    	lives = given_lives;
    	
		change_char(initPlayerChar);
    	
    	const int border_dist = 5;
    	
    	//assigns a random position to the actor
		int x0 = rand_pos(MIN_BOARD_X+border_dist, MAX_BOARD_X-border_dist);
    	int y0 = rand_pos(MIN_BOARD_Y+border_dist, MAX_BOARD_Y-border_dist);
    	    	
    	location_x = 0;
    	location_y = 0;
    	
		update_location(x0, y0);
	}
	
	//new constructor - creates actor with random position
	Actor (char initPlayerChar){
		
		const int DEFAULT_LIVES = 3;
		lives = DEFAULT_LIVES;
    	
		change_char(initPlayerChar);
    	
    	const int border_dist = 5;
    	
    	//assigns a random position to the actor
		int x0 = rand_pos(MIN_BOARD_X+border_dist, MAX_BOARD_X-border_dist);
    	int y0 = rand_pos(MIN_BOARD_Y+border_dist, MAX_BOARD_Y-border_dist);
    	    	
    	location_x = 0;
    	location_y = 0;
    	
		update_location(x0, y0);
	}
	
	//new function
	//if the actor has lives, this will be true
	int lives_left() const
	{
		if(lives > 0)
			return lives;
		else
			return 0;
	}
    
    //new function
    //call this when the actor is caught
    void caught()
	{
		//makes it so that the lives update each time
		for(int iter = 0; iter < lives; iter++)
    	{
    		terminal_put(iter, MAX_BOARD_Y, ' ');
    		terminal_refresh();
		}
		
		//reduces the lives by one each time
    	lives -= 1;
    	
    	//following places the player in a random position
    	const int border_dist = 5;
    	
    	int x0 = rand_pos(MIN_BOARD_X+border_dist, MAX_BOARD_X-border_dist);
    	int y0 = rand_pos(MIN_BOARD_Y+border_dist, MAX_BOARD_Y-border_dist);
    	    	
    	location_x = 0;
    	location_y = 0;
    	
		update_location(x0, y0);
    	
	}
    
    //new function
    //returns a random number between a range
    int rand_pos(int min, int max) const
	{
		/*
		returns a value between max and min without using do-while to \
		find valid position
		*/
		return rand()%max + min-1;
	}
    
    int get_x() const
    {
        return location_x;
    }
    
    int get_y() const
    {
        return location_y;
    }
    
    string get_location_string() const
    {
        char buffer[80];
        itoa(location_x,buffer,10);
        string formatted_location = "(" + string(buffer) + ",";
        itoa(location_y,buffer,10);
        formatted_location += string(buffer) + ")";
        return formatted_location;
    }
    
    //new function
    //displays lives on the bottom left corner
    void display_lives()
    {
    	//the heart is a ^
		const int HEART = int('^');
		for(int iter = 0; iter < lives; iter++)
		{
			terminal_put(iter, MAX_BOARD_Y, HEART);
        	terminal_refresh();
		}
	}
    
    void change_char(char new_actor_char)
    {
        actorChar = min(int('~'),max(int(new_actor_char),int(' ')));
    }

    bool can_move(int delta_x, int delta_y) const
    {
        int new_x = location_x + delta_x;
        int new_y = location_y + delta_y;

        return new_x >= MIN_BOARD_X && new_x <= MAX_BOARD_X
          && new_y >= MIN_BOARD_Y && new_y <= MAX_BOARD_Y;
    }

    void update_location(int delta_x, int delta_y)
    {
        if (can_move(delta_x, delta_y))
        {
            terminal_clear_area(location_x, location_y, 1, 1);
            location_x += delta_x;
            location_y += delta_y;
            put_actor();
        }
    }
    
    void put_actor() const
    {
        terminal_put(location_x, location_y, actorChar);
        terminal_refresh();
    }
    
};
#endif

/*
End of file - gooseEscapeActors.hpp
*/
