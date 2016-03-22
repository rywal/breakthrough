//
//  Evaluation.h
//  
//
//  Created by Ryan Walters on 3/22/16.
//
//

#ifndef Evaluation_h
#define Evaluation_h

#include "globals.h"
#include "Game.h"

class Evaluation {
    Game game;
    int current_depth;
    int max_depth;
    pair<string, DIRECTION> best_move;
    
    Evaluation(Game g, int cur_depth, int m_depth);
    long int evaluate(bool max);
    long int find_max();
    long int find_min();
};

#endif /* Evaluation_h */
