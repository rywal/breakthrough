//
//  State.h
//  
//  Represents the playing board at some point in time
//

#ifndef State_h
#define State_h

#include <stdio.h>
#include <vector>

class State {
    
private:
    
    //  The board is an 8x8 playing board
    //
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
    //  -1 for unfinished game
    //  0 for draw
    //  1 for win (person_is_player holds the current winner)
    int status;
    
public:
    
    //  Default Constructor
    State();
    
    //  Copy Constructor
    State(State *s);
    
    //  Destructor
    ~State();
    
};

#endif /* State_h */