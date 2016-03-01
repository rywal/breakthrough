//
//  State.cpp
//  

#include "State.h"


#define WHITE 'o'
#define BLACK 'x'
#define EMPTY '_'


State::State(){
	
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if (i==1 || i==0)
				board[i].push_back(WHITE);
			else if (i==6 || i==7)
				board[i].push_back(BLACK);
			else
				board[i].push_back(EMPTY);
		}
	}
	
	num_moves=0;
	status=-1;
}	

//this assumes that the state passed as an argument is a completely updated and defined state
State::State(State *s){
	
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
					board[i][j]=s->board[i][j];
	
	num_moves=s->num_moves;
	status=s->status;
}

vector<vector<char > > State::get_board(){return board;}

bool State::get_turn(){return person_is_player;}

void State::set_turn(bool turn){person_is_player=turn;}