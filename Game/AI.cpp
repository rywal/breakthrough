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

using namespace std;

AI::AI() {
    difficulty_level = EASY;
    printf("; AI set difficulty to: EASY\n");
}

AI::AI(DIFFICULTY d) {
    difficulty_level = d;
    printf("; AI difficulty level changed\n");
}

AI::AI(const AI &ai) {

}

AI::~AI() {

}

bool AI::make_move(Game* game) {
    printf("; AI is currently choosing a move...\n");
    
//    cout << game->game_type << " gt\n";
    
    if (difficulty_level == EASY) {
        choose_random( game );
        return true;
        
    } else if(difficulty_level == MEDIUM) {
        
        return true;
    } else if(difficulty_level == HARD) {
        
        return true;
    }
    
    return false;
}

bool AI::choose_random(Game* game) {
    printf("; Choosing a random move based on easy difficulty level\n");
    
    // Find all possible moves
    vector< pair<string, DIRECTION> > all_possible_moves = possible_moves(game->current_state);

    if (all_possible_moves.size() == 0)
        return false;
    
    // Randomly pick a possible move
    srand (time(NULL));
    int random_move = rand() % all_possible_moves.size();
    
    cout << "Making move with random index: " << random_move << "\n";
    
    // Make a move using the random number
    
    cout << "1: " << all_possible_moves[random_move].first[0] << "\n";
    cout << "2: " << (all_possible_moves[random_move].first[1] - '0') << "\n";
    cout << "3: " << all_possible_moves[random_move].second << "\n";
    game->update(all_possible_moves[random_move].first[0],
                (all_possible_moves[random_move].first[1] - '0'),
                all_possible_moves[random_move].second);
    
    return true;
}

vector< pair<string, DIRECTION> > AI::possible_moves(State state) {
    cout << "finding moves...1\n";
    // Figure out which player we are finding moves for
    char game_piece = state.get_turn() ? 'o' : 'x';
    cout << "finding moves...2\n";
    vector< pair<string, DIRECTION> > moves;
    
    for () {
        state.get_board()[row][column];
    }
    pair<string, DIRECTION> move = make_pair("a2", FWD);
    
    moves.push_back(move);
    cout << "finding moves...3\n";
    return moves;
}