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
    /* Initialize head and tail to null, initialize size to 0*/
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
    /* Set next of new node to current head*/
    new_node->next = l->head;

    /* Update head to new node*/
    l->head = new_node;

    /* Increment size */
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

    /* Update next node of tail and update tail to new node*/
    l->tail->next = new_node;
    l->tail = new_node;

    /* Increment size */
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
    /* Insert front if existing node is linked list head and return */
    if (existing == l->head)
    {
        LinkedList_insert_front(l, new_node);
        return;
    }

    /* Pointer for linked list traversal*/
    Node *ptr = l->head;

    /* Traverse through linked list */
    while(ptr)
    {
        /* If node before existing is found */
        if (ptr->next == existing)
        {
            break;
        }

        /* Next node */
        ptr = ptr->next;
    }

    /* Return if node not found */
    if (!ptr)
    {
        return;
    }

    /* Point new node next to existing*/
    new_node->next = existing;

    /* Update node before existing next to new node*/
    ptr->next = new_node;

    /* Increment size */
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
    }

    /* Set new node next to existing next */
    new_node->next = existing->next;

    /* Set existing next to new node*/
    existing->next = new_node;

    /* Increment size */
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
			/* Find node before one to remove */
			if (ptr->next == node)
			{
				break;
			}
		}

		/* Return if node never found */
		if (!ptr)
		{
			return;
		}

		/* Set ptr next to existing node's next time */
		ptr->next = node->next;
	}

	/* Decrement size */
	l->size--;

	/* Make sure tail is NULL if new size is 0 */
	if (!l->size)
	{
		l->tail = NULL;
	}

	/* Free memory */
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