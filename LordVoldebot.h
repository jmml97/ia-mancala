/*
 * LordVoldebot.h
 *
 *  Created on: 15 mayo 2018
 *      Author: jmml
 */

#include "Bot.h"

#ifndef LORDVOLDEBOT_H_
#define LORDVOLDEBOT_H_

struct Node {

    GameState state;
    Move move;

};

class LordVoldebot: Bot
{
  public:
    LordVoldebot();
    ~LordVoldebot();


    void initialize();
    string getName();
    Move nextMove(const vector<Move>& adversary, const GameState& state);

    // Calcula el mejor movimiento entre todos los posibles.
    // Utiliza la estrategia conocida como "poda alfa-beta".
    //
    // Los parámetros de entrada son:
    // node       Un nodo conteniendo el estado inicial del árbol
    // depth      Profundidad hasta la que se quiere explorar el árbol
    // alpha      Valor alfa del algoritmo alfa-beta
    // beta       Valor beta del algoritmo alfa-beta
    // maximize   Si el nodo del que partimos es uno que queremos maximizar o
    //            minimizar.
    //
    // La función devuelve el un pair que contiene el valor del nodo elegido
    // y el movimiento necesario para llegar a él.
    std::pair<double, Move> AlphaBeta(Node node, int depth, int alpha,
                                   int beta, bool maximize);

};

#endif /* LORDVOLDEBOT_H_ */
