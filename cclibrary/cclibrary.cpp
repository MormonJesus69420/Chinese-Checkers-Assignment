#include "cclibrary.h"

namespace CC
{

  std::unordered_set<BitPos> Graph::pieceNodes(const BitBoard& board,
                                               PlayerId        player)
  {

    std::unordered_set<BitPos> nodes;
    return nodes;
  }

  std::unordered_set<BitPos> Graph::toNodes(const BitPieces& pieces)
  {

    std::unordered_set<BitPos> nodes;
    return nodes;
  }

  const BitNbhd& Graph::nbhdNodes(BitPos node)
  {

    static BitNbhd nbhd;
    return nbhd;
  }

  std::unordered_set<BitMove> Graph::generateMoves(const BitBoard& board,
                                                   PlayerId        player)
  {

    std::unordered_set<BitMove> moves;
    return moves;
  }

  std::unordered_set<BitMove> Graph::generateMoves(const BitBoard& board,
                                                   BitPos          node)
  {

    std::unordered_set<BitMove> moves;
    return moves;
  }


  namespace alg
  {

    // Board validation
    BitPieces occupiedPositions(const BitBoard& board) { return BitPieces(); }

    bool occupied(const BitPieces& pieces, BitPos node) { return false; }

    bool occupied(const BitBoard& board, BitPos node) { return false; }

    // Move validation
    bool isLegalMove(const BitBoard& board, PlayerId player, BitMove move)
    {
      return false;
    }

    // Path finding
    std::vector<BitPos> dijkstraPath(BitBoard board, PlayerId player,
                                     BitPieces goal)
    {
      return std::vector<BitPos>();
    }

    std::vector<BitPos> dijkstraPath(BitBoard board, BitPos snode, BitPos enode)
    {
      return std::vector<BitPos>();
    }

  }   // END namespace alg

  Game::Game() {}

  void Game::initNewGame(NoPlayers no_players) {}

  bool Game::move(PlayerId player, BitMove move) { return false; }

  BitPieces Game::pieces(PlayerId) const { return BitPieces(); }
  BitPieces Game::goal(PlayerId) const { return BitPieces(); }

  std::set<PlayerId> Game::players() const { return std::set<PlayerId>(); }

  const BitBoard& Game::board() const
  {

    static BitBoard board;
    return board;
  }


}   // END namespace CC
