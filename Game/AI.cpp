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

string AI::choose_random(Game* game) {
	printf("; Choosing the maximum move based on medium difficulty level\n");
	
	Tree choices();
	
	
}
vector< pair<string, DIRECTION> > AI::possible_moves(Game* game, State state) {
//    cout << "finding moves...1\n";
    // Figure out which player we are finding moves for
    char game_piece = state.get_turn() ? 'o' : 'x';
//    cout << "finding moves...2\n";
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
    
//    cout << "finding moves...3\n";
    return moves;
}

//----------------------------Testing----------------------------//	

long int value_node(State state_of_a_child){
	//This gives child's value to each node state
	//Positive numbers means better for the WHITE, negative is better for the BLACK
	int child_value=0;	
	for (int i=7; i>-1; i--){
		for(int j=0; j<8; j++){
			if(state_of_a_child.get_board()[i][j]=='o'){//check for whites
				child_value+=pow(9.0,(i));
			}
			if(state_of_a_child.get_board()[i][j]=='x'){//check for blacks
				child_value-=pow(9.0,(7-i));
			}
		}
	}
	return (child_value);
}

void save_root_states(State state_of_node, vector<Node*>children_nodes, Node* parent, bool white/*or not*/, int i, int j, int count){
	//This function saves the states of possible moves
	if((state_of_node.get_board()[i][j]=='o' && white)||(state_of_node.get_board()[i][j]=='x' && !white)){
		char turn = white ? 'o' : 'x';
		char n_turn = white ? 'x' : 'o';
		int row = white ? i+1 : i-1;
		int col = white ? j+count : j-count;
		if((white&&i<7)||(!white&&i>0)){
			if(state_of_node.get_board()[row][col]!=turn){
				State temp=state_of_node;
				long int value;
				temp.set_board(i,j,'_');
				temp.set_board(row,col,turn);
				value=value_node(temp);
				temp.switch_turn();
				children_nodes.push_back(new Node(temp, value, parent, i, j, count));
				//create node -> push_back into vector
			}
		}
	}
}

vector<Node*> find_node_roots(Node* parent){	//Find the roots of ONLY the current node
	//---Possibly defined in an above function??---//
//	vector<State> children_states;
//	vector<long int> values;
	vector<Node*> children_nodes;
	bool white = parent->get_state().get_turn();
	//---------------------------------------------//
	
	for (int i=7; i>-1; i--){
		for(int j=0; j<8; j++){
			for(int e=-1; e<2; e++){//-1 checks for left, 0 for fwd, 1 for right
				if(white&&j!=0&&e!=-1 || !white&&j!=7&&e!=-1 || white&&j!=7&&e!=1 || !white&&j!=0&&e!=1 ){
					save_root_states(parent->get_state(), children_nodes, parent, white ,i,j,e);
				}
			}
		}
    }
	return children_nodes;
}

vector<Node*> evaluation_function(vector<Node*> parents){
	vector<Node*> children;
	vector<Node*> total_children;
	for(int i=0; i<parents.size(); i++){
		children= find_node_roots(parents[i]);
		total_children.insert(total_children.end(), children.begin(), children.end());
		for(int j=0; j<children.size(); j++){
			parents[i]->push_back(children[j]);
		}
	}
	return total_children;
}
	

Tree evaluation_function(State state_of_node, int depth ){
	Node* parent_node= new Node(state_of_node, value_node(state_of_node));
	vector<Node*> temp_vec= find_node_roots(parent_node);
	for(int i=0; i<temp_vec.size(); i++){
		parent_node->push_back(temp_vec[i]);
	}
	vector<vector<Node*>> depth_list;
	depth_list.push_back(temp_vec);
	
	for(int d=1; d<depth; d++){
			depth_list.push_back(evaluation_function(depth_list[d-1]));
	}
	
}

//----^------^-------^----^---Testing---^----^-------^------^----//	