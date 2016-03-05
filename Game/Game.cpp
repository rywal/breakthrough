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

bool Game::valid_move(int row, char column, DIRECTION d){
		if(current_state.get_turn()){	//I am assuming that the person is always white
			//check if piece is white
			if (current_state.get_board()[row-1][column-'a']!='o') return false;
			//check if the piece can move d
			//things to consider:
				//if piece is in Column A, piece can't move left
			if (column=='a' && d == LEFT) return false;	
				//if piece is in Column H, piece can't move right
			if (column=='h' && d == RIGHT) return false;
				//if there is a piece in front of it, it can't move forward
			if (current_state.get_board()[row][column-'a']!='_') return false;
			return true;
		}else {
			//check if piece is black
			if (current_state.get_board()[row-1][column-'a']!='o') return false;
			//check if the piece can move d
			//things to consider:
				//remember black is moving in the opposite direction
				//if piece is in Column H, piece can't move left
			if (column=='h' && d == LEFT) return false;	
				//if piece is in Column A, piece can't move right
			if (column=='a' && d == RIGHT) return false;	
				//if there is a piece in front of it, it can't move forward
			if (current_state.get_board()[row-2][column-'a']!='_') return false;
			return true;
		}
}

State Game::update(char column, int row, DIRECTION d){
	State temp;
	if(valid_move(row, column, d)){
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
		current_state.switch_turn();
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

/*int main(){
	Game new_game;
	new_game.display_board();
	new_game.update(2, 'b', RIGHT);
	new_game.display_board();
	new_game.update(7, 'b', FWD);
	new_game.display_board();
	new_game.update(2, 'b', RIGHT);
	new_game.display_board();
	new_game.update(2, 'b', RIGHT);
	new_game.display_board();
	new_game.update(2, 'b', RIGHT);
	new_game.display_board();
	
}*/