/*
 * Croqueta.cpp
 * Implementación de un Bot que juega a Mancala utilizando la estrategia
 * conocida como "poda alfa-beta".
 *
 *  Created on: 15 mayo 2018
 *      Author: jmml
 */

#include <string>
#include <cstdlib>
#include <iostream>
#include <limits>       // std::numeric_limits
#include <algorithm>    // std::max
#include <utility>      // std::pair, std::make_pair
#include <chrono>       // std::chrono

#include "Croqueta.h"
using namespace std;

std::chrono::time_point<std::chrono::high_resolution_clock> start;
std::chrono::milliseconds limit(1900);

Croqueta::Croqueta()
{
    // Inicializar las variables necesarias para ejecutar la partida

}

Croqueta::~Croqueta()
{
    // Liberar los recursos reservados (memoria, ficheros, etc.)
}

void Croqueta::initialize()
{
    // Inicializar el bot antes de jugar una partida
}

string Croqueta::getName()
{
    return "Croqueta"; // Sustituir por el nombre del bot
}

std::pair<double, Move> Croqueta::AlphaBeta(Node node, int depth, int alpha,
        int beta, bool maximize)
{
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> fdiff = now - start;
    std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(fdiff);

    if (diff > limit) {
      return make_pair(9000, M_NONE);
    }

    if (depth == 0 || node.state.isFinalState()) {

        Player player = this->getPlayer();

        // La heurística que vamos a utilizar valora un elemento del juego:
        //
        // - Nuestra puntuación respecto a la del adversario, que queremos
        //   maximizar
        //  Nuestra heurística será por tanto:
        //    puntuación_jugador - puntuación_adversario

        int score = node.state.getScore(player);
        int opponent_score;

        double value = score - opponent_score;

        return std::make_pair(value, M_NONE);
    }

    if (maximize) {
        int best_value = std::numeric_limits<int>::min();
        Move best_move;

        for (int i = 1; i <= 6; i++) {
            Node child_node = {node.state.simulateMove((Move) i), (Move) i};

            double value;

            // Tener que maximizar o minimizar el siguiente nodo del árbol
            // dependerá de si vuelve a ser el turno del bot.
            if (child_node.state.getCurrentPlayer() == node.state.getCurrentPlayer()) {
                value = AlphaBeta(child_node, depth - 1, alpha, beta, true).first;
            } else {
                value = AlphaBeta(child_node, depth - 1, alpha, beta, false).first;
            }

            if (value > best_value) {
                best_value = value;
                best_move = (Move) i;
            }

            alpha = std::max(alpha, best_value);

            if (beta <= alpha) {
                break;
            }
        }

        return std::make_pair(best_value, best_move);
    } else {

        int best_value = std::numeric_limits<int>::max();
        Move best_move;

        for (int i = 1; i <= 6; i++) {
            
            Node child_node = {node.state.simulateMove((Move) i), (Move) i};

            double value;

            // Tener que maximizar o minimizar el siguiente nodo del árbol
            // dependerá de si vuelve a ser el turno del bot.
            if (child_node.state.getCurrentPlayer() == node.state.getCurrentPlayer()) {
                value = AlphaBeta(child_node, depth - 1, alpha, beta, false).first;
            } else {
                value = AlphaBeta(child_node, depth - 1, alpha, beta, true).first;
            }


            if (value < best_value) {
                best_value = value;
                best_move = (Move) i;
            }

            beta = std::min(beta, best_value);

            if (beta <= alpha) {
                break;
            }
        }

        return std::make_pair(best_value, best_move);
    }

}

Move Croqueta::nextMove(const vector<Move>& adversary, const GameState& state)
{

    int depth = 15;

    Player turno = this->getPlayer();
    long timeout = this->getTimeOut();

    Node origin = {state, M_NONE};

    double new_value;
    double old_value;
    pair<double, Move> path;
    Move move;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < 20 && new_value != 9000; ++i) {
      //cerr << "profundidad: " << i << endl; 
      path = AlphaBeta(origin, i, std::numeric_limits<int>::min(),
                          std::numeric_limits<int>::max(), true);
      new_value = path.first;

      if (new_value != 9000) {
        old_value = new_value;
        move = path.second;
      }
    }

    return move;
}
