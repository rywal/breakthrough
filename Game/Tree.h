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
vector<Node*> node_list; //Add for quick traversal? (use .get_depth on each node)
vector<vector<Node*>> depth_list;
int largest_depth; //When adding nodes to list, keep track of largest depth

/*for(int e=0; e<largest_depth; e++){  FOR DEPTH list
	for(int i=0; i<node_list.size(); i++){
		if (node_list[i].get_depth()==e){
			depth_list[e].push_back(node_list[i]);
		}
	}
}*/

    
public:
    
    //  Default Constructor
    Tree();

    //  Destructor
    ~Tree(){}
    	
	Node get_tree(); //Not sure on the data type for this
	void add_node_w_children(vector<State> children, vector<long int> values, Node* parent_node/*Or just Node??*/); //Add new_node to node_list 
	//void add_node_w_children(Node new_node);//Not sure which one should be implemented??
	Node get_node(int depth/*SOMETHING ELSE IS NEEDED TOO*/);
	
	
};


#endif /* Tree_h */