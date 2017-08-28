# CMake project setup
cmake_minimum_required(VERSION 3.4)
project(CCTemplate VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)


# Compiler settings
if(MSVC)
  message("Compiler: ${CMAKE_CXX_COMPILER_ID}")
elseif (CMAKE_CXX_COMPILER_ID MATCHES GNU)
  message("Compiler: ${CMAKE_CXX_COMPILER_ID}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Werror")
elseif (CMAKE_CXX_COMPILER_ID MATCHES Clang)
  message("Compiler: ${CMAKE_CXX_COMPILER_ID}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -pedantic -Werror")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat -Wno-c++98-compat-pedantic")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-documentation" )
else()
  message(FATAL_ERROR "Compiler platform <${CMAKE_CXX_COMPILER_ID}> not supported!")
endif()


# Interface
include_directories(${CC_INTERFACE_SOURCE_DIR})
message("Interface include source dir: ${CC_INTERFACE_SOURCE_DIR}")
link_directories(${CC_INTERFACE_BUILD_DIR})
message("Interface include build dir: ${CC_INTERFACE_BUILD_DIR}")


# Library
option(BUILD_LIBRARY "Build CC library..." TRUE)
if(BUILD_LIBRARY)
  add_subdirectory(cclibrary)
endif()


# Client
option(BUILD_CLIENT "Build CC client..." FALSE)
if(BUILD_CLIENT)
  add_subdirectory(client)
endif()
