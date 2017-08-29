#include "cclibrary.h"

namespace CC
{

  BitNodeSet Graph::pieceNodes(const BitBoard& board, PlayerId player)
  {

    BitNodeSet nodes;
    return nodes;
  }

  BitNodeSet Graph::toNodes(const BitPieces& pieces)
  {

    BitNodeSet nodes;
    return nodes;
  }

  const BitNbhd& Graph::nbhdNodes(BitPos node)
  {

    static BitNbhd nbhd;
    return nbhd;
  }

  BitMoveSet Graph::generateMoves(const BitBoard& board, PlayerId player)
  {

    BitMoveSet moves;
    return moves;
  }

  BitMoveSet Graph::generateMoves(const BitBoard& board, BitPos node)
  {

    BitMoveSet moves;
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
}   // END namespace CC


namespace MySoothingNamespace
{


}   // END namespace CC
