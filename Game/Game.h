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
	
	bool termination_check(){
		
		//Checking for any pieces 
		int end_this=0;
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				if (board[i][j]=='o'){
					end_this=1;
					break;
				}
			}
		}
		if(end_this=0){return false;}
		//if(i==8&&j==8)
		
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				if (board[i][j]=='x'){ 
					end_this=1;
					break;
				}
			}
		}
		if(end_this=0){return false;}

		//Checking for x's on the bottom row
		for(int j=0; j<8; j++){
			if (board[0][j]=='x'){
				end_this=1;
				break;
			}
		}
		if(end_this=0){return false;}
		
		//Checking o's on the top row
		for(int j=0; j<8; j++){
			if (board[7][j]=='o'){
				end_this=1;
				break;
			}
		} 
		if(end_this=0){return false;}
		
	}
    
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
