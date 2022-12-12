/*
 * Copyright (C) Evan Stoddard.
 */

/**
 * @file doubleylinkedlist_tests.cpp
 * @author Evan Stoddard
 * @brief
 */

#include <gtest/gtest.h>
#include "doubleylinkedlist.h"

class DoubleLinkedLists_Tests : public ::testing::Test
{
protected:
	void SetUp() override
	{
		DoubleyLinkedList_init(&_linkedList);
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
			DoubleEndedNode *node = DoubleyLinkedList_create_node();
			node->value = i;

			// Add node
			DoubleyLinkedList_insert_back(&_linkedList, node);
		}
	}
	void insertFrontIters(int iterations)
	{
		for (int i = 0; i < iterations; i++)
		{
			// Create node
			DoubleEndedNode *node = DoubleyLinkedList_create_node();
			node->value = i;

			// Add node
			DoubleyLinkedList_insert_front(&_linkedList, node);
		}
	}


protected:
	DoubleyLinkedList _linkedList;
};

/*****************************************************************************
 * Initialization Tests
 *****************************************************************************/
TEST_F(DoubleLinkedLists_Tests, IsEmptyPostInit)
{
	// Ensure size is 0
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 0);
	EXPECT_EQ(_linkedList.size, 0);

	// Ensure Head and Tail are null
	EXPECT_EQ(_linkedList.head, nullptr);
	EXPECT_EQ(_linkedList.tail, nullptr);
}

/*****************************************************************************
 * Insert Front cases
 *****************************************************************************/
TEST_F(DoubleLinkedLists_Tests, SingleInsertFront)
{
	// Create single not and insert front
	DoubleEndedNode *node = DoubleyLinkedList_create_node();
	node->value = 0xFEEDBEEF;
	DoubleyLinkedList_insert_front(&_linkedList, node);

	// Verify head and tail are same pointer
	EXPECT_EQ(_linkedList.head, _linkedList.tail);

	// Verify head and tail equal node
	EXPECT_EQ(_linkedList.head, node);
	EXPECT_EQ(_linkedList.tail, node);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xFEEDBEEF);

	// Verify next and prev values are null
	EXPECT_EQ(node->next, nullptr);
	EXPECT_EQ(node->prev, nullptr);

	// Verify size is 1
	EXPECT_EQ(_linkedList.size, 1);
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 1);
}

TEST_F(DoubleLinkedLists_Tests, InsertTwoFront)
{
	// Create and insert nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *secondNode = DoubleyLinkedList_create_node();

	firstNode->value = 0xFEEDBEEF;
	secondNode->value = 0xDEADBEEF;
	DoubleyLinkedList_insert_front(&_linkedList, secondNode);
	DoubleyLinkedList_insert_front(&_linkedList, firstNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify head and tail equal node
	EXPECT_EQ(_linkedList.head, firstNode);
	EXPECT_EQ(_linkedList.tail, secondNode);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xDEADBEEF);

	// Verify node next/prev pointers correct
	EXPECT_EQ(firstNode->prev, nullptr);
	EXPECT_EQ(firstNode->next, secondNode);

	EXPECT_EQ(secondNode->prev, firstNode);
	EXPECT_EQ(secondNode->next, nullptr);

	// Verify size is 2
	EXPECT_EQ(_linkedList.size, 2);
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 2);
}

TEST_F(DoubleLinkedLists_Tests, InsertFrontLargeSet)
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
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), iterations);

	// Verify values are correct
	DoubleEndedNode* ptr = _linkedList.head;
	DoubleEndedNode* prev_node = _linkedList.head->prev;
	int counter = iterations - 1;

	while(ptr)
	{
		// Check value
		EXPECT_EQ(ptr->value, counter);

		// Verify node pointers are correct
		EXPECT_EQ(ptr->prev, prev_node);

		// Decrement counter and advance ptr
		counter--;
		prev_node = ptr;
		ptr = ptr->next;
	}
}

/*****************************************************************************
 * Insert Back cases
 *****************************************************************************/
TEST_F(DoubleLinkedLists_Tests, SingleInsertBack)
{
	// Create single not and insert front
	DoubleEndedNode *node = DoubleyLinkedList_create_node();
	node->value = 0xFEEDBEEF;
	DoubleyLinkedList_insert_back(&_linkedList, node);

	// Verify head and tail are same pointer
	EXPECT_EQ(_linkedList.head, _linkedList.tail);

	// Verify head and tail equal node
	EXPECT_EQ(_linkedList.head, node);
	EXPECT_EQ(_linkedList.tail, node);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xFEEDBEEF);

	// Verify next and prev values are null
	EXPECT_EQ(node->next, nullptr);
	EXPECT_EQ(node->prev, nullptr);

	// Verify size is 1
	EXPECT_EQ(_linkedList.size, 1);
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 1);
}

TEST_F(DoubleLinkedLists_Tests, InsertTwoBack)
{
	// Create and insert nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *secondNode = DoubleyLinkedList_create_node();

	firstNode->value = 0xFEEDBEEF;
	secondNode->value = 0xDEADBEEF;
	DoubleyLinkedList_insert_back(&_linkedList, firstNode);
	DoubleyLinkedList_insert_back(&_linkedList, secondNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify head and tail equal node
	EXPECT_EQ(_linkedList.head, firstNode);
	EXPECT_EQ(_linkedList.tail, secondNode);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xDEADBEEF);

	// Verify node next/prev pointers correct
	EXPECT_EQ(firstNode->prev, nullptr);
	EXPECT_EQ(firstNode->next, secondNode);

	EXPECT_EQ(secondNode->prev, firstNode);
	EXPECT_EQ(secondNode->next, nullptr);

	// Verify size is 2
	EXPECT_EQ(_linkedList.size, 2);
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 2);
}

TEST_F(DoubleLinkedLists_Tests, InsertBackLargeSet)
{
	// Number of values to insert
	int iterations = 100000;

	// Insert nodes
	insertBackIters(iterations);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0);
	EXPECT_EQ(_linkedList.tail->value, iterations - 1);

	// Verify size is correct
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), iterations);

	// Verify values are correct
	DoubleEndedNode* ptr = _linkedList.head;
	DoubleEndedNode* prev_node = _linkedList.head->prev;
	int counter = 0;

	while(ptr)
	{
		// Check value
		EXPECT_EQ(ptr->value, counter);

		// Verify node pointers are correct
		EXPECT_EQ(ptr->prev, prev_node);

		// Decrement counter and advance ptr
		counter++;
		prev_node = ptr;
		ptr = ptr->next;
	}
}

/*****************************************************************************
 * Insert Before cases
 *****************************************************************************/
TEST_F(DoubleLinkedLists_Tests, InsertBeforeSingleHead)
{
	// Create nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *secondNode = DoubleyLinkedList_create_node();
	firstNode->value = 0xFEEDBEEF;
	secondNode->value = 0xDEADBEEF;

	// Insert Front
	DoubleyLinkedList_insert_front(&_linkedList, secondNode);

	// Insert second node before head
	DoubleyLinkedList_insert_before(&_linkedList, secondNode, firstNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xDEADBEEF);

	// Expect old head is tail and new second node is new head
	EXPECT_EQ(_linkedList.head, firstNode);
	EXPECT_EQ(_linkedList.tail, secondNode);

	EXPECT_EQ(firstNode->prev, nullptr);
	EXPECT_EQ(firstNode->next, secondNode);

	EXPECT_EQ(secondNode->prev, firstNode);
	EXPECT_EQ(secondNode->next, nullptr);

	// Verify size is 2
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 2);
}

TEST_F(DoubleLinkedLists_Tests, InsertBeforeDoubleHead)
{
	// Create nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *secondNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *thirdNode = DoubleyLinkedList_create_node();
	firstNode->value = 0xFEEDBEEF;
	secondNode->value = 0xDEADBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	DoubleyLinkedList_insert_front(&_linkedList, thirdNode);
	DoubleyLinkedList_insert_front(&_linkedList, secondNode);

	// Insert third node before head
	DoubleyLinkedList_insert_before(&_linkedList, secondNode, firstNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xCAFEF00D);

	// Expect old head is tail and new second node is new head
	EXPECT_EQ(_linkedList.head, firstNode);
	EXPECT_EQ(_linkedList.tail, thirdNode);

	EXPECT_EQ(firstNode->prev, nullptr);
	EXPECT_EQ(firstNode->next, secondNode);

	EXPECT_EQ(secondNode->prev, firstNode);
	EXPECT_EQ(secondNode->next, thirdNode);

	EXPECT_EQ(thirdNode->prev, secondNode);
	EXPECT_EQ(thirdNode->next, nullptr);

	// Verify size is 3
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 3);
}

TEST_F(DoubleLinkedLists_Tests, InsertBeforeTailDoubleValues)
{
	// Create nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *secondNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *thirdNode = DoubleyLinkedList_create_node();
	firstNode->value = 0xFEEDBEEF;
	secondNode->value = 0xDEADBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	DoubleyLinkedList_insert_front(&_linkedList, thirdNode);
	DoubleyLinkedList_insert_front(&_linkedList, firstNode);

	// Insert third node before head
	DoubleyLinkedList_insert_before(&_linkedList, thirdNode, secondNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xCAFEF00D);

	EXPECT_EQ(_linkedList.head, firstNode);
	EXPECT_EQ(_linkedList.tail, thirdNode);

	EXPECT_EQ(firstNode->prev, nullptr);
	EXPECT_EQ(firstNode->next, secondNode);

	EXPECT_EQ(secondNode->prev, firstNode);
	EXPECT_EQ(secondNode->next, thirdNode);

	EXPECT_EQ(thirdNode->prev, secondNode);
	EXPECT_EQ(thirdNode->next, nullptr);

	// Verify size is 3
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 3);
}

/*****************************************************************************
 * Insert After cases
 *****************************************************************************/
TEST_F(DoubleLinkedLists_Tests, InsertAfterSingleHead)
{
	// Create nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *secondNode = DoubleyLinkedList_create_node();
	firstNode->value = 0xFEEDBEEF;
	secondNode->value = 0xDEADBEEF;

	// Insert Front
	DoubleyLinkedList_insert_front(&_linkedList, firstNode);

	// Insert second node before head
	DoubleyLinkedList_insert_after(&_linkedList, firstNode, secondNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xDEADBEEF);

	// Expect old head is tail and new second node is new head
	EXPECT_EQ(_linkedList.head, firstNode);
	EXPECT_EQ(_linkedList.tail, secondNode);

	EXPECT_EQ(firstNode->prev, nullptr);
	EXPECT_EQ(firstNode->next, secondNode);

	EXPECT_EQ(secondNode->prev, firstNode);
	EXPECT_EQ(secondNode->next, nullptr);

	// Verify size is 2
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 2);
}

TEST_F(DoubleLinkedLists_Tests, InsertAfterDoubleHead)
{
	// Create nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *secondNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *thirdNode = DoubleyLinkedList_create_node();
	firstNode->value = 0xFEEDBEEF;
	secondNode->value = 0xDEADBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	DoubleyLinkedList_insert_front(&_linkedList, thirdNode);
	DoubleyLinkedList_insert_front(&_linkedList, firstNode);

	DoubleyLinkedList_insert_after(&_linkedList, firstNode, secondNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xCAFEF00D);

	// Expect old head is tail and new second node is new head
	EXPECT_EQ(_linkedList.head, firstNode);
	EXPECT_EQ(_linkedList.tail, thirdNode);

	EXPECT_EQ(firstNode->prev, nullptr);
	EXPECT_EQ(firstNode->next, secondNode);

	EXPECT_EQ(secondNode->prev, firstNode);
	EXPECT_EQ(secondNode->next, thirdNode);

	EXPECT_EQ(thirdNode->prev, secondNode);
	EXPECT_EQ(thirdNode->next, nullptr);

	// Verify size is 3
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 3);
}

TEST_F(DoubleLinkedLists_Tests, InsertAfterTailDoubleValues)
{
	// Create nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *secondNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *thirdNode = DoubleyLinkedList_create_node();
	firstNode->value = 0xFEEDBEEF;
	secondNode->value = 0xDEADBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	DoubleyLinkedList_insert_front(&_linkedList, secondNode);
	DoubleyLinkedList_insert_front(&_linkedList, firstNode);

	DoubleyLinkedList_insert_after(&_linkedList, secondNode, thirdNode);

	// Verify head and tail are not same pointer
	EXPECT_NE(_linkedList.head, _linkedList.tail);

	// Verify value of head and tail are correct
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xCAFEF00D);

	EXPECT_EQ(_linkedList.head, firstNode);
	EXPECT_EQ(_linkedList.tail, thirdNode);

	EXPECT_EQ(firstNode->prev, nullptr);
	EXPECT_EQ(firstNode->next, secondNode);

	EXPECT_EQ(secondNode->prev, firstNode);
	EXPECT_EQ(secondNode->next, thirdNode);

	EXPECT_EQ(thirdNode->prev, secondNode);
	EXPECT_EQ(thirdNode->next, nullptr);

	// Verify size is 3
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 3);
}

/*****************************************************************************
 * Remove cases
 *****************************************************************************/
TEST_F(DoubleLinkedLists_Tests, RemoveSingleHead)
{
	// Create nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	firstNode->value = 0xDEADBEEF;

	// Insert Front
	DoubleyLinkedList_insert_front(&_linkedList, firstNode);

	// Delete First node
	DoubleyLinkedList_remove(&_linkedList, firstNode);

	// Verify size is 0
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 0);

	// Verify head and tail are null
	EXPECT_EQ(_linkedList.tail, nullptr);
	EXPECT_EQ(_linkedList.head, nullptr);
}

TEST_F(DoubleLinkedLists_Tests, RemoveDoubleHead)
{
	// Create nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *secondNode = DoubleyLinkedList_create_node();
	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;

	// Insert Front
	DoubleyLinkedList_insert_back(&_linkedList, firstNode);
	DoubleyLinkedList_insert_back(&_linkedList, secondNode);

	// Delete First node
	DoubleyLinkedList_remove(&_linkedList, firstNode);

	// Verify value
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);

	EXPECT_EQ(secondNode->prev, nullptr);
	EXPECT_EQ(secondNode->next, nullptr);

	// Verify size is 1
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 1);

	// Verify head and tail are both second node
	EXPECT_EQ(_linkedList.tail, secondNode);
	EXPECT_EQ(_linkedList.head, secondNode);
}

TEST_F(DoubleLinkedLists_Tests, RemoveDoubleTail)
{
	// Create nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *secondNode = DoubleyLinkedList_create_node();
	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;

	// Insert Front
	DoubleyLinkedList_insert_back(&_linkedList, firstNode);
	DoubleyLinkedList_insert_back(&_linkedList, secondNode);

	// Delete First node
	DoubleyLinkedList_remove(&_linkedList, secondNode);

	// Verify value
	EXPECT_EQ(_linkedList.head->value, 0xDEADBEEF);

	EXPECT_EQ(firstNode->next, nullptr);
	EXPECT_EQ(firstNode->prev, nullptr);

	// Verify size is 1
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 1);

	// Verify head and tail are both second node
	EXPECT_EQ(_linkedList.tail, firstNode);
	EXPECT_EQ(_linkedList.head, firstNode);
}

TEST_F(DoubleLinkedLists_Tests, RemoveMiddle)
{
	// Create nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *secondNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *thirdNode = DoubleyLinkedList_create_node();

	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	DoubleyLinkedList_insert_back(&_linkedList, firstNode);
	DoubleyLinkedList_insert_back(&_linkedList, secondNode);
	DoubleyLinkedList_insert_back(&_linkedList, thirdNode);

	// Delete First node
	DoubleyLinkedList_remove(&_linkedList, secondNode);

	EXPECT_EQ(firstNode->prev, nullptr);
	EXPECT_EQ(firstNode->next, thirdNode);

	EXPECT_EQ(thirdNode->prev, firstNode);
	EXPECT_EQ(thirdNode->next, nullptr);

	// Verify value
	EXPECT_EQ(_linkedList.head->value, 0xDEADBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xCAFEF00D);

	// Verify size is 2
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 2);

	// Verify head and tail are both second node
	EXPECT_EQ(_linkedList.head, firstNode);
	EXPECT_EQ(_linkedList.tail, thirdNode);
	EXPECT_EQ(_linkedList.head->next, thirdNode);
}

TEST_F(DoubleLinkedLists_Tests, RemoveHeadWithMiddle)
{
	// Create nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *secondNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *thirdNode = DoubleyLinkedList_create_node();

	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	DoubleyLinkedList_insert_back(&_linkedList, firstNode);
	DoubleyLinkedList_insert_back(&_linkedList, secondNode);
	DoubleyLinkedList_insert_back(&_linkedList, thirdNode);

	// Delete First node
	DoubleyLinkedList_remove(&_linkedList, firstNode);

	// Verify value
	EXPECT_EQ(_linkedList.head->value, 0xFEEDBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xCAFEF00D);

	EXPECT_EQ(secondNode->next, thirdNode);
	EXPECT_EQ(secondNode->prev, nullptr);

	EXPECT_EQ(thirdNode->prev, secondNode);
	EXPECT_EQ(thirdNode->next, nullptr);

	// Verify size is 2
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 2);

	// Verify head and tail are both second node
	EXPECT_EQ(_linkedList.head, secondNode);
	EXPECT_EQ(_linkedList.tail, thirdNode);
	EXPECT_EQ(_linkedList.head->next, thirdNode);
}

TEST_F(DoubleLinkedLists_Tests, RemoveTailWithMiddle)
{
	// Create nodes
	DoubleEndedNode *firstNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *secondNode = DoubleyLinkedList_create_node();
	DoubleEndedNode *thirdNode = DoubleyLinkedList_create_node();

	firstNode->value = 0xDEADBEEF;
	secondNode->value = 0xFEEDBEEF;
	thirdNode->value = 0xCAFEF00D;

	// Insert Front
	DoubleyLinkedList_insert_back(&_linkedList, firstNode);
	DoubleyLinkedList_insert_back(&_linkedList, secondNode);
	DoubleyLinkedList_insert_back(&_linkedList, thirdNode);

	// Delete First node
	DoubleyLinkedList_remove(&_linkedList, thirdNode);

	// Verify value
	EXPECT_EQ(_linkedList.head->value, 0xDEADBEEF);
	EXPECT_EQ(_linkedList.tail->value, 0xFEEDBEEF);

	EXPECT_EQ(firstNode->next, secondNode);
	EXPECT_EQ(firstNode->prev, nullptr);

	EXPECT_EQ(secondNode->prev, firstNode);
	EXPECT_EQ(secondNode->next, nullptr);

	// Verify size is 2
	EXPECT_EQ(DoubleyLinkedList_size(&_linkedList), 2);

	// Verify head and tail are both second node
	EXPECT_EQ(_linkedList.head, firstNode);
	EXPECT_EQ(_linkedList.tail, secondNode);
}
