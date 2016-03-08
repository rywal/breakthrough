//
//  AI.h
//
//  Makes game move decisions based on different algorithms
//


#ifndef AI_h
#define AI_h

#include <stdio.h>
#include "globals.h"
#include "Game.h"

class Game;
class State;

using namespace std;

class AI {
    
private:
    
    DIFFICULTY difficulty_level;
    
public:
    
    AI();
    AI(DIFFICULTY d);
    AI(const AI &ai);
    ~AI();
    
    void set_difficulty(DIFFICULTY d) { difficulty_level = d; }
    
    //  Makes a move based on the game sent to it
    //
    //  Return value is based on ability to make a move(see algorithms)
    bool make_move(Game* game);
    
    //  Uses a random alorithm to find a move with "EASY" difficulty
    //
    //  Returns TRUE  if a move was found and made
    //          FALSE if a move could not be made
    bool choose_random(Game* game);
    
    //  Find all moves that can be made with a state
    vector< pair<string, DIRECTION> > possible_moves(State state);
};

#endif /* AI_h */
