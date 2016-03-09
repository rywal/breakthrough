//
//  Game.cpp
//

#include "Game.h"
#include "State.h"
#include "AI.h"

Game::Game(){
	display=false;
    game_type = HH;
    save_state();
}

void Game::set_game_type(GAMETYPE g, DIFFICULTY d) {
    
    game_type = g;
    delete[] ai;
    ai = new AI(d);
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
            if (d == LEFT && current_state.get_board()[row+1][column-'a'-1]=='o' ) return false;
			if (d == RIGHT && current_state.get_board()[row+1][column-'a'+1]=='o' ) return false;
			if (current_state.get_board()[row][column-'a']!='_' && d == FWD) return false;
            // Check if can move left
            if ( (column-'a'-1) >= 0 && d == LEFT)
                if (current_state.get_board()[row][column-'a'-1] == 'o')
                    return false;
            
            // Check if can move right
            if ( (column+1) <= 'h' && d == RIGHT)
                if (current_state.get_board()[row][column-'a'+1] == 'o')
                    return false;
            
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
			if (d == LEFT && current_state.get_board()[row-1][column-'a'+1]=='x' ) return false;
			
			if (d == RIGHT && current_state.get_board()[row-1][column-'a'-1]=='x' ) return false;
			
			if (current_state.get_board()[row-2][column-'a']!='_' && d == FWD) return false;
            
            // Check if can move left
            if ( (column-'a'-1) >= 0 && d == LEFT)
                if (current_state.get_board()[row-1][column-'a'-1] == 'x')
                    return false;
            
            // Check if can move right
            if ( (column+1) <= 'h' && d == RIGHT)
                if (current_state.get_board()[row-1][column-'a'+1]=='x')
                    return false;
            
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
		current_state.set_status(termination_check());
		
		if(display)
			display_board();
		save_state();
        
        // If game type involves an AI, let it make it's move
        if (game_type != HH && !current_state.get_turn()) {
            ai->make_move( this );
//                current_state.switch_turn();
//                current_state.set_status(termination_check());
//                if(display)
//                    display_board();
//                save_state();
//            }
        }
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
    if (!display) {
        return;
    }
	if(current_state.get_status()==0){
		(current_state.get_turn()) ? (cout<<"; White's ") : (cout<<"; Black's ");
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
	} else {
		(!current_state.get_turn()) ? (white_v()) : (black_v());
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
}	

bool Game::termination_check(){
		
	//Checking for any pieces 
	int end_this=0;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if (current_state.get_board()[i][j]=='o'){
				end_this=1;
				break;
			}
		}
	}
	if(end_this=0){return false;}

	end_this=0;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if (current_state.get_board()[i][j]=='x'){ 
				end_this=1;
				break;
			}
		}
	}
	if(end_this=0){return false;}

	end_this=0;
	//Checking for x's on the bottom row
	for(int j=0; j<8; j++){
		if (current_state.get_board()[0][j]=='x'){
			end_this=1;
			break;
		}
	}
	if(end_this=0){return false;}
	
	end_this=0;
	//Checking o's on the top row
	for(int j=0; j<8; j++){
		if (current_state.get_board()[7][j]=='o'){
			end_this=1;
			break;
		}
	} 
	if(end_this=0){return false;}
		
}
string Game::who_won(){
	string out;
	(!current_state.get_turn()) ? (out="; White ") : (out="; Black ");
	out+="is the winner!";
	return out;
}
	
void Game::white_v(){
	current_state.set_board(5,1, 'W');
	current_state.set_board(5,2, 'H');
	current_state.set_board(5,3, 'I');
	current_state.set_board(5,4, 'T');
	current_state.set_board(5,5, 'E');
	current_state.set_board(4,2, 'I');
	current_state.set_board(4,3, 'S');
	current_state.set_board(3,2, 'T');
	current_state.set_board(3,3, 'H');
	current_state.set_board(3,4, 'E');
	current_state.set_board(2,1, 'W');
	current_state.set_board(2,2, 'I');
	current_state.set_board(2,3, 'N');
	current_state.set_board(2,4, 'N');
	current_state.set_board(2,5, 'E');
	current_state.set_board(2,6, 'R');
}	

void Game::black_v(){
	current_state.set_board(6,1, 'B');
	current_state.set_board(6,2, 'L');
	current_state.set_board(6,3, 'A');
	current_state.set_board(6,4, 'C');
	current_state.set_board(6,5, 'K');
	current_state.set_board(5,2, 'I');
	current_state.set_board(5,3, 'S');
	current_state.set_board(4,2, 'T');
	current_state.set_board(4,3, 'H');
	current_state.set_board(4,4, 'E');
	current_state.set_board(3,1, 'W');
	current_state.set_board(3,2, 'I');
	current_state.set_board(3,3, 'N');
	current_state.set_board(3,4, 'N');
	current_state.set_board(3,5, 'E');
	current_state.set_board(3,6, 'R');
}

void Game::save_state(){
	previous_states.push_back(current_state);
	//might include output to a file if we need it
}

void Game::undo(){
	if (current_state.get_num_moves()<1){
		cout<<"No moves to undo\n";
	}
	else {
        current_state=previous_states[previous_states.size()-1];
        previous_states.pop_back();
		if(display)
			display_board();
	}
}
bool Game::game_over(){
	return current_state.get_status();
}

void Game::undo_two_turns(){ 
//when playing an AI they may move too fast to press undo twice
	if (current_state.get_num_moves()<2){
		cout<<"Not enough moves to undo\n";
	}
	else {
		cout<<"1\n";
		previous_states.pop_back();
		cout<<"1\n";
		previous_states.pop_back();
		cout<<"1\n";
		current_state=previous_states[previous_states.size()-1];
		cout<<"1\n";
		if(display)
			display_board();
	}
}
