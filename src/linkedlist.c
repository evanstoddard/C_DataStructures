/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file linkedlist.c
 * @author Evan Stoddard
 * @brief
 */

#include "linkedlist.h"
#include <stdlib.h>

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
void LinkedList_init(LinkedList* l)
{
    l->head = NULL;
    l->tail = NULL;

    l->size = 0;
}

/**
 * @brief Creates an empty node
 *
 * @return Node* Point to empty node
 */
Node* LinkedList_create_node()
{
	/* Initialize node memory to 0 */
    return (Node*)calloc(1, sizeof(Node));
}

/**
 * @brief Insert node at front of linked list
 *
 * @param l Linked List
 * @param new_node Node to add
 */
void LinkedList_insert_front(LinkedList* l, Node* new_node)
{
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
void LinkedList_insert_back(LinkedList* l, Node* new_node)
{
    /* If empty linked list, just add to front and return */
    if (!l->size)
    {
        LinkedList_insert_front(l, new_node);
        return;
    }

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
void LinkedList_insert_before(LinkedList* l, Node* existing, Node* new_node)
{
    /* Insert front if existing node is head and return */
    if (existing == l->head)
    {
        LinkedList_insert_front(l, new_node);
        return;
    }

    /* Iterate through linked list to find node before exisiting  */
    Node *ptr = l->head;
    while(ptr)
    {
        if (ptr->next == existing)
        {
            break;
        }

        ptr = ptr->next;
    }

    if (!ptr)
    {
        return;
    }

    new_node->next = existing;
    ptr->next = new_node;

    l->size++;
}

/**
 * @brief Insert node after existing node
 *
 * @param l Linked list
 * @param existing Existing node
 * @param new_node New node
 */
void LinkedList_insert_after(LinkedList* l, Node* existing, Node* new_node)
{
    /* Insert back if existing node is tail */
    if (existing == l->tail)
    {
        LinkedList_insert_back(l, new_node);
		return;
    }

    new_node->next = existing->next;
    existing->next = new_node;

    l->size++;
}

/**
 * @brief Remove item from linked list and memory
 *
 * @param l Linked list
 * @param node Node to remove
 */
void LinkedList_remove(LinkedList* l, Node* node)
{
	/* If node is head then update head to next node */
	if (node == l->head)
	{
		l->head = node->next;
	}
	else
	{
		/* Traverse through linked list */
		Node* ptr = l->head;
		while(ptr)
		{
			if (ptr->next == node)
			{
				break;
			}

			ptr = ptr->next;
		}

		if (!ptr)
		{
			return;
		}

		ptr->next = node->next;

		/* Update tail if tail deleted */
		if (node == l->tail)
		{
			l->tail = ptr;
			l->tail->next = NULL;
		}
	}

	l->size--;

	/* Make sure tail is NULL if new size is 0 */
	if (!l->size)
	{
		l->tail = NULL;
	}

	free(node);
}

/**
 * @brief Delete all elements in linked list
 *
 * @param l Linked list
 */
void LinkedList_clear(LinkedList* l)
{
	/* Do nothing if linked list empty*/
	if (!l->size)
	{
		return;
	}

	Node *ptr = l->head;
	do
	{
		Node *current = ptr;
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
size_t LinkedList_size(LinkedList* l)
{
	return l->size;
}