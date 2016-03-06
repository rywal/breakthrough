//
//  Game.cpp
//  
//
//  Created by Ryan Walters on 2/28/16.
//
//

#include "Game.h"

Game::Game(){
	display=false;
}

bool Game::valid_move(int row, char column, DIRECTION d){
		if (row<1 || row>8){ cout<<row<<"HERE\n"; return false;}
		if (column<'a' || column >'h'){ return false;}
		
		
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
			if (current_state.get_board()[row-1][column-'a']!='x') return false;
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
				current_state.set_board(row-2,column-'a', 'x');
			if (d==LEFT)
				current_state.set_board(row-2,column-'a'+1, 'x');
			if (d==RIGHT)
				current_state.set_board(row-2,column-'a'-1, 'x');
		}
		current_state.switch_turn();
		if(display)
			display_board();
		save_state();
	} else {
		printf("That's an invalid move! Try again.\n");
	}
	return temp;
}

void Game::display_toggle(){
	display=(!display);
	if(display)
		display_board();
}

void Game::display_board(){
	(current_state.get_turn()) ? (cout<<"White's ") : (cout<<"Black's");
	cout<<"turn\n";
	cout<<";   ";
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

void Game::save_state(){
	previous_states.push_back(current_state);
	//might include output to a file if we need it
}

void Game::undo(){
	previous_states.pop_back();
	current_state=previous_states[previous_states.size()-1];
	if(display)
		display_board();
}

void Game::undo_two_turns(){ 
//when playing an AI they may move to fast to press undo twice
	previous_states.pop_back();
	previous_states.pop_back();
	current_state=previous_states[previous_states.size()-1];
	if(display)
		display_board();
}
