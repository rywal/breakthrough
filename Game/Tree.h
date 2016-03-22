//
//  Tree.h
//  
//  Represents the Tree of States for AI Algorithms
//  Represented as a sort of linked list with vector traversal??

#ifndef State_h
#define State_h

#include "Node.h"

using namespace std;

class Tree {
	
private:

Node* root_node; //Not sure on the data type for this? (Also this should be the CURRENT STATE'S NODE)
vector<Node*> node_list; //Add for quick traversal?
vector<vector<Node*> depth_list;
    
public:
    
    //  Default Constructor
    Tree();
    Tree(State current_state, int depth);

    //  Destructor
    ~Tree(){}
    	
	Node get_tree(); //Not sure on the data type for this
	void add_node_w_children(vector<State> children, vector<long int> value, Node* parent_node/*Or just Node??*/); //Add new_node to node_list
	//void add_node_w_children(Node new_node);//Not sure which one should be implemented??
	Node get_node(int depth/*SOMETHING ELSE IS NEEDED TOO*/);
	get_root_children(); //Basically "return root_node.get_children()"
	
};


#endif /* Tree_h */