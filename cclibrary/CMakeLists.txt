# CMake sub-project setup
project(cclibrary VERSION 0.1 LANGUAGES CXX)

# Find libs
# find_package(benchmark)

#
set( HDRS cclibrary.h)
set( SRCS cclibrary.cpp)
add_library(${PROJECT_NAME} ${HDRS} ${SRCS})
#target_link_libraries(${PROJECT_NAME} )

option(BUILD_LIBRARY_TESTS "Build CC library unit tests..." TRUE)
if(BUILD_LIBRARY_TESTS)

  # Find GTest
  find_package(GTest REQUIRED)

  # Test whether GTest where found
  if(GTEST_FOUND)

    # enable cmake testing framework; ctest
    enable_testing()

    # Tests
    set(TESTS hello_world)

    # Add tests
    foreach(TEST ${TESTS})

      add_executable( unittest_${TEST} ${HDRS} unittests/${TEST}.cc  )
      target_link_libraries(unittest_${TEST}
        ${PROJECT_NAME} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
      gtest_add_tests( unittest_${TEST} "" AUTO )
    endforeach(TEST)
  else()
    message("GTest not found!")
  endif()
endif()

option(BUILD_LIBRARY_TESTS "Build CC library unit tests..." TRUE)
if(BUILD_LIBRARY_TESTS)


endif()
