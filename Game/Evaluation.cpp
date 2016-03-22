//
//  Evaluation.cpp
//  
//
//  Created by Ryan Walters on 3/22/16.
//
//

#include "Evaluation.h"

Evaluation::Evaluation(Game g, int cur_depth, int m_depth) {
    game = g;
    current_depth = cur_depth;
    max_depth = m_depth;
}

vector< pair<string, DIRECTION> > possible_moves(Game game, State state) {
    // Figure out which player we are finding moves for
    char game_piece = state.get_turn() ? 'o' : 'x';
    vector< pair<string, DIRECTION> > moves;
    
    for (int row = 1; row <= 8; row++) {
        for (char col = 'a'; col <= 'h'; col++) {
            if(state.get_board()[row-1][col - 'a'] == game_piece) {
                for (auto d : {FWD, LEFT, RIGHT}) {
                    if ( game->valid_move(row, col, d) ) {
                        string position = boost::lexical_cast<string>(col) + to_string(row);
                        pair<string, DIRECTION> move = make_pair(position, d);
                        moves.push_back( move );
                    }
                }
            }
        }
    }
    
    return moves;
}

long int Evaluation::evaluate(bool max) {
    // Check if game is over or depth level is met
    if (game->game_over() || current_depth >= max_depth) {
        if (game.current_state.get_status() == 1) {
            // Winner has been found
            if (game.current_state.get_turn()) {
                // The player has won
                return pow(9, 8);
            } else {
                // The opponent has won. This would be bad!
                return (-1) * pow(9, 8);
            }
        } else {
            // Game is not over, but we got to the max depth
            return 0;
        }
    }
    
    // Setup structures to find children moves and values
    vector<int> children_values;
    vector< pair<string, DIRECTION> > possible_moves = possible_moves(game, game.current_state);
    
    // Quit if there are no possible moves to make
    if (possible_moves.size() == 0) {
        return 0;
    }
    
    // For each move available, find out the child moves available and their board values
    //   If minimum, add the minimum value to children_values
    //   If maximum, add the maximum value to children_values
    for (int i = 0; i < possible_moves.size(); i++) {
        Game next_depth_game = game;
        next_depth_game->update( possible_moves[i].first[0],
                                (possible_moves[i].first[1] - '0'),
                                possible_moves[i].second );
        
        evaluate_min_max(next_depth_game, !max, current_depth+1, max_depth);
        
    }
    
    // For each child value, find the minimum or maximum value(based on if we are searching for min/max)
    
    // Once the best value is found, store the move as the best_move to make
    best_move = possible_moves[best];
    
    return 0;
}

long int Evaluation::find_max() {
    return evaluate(true);
}

long int Evaluation::find_min() {
    return evaluate(false);
}