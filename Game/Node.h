//
//  Node.h
//  
//  Represents a Node of a Tree of States for AI Algorithms
//

#ifndef Node_h
#define Node_h

#include <iostream>
#include <stdio.h>
#include <vector>
#include "globals.h"
#include "State.h"

using namespace std;

class Node {
	
private:

vector<pair<string, DIRECTION>> move;//The move that is needed to make this State
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
    
    void push_back(Node* child);	
	void create_node_w_children(vector<State> children_states /*each state will be converted into a node*/, vector<long int> value, Node* parent_node); //Get new_depth from parent's depth
	void create_root();
	long int get_value();
	State get_state();
	int get_depth(); //Basically "return depth;"
	bool is_leaf(); //Basically "return (children.size()==0);"
	vecotr<Node*> get_children();//Basically "return children;"
	//bool is_root(); //Basically "return (!parent_node);" (or if parent_node==NULL)  {Probably unnecessary}
};


#endif /* Node_h */