#include "cclibrary.h"

namespace CC {

  BitNodeSet Graph::pieceNodes(const BitBoard& board, PlayerId player) {
    BitNodeSet nodes;
    return nodes;
  }

  BitNodeSet Graph::toNodes(const BitPieces& pieces) {
    BitNodeSet nodes;
    return nodes;
  }

  const BitNbhd& Graph::nbhdNodes(BitPos node) {
    static BitNbhd nbhd;
    return nbhd;
  }

  BitMoveSet Graph::generateMoves(const BitBoard& board, PlayerId player) {
    BitMoveSet moves;
    return moves;
  }

  BitMoveSet Graph::generateMoves(const BitBoard& board, BitPos node) {
    BitMoveSet moves;
    return moves;
  }

  namespace alg {

    // Board validation
    BitPieces occupiedPositions(const BitBoard& board) {
      BitPieces occupied
        = BitPieces(std::string("0000000000000000000000000000000000000000"
                                "0000000000000000000000000000000000000000"
                                "00000000000000000000000000000000000000000"));

      for (BitPieces bp : board) {
        occupied |= bp;
      }

      return occupied;
    }

    bool occupied(const BitPieces& pieces, BitPos node) {
      auto id = node.value();
      if (id < 0 || id > 120) return true;

      return pieces.test(id);
    }

    bool occupied(const BitBoard& board, BitPos node) {
      auto id = node.value();
      if (id < 0 || id > 120) return true;

      return occupiedPositions(board).test(id);
    }

    // Move validation
    bool isLegalMove(const BitBoard& board, PlayerId player, BitMove move) {
      return false;
    }

    // Path finding
    std::vector<BitPos> dijkstraPath(BitBoard board, PlayerId player,
                                     BitPieces goal) {
      return std::vector<BitPos>();
    }

    std::vector<BitPos> dijkstraPath(BitBoard board, BitPos snode,
                                     BitPos enode) {
      return std::vector<BitPos>();
    }

  }   // END namespace alg
}   // END namespace CC

namespace GaymSpace {
  using namespace CC;

  bool Game::initNewGame() {
    const std::unordered_set<size_t> playerNumberSet = {2, 3, 4, 6};

    const auto playerNumber = NoPlayers(m_players.size());

    if (playerNumberSet.count(size_t(playerNumber)) == 0) {
      return false;
    }

    switch (playerNumber) {
      case NoPlayers::Zero:
        return false;
      case NoPlayers::Two:
        initPlayer(getPieces(PieceSetId::One, true),
                   getPieces(PieceSetId::One, false));
        initPlayer(getPieces(PieceSetId::One, false),
                   getPieces(PieceSetId::One, true));
        break;
      case NoPlayers::Three:
        initPlayer(getPieces(PieceSetId::One, true),
                   getPieces(PieceSetId::One, false));
        initPlayer(getPieces(PieceSetId::Three, true),
                   getPieces(PieceSetId::Three, false));
        initPlayer(getPieces(PieceSetId::Two, false),
                   getPieces(PieceSetId::Two, true));
        break;
      case NoPlayers::Four:
        initPlayer(getPieces(PieceSetId::One, true),
                   getPieces(PieceSetId::One, false));
        initPlayer(getPieces(PieceSetId::One, false),
                   getPieces(PieceSetId::One, true));
        initPlayer(getPieces(PieceSetId::Two, true),
                   getPieces(PieceSetId::Two, false));
        initPlayer(getPieces(PieceSetId::Two, false),
                   getPieces(PieceSetId::Two, true));
        break;
      case NoPlayers::Six:
        initPlayer(getPieces(PieceSetId::One, true),
                   getPieces(PieceSetId::One, false));
        initPlayer(getPieces(PieceSetId::Two, true),
                   getPieces(PieceSetId::Two, false));
        initPlayer(getPieces(PieceSetId::Three, true),
                   getPieces(PieceSetId::Three, false));
        initPlayer(getPieces(PieceSetId::One, false),
                   getPieces(PieceSetId::One, true));
        initPlayer(getPieces(PieceSetId::Two, false),
                   getPieces(PieceSetId::Two, true));
        initPlayer(getPieces(PieceSetId::Three, false),
                   getPieces(PieceSetId::Three, true));
        break;
    }

    return true;
  }

  void Game::clearGame() {}

  bool Game::move(PlayerId player_id, BitMove move) { return false; }

  void Game::think(std::chrono::seconds max_time) {}

  PlayerType Game::currentPlayerType() const { return PlayerType::Human; }

  BitPieces Game::pieces(PlayerId player_id) const {
    auto id = size_t(player_id);
    if (id > m_board.size()) return BitPieces();
    return m_board[id];
  }

  BitPieces Game::goal(PlayerId player_id) const {
    auto id = size_t(player_id);
    if (id > m_goal.size()) return BitPieces();
    return m_goal[id];
  }

  PlayerIdSet Game::playerIds() const {
    PlayerIdSet idSet;
    for (size_t i = 0; i < m_players.size(); i++) idSet.insert(PlayerId(i));
    return idSet;
  }

  const Game::PlayerVector& Game::players() const { return m_players; }

  const BitBoard& Game::board() const { return m_board; }

  void Game::initPlayer(const BitPieces& start, const BitPieces& goal) {
    m_board.push_back(start);
    m_goal.push_back(goal);
  }

  const BitPieces& Game::getPieces(const CC::PieceSetId& setId,
                                   bool                  getFirstInPair) {
    return getFirstInPair ? pieceSets().at(size_t(setId)).first
                          : pieceSets().at(size_t(setId)).second;
  }

}   // END namespace GaymSpace
