# CMake sub-project setup
project(cclibrary VERSION 0.1 LANGUAGES CXX)


# List source files
set( HDRS cclibrary.h)
set( SRCS cclibrary.cpp)
add_library(${PROJECT_NAME} ${HDRS} ${SRCS})


# Build unittest rules
option(BUILD_LIBRARY_TESTS "Build CC library unittests..." FALSE)
if(BUILD_LIBRARY_TESTS)

  # Find GTest
  find_package(GTest QUIET)
  if(GTEST_FOUND)

    message("GTest found!")

    # Add GTest include folder and libraries
    include_directories(${GTEST_INCLUDE_DIR})
    link_libraries(${GTEST_BOTH_LIBRARIES})

    # Enable cmake testing framework; ctest
    enable_testing()

    # Tests
    set(TESTS predefined_unittests my_unittests)

    # Add tests
    foreach(TEST ${TESTS})

      add_executable( unittest_${TEST} ${HDRS} unittests/${TEST}.cc  )
      target_link_libraries(unittest_${TEST}
        ${PROJECT_NAME} CCInterface ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
      gtest_add_tests( unittest_${TEST} "" AUTO )
    endforeach(TEST)
  else()
    message("GTest not found!")
  endif()
endif()


# Build benchmark rules
option(BUILD_LIBRARY_BENCHMARKS "Build CC library benchmarks..." FALSE)
if(BUILD_LIBRARY_BENCHMARKS)

  # Find GTest
  find_package(benchmark QUIET)
  if(benchmark_FOUND)

    message("Google Benchmark found!")

    # Enable cmake testing framework; ctest
    enable_testing()

    # Benchmarks
    set(BENCHS predefined_benchmarks)

    # Add benchmarks
    foreach(BENCH ${BENCHS})

      set(BENCH_NAME "bench_${BENCH}")
      add_executable(${BENCH_NAME} benchmarks/${BENCH}.cc)
      target_link_libraries(${BENCH_NAME} ${ARGN} ${PROJECT_NAME} CCInterface benchmark::benchmark pthread)
      add_test(NAME ${BENCH_NAME} COMMAND ${BENCH_NAME})
    endforeach(BENCH)
  else()
    message("Google Benchmark not found!")
  endif()

endif()
