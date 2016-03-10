//
//  Game.h
//
//  Handles game mechanics and stores states
//

#ifndef Game_h
#define Game_h

#include <stdio.h>
#include "globals.h"
#include "State.h"
#include "AI.h"

class AI;

class Game {

private:
    
    //  Vector of all previous game states
    //
    //  This exists to easily allow reverting to a previous state, via an undo command
    std::vector< State > previous_states;
	
    //Display Toggle
    bool display;
    bool output_to_socket;
    int socketfd;
    
    AI *ai;
    
public:
    
    //  Holds the current state of the game
    State current_state;
    
    // Holds the current type of game
    GAMETYPE game_type;
    
    // Constructors and Destructor
    Game();
    Game(const Game &g);
    Game(int newsockfd);
    ~Game(){}
    
    void set_game_type(GAMETYPE g, DIFFICULTY d);
	bool valid_move(int row, char column, DIRECTION d);
    void display_board();
    bool termination_check();
    bool game_over();
    string who_won();
	int game_status(State);
	void save_state();
	void undo();
	void undo_two_turns();
	void display_toggle();
	void white_v();
	void black_v();
	State update(char column, int row, DIRECTION d);
    
};

#endif /* Game_h */
