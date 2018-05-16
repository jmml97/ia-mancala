/*
 * Croqueta.h
 *
 *  Created on: 15 mayo 2018
 *      Author: jmml
 */

#include "Bot.h"

#ifndef CROQUETA_H_
#define CROQUETA_H_

struct Node {

    GameState state;
    Move move;

};

class Croqueta: Bot
{
  public:
    Croqueta();
    ~Croqueta();


    void initialize();
    string getName();
    Move nextMove(const vector<Move>& adversary, const GameState& state);

    std::pair<double, Move> AlphaBeta(Node node, int depth, int alpha,
                                      int beta, bool maximize);

};

#endif /* CROQUETA_H_ */
