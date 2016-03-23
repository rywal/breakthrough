#include "Tree.h"

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

Node* Tree::get_min_node(){
	Node* min_node=depth_list[1][0][0];
	int min=depth_list[1][0][0]->get_value();
	for(int i=1; i<max_depth; i++){
		for(int j=0; j<depth_list[i].size(); i++){
			for(int k=0; k<depth_list[i][j].size(); k++){
				if (min>depth_list[i][j][k]->get_value()){
					min=depth_list[i][j][k]->get_value();
					min_node=depth_list[i][j][k];
				}
			}
		}		
	}
	return min_node;
}

Node* Tree::get_max_node(){
	Node* max_node=depth_list[1][0][0];
	int max=depth_list[1][0][0]->get_value();
	for(int i=1; i<max_depth; i++){
		for(int j=0; j<depth_list[i].size(); i++){
			for(int k=0; k<depth_list[i][j].size(); k++){
				if (max<depth_list[i][j][k]->get_value()){
					max=depth_list[i][j][k]->get_value();
					max_node=depth_list[i][j][k];
				}
			}
		}		
	}
	return max_node;
}