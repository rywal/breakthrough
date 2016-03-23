//
//  Tree.h
//  
//  Represents the Tree of States for AI Algorithms
//  Represented as a sort of linked list with vector traversal??

#ifndef Tree_h
#define Tree_h

#include "Node.h"

using namespace std;

class Tree {
	
private:

Node* root_node; //Not sure on the data type for this? (Also this should be the CURRENT STATE'S NODE)
//vector<Node*> node_list; //Add for quick traversal?
vector<vector<vector<Node*>>> depth_list; //To keep track of all children of a depth
int max_depth;
    
public:
    
    //  Default Constructor
    Tree();
    Tree(Node* rn, int md, vector<vector<vector<Node*>>> dlist);

    //  Destructor
    ~Tree(){}
    	
	Node* get_tree(); //Not sure on the data type for this
	void add_node_w_children(vector<State> children, vector<long int> value, Node* parent_node/*Or just Node??*/); //Add new_node to node_list
	//void add_node_w_children(Node new_node);//Not sure which one should be implemented??
	Node* get_node(int depth/*SOMETHING ELSE IS NEEDED TOO*/);
	vector<Node*> get_root_children(); //Basically "return root_node.get_children()"
	Node* get_min_node();
	
};


#endif /* Tree_h */