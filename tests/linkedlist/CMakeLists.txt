# Project
project(tests_linkedlist)

# Include google test
include(${CMAKE_SOURCE_DIR}/cmake/google_test.cmake)

# Include src directory
include_directories(${CMAKE_SOURCE_DIR}/src)

# Create target
add_executable(tests_linkedlist
	linkedlist_tests.cpp
)

# Link libraries
target_link_libraries(tests_linkedlist
	GTest::gtest_main
	datastructures
)