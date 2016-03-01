//
//  AI.h
//
//  Makes game move decisions based on different algorithms
//

#ifndef AI_h
#define AI_h

#include <stdio.h>

// Holds the difficulty of the current AI
//
//   EASY will implement a semi-random algorithm
//   MEDIUM will implement limited depth min-max algorithm
//   HARD will implement alpha-beta pruning algorithm
enum DIFFICULTY { EASY, MEDIUM, HARD };

class AI {
    
private:
    
    DIFFICULTY difficulty_level;
    
public:
    
    AI();
    AI(const AI &ai);
    ~AI();
};

#endif /* AI_h */
