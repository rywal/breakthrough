//
//  State.cpp
//  

#include "State.h"


#define WHITE 'o'
#define BLACK 'x'
#define EMPTY '_'


State::State(){
	vector<char> empty;
	for(int i=0; i<8; i++){
		board.push_back(empty);
		for(int j=0; j<8; j++){
			if (i==1 || i==0)
				board[i].push_back(WHITE);
			else if (i==6 || i==7)
				board[i].push_back(BLACK);			
			else
				board[i].push_back(EMPTY);
		}
	}
	person_is_player=true;
	num_moves=0;
	status=-1;
}	

//this assumes that the state passed as an argument is a completely updated and defined state
State::State(State* s){
	
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++)
					board[i][j]=s->get_board()[i][j];
	
	num_moves=s->get_num_moves();
	status=s->get_status();
}



vector<vector<char > > State::get_board(){return board;}

void State::set_board(int i, int j, char a){ board[i][j]=a;}
int State::get_num_moves(){return num_moves;}
int State::get_status(){return status;}
bool State::get_turn(){return person_is_player;}
void State::set_turn(bool turn){person_is_player=turn;}
void State::switch_turn(){person_is_player=(!person_is_player);}

