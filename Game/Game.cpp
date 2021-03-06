//
//  Game.cpp
//

#include "Game.h"
#include "State.h"
#include "AI.h"
#include <string>
#include <math.h>

#define BUFFER_SIZE 1024

Game::Game(){
	display=false;
    output_to_socket = false;
    game_type = HH;
    save_state();
    ai = new AI();
}

Game::Game(Game* g){
    display = g->display;
    output_to_socket = g->output_to_socket;
    game_type = g->game_type;
    ai = g->ai;
}

Game::Game(int newsockfd){
	display=false;
    output_to_socket = true;
    game_type = HA;
    save_state();
    ai = new AI();
	socketfd=newsockfd;
}

void Game::set_game_type(GAMETYPE g, DIFFICULTY d) {
    
    game_type = g;
    if (g == HH) {
        ai = new AI(d);
    } else {
        ai = new AI(d, socketfd);
    }
}

bool Game::valid_move(int row, char column, DIRECTION d){
    if (game_over()) {
        return false;
    }
    
    if (row < 1 || row > 8){ return false;}
    if (column <'a' || column >'h'){ return false;}
    
    
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
        if (d == LEFT && current_state.get_board()[row][column-'a'-1]=='o' ) return false;
        if (d == RIGHT && current_state.get_board()[row][column-'a'+1]=='o' ) return false;
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
        if (d == LEFT && current_state.get_board()[row-2][column-'a'+1]=='x' ) return false;
        
        if (d == RIGHT && current_state.get_board()[row-2][column-'a'-1]=='x' ) return false;
        
        if (current_state.get_board()[row-2][column-'a'] != '_' && d == FWD) return false;
        
        // Check if can move left
        if ( (column-'a'+1) >= 0 && d == LEFT && row > 1)
            if (current_state.get_board()[row-2][column-'a'+1] == 'x')
                return false;
        
        // Check if can move right
        if ( (column+1) <= 'h' && d == RIGHT)
            if (current_state.get_board()[row-2][column-'a'-1]=='x')
                return false;
        
        return true;
    }
}

State Game::update(char column, int row, DIRECTION d){
	State temp;
    if (game_over()) {
        return temp;
    }
    
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
        if (game_type != HH && !current_state.get_turn() && !game_over()) {
            ai->make_move( this );
            current_state.set_status(termination_check());
        }
	} else {
        if (output_to_socket) {
            
            string e = "; Invalid move '" + string(1, column) + to_string(row) + " " + to_string(d) + "\n";
            write(socketfd, e.c_str(), sizeof(e));
        } else {
			printf("That's an invalid move! Try again.\n");
        }
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
        if (output_to_socket) {
            string t = current_state.get_turn() ? "; White's " : "; Black's ";
            t += "turn\n";
            write(socketfd, t.c_str(), t.length());
        } else {
			(current_state.get_turn()) ? (cout<<"; White's ") : (cout<<"; Black's ");
			cout<<"turn\n";
        }
        
        string b = ";   ";
		for (char i='A'; i<'I'; i++)
			b += " " + string(1, i);
        b += "\n";
		for (int i=7; i>-1; i--){
			b += "; " + to_string( (i+1) ) + " ";
			for(int j=0; j<8; j++){
				b += string(1, '|') + string(1, current_state.get_board()[i][j]);
            }
			b += "|\n";
        }
        
        if (output_to_socket) {
            write(socketfd, b.c_str(), b.length());
        } else {
            cout << b;
        }
	} else {
//		(!current_state.get_turn()) ? (white_v()) : (black_v());
        string b = ";   ";
        for (char i='A'; i<'I'; i++)
            b += " " + string(1, i);
        b += "\n";
        for (int i=7; i>-1; i--){
            b += "; " + to_string( (i+1) ) + " ";
            for(int j=0; j<8; j++){
                b += string(1, '|') + string(1, current_state.get_board()[i][j]);
            }
            b += "|\n";
        }
        
        if (output_to_socket) {
            write(socketfd, b.c_str(), b.length());
        } else {
            cout << b;
        }

	}
}		

bool Game::termination_check(){
		
	//Checking for any pieces 
	int white_count = 0;
	int black_count = 0;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			if (current_state.get_board()[i][j]=='o'){
				white_count = 1;
			}
			if (current_state.get_board()[i][j]=='x'){ 
				black_count = 1;
			}
		}
	}
	if(black_count == 0 || white_count == 0){return true;}


	//Checking for x's on the bottom row
	for(int j=0; j<8; j++){
		if (current_state.get_board()[0][j]=='x'){
            who_won();
			return true;
		}
	}
	
	for(int j=0; j<8; j++){
        if (current_state.get_board()[7][j]=='o'){
            who_won();
			return true;
		}
	} 
	
	return false;
}

string Game::who_won(){
	string out;
	(!current_state.get_turn()) ? (out="; White ") : (out="; Black ");
	out+="is the winner!\n";
    
    if (current_state.get_status() == true) {
        if (output_to_socket) {
            write(socketfd, out.c_str(), out.length());
        } else {
            printf(out.c_str());
        }
    }
	return out;
}
	
//void Game::white_v(){
//	current_state.set_board(5,1, 'W');
//	current_state.set_board(5,2, 'H');
//	current_state.set_board(5,3, 'I');
//	current_state.set_board(5,4, 'T');
//	current_state.set_board(5,5, 'E');
//	current_state.set_board(4,2, 'I');
//	current_state.set_board(4,3, 'S');
//	current_state.set_board(3,2, 'T');
//	current_state.set_board(3,3, 'H');
//	current_state.set_board(3,4, 'E');
//	current_state.set_board(2,1, 'W');
//	current_state.set_board(2,2, 'I');
//	current_state.set_board(2,3, 'N');
//	current_state.set_board(2,4, 'N');
//	current_state.set_board(2,5, 'E');
//	current_state.set_board(2,6, 'R');
//}	
//
//void Game::black_v(){
//	current_state.set_board(5,1, 'B');
//	current_state.set_board(5,2, 'L');
//	current_state.set_board(5,3, 'A');
//	current_state.set_board(5,4, 'C');
//	current_state.set_board(5,5, 'K');
//	current_state.set_board(4,2, 'I');
//	current_state.set_board(4,3, 'S');
//	current_state.set_board(3,2, 'T');
//	current_state.set_board(3,3, 'H');
//	current_state.set_board(3,4, 'E');
//	current_state.set_board(2,1, 'W');
//	current_state.set_board(2,2, 'I');
//	current_state.set_board(2,3, 'N');
//	current_state.set_board(2,4, 'N');
//	current_state.set_board(2,5, 'E');
//	current_state.set_board(2,6, 'R');
//}

void Game::save_state(){
	previous_states.push_back(current_state);
}

void Game::undo(){
	if (current_state.get_num_moves()<2){
        if (output_to_socket) {
            string m = "; No moves to undo\n";
            write(socketfd, m.c_str(), m.length());
        } else {
			cout<<"No moves to undo\n";
        }
	} else {
        if (game_type != HH) {
            previous_states.pop_back();
            previous_states.pop_back();
        }
        
        current_state = previous_states.back();
		if(display)
			display_board();
	}
}
bool Game::game_over(){
	return current_state.get_status();
}
bool Game::get_display(){
	return display;
}