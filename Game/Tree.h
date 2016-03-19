//
//  Tree.h
//  
//  Represents the Tree of States for AI Algorithms
//

#ifndef State_h
#define State_h

#include <iostream>
#include <stdio.h>
#include <vector>
#include "globals.h"

using namespace std;

class Tree {
	
private:

vector<vector<State>> state_tree; //Not sure on the data type for this
State* parent_node; //Not sure on the data type for this
vector<State> children;
vector<int> values;

    
public:
    
    //  Default Constructor
    Tree();

    //  Destructor
    ~Tree(){}
    	
	vector<vector<State>> get_tree(); //Not sure on the data type for this
	void add_node_w_children(vector<State> children, vector<int> value, State* parent_node);
	
};


#endif /* Tree_h */