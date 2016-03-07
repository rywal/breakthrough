//
//  AI.h
//
//  Makes game move decisions based on different algorithms
//


#include <stdio.h>
#include "State.h"
#include "Game.h"

#ifndef AI_h
#define AI_h

// Holds the difficulty of the current AI
//
//   EASY will implement a semi-random algorithm
//   MEDIUM will implement limited depth min-max algorithm
//   HARD will implement alpha-beta pruning algorithm
enum DIFFICULTY { EASY, MEDIUM, HARD };

class Game;

class AI {
    
private:
    
    DIFFICULTY difficulty_level;
    
public:
    
    AI();
    AI(DIFFICULTY d);
    AI(const AI &ai);
    ~AI();
    
    //  Makes a move based on the game sent to it
    //
    //  Return value is based on ability to make a move(see algorithms)
    bool make_move(Game* game);
    
    //  Uses a random alorithm to find a move with "EASY" difficulty
    //
    //  Returns TRUE  if a move was found and made
    //          FALSE if a move could not be made
    bool choose_random(Game* game);
};

#endif /* AI_h */
