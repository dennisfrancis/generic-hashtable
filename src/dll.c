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
 * @file dll.c
 * @author Dennis Francis
 * @date 10 Jan 2025
 * @brief C source file for generic doubly linked list implementation.
 *
 * This doubly linked list allows the storage of data of user defined type.
 */

#include "dll.h"
#include <stdlib.h>
#include <string.h>

static int __create_node(void* element, NODEptr* new_node);

void list_init(list_t* lst, int (*comp_keys)(void*, void*))
{
    lst->head = NULL;
    lst->count = 0;
    lst->comp_keys = comp_keys;
}

/**
 * @brief Creates a new node that will hold the provided pointer to data.
 *
 * @param element Pointer to the data (in heap) to be stored in the new node.
 * @param new_node Pointer to a node pointer variable where the newly allocated
 * node's address is to be placed.
 *
 * @return 0 in case of allocation failure, else returns 0.
 */
static int __create_node(void* element, NODEptr* new_node)
{
    *new_node = (NODEptr)malloc(sizeof(NODE));
    if (*new_node)
    {
        (*new_node)->element = element;
        (*new_node)->next = NULL;
        (*new_node)->prev = NULL;
        return 0;
    }

    return -1;
}

int list_insert(list_t* lst, void* element)
{
    NODEptr new_node;
    if (__create_node(element, &new_node) == 0)
    {
        if (lst->count == 0)
        {
            lst->head = new_node;
        }
        else
        {
            NODEptr next = lst->head;
            lst->head = new_node;
            lst->head->next = next;
            next->prev = lst->head;
        }
        ++(lst->count);
        return 0;
    }
    return -1;
}

void* isPresent(list_t* lst, void* ref_element, void** ret_node)
{
    NODEptr node = lst->head;
    int flag = 0;
    if (!node)
    {
        if (ret_node)
            *(NODEptr*)ret_node = NULL;
        return NULL;
    }

    while (!flag && node)
    {
        if (lst->comp_keys(node->element, ref_element) == 0)
        {
            flag = 1;
        }
        else
        {
            node = node->next;
        }
    }
    if (ret_node)
    {
        if (flag)
            *(NODEptr*)ret_node = (void*)node;
        else
            *(NODEptr*)ret_node = NULL;
    }
    return ((node) ? node->element : NULL);
}

void list_delete(list_t* lst, void* node)
{
    NODEptr save = node;
    NODEptr prev, next;
    if (!node)
        return;
    if (save)
    {
        prev = save->prev;
        next = save->next;
        if (!prev && !next)
            lst->head = NULL;
        else if (!prev && next)
        {
            lst->head = next;
            next->prev = NULL;
        }
        else if (prev && !next)
            prev->next = NULL;
        else
        {
            prev->next = next;
            next->prev = prev;
        }
        free(save->element);
        free(save);
        --(lst->count);
    }
}

void list_cleanup(list_t* lst)
{
    NODEptr node, next;
    node = lst->head;

    while (node)
    {
        next = node->next;
        free(node->element);
        free(node);
        node = next;
    }
}
