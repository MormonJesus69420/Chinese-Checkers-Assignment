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
    BitPieces occupied = BitPieces(std::string("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));

    for(BitPieces bp: board){
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

void Game::initNewGame(NoPlayers no_players) {
    m_no_players = no_players;

    switch (m_no_players) {
    case NoPlayers::Zero:
        // DO SOMETHING
        break;
    case NoPlayers::Two:
        // REFACTOR TO METHOD initPlayer(BitPieces start, BitPieces goal)
        initPlayer(PieceSetId::One, true);
        initPlayer(PieceSetId::One, false);
        break;
    case NoPlayers::Three:
        // DO SOMETHING
        break;
    case NoPlayers::Four:
        // DO SOMETHING
        break;
    case NoPlayers::Six:
        // DO SOMETHING
        break;
    default:
        break;
    }
    // TODO EVERYTHING
}

bool Game::move(PlayerId player, BitMove move) {
    // TODO

    return false;
}

BitPieces Game::pieces(PlayerId) const {
    // TODO
    BitPieces pieces;
    return pieces;
}

BitPieces Game::goal(PlayerId) const {
    // TODO
    BitPieces pieces;
    return pieces;
}

PlayerIdSet Game::players() const {
    // TODO
    PlayerIdSet set;
    return set;
}

const BitBoard &Game::board() const {
    // TODO
    return m_board;
}

void Game::initPlayer(PieceSetId setId, bool firstIsStart)
{
    const auto & pair = pieceSets().at(size_t(setId));
    BitPieces start = firstIsStart ? pair.first: pair.second;
    BitPieces goal = firstIsStart ? pair.second: pair.first;
    m_board.push_back(start);
    m_goal.push_back(goal);
}



} // END namespace GaymSpace
