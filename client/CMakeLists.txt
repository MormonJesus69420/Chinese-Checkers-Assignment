# CMake sub-project setup
project(client VERSION 0.1 LANGUAGES CXX)

set( SRCS main.cpp)
add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} cclibrary CCInterface)
