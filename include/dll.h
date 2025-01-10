/************************************************************************
 * Generic HashTable                                                    *
 * Copyright (C) 2012 by Dennis Francis                                 *
 *                                                                      *
 * This program is free software: you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * This program is distributed in the hope that it will be useful,      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.*
 ************************************************************************/

/**
 * @file dll.h
 * @author Dennis Francis
 * @date 10 Jan 2025
 * @brief Header file for generic doubly linked list implementation.
 *
 * This doubly linked list allows the storage of data of user defined type.
 */

#pragma once

/**
 * @brief Internal struct representing a node of the doubly linked list.
 */
typedef struct ND
{
    struct ND* prev; /**< Points to the previous node of the linked list */
    struct ND* next; /**< Points to the next node of the linked list */
    void* element; /**< Points to the data held by the node */

} NODE, *NODEptr;

/**
 * @brief External struct representing a doubly linked list.
 */
typedef struct
{
    NODEptr head; /**< Points to the head of the linked list */
    int count; /**< Number of nodes in the linked list */
    int (*comp_keys)(void*, void*); /**< pointer to a function that compares
                                      the data of two nodes @see list_init() */

} list_t;

/**
 * @brief Initializes a list struct.
 *
 * @param lst Pointer to list_t struct that should be initialized.
 * @param comp_keys Pointer to a function which takes pointers to the data of
 * two nodes and return 0 if they are equal.
 */
void list_init(list_t* lst, int (*comp_keys)(void*, void*));

/**
 * @brief Inserts a new node into the list which will hold the given data.
 *
 * @param lst Pointer to an initialized list structure.
 * @param element Pointer to the data (in heap) that need to be held and owned
 * by the new node that will be created and inserted.
 * @return 0 on success and -1 if there is a memory allocation error.
 */
int list_insert(list_t* lst, void* element);

/**
 * @brief Checks if there is an node which contains data that matches the
 * supplied data.
 *
 * @param lst Pointer to an initialized list structure.
 * @param ref_element Pointer to data that needs to be checked against data in
 * every list nodes.
 * @param ret_node If there is a match ret_node will be made to point to the
 * matched node pointer.
 *
 * @return NULL if there is no match else the pointer to the data held by
 * matching node is returned.
 */
void* isPresent(list_t* lst, void* ref_element, void** ret_node);

/**
 * @brief Deletes a node from the list and frees its associated data.
 *
 * @lst Pointer to an initialized list structure.
 * @node node Pointer to the node to be deleted.
 */
void list_delete(list_t* lst, void* node);

/**
 * @brief Frees all nodes and associated data in the given list.
 *
 * @param lst Pointer to an initialized list structure.
 */
void list_cleanup(list_t* lst);
