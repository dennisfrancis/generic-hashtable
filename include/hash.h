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
 * @file hash.h
 * @author Dennis Francis
 * @date 10 Jan 2025
 * @brief header file for generic hash table implementation.
 *
 * This hash table allows data (keys+values) of user defined type.
 */

#pragma once

#include "dll.h"

typedef struct HASHTABLE
{
    list_t* list_arr; /**< Array of doubly linked lists */
    int slots; /**< Number of slots in the hash table */
    unsigned int num_elements; /**< Number of data elements stored by the hash table */
    int element_size;

    unsigned long int (*hash)(void* element, void* params); /**< user defined
                                                              hash function
                                                              accepting the
                                                              data element
                                                              and another
                                                              user defined
                                                              hash parameters
                                                              */

    void** element_list;
    void* hash_params; /**< Used defined hash parameter(s) which will be
                         passed to hash() */
    char memFreed; /**< Boolean field to indicate if hash table innards are
                     allocated or not */

} hashtable_t;

/**
 * @brief Initializes the provided hash table instance.
 *
 * @param ht Pointer to the hash table instance to be initialized.
 * @param slots Number of slots to be created in the hash table.

 * @param comp_keys  Pointer to a function that takes pointers to two user
 * defined data elements. This function must return 0 if the data arguments are
 * equal.
 *
 * @param hash Pointer to a function that computes an int hash of a user
 * defined data element. This function also takes a pointer to another user
 * defined hash parameter(s) data which the function may use in the computation
 * of the hash.
 *
 * @param hash_params Pointer to a user defined data structure that may hold
 * parameter(s) for the computation of hash function. This is passed as the
 * second parameter of @@hash provided whenever a hash needs to be computed.
 *
 * @return -1 if there is an allocation failure else returns 0.
 */
int hashtable_init(hashtable_t* ht, int slots, int (*comp_keys)(void*, void*),
                   unsigned long int (*hash)(void* element, void* params), void* hash_params);

/**
 * @brief Deallocates all memory related to the passed hash table instance.
 *
 * @param ht Pointer to hash table instance to be destroyed.
 */
void hashtable_destroy(hashtable_t* ht);

/**
 * @brief Inserts a new data element into the hash table. This does not check
 * if the element already exists.
 *
 * @parm ht Pointer to hash table instance.
 * @parm element Pointer to the data item to be inserted.
 * @param slot Provide the slot number for the data item if its hash is
 * already known (optimization) if not provide any negative long int.
 *
 * @return -1 if there is an error allocating memory for the insertion else
 * returns 0.
 */
int hashtable_insert(hashtable_t* ht, void* element, long int slot);

/**
 * @brief Checks for the existence of the data element in the hash table.
 *
 * @param ht Pointer to hash table instance.
 * @param ref_element Data element to be searched in the hash table.
 * @param ht_node On successful search, ht_node will be made to point to the
 * matched doubly linked list node pointer.
 *
 * @return NULL if search failed else the address of the found data element.
 */
void* is_in_hashtable(hashtable_t* ht, void* ref_element, void** ht_node);

/**
 * @brief Deletes the provided linked list node at the given slot.
 *
 * @parm ht Pointer to the hash table instance.
 * @parm slot Slot number where @@ht_node is present.
 * @param ht_node Linked list node which needs to be deleted.
 */
void hashtable_delete(hashtable_t* ht, unsigned int slot, void* ht_node);

/**
 * @brief Collects pointers to all data elements into an array and returns.
 *
 * Returns a pointer to an array of pointers. Each pointer in that array will
 * point to some field in the data elements. The user must not free this
 * pointer. It will be cleaned up during hashtable_destroy() or during next
 * call to this function.
 *
 * @param ht Pointer to hash table instance.
 * @param num_elements (implicit return) Number of data elements found in the hash table.

 * @param get_field User defined function that extracts a field off the passed
 * data element. If this is non NULL, this function will be used to extract
 * fields off all data elements in the hash table and an array of fields will
 * be returned. If this is NULL an array of the data elements will be returned.
 *
 * @param get_index User defined function that takes the pointer to data
 * element and returns and index where address of the (field of the) data
 * element is to be stored in the returned list. If this parameter is NULL,
 * order of items in the returned array is undefined.
 *
 */
void** get_elements_in_hashtable(hashtable_t* ht, int* num_elements, void* (*get_field)(void*),
                                 unsigned int (*get_index)(void*));
