// cc lib
#include "../cclibrary/cclibrary.h"
#include "../cclibrary/aiplayer.h"

// stl
#include <exception>
#include <iostream>

int main(int /*argc*/, char** /*argv*/) try {

  GaymSpace::Game game;
  game.addPlayer<GaymSpace::AiPlayer>();
  game.addPlayer<GaymSpace::AiPlayer>();

  game.initNewGame();

  for (size_t t = 0; t < 100; t++) {
    for (const auto& player : game.playerIds()) {
      const auto& board = game.board();
      std::cout << "  " << CC::alg::occupiedPositions(board) << std::endl;
      std::cout << "Player " << size_t(player) << " takes a turn \n";
      game.think(std::chrono::seconds(1));
      //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
  //  const auto &players = game.playerIds();
  //  std::cout << "Player pieces:" << std::endl;
  //  for (const auto &player : players) {
  //    std::cout << "  " << game.pieces(player) << " --> " << game.goal(player)
  //              << std::endl;
  //  }

  //  const auto &board = game.board();
  //  std::cout << "Board occupied positions:" << std::endl;
  //  std::cout << "  " << CC::alg::occupiedPositions(board) << std::endl;

  return 0;
} catch (std::range_error e) {
  std::cout << "Range error; what: " << e.what() << std::endl;
} catch (std::exception e) {
  std::cout << "Some standard exception occured; what: " << e.what()
            << std::endl;
} catch (...) {
  std::cout << "Some exception occured..." << std::endl;
}
