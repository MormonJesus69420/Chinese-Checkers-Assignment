// gtest
#include <gtest/gtest.h>   // googletest header file

// cc library
#include "../cclibrary.h"

using CustomGameClass = GaymSpace::Game;

auto emptyBitPieces
  = CC::BitPieces(std::string("0000000000000000000000000000000000000000"
                              "0000000000000000000000000000000000000000"
                              "00000000000000000000000000000000000000000"));
auto sixPlayerBitPieces
  = CC::BitPieces(std::string("1111111111111100000111111100000011111000"
                              "0000111000000001000000000100000000111000"
                              "00001111100000011111110000011111111111111"));
auto twoPlayerBitPieces
  = CC::BitPieces(std::string("1111111111000000000000000000000000000000"
                              "0000000000000000000000000000000000000000"
                              "00000000000000000000000000000001111111111"));
auto playerOnePieces
  = CC::BitPieces(std::string("0000000000000000000000000000000000000000"
                              "0000000000000000000000000000000000000000"
                              "00000000000000000000000000000001111111111"));
auto playerTwoPieces
  = CC::BitPieces(std::string("1111111111000000000000000000000000000000"
                              "0000000000000000000000000000000000000000"
                              "00000000000000000000000000000000000000000"));
auto emptyBoard     = CC::BitBoard{};
auto twoPlayerBoard = CC::BitBoard{playerOnePieces, playerTwoPieces};
auto playerOneId    = CC::PlayerId::One;
auto zero           = size_t(0);

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
  auto goal     = game.goal(playerOneId);
  auto playerId = game.currentPlayerId();

  EXPECT_EQ(board.size(), zero);
  EXPECT_EQ(goal, emptyBitPieces);
  EXPECT_EQ(playerId, playerOneId);
}

TEST(MyUnittests, OccupiedPositions_EmptyBitBoard_ReturnsEmptyBitBoard) {
  auto pieces = CC::alg::occupiedPositions(emptyBoard);

  EXPECT_EQ(pieces, emptyBitPieces);
}

TEST(MyUnittests, OccupiedPositions_TwoPlayers_ReturnsBoardWithPlayers) {
  auto pieces = CC::alg::occupiedPositions(twoPlayerBoard);

  EXPECT_EQ(pieces, twoPlayerBitPieces);
}

TEST(MyUnittests, OccupiedSinglePlayer_CorrectBitPos_ReturnsBool) {
  auto occupied   = CC::alg::occupied(playerOnePieces, CC::BitPos(0));
  auto unoccupied = CC::alg::occupied(playerOnePieces, CC::BitPos(60));

  EXPECT_EQ(occupied, true);
  EXPECT_EQ(unoccupied, false);
}

TEST(MyUnittests, OccupiedSinglePlayer_WrongBitPos_ReturnsFalse) {
  auto wrong1 = CC::alg::occupied(playerOnePieces, CC::BitPos(-1));
  auto wrong2 = CC::alg::occupied(playerOnePieces, CC::BitPos(121));
  auto wrong3 = CC::alg::occupied(playerOnePieces, CC::BitPos::invalid());

  EXPECT_EQ(wrong1, false);
  EXPECT_EQ(wrong2, false);
  EXPECT_EQ(wrong3, false);
}

TEST(MyUnittests, OccupiedWholeBoard_CorrectBitPos_ReturnsBool) {
  auto occupied1  = CC::alg::occupied(twoPlayerBoard, CC::BitPos(0));
  auto occupied2  = CC::alg::occupied(twoPlayerBoard, CC::BitPos(120));
  auto unoccupied = CC::alg::occupied(twoPlayerBoard, CC::BitPos(60));

  EXPECT_EQ(occupied1, true);
  EXPECT_EQ(occupied2, true);
  EXPECT_EQ(unoccupied, false);
}

TEST(MyUnittests, OccupiedWholeBoard_WrongBitPos_ReturnsFalse) {
  auto wrong1 = CC::alg::occupied(twoPlayerBoard, CC::BitPos(-1));
  auto wrong2 = CC::alg::occupied(twoPlayerBoard, CC::BitPos(121));
  auto wrong3 = CC::alg::occupied(twoPlayerBoard, CC::BitPos::invalid());

  EXPECT_EQ(wrong1, false);
  EXPECT_EQ(wrong2, false);
  EXPECT_EQ(wrong3, false);
}

TEST(MyUnittests, Pieces_ValidPlayer_ReturnsPlayerBitSet) {
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  auto playerPieces = game.pieces(CC::PlayerId::One);

  EXPECT_EQ(playerPieces, playerOnePieces);
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
