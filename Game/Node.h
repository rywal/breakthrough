//
//  Node.h
//  
//  Represents a Node of a Tree of States for AI Algorithms
//

#ifndef State_h
#define State_h

#include <iostream>
#include <stdio.h>
#include <vector>
#include "globals.h"

using namespace std;

class Node {
	
private:

State current_state;//The current node's state
long int current_value; //This holds the current value of the board
Node* parent_node; //for ROOT this is NULL
vector<Node*> children; //Keeps track of each child Node/leaf
int depth; //Keeps track of how far down the Node is from the root (root being 0 depth deep)
    
public:
    
    //  Default Constructor
    Node();
    Node(State cs, long int value, Node* pn=NULL); 

    //  Destructor
    ~Node(){}
    
    void pushback(long	
	void create_node_w_children(vector<State> children_states /*each state will be converted into a node*/, vector<long int> value, Node* parent_node); //Get new_depth from parent's depth
	void create_root();
	long int get_value();
	int get_depth(); //Basically "return depth;"
	bool is_leaf(); //Basically "return (children.size()==0);"
	vector<long int> get_values(); //Basicaly "return values;"
	//bool is_root(); //Basically "return (!parent_node);" (or if parent_node==NULL)  {Probably unnecessary}
};


#endif /* Node_h */