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
vector<State> children;
vector<int> values;

    
public:
    
    //  Default Constructor
    Node();

    //  Destructor
    ~Node(){}
    	
	void create_node_w_children(vector<State> children, vector<int> value, State* parent_node);
};


#endif /* Node_h */