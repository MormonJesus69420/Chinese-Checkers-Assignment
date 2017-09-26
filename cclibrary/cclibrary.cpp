#include "cclibrary.h"

namespace CC {

  BitNodeSet Graph::pieceNodes(const BitBoard& board, PlayerId player) {
    BitNodeSet nodes;
    if (size_t(player) >= board.size()) return nodes;

    BitPieces pieces = board.at(size_t(player));
    nodes            = toNodes(pieces);

    if (nodes.size() != 10) return BitNodeSet();

    return nodes;
  }

  BitNodeSet Graph::toNodes(const BitPieces& pieces) {
    BitNodeSet nodes;

    for (size_t i = 0; i < pieces.size(); i++)
      if (pieces.test(i)) nodes.emplace(BitPos{i});

    return nodes;
  }

  const BitNbhd& Graph::nbhdNodes(BitPos node) {
    auto& pair = m_graph.at(node.value());
    return pair.second;
  }

  BitMoveSet Graph::generateMoves(const BitBoard& board, PlayerId player) {
    BitMoveSet moves;
    auto       nodes = pieceNodes(board, player);
    for (auto node : nodes) {
      auto nodeMoves = generateMoves(board, node);
      moves.insert(nodeMoves.begin(), nodeMoves.end());
    }

    return moves;
  }

  BitMoveSet Graph::generateMoves(const BitBoard& board, BitPos node) {
    BitMoveSet moves;   // Like Jagger
    auto       firstNeighbor = nbhdNodes(node);

    for (size_t i = 0; i < firstNeighbor.size(); i++) {
      BitPos& neigh = firstNeighbor.at(i);
      if (neigh != BitPos::invalid()) {
        if (!CC::alg::occupied(board, neigh))
          moves.emplace(node, neigh);
        else {
          const BitPos& neigh2 = Graph::nbhdNodes(neigh).at(i);
          if (neigh2 != BitPos::invalid() && !CC::alg::occupied(board, neigh2))
            moves.emplace(node, neigh2);
        }
      }
    }
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
      if (node == BitPos::invalid()) return false;

      return pieces.test(id);
    }

    bool occupied(const BitBoard& board, BitPos node) {
      auto id = node.value();
      if (node == BitPos::invalid()) return false;

      return occupiedPositions(board).test(id);
    }

    // Move validation
    bool isLegalMove(const BitBoard& board, PlayerId player, BitMove move) {
      auto id = size_t(player);
      if (board.size() <= id) return false;

      if (move.first == BitPos::invalid() || move.second == BitPos::invalid())
        return false;

      BitPieces pieces = board[id];
      if (!occupied(pieces, move.first) || occupied(board, move.second))
        return false;

      auto neigh = Graph::nbhdNodes(move.first);
      for (size_t i = 0; i < neigh.size(); i++) {
        BitPos& neigh1 = neigh.at(i);
        if (neigh1 == move.second) return true;
        if (neigh1 != BitPos::invalid() && occupied(board, neigh1)) {
          const BitPos& neigh2 = Graph::nbhdNodes(neigh1).at(i);
          if (neigh2 != BitPos::invalid() && neigh2 == move.second) return true;
        }
      }

      return false;
    }

    // Path finding
    std::vector<BitPos> dijkstraPath(BitBoard board, PlayerId player,
                                     BitPieces goal) {
      // TODO

      return std::vector<BitPos>();
    }

    std::vector<BitPos> dijkstraPath(BitBoard board, BitPos snode,
                                     BitPos enode) {
      // TODO

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

    currentPlayer = PlayerId(0);

    switch (playerNumber) {
      case NoPlayers::Zero:
        return false;
      case NoPlayers::Two:
        initPlayer(getPieces(PieceSetId::One, true),
                   getPieces(PieceSetId::One, false));
        initPlayer(getPieces(PieceSetId::One, false),
                   getPieces(PieceSetId::One, true));
        move(PlayerId::One, BitMove{BitPos{5}, BitPos{17}});
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
        initPlayer(getPieces(PieceSetId::Two, true),
                   getPieces(PieceSetId::Two, false));
        initPlayer(getPieces(PieceSetId::One, false),
                   getPieces(PieceSetId::One, true));
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

  void Game::clearGame() {
    m_board.clear();
    m_goal.clear();
    m_players.clear();
    currentPlayer = PlayerId::One;
  }

  bool Game::move(PlayerId player_id, BitMove move) {
    // TODO UPDATE CURRENT PLAYER
    if (!alg::isLegalMove(m_board, player_id, move)) return false;

    m_board.at(size_t(player_id))[move.first.value()]  = 0;
    m_board.at(size_t(player_id))[move.second.value()] = 1;
    return true;
  }

  void Game::think(std::chrono::seconds max_time) {
    // TODO
  }

  PlayerType Game::currentPlayerType() const {
    // TODO
    return PlayerType::Human;
  }

  PlayerId Game::currentPlayerId() const { return currentPlayer; }

  BitPieces Game::pieces(PlayerId player_id) const {
    auto id = size_t(player_id);
    if (id >= m_board.size()) return BitPieces();
    return m_board[id];
  }

  BitPieces Game::goal(PlayerId player_id) const {
    auto id = size_t(player_id);
    if (id >= m_goal.size()) return BitPieces();
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
