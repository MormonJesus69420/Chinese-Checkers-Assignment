#include "cclibrary.h"

namespace CC {

BitNodeSet Graph::pieceNodes(const BitBoard &board, PlayerId player) {

  BitNodeSet nodes;
  return nodes;
}

BitNodeSet Graph::toNodes(const BitPieces &pieces) {

  BitNodeSet nodes;
  return nodes;
}

const BitNbhd &Graph::nbhdNodes(BitPos node) {
  static BitNbhd nbhd;
  return nbhd;
}

BitMoveSet Graph::generateMoves(const BitBoard &board, PlayerId player) {

  BitMoveSet moves;
  return moves;
}

BitMoveSet Graph::generateMoves(const BitBoard &board, BitPos node) {

  BitMoveSet moves;
  return moves;
}

namespace alg {

// Board validation
BitPieces occupiedPositions(const BitBoard &board) {
  BitPieces occupied = BitPieces(std::string(
      "000000000000000000000000000000000000000000000000000000000000000000000000"
      "0000000000000000000000000000000000000000000000000"));

  for (BitPieces bp : board) {
    occupied |= bp;
  }

  return occupied;
}

bool occupied(const BitPieces &pieces, BitPos node) { return false; }

bool occupied(const BitBoard &board, BitPos node) { return false; }

// Move validation
bool isLegalMove(const BitBoard &board, PlayerId player, BitMove move) {
  return false;
}

// Path finding
std::vector<BitPos> dijkstraPath(BitBoard board, PlayerId player,
                                 BitPieces goal) {
  return std::vector<BitPos>();
}

std::vector<BitPos> dijkstraPath(BitBoard board, BitPos snode, BitPos enode) {
  return std::vector<BitPos>();
}

} // END namespace alg
} // END namespace CC

namespace GaymSpace {
using namespace CC;

bool Game::initNewGame() {
  const std::unordered_set<size_t> playerNumberSet = {
      2, 3, 4, 6};

  const auto playerNumber = NoPlayers(m_players.size());

  if (playerNumberSet.count(size_t(playerNumber)) == 0) {
    return false;
  }

  switch (playerNumber) {
  case NoPlayers::Two:
    initPlayer( PieceSetId::One, PlayerId::One);
    initPlayer( PieceSetId::One , PlayerId::Two);
    break;
  default:
    break;
  }

  return false;
}

void Game::clearGame() {}

bool Game::move(PlayerId player_id, BitMove move) { return false; }

void Game::think(std::chrono::seconds max_time) {}

PlayerType Game::currentPlayerType() const { return PlayerType::Human; }

BitPieces Game::pieces(PlayerId player_id) const {
  BitPieces pieces;
  return pieces;
}

BitPieces Game::goal(PlayerId player_id) const {
  BitPieces pieces;
  return pieces;
}

PlayerIdSet Game::playerIds() const {
  PlayerIdSet idSet;
  return idSet;
}

const Game::PlayerVector &Game::players() const { return m_players; }

const BitBoard &Game::board() const { return m_board; }

void Game::initPlayer(PieceSetId setId, CC::PlayerId playerId) {
  const auto &pair = pieceSets().at(size_t(setId));
  if (size_t(playerId) % 2 == 0) {
    m_board.push_back(pair.first);
    m_goal.push_back(pair.second);
  } else {
    m_board.push_back(pair.second);
    m_goal.push_back(pair.first);
  }
}

} // END namespace GaymSpace
