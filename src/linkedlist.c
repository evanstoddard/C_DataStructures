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