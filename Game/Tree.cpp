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

// Referenced this article for help on alpha-beta pruning http://will.thimbleby.net/algorithms/doku.php?id=algorithm:minimax_alpha-beta
pair<long int, Node*> Tree::alphaBeta(Node* node, pair<long int, Node*> alpha, pair<long int, Node*> beta, bool maximizePlayer){
    pair<long int, Node*> bestValue;
    
    if (node->get_num_children() == 0) {
        bestValue = make_pair(node->get_value(), node);
    } else if (maximizePlayer) {
        bestValue = alpha;
        
        // Run for all children in the node
        for (int i = 0; i < node->get_num_children(); i++) {
            pair<long int, Node*> childValue = alphaBeta(node->get_children()[i], bestValue, beta, false);
            bestValue = (bestValue.first > childValue.first) ? bestValue : childValue;
            
            if (beta.first <= bestValue.first) {
                break;
            }
        }
    } else {
        bestValue = beta;
        
        // Run for all children in the node
        for (int i = 0; i < node->get_num_children(); i++) {
            pair<long int, Node*> childValue = alphaBeta(node->get_children()[i], alpha, bestValue, true);
            bestValue = (bestValue.first < childValue.first) ? bestValue : childValue;
            
            if (bestValue.first <= alpha.first) {
                break;
            }
        }
    }
    return bestValue;
}
