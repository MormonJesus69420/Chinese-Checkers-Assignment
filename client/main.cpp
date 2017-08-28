// cc lib
#include "../cclibrary/cclibrary.h"

// stl
#include <iostream>
#include <exception>



int main( int /*argc*/, char** /*argv*/ ) try {

  MySoothingNamespace::Game game;

  game.initNewGame(CC::NoPlayers::Six);


  const auto& players = game.players();
  std::cout << "Player pieces:" << std::endl;
  for( const auto& player : players ) {
    std::cout << "  " << game.pieces(player) << " --> " << game.goal(player) << std::endl;
  }

  const auto& board = game.board();
  std::cout << "Board occupied positions:" << std::endl;
  std::cout << "  " << CC::alg::occupiedPositions(board) << std::endl;


  return 0;
}
catch(std::range_error e) {
  std::cout << "Range error; what: " << e.what() << std::endl;
}
catch(std::exception e){
  std::cout << "Some standard exception occured; what: " << e.what() << std::endl;
}
catch(...){
  std::cout << "Some exception occured..." << std::endl;
}
