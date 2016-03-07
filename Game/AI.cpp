//
//  AI.cpp
//  
//  Implementation of AI Class
//

#include "AI.h"

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
    
}