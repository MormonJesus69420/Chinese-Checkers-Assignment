#ifndef CC_LIBRARY_H
#define CC_LIBRARY_H

#include <ccinterface.h>

namespace GaymSpace {

class Game : public CC::GameInterface {
public:
  void initNewGame(CC::NoPlayers no_players) override;
  bool move(CC::PlayerId player, CC::BitMove move) override;
  CC::BitPieces pieces(CC::PlayerId) const override;
  CC::BitPieces goal(CC::PlayerId) const override;
  CC::PlayerIdSet players() const override;
  const CC::BitBoard &board() const override;
private:
  void initPlayer(CC::PieceSetId setId, bool firstIsStart);
};

} // END namespace GaymSpace

#endif // CC_LIBRARY_H
