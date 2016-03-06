//
//  State.h
//  
//  Represents the playing board at some point in time
//

#ifndef State_h
#define State_h

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class State {
    
private:
    
    //  The board is an 8x8 playing board
    //  Rows are indexed 1-8, (BOTTOM to top)
    //  Columns are indexed A-H (Left to right)
    //
    //  Each spot on the board is represented with a char
    //     White = 'o'
    //     Black = 'x'
    //     Empty = '_'
    //
    std::vector< std::vector< char > > board;
    
    
    //  Holds the number of moves taken to get to the current state
    int num_moves;
    
    
    //  Boolean to hold current player
    //
    //  TRUE if current player is person
    //  FALSE if current player is opponent(could be AI or human)
    bool person_is_player;
    
    //  Status of game
    //
<<<<<<< HEAD
    //  -1 for unfinished game
=======
    //  0 for unfinished game
>>>>>>> 9fcc59a... fixed some minor changes
    //  1 for win (person_is_player holds the current winner)
    bool status;
    
public:
    
    //  Default Constructor
    State();
    
    //  Copy Constructor
    State(State* s);

    //  Destructor
    ~State(){}
    	
	vector<vector<char> > get_board();  
	int get_num_moves();
	int get_status();
	void set_status(bool s);  
	void set_board(int i, int j, char a);
	bool get_turn();
	void set_turn(bool turn);
	void switch_turn();
};


#endif /* State_h */
