//
//  globals.h
//

#ifndef globals_h
#define globals_h

#include <algorithm>
#include <boost/regex.hpp>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <utility> // used for pair


//  Possible moves from each piece
//
//  Here, FORWARD direction is assumed to be the direction a piece can legally advance in
//  Here, LEFT/RIGHT is assumed to be FORWARD one place and LEFT/RIGHT one place
//    LEFT/RIGHT are assumed to be with respect to the game board(Column A will always be "most left", Column H will always be "most right")
enum DIRECTION { LEFT, FWD, RIGHT };


//  Type of game
//
//  HH = Human-Human
//  HA = Human-AI
//  AA = AI-AI
enum GAMETYPE { HH, HA, AA };

// Holds the difficulty of the current AI
//
//   EASY will implement a semi-random algorithm
//   MEDIUM will implement limited depth min-max algorithm
//   HARD will implement alpha-beta pruning algorithm
enum DIFFICULTY { EASY, MEDIUM, HARD };

#endif