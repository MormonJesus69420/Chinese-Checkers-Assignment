// gtest
#include <gtest/gtest.h> // googletest header file

// cc library
#include "../cclibrary.h"

using CustomGameClass = GaymSpace::Game;

TEST(PredefinedUnittests, HelloWorld) { CustomGameClass game; }

TEST(PredefinedUnittests, InitNewGameSavesNumnerOfPlayers) {
    auto playerNum = CC::NoPlayers::Two;
    CustomGameClass game;
    game.initNewGame(playerNum);

    ASSERT_EQ(game.board().size(), size_t(playerNum));
}

