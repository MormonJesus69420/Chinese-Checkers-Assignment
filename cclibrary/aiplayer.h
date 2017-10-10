#ifndef CC_AIPLAYER_H
#define CC_AIPLAYER_H

#include "cclibrary.h"
#include "map"
#include "queue"
#include <utility>

namespace GaymSpace {
  class AiPlayer : public CC::AIInterface {
  public:
    AiPlayer();

    void think(const CC::BitBoard& pieces, const CC::BitBoard& goals,
               CC::PlayerId player_id, std::chrono::seconds max_time) override;

    CC::BitMove bestBitMove() const override;

  private:
    CC::BitMove bestMove;
    std::map<CC::BitPos, size_t> values;
    bool valuesNotInitialized = true;
    void generateInitialValueSet(const CC::BitBoard& pieces,
                                 const CC::BitBoard& goals,
                                 CC::PlayerId        player_id);
    void addValueAndPushNeighbours(CC::BitPos                      pos,
                                   std::unordered_set<CC::BitPos>& visited,
                                   std::queue<CC::BitPos>&         queue);
    CC::BitPos getFurthestGoalPiece(CC::BitPieces goal);
  };
}

#endif   // AIPLAYER_H
