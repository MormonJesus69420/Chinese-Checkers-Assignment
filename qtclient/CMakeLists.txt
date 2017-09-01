# CMake sub-project setup
project(qtclient VERSION 0.1 LANGUAGES CXX)

# Find Qt libs
find_package(Qt5Core 5.9)
find_package(Qt5Quick 5.9)
find_package(Qt5Gui 5.9)

# Files
set( HDRS
  guiapplication.h )

set( SRCS
  main.cpp
  ccgamemodel.cpp
  guiapplication.cpp )

QT5_WRAP_CPP( HDRS_MOC
  ccgamemodel.h
  guiapplication.h )

QT5_ADD_RESOURCES( RCCS_MOC
  resources/qml.qrc )

# Executable
add_executable(${PROJECT_NAME} ${SRCS} ${HDRS} ${HDRS_MOC} ${RCCS_MOC})
target_link_libraries(${PROJECT_NAME}
  cclibrary CCInterface
  Qt5::Core Qt5::Quick Qt5::Gui)
