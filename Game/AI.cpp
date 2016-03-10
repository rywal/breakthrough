//
//  AI.cpp
//  
//  Implementation of AI Class
//

#include "AI.h"
#include <stdlib.h> // used for rand function
#include <time.h> // used for time
#include <utility> // used for pair
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>

using namespace std;

AI::AI() {
    difficulty_level = EASY;
    printf("; AI set difficulty to: EASY\n");
}

AI::AI(DIFFICULTY d) {
    difficulty_level = d;
    printf("; AI difficulty level changed\n");
}

AI::AI(DIFFICULTY d, int s) {
    difficulty_level = d;
    socketfd = s;
    printf("; AI difficulty level changed\n");
}

AI::AI(const AI &ai) {

}

AI::~AI() {

}

string AI::make_move(Game* game) {
    printf("; AI is currently choosing a move...\n");
    
//    cout << game->game_type << " gt\n";
    if (difficulty_level == EASY) {
        return choose_random( game );
    } else if(difficulty_level == MEDIUM) {
        return choose_random( game );
    } else if(difficulty_level == HARD) {
        return choose_random( game );
    }
    
    return "";
}

string AI::choose_random(Game* game) {
    printf("; Choosing a random move based on easy difficulty level\n");
    
    // Find all possible moves
    vector< pair<string, DIRECTION> > all_possible_moves = possible_moves(game, game->current_state);

    if (all_possible_moves.size() == 0)
        return "EXIT";
    
    // Randomly pick a possible move
    srand (time(NULL));
    int random_move = rand() % all_possible_moves.size();
    
//    cout << "Making move with random index: " << random_move << "\n";
    
    // Make a move using the random number
    string text_move = all_possible_moves[random_move].first;
    transform(text_move.begin(), text_move.end(), text_move.begin(), ::toupper);
    
    string move_output = text_move + " ";
    switch (all_possible_moves[random_move].second) {
        case FWD:
            move_output += "FWD\n";
            break;
            
        case LEFT:
            move_output += "LEFT\n";
            break;
            
        case RIGHT:
            move_output += "RIGHT\n";
            break;
            
        default:
            break;
    }
    
    if (socketfd) {
        write(socketfd, move_output.c_str(), move_output.length());
        cout << move_output;
    } else {
        cout << move_output;
    }
    
    game->update( all_possible_moves[random_move].first[0],
                  (all_possible_moves[random_move].first[1] - '0'),
                  all_possible_moves[random_move].second );
    
    return move_output;
}

vector< pair<string, DIRECTION> > AI::possible_moves(Game* game, State state) {
//    cout << "finding moves...1\n";
    // Figure out which player we are finding moves for
    char game_piece = state.get_turn() ? 'o' : 'x';
//    cout << "finding moves...2\n";
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
    
//    cout << "finding moves...3\n";
    return moves;
}