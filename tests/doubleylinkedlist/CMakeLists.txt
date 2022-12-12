# Project
project(tests_doubleylinkedlist)

# Include google test
include(${CMAKE_SOURCE_DIR}/cmake/google_test.cmake)

# Include src directory
include_directories(${CMAKE_SOURCE_DIR}/src)

# Create target
add_executable(tests_doubleylinkedlist EXCLUDE_FROM_ALL
	doubleylinkedlist_tests.cpp
)

# Link libraries
target_link_libraries(tests_doubleylinkedlist
	GTest::gtest_main
	datastructures
)

# Run target
add_custom_target(tests_doubleylinkedlist_run
	DEPENDS tests_doubleylinkedlist
	COMMAND tests_doubleylinkedlist
)