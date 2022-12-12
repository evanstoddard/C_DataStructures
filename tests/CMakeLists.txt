# Add subdirectories
add_subdirectory(linkedlist)
add_subdirectory(doubleylinkedlist)

# List of tests to run
set(TESTS_TO_RUN
	tests_linkedlist_run
	tests_doubleylinkedlist_run
)

# Run all tests in TESTS_TO_RUN lists
add_custom_target(tests
	DEPENDS ${TESTS_TO_RUN}
)