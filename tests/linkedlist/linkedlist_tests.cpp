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
	EXPECT_EQ(_linkedList.size, 1);
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

/*****************************************************************************
 * Insert Back cases
 *****************************************************************************/
TEST_F(LinkedList_Tests, SingleInsertBack)
{
	// Create single not and insert front
	Node *node = LinkedList_create_node();
	node->value = 0xFEEDBEEF;
	LinkedList_insert_back(&_linkedList, node);

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
}

TEST_F(LinkedList_Tests, InsertTwoBack)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	Node *secondNode = LinkedList_create_node();
	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;

	// Insert Front
	LinkedList_insert_back(&_linkedList, firstNode);
	LinkedList_insert_back(&_linkedList, secondNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xDEADBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xFEEDBEEF);

	// Verify size is 2
	EXPECT_EQ(LinkedList_size(&_linkedList), 2);
}

TEST_F(LinkedList_Tests, InsertBackLargeSet)
{
	// Number of values to insert
	int iterations = 100000;

	// Insert nodes
	insertBackIters(iterations);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.tail->value, iterations - 1);
	EXPECT_EQ(_linkedList.head->value, 0);

	// Verify size is correct
	EXPECT_EQ(LinkedList_size(&_linkedList), iterations);

	// Verify values are correct
	Node* ptr = _linkedList.head;
	int counter = 0;

	while(ptr)
	{
		// Check value
		EXPECT_EQ(ptr->value, counter);

		// Decrement counter and advance ptr
		counter++;
		ptr = ptr->next;
	}
}

/*****************************************************************************
 * Insert Before cases
 *****************************************************************************/
TEST_F(LinkedList_Tests, InsertBeforeSingleHead)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	Node *secondNode = LinkedList_create_node();
	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;

	// Insert Front
	LinkedList_insert_front(&_linkedList, firstNode);

	// Insert second node before head
	LinkedList_insert_before(&_linkedList, firstNode, secondNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xDEADBEEF);

	// Expect old head is tail and new second node is new head
	EXPECT_EQ(_linkedList.tail, firstNode);
	EXPECT_EQ(_linkedList.head, secondNode);

	// Verify size is 2
	EXPECT_EQ(LinkedList_size(&_linkedList), 2);
}

TEST_F(LinkedList_Tests, InsertBeforeHeadDoubleValues)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	Node *secondNode = LinkedList_create_node();
	Node *thirdNode = LinkedList_create_node();
	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	LinkedList_insert_front(&_linkedList, firstNode);
	LinkedList_insert_front(&_linkedList, secondNode);

	// Insert second node before head
	LinkedList_insert_before(&_linkedList, secondNode, thirdNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify values are correct
	EXPECT_EQ(_linkedList.head->value, 0xCAFEF00D);
	EXPECT_EQ(_linkedList.head->next->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xDEADBEEF);

	// Expect head is new node and first node is tail
	EXPECT_EQ(_linkedList.tail, firstNode);
	EXPECT_EQ(_linkedList.head, thirdNode);

	// Verify size is 3
	EXPECT_EQ(LinkedList_size(&_linkedList), 3);
}

TEST_F(LinkedList_Tests, InsertBeforeTailDoubleValues)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	Node *secondNode = LinkedList_create_node();
	Node *thirdNode = LinkedList_create_node();
	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	LinkedList_insert_front(&_linkedList, firstNode);
	LinkedList_insert_front(&_linkedList, secondNode);

	// Insert second node before head
	LinkedList_insert_before(&_linkedList, firstNode, thirdNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify values are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.head->next->value, 0xCAFEF00D);
	EXPECT_EQ(_linkedList.tail->value, 0xDEADBEEF);

	// Expect head is new node and first node is tail
	EXPECT_EQ(_linkedList.tail, firstNode);
	EXPECT_EQ(_linkedList.head, secondNode);

	// Verify size is 3
	EXPECT_EQ(LinkedList_size(&_linkedList), 3);
}

/*****************************************************************************
 * Insert After cases
 *****************************************************************************/
TEST_F(LinkedList_Tests, InsertAfterSingleHead)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	Node *secondNode = LinkedList_create_node();
	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;

	// Insert Front
	LinkedList_insert_front(&_linkedList, firstNode);

	// Insert second node after head
	LinkedList_insert_after(&_linkedList, firstNode, secondNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xDEADBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xFEEDBEEF);

	// Expect old head is tail and new second node is new head
	EXPECT_EQ(_linkedList.head, firstNode);
	EXPECT_EQ(_linkedList.tail, secondNode);

	// Verify size is 2
	EXPECT_EQ(LinkedList_size(&_linkedList), 2);
}

TEST_F(LinkedList_Tests, InsertAfterHeadDoubleValues)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	Node *secondNode = LinkedList_create_node();
	Node *thirdNode = LinkedList_create_node();
	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	LinkedList_insert_front(&_linkedList, firstNode);
	LinkedList_insert_front(&_linkedList, secondNode);

	// Insert second node after head
	LinkedList_insert_after(&_linkedList, secondNode, thirdNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify values are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.head->next->value, 0xCAFEF00D);
	EXPECT_EQ(_linkedList.tail->value, 0xDEADBEEF);

	// Expect head is new node and first node is tail
	EXPECT_EQ(_linkedList.tail, firstNode);
	EXPECT_EQ(_linkedList.head, secondNode);

	// Verify size is 3
	EXPECT_EQ(LinkedList_size(&_linkedList), 3);
}

TEST_F(LinkedList_Tests, InsertAfterTailDoubleValues)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	Node *secondNode = LinkedList_create_node();
	Node *thirdNode = LinkedList_create_node();
	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	LinkedList_insert_front(&_linkedList, firstNode);
	LinkedList_insert_front(&_linkedList, secondNode);

	// Insert second node before head
	LinkedList_insert_after(&_linkedList, firstNode, thirdNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify values are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.head->next->value, 0xDEADBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xCAFEF00D);

	// Expect head is new node and first node is tail
	EXPECT_EQ(_linkedList.tail, thirdNode);
	EXPECT_EQ(_linkedList.head, secondNode);

	// Verify size is 3
	EXPECT_EQ(LinkedList_size(&_linkedList), 3);
}

/*****************************************************************************
 * Remove cases
 *****************************************************************************/
TEST_F(LinkedList_Tests, RemoveSingleHead)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	firstNode->value = 0xDEADBEEF;

	// Insert Front
	LinkedList_insert_front(&_linkedList, firstNode);

	// Delete First node
	LinkedList_remove(&_linkedList, firstNode);

	// Verify size is 0
	EXPECT_EQ(LinkedList_size(&_linkedList), 0);

	// Verify head and tail are null
	EXPECT_EQ(_linkedList.tail, nullptr);
	EXPECT_EQ(_linkedList.head, nullptr);
}

TEST_F(LinkedList_Tests, RemoveDoubleHead)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	Node *secondNode = LinkedList_create_node();
	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;

	// Insert Front
	LinkedList_insert_back(&_linkedList, firstNode);
	LinkedList_insert_back(&_linkedList, secondNode);

	// Delete First node
	LinkedList_remove(&_linkedList, firstNode);

	// Verify value
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);

	// Verify size is 1
	EXPECT_EQ(LinkedList_size(&_linkedList), 1);

	// Verify head and tail are both second node
	EXPECT_EQ(_linkedList.tail, secondNode);
	EXPECT_EQ(_linkedList.head, secondNode);
}

TEST_F(LinkedList_Tests, RemoveDoubleTail)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	Node *secondNode = LinkedList_create_node();
	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;

	// Insert Front
	LinkedList_insert_back(&_linkedList, firstNode);
	LinkedList_insert_back(&_linkedList, secondNode);

	// Delete First node
	LinkedList_remove(&_linkedList, secondNode);

	// Verify value
	EXPECT_EQ(_linkedList.head->value, 0xDEADBEEF);

	// Verify size is 1
	EXPECT_EQ(LinkedList_size(&_linkedList), 1);

	// Verify head and tail are both second node
	EXPECT_EQ(_linkedList.tail, firstNode);
	EXPECT_EQ(_linkedList.head, firstNode);
}

TEST_F(LinkedList_Tests, RemoveMiddle)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	Node *secondNode = LinkedList_create_node();
	Node *thirdNode = LinkedList_create_node();

	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	LinkedList_insert_back(&_linkedList, firstNode);
	LinkedList_insert_back(&_linkedList, secondNode);
	LinkedList_insert_back(&_linkedList, thirdNode);

	// Delete First node
	LinkedList_remove(&_linkedList, secondNode);

	// Verify value
	EXPECT_EQ(_linkedList.head->value, 0xDEADBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xCAFEF00D);

	// Verify size is 2
	EXPECT_EQ(LinkedList_size(&_linkedList), 2);

	// Verify head and tail are both second node
	EXPECT_EQ(_linkedList.head, firstNode);
	EXPECT_EQ(_linkedList.tail, thirdNode);
	EXPECT_EQ(_linkedList.head->next, thirdNode);
}

TEST_F(LinkedList_Tests, RemoveHeadWithMiddle)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	Node *secondNode = LinkedList_create_node();
	Node *thirdNode = LinkedList_create_node();

	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	LinkedList_insert_back(&_linkedList, firstNode);
	LinkedList_insert_back(&_linkedList, secondNode);
	LinkedList_insert_back(&_linkedList, thirdNode);

	// Delete First node
	LinkedList_remove(&_linkedList, firstNode);

	// Verify value
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xCAFEF00D);

	// Verify size is 2
	EXPECT_EQ(LinkedList_size(&_linkedList), 2);

	// Verify head and tail are both second node
	EXPECT_EQ(_linkedList.head, secondNode);
	EXPECT_EQ(_linkedList.tail, thirdNode);
	EXPECT_EQ(_linkedList.head->next, thirdNode);
}

TEST_F(LinkedList_Tests, RemoveTailWithMiddle)
{
	// Create nodes
	Node *firstNode = LinkedList_create_node();
	Node *secondNode = LinkedList_create_node();
	Node *thirdNode = LinkedList_create_node();

	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	LinkedList_insert_back(&_linkedList, firstNode);
	LinkedList_insert_back(&_linkedList, secondNode);
	LinkedList_insert_back(&_linkedList, thirdNode);

	// Delete First node
	LinkedList_remove(&_linkedList, thirdNode);

	// Verify value
	EXPECT_EQ(_linkedList.head->value, 0xDEADBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xFEEDBEEF);

	// Verify size is 2
	EXPECT_EQ(LinkedList_size(&_linkedList), 2);

	// Verify head and tail are both second node
	EXPECT_EQ(_linkedList.head, firstNode);
	EXPECT_EQ(_linkedList.tail, secondNode);
	EXPECT_EQ(_linkedList.head->next, secondNode);
}