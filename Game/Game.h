//
//  Game.h
//
//  Handles game mechanics and stores states
//

#ifndef Game_h
#define Game_h

#include <stdio.h>
#include "State.h"

//  Possible moves from each piece
//
//  Here, FORWARD direction is assumed to be the direction a piece can legally advance in
//  Here, LEFT/RIGHT is assumed to be FORWARD one place and LEFT/RIGHT one place
//    LEFT/RIGHT are assumed to be with respect to the game board(Column A will always be "most left", Column H will always be "most right")
enum DIRECTION { LEFT, FWD, RIGHT };

class Game {

private:
    
    //  Holds the current state of the game
    State current_state;
    
    //0 for white, 1 for black;
    
    //  Vector of all previous game states
    //
    //  This exists to easily allow reverting to a previous state, via an undo command
    std::vector< State > previous_states;
    
public:
    
    Game();
    Game(const Game &g);
    ~Game(){}
    
	bool valid_move(int row, char column, DIRECTION d);
    void display_board();
	int game_status(State);
	void save_state();
	void undo();
	void undo_to_person();
	State update(char column, int row, DIRECTION d);
    
};

#endif /* Game_h */
