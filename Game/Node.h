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

vector<State>* Node;
Node* parent_node;
vector<State> children; //Keeps track of each child Node/leaf
vector<int> values; //Keeps track of each child's value
int depth; //Keeps track of how far down the Node is from the root (root being 0 depth deep)
    
public:
    
    //  Default Constructor
    Node();

    //  Destructor
    ~Node(){}
    	
	void create_node_w_children(vector<State> children, vector<int> value, State* parent_node); //Get new_depth from parent's depth
	int get_depth(); //Basically "return depth;"
	bool is_leaf(); //Basically "return (children.size()==0);"
};


#endif /* Node_h */