#include "Tree.h"
#include <stdlib.h> // used for rand function
#include <time.h> // used for time

Tree::Tree(){}
Tree::Tree(Node* rn, int md, vector<vector<vector<Node*>>> dlist){
	root_node=rn;
	max_depth=md;
	depth_list=dlist;
}

Node* Tree::get_tree_root(){return root_node;}; //Not sure on the data type for this
//void Tree::add_node_w_children(vector<State> children, vector<long int> value, Node* parent_node/*Or just Node??*/); //Add new_node to node_list
	//void add_node_w_children(Node new_node);//Not sure which one should be implemented??
Node* Tree::get_node(int depth, int parent_index, int child_index){return depth_list[depth][parent_index][child_index];}
vector<Node*> Tree::get_root_children(){return root_node->get_children();} //Basically "return root_node.get_children()"

void Tree::display_tree(){
	cout<<max_depth<<'\n';
	for(int i=0; i<(max_depth+1); i++){
		for(int j=0; j<depth_list[i].size(); i++){
			for(int k=0; k<depth_list[i][j].size(); k++){
				cout<<'x';
			}
			cout<<' ';
		}
		cout<<'\n';
	}
}	
Node* Tree::get_min_node(){
	Node* current_node = depth_list[1][0][0];
	int min = depth_list[1][0][0]->get_value();

    vector<Node*> min_nodes; // Holds all nodes with same minimum value to randomly select from later
    
	for(int i=1; i < (max_depth + 1); i++){
		for(int j=0; j < depth_list[i].size(); i++){
			for(int k=0; k < depth_list[i][j].size(); k++){
                if (min > depth_list[i][j][k]->get_value()){
                    current_node = depth_list[i][j][k];
                    
                    min_nodes.clear();
                    min_nodes.push_back(current_node);
                    min = depth_list[i][j][k]->get_value();
                } else { // Previous min is larger than new min. Clear vector of previous min_nodes
                    current_node = depth_list[i][j][k];
                    
                    // Check if still same value as previous min
                    if (min == depth_list[i][j][k]->get_value()) {
                        min_nodes.push_back(current_node);
                    }
                }
			}
		}		
	}
    
    // Randomly pick a possible move
    srand (time(NULL));
    int random_move = 0;
    if (min_nodes.size() > 0) {
        random_move = rand() % min_nodes.size();
    }
    
	return min_nodes[random_move];
}

Node* Tree::get_max_node(){
	Node* current_node = depth_list[1][0][0];
    int max = depth_list[1][0][0]->get_value();
    
    vector<Node*> max_nodes; // Holds all nodes with same minimum value to randomly select from later
    
    for(int i=1; i < (max_depth + 1); i++){
        for(int j=0; j < depth_list[i].size(); i++){
            for(int k=0; k < depth_list[i][j].size(); k++){
                if (max < depth_list[i][j][k]->get_value()){
                    current_node = depth_list[i][j][k];
                    
                    max_nodes.clear();
                    max_nodes.push_back(current_node);
                    max = depth_list[i][j][k]->get_value();
                } else { // Previous min is larger than new min. Clear vector of previous min_nodes
                    current_node = depth_list[i][j][k];
                    
                    // Check if still same value as previous min
                    if (max == depth_list[i][j][k]->get_value()) {
                        max_nodes.push_back(current_node);
                    }
                }
            }
        }
    }
    
       
    // Randomly pick a possible move
    srand (time(NULL));
    int random_move = 0;
    if (max_nodes.size() > 0) {
        random_move = rand() % max_nodes.size();
    }
    
    return max_nodes[random_move];

} 
//______________________________________________
//----------------A-B Pruning-------------------
pair<long int, Node*> max_value (Node* parent, long int a, long int b){
// return utility value α: best MAX on path to state ; β: best MIN on path to state
// if Cutoff(state) then return Utility(state){
	long int v = -2147483647;
    Node* temp;
    pair<long int, Node*> max_move = make_pair(v, parent);
    
	for(int i = 0; i < parent->get_num_children(); i++){// each s in Successor(state) do
		temp = parent->get_children()[i];
		pair<long int, Node*> comparison = min_value(temp,a,b);
        
		max_move.first = (a > comparison.first) ? a : comparison.first;
        max_move.second = (a > comparison.first) ? parent : temp;
        
		if (max_move.first >= b){
			return comparison; /* CUT!! */
		} 
        a = (a > max_move.first) ? a : max_move.first;
	}
    
	return max_move;
}

pair<long int, Node*> min_value (Node* parent,long int a, long int b){
// return utility value α: best MAX on path to state ; β: best MIN on path to state 
//if Cutoff(state) then return Utility (state)
	long int v=2147483647;
    Node* temp;
    pair<long int, Node*> min_move = make_pair(v, parent);
    
    for(int i = 0; i < parent->get_num_children(); i++){// each s in Successor(state) do
        temp = parent->get_children()[i];
        pair<long int, Node*> comparison = max_value(temp,a,b);
        
        min_move.first = (a < comparison.first) ? a : comparison.first;
        min_move.second = (a < comparison.first) ? parent : temp;
        
        if (min_move.first <= b){
            return comparison; /* CUT!! */
        }
        a = (a < min_move.first) ? a : min_move.first;
    }
    
    return min_move;
}
