#include "cclibrary.h"

namespace CC {

  BitNodeSet Graph::pieceNodes(const BitBoard& board, PlayerId player) {
    BitNodeSet nodes;
    if (size_t(player) >= board.size()) return nodes;

    BitPieces pieces = board.at(size_t(player));

    return toNodes(pieces);
  }

  BitNodeSet Graph::toNodes(const BitPieces& pieces) {
    BitNodeSet nodes;

    for (size_t i = 0; i < pieces.size(); i++)
      if (pieces.test(i)) nodes.emplace(BitPos{i});

    return nodes;
  }

  const BitNbhd& Graph::nbhdNodes(BitPos node) {
    return m_graph.at(node.value()).second;
  }

  BitMoveSet Graph::generateMoves(const BitBoard& board, PlayerId player) {
    BitMoveSet moves;
    for (auto node : pieceNodes(board, player)) {
      auto nodeMoves = generateMoves(board, node);
      moves.insert(nodeMoves.begin(), nodeMoves.end());
    }

    return moves;
  }

  BitMoveSet Graph::generateMoves(const BitBoard& board, BitPos node) {
    BitMoveSet moves;   // Like Jagger
    auto       firstNeighbor = nbhdNodes(node);

    for (size_t i = 0; i < firstNeighbor.size(); i++) {
      if (firstNeighbor.at(i) != BitPos::invalid()) {
        if (!CC::alg::occupied(board, firstNeighbor.at(i)))
          moves.emplace(node, firstNeighbor.at(i));
        else {
          auto secondNeighbor = nbhdNodes(firstNeighbor.at(i));
          if (secondNeighbor.at(i) != BitPos::invalid()
              && !CC::alg::occupied(board, secondNeighbor.at(i)))
            moves.emplace(node, secondNeighbor.at(i));
        }
      }
    }
    return moves;
  }


  namespace alg {
    // Board validation
    BitPieces occupiedPositions(const BitBoard& board) {
      BitPieces occupied;

      for (BitPieces bp : board) {
        occupied |= bp;
      }

      return occupied;
    }

    bool occupied(const BitPieces& pieces, BitPos node) {
      if (node == BitPos::invalid() || node.value() < 0 || node.value() > 120)
        return false;

      return pieces.test(node.value());
    }

    bool occupied(const BitBoard& board, BitPos node) {
      if (node == BitPos::invalid() || node.value() < 0 || node.value() > 120)
        return false;

      return occupiedPositions(board).test(node.value());
    }

    // Move validation
    bool isLegalMove(const BitBoard& board, PlayerId player, BitMove move) {
      // Check valid PlayerId
      if (board.size() <= size_t(player)) return false;
      // Check if BitMove has valid BitPos
      if (move.first == BitPos::invalid() || move.second == BitPos::invalid())
        return false;
      // Check if BitMove tries to move a player piece to unoccupied position
      if (!occupied(board[size_t(player)], move.first)
          || occupied(board, move.second))
        return false;

      auto neigh = Graph::nbhdNodes(move.first);
      for (size_t i = 0; i < neigh.size(); i++) {
        if (neigh.at(i) == move.second) return true;
        if (neigh.at(i) != BitPos::invalid() && occupied(board, neigh.at(i))) {
          auto neighNeigh = Graph::nbhdNodes(neigh.at(i));
          if (neighNeigh.at(i) != BitPos::invalid()
              && neighNeigh.at(i) == move.second)
            return true;
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
      std::vector<BitPos> found, front, left;
      left.
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

    currentPlayer = PlayerId::One;

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
    if (!alg::isLegalMove(m_board, player_id, move)) return false;

    m_board.at(size_t(player_id))[move.first.value()]  = 0;
    m_board.at(size_t(player_id))[move.second.value()] = 1;
    toggleCurrentPlayer();
    return true;
  }

  void Game::toggleCurrentPlayer() {
    auto playerCount = m_players.size();
    auto currentId   = size_t(currentPlayer);
    auto newId       = ++currentId % playerCount;

    currentPlayer = PlayerId(newId);
  }

  void Game::think(std::chrono::seconds max_time) {
    // TODO
  }

  PlayerType Game::currentPlayerType() const {
    return m_players.at(size_t(currentPlayer))->type();
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
