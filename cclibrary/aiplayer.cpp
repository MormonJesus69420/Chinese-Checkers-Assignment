#include "aiplayer.h"
#include <random>
#include <vector>

namespace GaymSpace {
  AiPlayer::AiPlayer() {}

  void AiPlayer::think(const CC::BitBoard& pieces, const CC::BitBoard& goals,
                       CC::PlayerId player_id, std::chrono::seconds max_time) {
    CC::BitMoveSet bms = CC::Graph::generateMoves(pieces, player_id);

    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> dis(0, bms.size() - 1);
    std::vector<CC::BitMove>        bitMoveVector(bms.begin(), bms.end());

    bestBitMove = bitMoveVector.at(dis(gen));
  }

  CC::BitMove AiPlayer::bestMove() const { return bestBitMove; }
}
