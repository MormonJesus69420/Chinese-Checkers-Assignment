#include "guiapplication.h"

// cc lib
#include "../cclibrary/cclibrary.h"


// stl
#include <iostream>
#include <exception>



int main(int argc, char** argv) try {

  GuiApplication a(argc, argv);
  return a.exec();
}
catch (std::range_error e) {
  std::cout << "Range error; what: " << e.what() << std::endl;
}
catch (std::exception e) {
  std::cout << "Some standard exception occured; what: " << e.what()
            << std::endl;
}
catch (...) {
  std::cout << "Some exception occured..." << std::endl;
}
