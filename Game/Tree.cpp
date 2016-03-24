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
	Node* min_node=depth_list[1][0][0];
	int min=depth_list[1][0][0]->get_value();
	for(int i=1; i<(max_depth+1); i++){
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
	for(int i=1; i<(max_depth+1); i++){
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
//______________________________________________
//----------------A-B Pruning-------------------
long int min_value (State state,Game game, long int a, long int b);

long int max_value (Node* parent, long int a, long int b){
// return utility value α: best MAX on path to state ; β: best MIN on path to state
// if Cutoff(state) then return Utility(state){
	long int v=–2147483647;
	Node* temp;
	for(int i=0; i<parent->get_num_children(); i++){// each s in Successor(state) do
		temp=parent->get_children()[i];
		long int comparison=min_value(temp,a,b);
		v = (a > comparison) ? a : comparison;
		if (v ≥ b){
			return v /* CUT!! */
		} 
		a = (a > v) ? a : v;
	}
	return v;
}

long int min-value (Node* parent,long int a, long int b){
// return utility value α: best MAX on path to state ; β: best MIN on path to state 
//if Cutoff(state) then return Utility (state)
	long int v=2147483648;
	Node* temp;
		for(int i=0; i<parent->get_num_children(); i++){// each s in Successor(state) do
			temp=parent->get_children()[i];
			long int comparison=max_value(temp,a,b);
			v = (b < comparison) ? b : comparison;
			if (v <= a){
				return v /* CUT!! */
			} 
			b = (b < v) ? b : v;
		}
	return v;
}
/*for each s in Successor(state) do
· v ← Min(β, Max-Value(s,game,α,β))
· if v ≤ α then return v /* CUT!! */
/*· β ←Min(β,v) end
return v*/
