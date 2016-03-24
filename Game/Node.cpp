#include "Node.h"
#include <boost/lexical_cast.hpp>

Node::Node(){}

Node::Node(long int value, Node* pn){
	current_value=value;
	parent_node=pn;
	depth=0;
}

Node::Node(long int value, Node* pn, int i, int j, int count){
	current_value=value;
	parent_node=pn;
	
	DIRECTION dir;
	if (count == -1){
		dir == LEFT;
	}else if (count == 0){
		dir == FWD;
	} else if (count == 1){
		dir == RIGHT;
	}
    
    char col = 'a' + j;
    string position = boost::lexical_cast<string>(col) + to_string(j+1);
    
	pair<string, DIRECTION> move = std::make_pair (position, dir);
    cout << "Added node(" << position << "): " << move.first << " " << move.second << " from " << i << " " << j << "\n";
	
	depth=pn->get_depth()+1;
}
    
void Node::set_children(vector<Node*> children_nodes){children=children_nodes;}
long int Node::get_value(){return current_value;}
int Node::get_depth(){return depth;}
vector<Node*> Node::get_children(){return children;}
pair<string, DIRECTION> Node::get_move(){return move;}
pair<string, DIRECTION> Node::get_first_move(){
	if(depth==0){
	}
	else if(depth==1){
		return get_move();
	}
	else{
		return parent_node->get_first_move();
	}
}

