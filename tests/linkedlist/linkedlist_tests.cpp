#include <gtest/gtest.h>
#include "linkedlist.h"

class LinkedList_Tests : public ::testing::Test
{
	protected:
	void SetUp() override {
		// Initialize linked list
		LinkedList_init(&_linkedList);
	}

	/**
	 * @brief Helper functions
	 *
	 */
	protected:
	void insertBackIters(int iterations)
	{
		for (int i = 0; i < iterations; i++)
		{
			// Create node
			Node *node = LinkedList_create_node();
			node->value = i;

			// Add node
			LinkedList_insert_back(&_linkedList, node);
		}
	}
	void insertFrontIters(int iterations)
	{
		for (int i = 0; i < iterations; i++)
		{
			// Create node
			Node *node = LinkedList_create_node();
			node->value = i;

			// Add node
			LinkedList_insert_front(&_linkedList, node);
		}
	}

	LinkedList _linkedList;
};

/*****************************************************************************
 * Initialization Tests
 *****************************************************************************/
TEST_F(LinkedList_Tests, IsEmptyInitially)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	// Ensure size is 0 and size getter equals struct value
	EXPECT_EQ(LinkedList_size(&_linkedList), 0);
	EXPECT_EQ(LinkedList_size(&_linkedList), _linkedList.size);

	// Ensure both head and tail pointers are null
	EXPECT_EQ(_linkedList.head, nullptr);
	EXPECT_EQ(_linkedList.tail, nullptr);
}

/*****************************************************************************
 * Insert Front cases
 *****************************************************************************/
TEST_F(LinkedList_Tests, SingleInsertFront)
{
	// Create single not and insert front
	Node *node = LinkedList_create_node();
	node->value = 0xFEEDBEEF;
	LinkedList_insert_front(&_linkedList, node);

	// Verify head and tail are same pointer
	EXPECT_EQ(_linkedList.head, _linkedList.tail);

	// Verify head and tail equal node
	EXPECT_EQ(_linkedList.head, node);
	EXPECT_EQ(_linkedList.tail, node);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xFEEDBEEF);

	// Verify size is 1
	EXPECT_EQ(LinkedList_size(&_linkedList), 1);
	EXPECT_EQ(LinkedList_size(&_linkedList), 1);
}

TEST_F(LinkedList_Tests, InsertTwoFront)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	Node *secondNode = LinkedList_create_node();
	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;

	// Insert Front
	LinkedList_insert_front(&_linkedList, firstNode);
	LinkedList_insert_front(&_linkedList, secondNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xDEADBEEF);

	// Verify size is 2
	EXPECT_EQ(LinkedList_size(&_linkedList), 2);
	EXPECT_EQ(LinkedList_size(&_linkedList), 2);
}

TEST_F(LinkedList_Tests, InsertFrontLargeSet)
{
	// Number of values to insert
	int iterations = 100000;

	// Insert nodes
	insertFrontIters(iterations);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, iterations - 1);
	EXPECT_EQ(_linkedList.tail->value, 0);

	// Verify size is correct
	EXPECT_EQ(LinkedList_size(&_linkedList), iterations);
	EXPECT_EQ(LinkedList_size(&_linkedList), iterations);

	// Verify values are correct
	Node* ptr = _linkedList.head;
	int counter = iterations - 1;

	while(ptr)
	{
		// Check value
		EXPECT_EQ(ptr->value, counter);

		// Decrement counter and advance ptr
		counter--;
		ptr = ptr->next;
	}
}