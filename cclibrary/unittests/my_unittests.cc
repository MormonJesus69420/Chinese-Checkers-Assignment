// gtest
#include <gtest/gtest.h>   // googletest header file

// cc library
#include "../cclibrary.h"

using CustomGameClass = GaymSpace::Game;

TEST(MyUnittests, OccupiedPositions_EmptyBitBoard_ReturnsEmptyBitBoard) {
  CustomGameClass game;
  game.initNewGame();

  auto pieces = CC::alg::occupiedPositions(game.board());

  EXPECT_EQ(pieces, CC::BitPieces(std::string(
                      "0000000000000000000000000000000000000000"
                      "0000000000000000000000000000000000000000"
                      "00000000000000000000000000000000000000000")));
}

TEST(MyUnittests,
     OccupiedPositions_SixPlayers_ReturnsBitBoardWithAllSixPlayers) {
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  auto pieces = CC::alg::occupiedPositions(game.board());

  EXPECT_EQ(pieces, CC::BitPieces(std::string(
                      "1111111111111100000111111100000011111000"
                      "0000111000000001000000000100000000111000"
                      "00001111100000011111110000011111111111111")));
}

TEST(MyUnittests, OccupiedSinglePlayer_CorrectBitPos_ReturnsBool) {
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  auto occupied
    = CC::alg::occupied(game.pieces(CC::PlayerId::One), CC::BitPos(0));
  auto unoccupied
    = CC::alg::occupied(game.pieces(CC::PlayerId::One), CC::BitPos(100));

  EXPECT_EQ(occupied, true);
  EXPECT_EQ(unoccupied, false);
}

TEST(MyUnittests, OccupiedSinglePlayer_WrongBitPos_ReturnsTrue) {
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  auto occupied1
    = CC::alg::occupied(game.pieces(CC::PlayerId::One), CC::BitPos(-1));
  auto occupied2
    = CC::alg::occupied(game.pieces(CC::PlayerId::One), CC::BitPos(121));

  EXPECT_EQ(occupied1, true);
  EXPECT_EQ(occupied2, true);
}

TEST(MyUnittests, OccupiedWholeBoard_CorrectBitPos_ReturnsBool) {
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  auto occupied1  = CC::alg::occupied(game.board(), CC::BitPos(0));
  auto occupied2  = CC::alg::occupied(game.board(), CC::BitPos(120));
  auto unoccupied = CC::alg::occupied(game.board(), CC::BitPos(50));

  EXPECT_EQ(occupied1, true);
  EXPECT_EQ(occupied2, true);
  EXPECT_EQ(unoccupied, false);
}

TEST(MyUnittests, OccupiedWholeBoard_WrongBitPos_ReturnsTrue) {
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  auto occupied1 = CC::alg::occupied(game.board(), CC::BitPos(-1));
  auto occupied2 = CC::alg::occupied(game.board(), CC::BitPos(121));

  EXPECT_EQ(occupied1, true);
  EXPECT_EQ(occupied2, true);
}

TEST(MyUnittests, Pieces_ValidPlayer_ReturnsPlayerBitSet) {
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  auto playerPieces = game.pieces(CC::PlayerId::One);

  EXPECT_EQ(playerPieces,
            game.pieceSets().at(size_t(CC::PieceSetId::One)).first);
}

TEST(MyUnittests, Pieces_InvalidPlayer_ReturnsEmptyBitSet) {
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  auto playerPieces = game.pieces(CC::PlayerId::Six);

  EXPECT_TRUE(playerPieces.none());
}

TEST(MyUnittests, Goal_ValidPlayer_ReturnsPlayerBitSet) {
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  auto playerPieces = game.goal(CC::PlayerId::One);

  EXPECT_EQ(playerPieces,
            game.pieceSets().at(size_t(CC::PieceSetId::One)).second);
}

TEST(MyUnittests, Goal_InvalidPlayer_ReturnsEmptyBitSet) {
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  auto playerPieces = game.goal(CC::PlayerId::Six);

  EXPECT_TRUE(playerPieces.none());
}

TEST(MyUnittests, PlayerIds__ReturnsProperSetOfIds) {
  CustomGameClass game;

  auto ids1 = game.playerIds();

  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  auto ids2 = game.playerIds();

  EXPECT_EQ(ids1.size(), size_t(0));
  EXPECT_EQ(ids2.size(), size_t(6));
}

TEST(MyUnittests, ClearGame__ShouldResetGame) {
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();
  game.clearGame();

  auto board    = game.board();
  auto goal     = game.goal(CC::PlayerId::One);
  auto playerId = game.currentPlayerId();

  EXPECT_EQ(board.size(), size_t(0));
  EXPECT_EQ(goal, CC::BitPieces(
                    std::string("0000000000000000000000000000000000000000"
                                "0000000000000000000000000000000000000000"
                                "00000000000000000000000000000000000000000")));
  EXPECT_EQ(playerId, CC::PlayerId::One);
}
