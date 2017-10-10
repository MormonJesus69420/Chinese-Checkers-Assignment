#include "aiplayer.h"
#include "cclibrary.h"
#include <algorithm>
#include <ccinterface.h>

using namespace CC;

namespace GaymSpace {
  AiPlayer::AiPlayer() {}

  void AiPlayer::think(const BitBoard& pieces, const BitBoard& goals,
                       PlayerId player_id, std::chrono::seconds max_time) {
    if (valuesNotInitialized) {
      generateInitialValueSet(pieces, goals, player_id);
      valuesNotInitialized = false;
    }

    auto sum = 0;

    for (auto node : Graph::pieceNodes(pieces, player_id)) sum += values[node];

    size_t               bestMoveSum  = 0;
    auto                 tempBestMove = BitMove();
    size_t               tempSum;
    std::vector<BitMove> moves;

    for (auto move : Graph::generateMoves(pieces, player_id))
      moves.push_back(move);

    std::random_shuffle(moves.begin(), moves.end());

    for (auto move : moves) {
      tempSum = sum - values[move.first] + values[move.second];
      if (tempSum > bestMoveSum) {
        tempBestMove = move;
        bestMoveSum  = tempSum;
      }
    }

    bestMove = tempBestMove;
  }

  BitMove AiPlayer::bestBitMove() const { return bestMove; }

  void AiPlayer::generateInitialValueSet(const BitBoard& pieces,
                                         const BitBoard& goals,
                                         PlayerId        player_id) {
    BitPos furthest = getFurthestGoalPiece(goals.at(size_t(player_id)));

    auto visited = std::unordered_set<BitPos>();
    auto queue   = std::queue<BitPos>();

    values[furthest] = 17;
    visited.insert(furthest);
    queue.push(furthest);

    while (!queue.empty()) {
      addValueAndPushNeighbours(queue.front(), visited, queue);
      queue.pop();
    }
  }

  void AiPlayer::addValueAndPushNeighbours(BitPos                      pos,
                                           std::unordered_set<BitPos>& visited,
                                           std::queue<BitPos>&         queue) {
    auto value = values[pos];
    auto nbhd  = Graph::nbhdNodes(pos);
    for (auto nb : nbhd) {
      if (nb == BitPos::invalid()) continue;
      if (visited.count(nb) != 0) continue;
      values[nb] = value - 1;
    }
    for (auto nb : nbhd) {
      if (nb == BitPos::invalid()) continue;
      if (visited.count(nb) == 0) {
        queue.push(nb);
        visited.insert(nb);
      }
    }
  }

  BitPos AiPlayer::getFurthestGoalPiece(BitPieces goal) {
    for (size_t t : {0, 10, 22, 98, 110, 120})
      if (goal.test(t)) return BitPos(t);
    return BitPos::invalid();
  }
}
