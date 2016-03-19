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

vector<Node> state_tree; //Not sure on the data type for this

    
public:
    
    //  Default Constructor
    Tree();

    //  Destructor
    ~Tree(){}
    	
	vector<Node> get_tree(); //Not sure on the data type for this
	void add_node_w_children(vector<State> children, vector<int> value, State* parent_node);//Or just Node??
	void add_node_w_children(Node new_node);//Not sure which one should be implemented??
	
};


#endif /* Tree_h */