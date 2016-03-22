#include "Node.h"
Node::Node(){}
Node::Node(State cs, long int value, Node* pn){
	current_state=cs;
	current_value=value;
	parent_node=pn;
}

Node::Node(State cs, long int value, Node* pn, int i, int j, int count){
	current_state=cs;
	current_value=value;
	parent_node=pn;
	int 
	
}
    
void Node::push_back(Node* child){children.push_back(child);}	
void Node::create_node_w_children(vector<State> children_states /*each state will be converted into a node*/, vector<long int> value, Node* parent_node){} //Get new_depth from parent's depth
void Node::create_root(){}
long int Node::get_value(){return current_value;}
State Node::get_state(){return current_state;}
int Node::get_depth(){return depth;} //Basically "return depth;"
bool Node::is_leaf(){return children.size()==0;}//Basically "return (children.size()==0);"