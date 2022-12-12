/*
 * Copyright (C) Evan Stoddard.
 */

/**
 * @file doubleylinkedlist.h
 * @author Evan Stoddard
 * @brief
 */

#ifndef DoubleyLinkedList_H_
#define DoubleyLinkedList_H_

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
typedef struct DoubleEndedNode
{
    uint64_t value;
	struct DoubleEndedNode* prev;
    struct DoubleEndedNode* next;
} DoubleEndedNode;

/**
 * @brief Linked List struct
 *
 */
typedef struct DoubleyLinkedList
{
    DoubleEndedNode *head;
    DoubleEndedNode *tail;
    size_t size;
} DoubleyLinkedList;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/
void DoubleyLinkedList_init(DoubleyLinkedList* l);

DoubleEndedNode* DoubleyLinkedList_create_node();

void DoubleyLinkedList_insert_front(DoubleyLinkedList* l, DoubleEndedNode* new_node);
void DoubleyLinkedList_insert_back(DoubleyLinkedList* l, DoubleEndedNode* new_node);
void DoubleyLinkedList_insert_before(DoubleyLinkedList* l, DoubleEndedNode* existing, DoubleEndedNode* new_node);
void DoubleyLinkedList_insert_after(DoubleyLinkedList* l, DoubleEndedNode* existing, DoubleEndedNode* new_node);
void DoubleyLinkedList_remove(DoubleyLinkedList* l, DoubleEndedNode* node);
void DoubleyLinkedList_clear(DoubleyLinkedList* l);

size_t DoubleyLinkedList_size(DoubleyLinkedList* l);

#ifdef __cplusplus
};
#endif

#endif /* DoubleyLinkedList_H_ */