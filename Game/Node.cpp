#include "Node.h"
Node::Node(){}
Node::Node(long int value, Node* pn){
	pair<string, DIRECTION> move = std::make_pair ("START MOV", dir);
	current_value=value;
	parent_node=pn;
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
	
}
    
void Node::push_back(Node* child){children.push_back(child);}	
void Node::create_node_w_children(vector<State> children_states /*each state will be converted into a node*/, vector<long int> value, Node* parent_node){} //Get new_depth from parent's depth
void Node::create_root(){}
long int Node::get_value(){return current_value;}
State Node::get_state(){return current_state;}
int Node::get_depth(){return depth;} //Basically "return depth;"
bool Node::is_leaf(){return children.size()==0;}//Basically "return (children.size()==0);"