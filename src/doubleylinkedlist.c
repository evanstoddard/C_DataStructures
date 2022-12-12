/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file doublelinkedlist.c
 * @author Evan Stoddard
 * @brief
 */

#include "doubleylinkedlist.h"
#include <stdlib.h>
#include <stdio.h>

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Variables
 *****************************************************************************/

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Functions
 *****************************************************************************/

/**
 * @brief Initialize linked list
 *
 * @param l Pointer to linked list
 */
void DoubleyLinkedList_init(DoubleyLinkedList* l)
{
    l->head = NULL;
    l->tail = NULL;

    l->size = 0;
}

/**
 * @brief Creates an empty node
 *
 * @return DoubleEndedNode* Point to empty node
 */
DoubleEndedNode* DoubleyLinkedList_create_node()
{
	/* Initialize node memory to 0 */
    return (DoubleEndedNode*)calloc(1, sizeof(DoubleEndedNode));
}

/**
 * @brief Insert node at front of linked list
 *
 * @param l Linked List
 * @param new_node Node to add
 */
void DoubleyLinkedList_insert_front(DoubleyLinkedList* l, DoubleEndedNode* new_node)
{
	/* Update current head previous pointer to new node */
	if (l->head)
	{
		l->head->prev = new_node;
	}

    new_node->next = l->head;
    l->head = new_node;

    l->size++;

    /* Update tail to head if very first node */
    if (!l->tail)
    {
        l->tail = new_node;
    }
}

/**
 * @brief Insert node at end of linked list
 *
 * @param l Linked list
 * @param new_node Node to add
 */
void DoubleyLinkedList_insert_back(DoubleyLinkedList* l, DoubleEndedNode* new_node)
{
    /* If empty linked list, just add to front and return */
    if (!l->size)
    {
        DoubleyLinkedList_insert_front(l, new_node);
        return;
    }

	new_node->prev = l->tail;
    l->tail->next = new_node;
    l->tail = new_node;

    l->size++;
}

/**
 * @brief Insert new before existing node
 *
 * @param l Linked list
 * @param existing Existing node
 * @param new_node Node to add
 */
void DoubleyLinkedList_insert_before(DoubleyLinkedList* l, DoubleEndedNode* existing, DoubleEndedNode* new_node)
{
    /* Insert front if existing node is head and return */
    if (existing == l->head)
    {
        DoubleyLinkedList_insert_front(l, new_node);
        return;
    }

	new_node->prev = existing->prev;
	new_node->next = existing;
	existing->prev->next = new_node;
	existing->prev = new_node;

    l->size++;
}

/**
 * @brief Insert node after existing node
 *
 * @param l Linked list
 * @param existing Existing node
 * @param new_node New node
 */
void DoubleyLinkedList_insert_after(DoubleyLinkedList* l, DoubleEndedNode* existing, DoubleEndedNode* new_node)
{
    /* Insert back if existing node is tail */
    if (existing == l->tail)
    {
        DoubleyLinkedList_insert_back(l, new_node);
		return;
    }

	new_node->next = existing->next;
	new_node->prev = existing;

	if (existing->next)
	{
		existing->next->prev = new_node;
	}
	existing->next = new_node;

    l->size++;
}

/**
 * @brief Remove item from linked list and memory
 *
 * @param l Linked list
 * @param node Node to remove
 */
void DoubleyLinkedList_remove(DoubleyLinkedList* l, DoubleEndedNode* node)
{
	if (node->next)
	{
		node->next->prev = node->prev;
	}

	if (node->prev)
	{
		node->prev->next = node->next;
	}

	if (node == l->head)
	{
		l->head = node->next;
	}

	if (node == l->tail)
	{
		l->tail = node->prev;
	}

	l->size--;
}

/**
 * @brief Delete all elements in linked list
 *
 * @param l Linked list
 */
void DoubleyLinkedList_clear(DoubleyLinkedList* l)
{
	/* Do nothing if linked list empty*/
	if (!l->size)
	{
		return;
	}

	DoubleEndedNode *ptr = l->head;
	do
	{
		DoubleEndedNode *current = ptr;
		ptr = current->next;

		free(current);
	}
	while(ptr);
}

/**
 * @brief Returns size of linked list
 *
 * @param l Linked list
 * @return size_t Size
 */
size_t DoubleyLinkedList_size(DoubleyLinkedList* l)
{
	return l->size;
}