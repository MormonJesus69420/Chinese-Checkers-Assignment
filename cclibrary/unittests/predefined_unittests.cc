// gtest
#include <gtest/gtest.h>   // googletest header file

// cc library
#include "../cclibrary.h"

using CustomGameClass = MySoothingNamespace::Game;

TEST(PredefinedUnittests, BoardInitialization_TwoPlayerGame_PlayerAndGoalPieces)
{
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  // Player one
  EXPECT_EQ(game.pieces(CC::PlayerId::One),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).first);
  EXPECT_EQ(
    game.goal(CC::PlayerId::One),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).second);

  // Player two
  EXPECT_EQ(
    game.pieces(CC::PlayerId::Two),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).second);
  EXPECT_EQ(game.goal(CC::PlayerId::Two),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).first);
}

TEST(PredefinedUnittests, BoardInitialization_ThreePlayerGame_PlayerAndGoalPieces)
{
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  // Player one
  EXPECT_EQ(game.pieces(CC::PlayerId::One),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).first);
  EXPECT_EQ(
    game.goal(CC::PlayerId::One),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).second);

  // Player two
  EXPECT_EQ(
    game.pieces(CC::PlayerId::Two),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Three)).first);
  EXPECT_EQ(game.goal(CC::PlayerId::Two),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Three)).second);

  // Player three
  EXPECT_EQ(
    game.pieces(CC::PlayerId::Three),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Two)).second);
  EXPECT_EQ(game.goal(CC::PlayerId::Three),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Two)).first);
}

TEST(PredefinedUnittests, BoardInitialization_FourPlayerGame_PlayerAndGoalPieces)
{
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();


  // Player one
  EXPECT_EQ(game.pieces(CC::PlayerId::One),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).first);
  EXPECT_EQ(
    game.goal(CC::PlayerId::One),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).second);

  // Player two
  EXPECT_EQ(
    game.pieces(CC::PlayerId::Two),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).second);
  EXPECT_EQ(game.goal(CC::PlayerId::Two),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).first);

  // Player three
  EXPECT_EQ(
    game.pieces(CC::PlayerId::Three),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Two)).first);
  EXPECT_EQ(game.goal(CC::PlayerId::Three),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Two)).second);

  // Player four
  EXPECT_EQ(
    game.pieces(CC::PlayerId::Four),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Two)).second);
  EXPECT_EQ(game.goal(CC::PlayerId::Four),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Two)).first);
}

TEST(PredefinedUnittests, BoardInitialization_SixPlayerGame_PlayerAndGoalPieces)
{
  CustomGameClass game;
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.addPlayer<CC::HumanPlayer>();
  game.initNewGame();

  // Player one
  EXPECT_EQ(game.pieces(CC::PlayerId::One),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).first);
  EXPECT_EQ(
    game.goal(CC::PlayerId::One),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).second);

  // Player two
  EXPECT_EQ(
    game.pieces(CC::PlayerId::Two),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Two)).first);
  EXPECT_EQ(game.goal(CC::PlayerId::Two),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Two)).second);

  // Player three
  EXPECT_EQ(
    game.pieces(CC::PlayerId::Three),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Three)).first);
  EXPECT_EQ(game.goal(CC::PlayerId::Three),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Three)).second);

  // Player four
  EXPECT_EQ(
    game.pieces(CC::PlayerId::Four),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).second);
  EXPECT_EQ(game.goal(CC::PlayerId::Four),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::One)).first);

  // Player five
  EXPECT_EQ(
    game.pieces(CC::PlayerId::Five),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Two)).second);
  EXPECT_EQ(game.goal(CC::PlayerId::Five),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Two)).first);

  // Player six
  EXPECT_EQ(
    game.pieces(CC::PlayerId::Six),
    CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Three)).second);
  EXPECT_EQ(game.goal(CC::PlayerId::Six),
            CustomGameClass::pieceSets().at(size_t(CC::PieceSetId::Three)).first);
}
