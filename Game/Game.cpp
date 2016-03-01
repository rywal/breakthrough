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
			return true;
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

State Game::update(int row, char column, DIRECTION d){
	State temp;
	if(valid_move(column, row, d)){
	current_state.set_board(row-1,column-'a', '_');
		if(current_state.get_turn()){
			if (d==FWD)
				current_state.set_board(row,column-'a', 'o');
			if (d==LEFT)
				current_state.set_board(row,column-'a'-1, 'o');
			if (d==RIGHT)
				current_state.set_board(row,column-'a'+1, 'o');
		} else {
			if (d==FWD)
				current_state.set_board(row-2,column-'a', 'o');
			if (d==LEFT)
				current_state.set_board(row-2,column-'a'+1, 'o');
			if (d==RIGHT)
				current_state.set_board(row-2,column-'a'-1, 'o');
		}
	} else {
		printf("That's an invalid move! Try again.\n");
	}
	return temp;
}

void Game::display_board(){
	cout<<"    ";
	for (char i='A'; i<'I'; i++)
		cout<<" "<<i;
	cout<<'\n';
	for (int i=7; i>-1; i--){
		cout<<"; "<<i+1<<" ";
		for(int j=0; j<8; j++){
			cout<<'|'<<current_state.get_board()[i][j];
		}
		cout<<"|\n";	
	}	
}

int main(){
	Game new_game;
	new_game.display_board();
	new_game.update(2, 'b', RIGHT);
	new_game.display_board();
	
	
}