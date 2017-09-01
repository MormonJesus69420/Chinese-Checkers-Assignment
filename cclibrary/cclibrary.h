#ifndef CC_LIBRARY_H
#define CC_LIBRARY_H

#include <ccinterface.h>

namespace GaymSpace {

class Game : public CC::GameInterface {
public:
  bool initNewGame() override;
  void clearGame() override;
  bool move(CC::PlayerId player_id, CC::BitMove move) override;
  void think(std::chrono::seconds max_time) override;
  CC::PlayerType currentPlayerType() const override;
  CC::BitPieces pieces(CC::PlayerId player_id) const override;
  CC::BitPieces goal(CC::PlayerId) const override;
  CC::PlayerIdSet playerIds() const;
  const PlayerVector& players() const override;
  const CC::BitBoard& board() const override;
private:
  void initPlayer(CC::PieceSetId setId, CC::PlayerId playerId);
};

} // END namespace GaymSpace

#endif // CC_LIBRARY_H
