/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file linkedlist.h
 * @author Evan Stoddard
 * @brief
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/
/**
 * @brief Linked List Node struct
 *
 */
typedef struct Node
{
    uint64_t value;
    struct Node *next;
} Node;

/**
 * @brief Linked List struct
 *
 */
typedef struct LinkedList
{
    Node *head;
    Node *tail;
    size_t size;
} LinkedList;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/
void LinkedList_init(LinkedList* l);

Node* LinkedList_create_node();

void LinkedList_insert_front(LinkedList* l, Node* new_node);
void LinkedList_insert_back(LinkedList* l, Node* new_node);
void LinkedList_insert_before(LinkedList* l, Node* existing, Node* new_node);
void LinkedList_insert_after(LinkedList* l, Node* existing, Node* new_node);
void LinkedList_remove(LinkedList* l, Node* node);
void LinkedList_clear(LinkedList* l);

size_t LinkedList_size(LinkedList* l);

#ifdef __cplusplus
};
#endif

#endif /* LINKEDLIST_H_ */
