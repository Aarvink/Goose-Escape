#ifndef GOOSE_ESCAPE_ACTORS
#define GOOSE_ESCAPE_ACTORS
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"

class Actor
{
  private:
    int actorChar;      
    int location_x, location_y;

  public:
    Actor()
    {
        actorChar = int('A');
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        put_actor();
    }

    Actor(char initPlayerChar, int x0, int y0)
    {
        change_char(initPlayerChar);
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        update_location(x0,y0);
    }
    
    //new constructor-takes char, gives random poisition
    Actor(char initPlayerChar)
    {
		change_char(initPlayerChar);
    	
    	const int border_dist = 5; //don't want to spawn on border
    	
    	//uses the random position function
		int x0 = rand_pos(MIN_BOARD_X+border_dist, MAX_BOARD_X-border_dist);
    	int y0 = rand_pos(MIN_BOARD_Y+border_dist, MAX_BOARD_Y-border_dist);
    	    	
    	location_x = 0;
    	location_y = 0;
    	
		update_location(x0, y0);
	}
    
    int rand_pos(int min, int max)
	{
		/*Takes random generated number then puts it in the range
		from min to max instead of using a more inefficient do-while
		Learned in previous class. 
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
