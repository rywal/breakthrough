//
//  Game.cpp
//  
//
//  Created by Ryan Walters on 2/28/16.
//
//

#include "Game.h"

Game::Game(){
}

bool Game::valid_move(char column, int row, DIRECTION d){
		if(current_state.get_turn()){	//I am assuming that the person is always white
			//check if piece is white
			//check if the piece can move d
			//things to consider:
				//if piece is in Column A, piece can't move left
				//if piece is in Column H, piece can't move right
				//if there is a piece in front of it, it can't move forward
		}else {
			//check if piece is black
			//check if the piece can move d
			//things to consider:
				//remember black is moving in the opposite direction
				//if piece is in Column H, piece can't move left
				//if piece is in Column A, piece can't move right
				//if there is a piece in front of it, it can't move forward
		}
}

State Game::update(char column, int row, DIRECTION d){

	if(valid_move(column, row, d)){
		printf("%s", current_state.get_board()[1][2]);
		//temp_board[row][column/* - ascii number for A */]=
		
		 
		
	}
	else {
		printf("That's an invalid move! Try again.\n");
	}
}

int main(){
	Game new_game;
	
}