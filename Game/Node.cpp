#include "Node.h"

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
	pair<string, DIRECTION> move = std::make_pair (to_string(i)+to_string(j), dir);
	
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

