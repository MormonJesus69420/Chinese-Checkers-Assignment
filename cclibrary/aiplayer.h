#ifndef CC_AIPLAYER_H
#define CC_AIPLAYER_H

#include "cclibrary.h"

namespace GaymSpace {
  class AiPlayer : public CC::AIInterface {
  public:
    AiPlayer();

    void think(const CC::BitBoard& pieces, const CC::BitBoard& goals,
               CC::PlayerId player_id, std::chrono::seconds max_time) override;

    CC::BitMove bestMove() const override;
  private:
    CC::BitMove bestBitMove;
  };
}

#endif   // AIPLAYER_H
