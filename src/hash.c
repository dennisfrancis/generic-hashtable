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
 * @file hash.c
 * @author Dennis Francis
 * @date 10 Jan 2025
 * @brief C source file for generic hash table implementation.
 *
 * This hash table allows data (keys+values) of user defined type.
 */

#include <stdlib.h>

#include "hash.h"

int hashtable_init(hashtable_t* ht, int slots, int (*comp_keys)(void*, void*),
                   unsigned long int (*hash)(void* element, void* params), void* hash_params)
{
    int i;
    if (ht->memFreed == 'N')
    {
        hashtable_destroy(ht);
    }
    ht->memFreed = 'Y';
    ht->slots = slots;
    ht->hash = hash;
    ht->hash_params = hash_params;
    ht->list_arr = (list_t*)malloc(slots * sizeof(list_t));

    if (!(ht->list_arr))
        return -1;

    for (i = 0; i < slots; i++)
    {
        list_init(ht->list_arr + i, comp_keys);
    }

    ht->num_elements = 0;
    ht->element_list = NULL;

    ht->memFreed = 'N';

    return 0;
}

void hashtable_destroy(hashtable_t* ht)
{
    int i;
    if (ht->memFreed == 'Y')
        return;
    for (i = 0; i < ht->slots; i++)
    {
        list_cleanup(ht->list_arr + i); // Free each list
    }
    free(ht->list_arr); // Free the array of list headers
    free(ht->element_list); // Null check is done by free()
    //free( ht->hash_params ); // do only if dynamically allocated
    ht->memFreed = 'Y';
}

int hashtable_insert(hashtable_t* ht, void* element, long int slot)
{ // Does not check for existence

    int target_slot = (slot < 0) ? (long int)ht->hash(element, ht->hash_params) : slot;
    int ret_val = list_insert(ht->list_arr + target_slot, element);
    if (ret_val == 0)
        ++(ht->num_elements);
    return ret_val;
}

void* is_in_hashtable(hashtable_t* ht, void* ref_element, void** ht_node)
{
    int target_slot = ht->hash(ref_element, ht->hash_params);
    return isPresent(ht->list_arr + target_slot, ref_element, ht_node);
}

void hashtable_delete(hashtable_t* ht, unsigned int slot, void* ht_node)
{
    list_delete(ht->list_arr + slot, ht_node);
    --(ht->num_elements);
}

void** get_elements_in_hashtable(hashtable_t* ht, int* num_elements, void* (*get_field)(void*),
                                 unsigned int (*get_index)(void*))
{
    int i, default_index, index = 0;
    list_t* lst;
    NODEptr node;
    if (ht->element_list)
    {
        free(ht->element_list);
    }
    ht->element_list = (void**)malloc((ht->num_elements) * sizeof(void*));
    if (!(ht->element_list))
        return NULL;
    for (i = 0, default_index = 0; i < ht->slots; i++)
    {
        lst = ht->list_arr + i;
        if (lst->count)
        {
            node = lst->head;
            while (node)
            {
                index = (get_index) ? (int)get_index(node->element) : default_index++;
                ((char**)ht->element_list)[index]
                    = (get_field) ? get_field(node->element) : node->element;
                node = node->next;
            }
        }
    }
    if (num_elements)
        *num_elements = ht->num_elements;

    return ht->element_list;
}
