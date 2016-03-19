//
//  Tree.h
//  
//  Represents the Tree of States for AI Algorithms
//

#ifndef State_h
#define State_h

#include "Node.h"

using namespace std;

class Tree {
	
private:

Node* root_node; //Not sure on the data type for this? (Also this should be the CURRENT STATE'S NODE)
vector<Node> node_list; //Add for quick traversal?
    
public:
    
    //  Default Constructor
    Tree();

    //  Destructor
    ~Tree(){}
    	
	Node get_tree(); //Not sure on the data type for this
	void add_node_w_children(vector<State> children, vector<int> value, Node* parent_node/*Or just Node??*/); //Add new_node to node_list
	//void add_node_w_children(Node new_node);//Not sure which one should be implemented??
	Node get_node(int depth/*SOMETHING ELSE IS NEEDED TOO*/);
	
	
};


#endif /* Tree_h */