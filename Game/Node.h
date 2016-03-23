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

pair<string, DIRECTION> move;//The move that is needed to make this State
long int current_value; //This holds the current value of the board
Node* parent_node; //for ROOT this is NULL
vector<Node*> children; //Keeps track of each child Node/leaf
int depth; //Keeps track of how far down the Node is from the root (root being 0 depth deep)

   
public:
    
    //  Default Constructor
    Node();
    Node(long int value, Node* pn=NULL);
	Node(long int value, Node* pn, int i, int j, int count){

    //  Destructor
    ~Node(){}
    
	void set_children(vector<Node*> children_nodes);//Basically "children=children_nodes;"
	long int get_value();
	int get_depth();
	vector<Node*> get_children();//Basically "return children;"
};


#endif /* Node_h */