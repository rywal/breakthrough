//
//  AI.cpp
//  
//  Implementation of AI Class
//

#include "AI.h"
#include <stdlib.h> // used for rand function
#include <time.h> // used for time
#include <utility> // used for pair
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>
#include <math.h>

using namespace std;

AI::AI() {
    difficulty_level = EASY;
    printf("; AI set difficulty to: EASY\n");
}

AI::AI(DIFFICULTY d) {
    difficulty_level = d;
    printf("; AI difficulty level changed\n");
}

AI::AI(DIFFICULTY d, int s) {
    difficulty_level = d;
    socketfd = s;
    printf("; AI difficulty level changed\n");
}

AI::AI(const AI &ai) {

}

AI::~AI() {

}

string AI::make_move(Game* game) {
    printf("; AI is currently choosing a move...\n");
    
//    cout << game->game_type << " gt\n";
    if (difficulty_level == EASY) {
        return choose_random( game );
    } else if(difficulty_level == MEDIUM) {
        return choose_min_max( game );
    } else if(difficulty_level == HARD) {
        return choose_random( game );
    }
    
    return "";
}

string AI::choose_random(Game* game) {
    printf("; Choosing a random move based on easy difficulty level\n");
    
    // Find all possible moves
    vector< pair<string, DIRECTION> > all_possible_moves = possible_moves(game, game->current_state);

    if (all_possible_moves.size() == 0)
        return "EXIT";
    
    // Randomly pick a possible move
    srand (time(NULL));
    int random_move = rand() % all_possible_moves.size();
    
//    cout << "Making move with random index: " << random_move << "\n";
    
    // Make a move using the random number
    string text_move = all_possible_moves[random_move].first;
    transform(text_move.begin(), text_move.end(), text_move.begin(), ::toupper);
    
    string move_output = text_move + " ";
    switch (all_possible_moves[random_move].second) {
        case FWD:
            move_output += "FWD\n";
            break;
            
        case LEFT:
            move_output += "LEFT\n";
            break;
            
        case RIGHT:
            move_output += "RIGHT\n";
            break;
            
        default:
            break;
    }
    
    if (socketfd) {
        write(socketfd, move_output.c_str(), move_output.length());
        cout << move_output;
    } else {
        cout << move_output;
    }
    
    game->update( all_possible_moves[random_move].first[0],
                  (all_possible_moves[random_move].first[1] - '0'),
                  all_possible_moves[random_move].second );
    
    return move_output;
}

string AI::choose_min_max(Game* game) {
    printf("; Choosing the maximum move based on medium difficulty level\n");
    
    // Create evaluation class instance with current game
    Evaluation eval(game, true, 0, 2);
    eval.find_max();
    best_move = eval.best_move;
    
    if (best_move.first == "") {
        printf("; No move found using minmax algorithm\n");
        return "";
    }
    
    // Find string representation of best move to output to server/client
    string text_move = best_move.first;
    transform(text_move.begin(), text_move.end(), text_move.begin(), ::toupper);
    
    string move_output = text_move + " ";
    switch (best_move.second) {
        case FWD:
            move_output += "FWD\n";
            break;
            
        case LEFT:
            move_output += "LEFT\n";
            break;
            
        case RIGHT:
            move_output += "RIGHT\n";
            break;
            
        default:
            break;
    }
    
    // Write string representation of the move to the correct place
    if (socketfd) {
        write(socketfd, move_output.c_str(), move_output.length());
        cout << move_output;
    } else {
        cout << move_output;
    }

    
    // Update the game with the best move to make
    game->update( best_move.first[0],
                 (best_move.first[1] - '0'),
                  best_move.second );
    
    return move_output;
}

vector< pair<string, DIRECTION> > AI::possible_moves(Game* game, State state) {
    // Figure out which player we are finding moves for
    char game_piece = state.get_turn() ? 'o' : 'x';
    vector< pair<string, DIRECTION> > moves;
    
    for (int row = 1; row <= 8; row++) {
        for (char col = 'a'; col <= 'h'; col++) {
            if(state.get_board()[row-1][col - 'a'] == game_piece) {
                for (auto d : {FWD, LEFT, RIGHT}) {
                    if ( game->valid_move(row, col, d) ) {
                        string position = boost::lexical_cast<string>(col) + to_string(row);
                        pair<string, DIRECTION> move = make_pair(position, d);
                        moves.push_back( move );
                    }
                }
            }
        }
    }
    
    return moves;
}

//----------------------------Testing----------------------------//	

long int value_node(vector<vector<char>> node_board){
	//This gives child's value to each node
	//Positive numbers means better for the WHITE, negative is better for the BLACK
	int child_value=0;	
	for (int i=7; i>-1; i--){
		for(int j=0; j<8; j++){
			if(node_board[i][j]=='o'){//check for whites
				child_value += pow(9.0,(i));
			}
			if(node_board[i][j]=='x'){//check for blacks
				child_value -= pow(9.0,(7-i));
			}
		}
	}
	return (child_value);
}

void save_root_states(vector<vector<char>> node_board, vector<Node*>children_nodes, Node* parent, bool white/*or not*/, int i, int j, int count, int max_depth, int is_this_depth){
	//This function saves the states of possible moves
	if((node_board[i][j]=='o' && white)||(node_board[i][j]=='x' && !white)){
		char turn = white ? 'o' : 'x';
		int row = white ? i+1 : i-1;
		int col = white ? j+count : j-count; //Direction will be the same for both turns
		if((i<7)&&(i>0)){
			if(node_board[row][col]!=turn){
				//--Change the new board
				node_board[i][j]='_';
				node_board[row][col]=turn;
				//--Create the new Node
				Node new_node = new Node(value_node(node_board), parent, i, j, count);
				if(is_this_depth==0){
					new_node.set_children(find_node_roots(new_node, node_board, !white, max_depth));
				}
				//--Push back the whole Node
				children_nodes.push_back(new_node);
			}
		}
	}
}

vector<Node*> find_node_roots(Node* parent, vector<vector<char>> parent_board, bool white, int max_depth, int is_this_depth){	//Find the ??all?? roots of the current node
	//This is recursively called to 
	
	vector<Node*> children_nodes;
	if(parent.get_depth() < max_depth){
		for (int i=7; i>-1; i--){
			for(int j=0; j<8; j++){
				for(int e = -1; e < 2; e++){//-1 checks for left, 0 for fwd, 1 for right
					if((white && j != 0 && e != -1) || (!white && j != 7 && e != -1)){
						save_root_states(parent_board, children_nodes, parent, white ,i,j,e, max_depth, is_this_depth);
					}else if((white && j !=7 && e != 1) || (!white && j != 0 && e != 1)){ //For formating
						save_root_states(parent_board, children_nodes, parent, white ,i,j,e, max_depth, is_this_depth);
					}
				}
			}
		}
	}
	return children_nodes;
}

vector<Node*> children_at_depth(vector<Node*> parents, bool white, int max_depth){
	vector<Node*> children;
	vector<Node*> total_children;
	for(int i=0; i<parents.size(); i++){
		
		//-------THIS LINE NO LONGER WORKS, find_node_roots now uses recursion--------//
		children= find_node_roots(parents[i], parents[i].get_node_board() /*parent_boards[i] //CURRENT BOARD!! ,*/, white, max_depth);
		//-------THIS LINE NO LONGER WORKS, find_node_roots now uses recursion--------//
		
		total_children.insert(total_children.end(), children.begin(), children.end());
		for(int j=0; j<children.size(); j++){
			parents[i]->push_back(children[j]);
		}
	}
	return total_children;
}

Tree evaluation_function(State current_state, int max_depth){
	Node* parent_node= new Node(value_node(current_state.get_board()), nullptr);
	//vector<Node*> depth_one_children= find_node_roots(parent_node, current_state.get_board(), current_state.get_turn(), depth);

	parent_node.set_children(find_node_roots(parent_node, current_state.get_board(), current_state.get_turn(), max_depth, 0));
	
	vector<vector<Node*>> depth_list;
	depth_list.push_back(depth_one_children);
	
	for(int d=1; d<depth; d++){
			depth_list.push_back(children_at_depth(depth_list[d-1], ((current_state.get_turn()+1)%2!=0) /*Alternate Turns for each depth*/, depth));
	}
	
	return (/*new??*/ Tree(parent_node, max_depth/*, depth_list*/));
}

//----^------^-------^----^---Testing---^----^-------^------^----//	