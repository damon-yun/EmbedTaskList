/*******************************************************************************
* -----------------------------------------------------------------------------
*									     									 
* e_task_list.c - definitions for the emebd task list interface			     			 
*									     
* -----------------------------------------------------------------------------
* Copyright (C) Damon Zhang
* All rights reserved.
*
* Author : Damon Zhang
* Website: https://damon-yun.github.io/blog.github.io/
* E-mail : damonzhang92@foxmail.com
* -----------------------------------------------------------------------------
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* Code is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
* or GNU Library General Public License, as applicable, for more details.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/

/**
 * \file
 * \brief embed task list
 * 
 * \internal
 * \par Modification History
 * - 1.00 17-07-13  damon.zhang, first implementation.
 * \endinternal
 */

#include "e_common.h"
#include "e_task_list.h"

/*******************************************************************************
 * Private define region: constant & MACRO defined here                              
 ******************************************************************************/

/*******************************************************************************
 * extern region: extern global variable & function prototype                 
 ******************************************************************************/

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

e_task_node_t  __task_node_pool[E_TASK_NODE_NUM];
uint8_t        __task_node_used[E_TASK_NODE_NUM];

e_task_node_t *__p_task_queue_head = NULL;
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public functions:ISR
 ****************************************************************************/
void e_task_list_isr(uint32_t system_tick)
{
    e_task_node_t *p_task_node = __p_task_queue_head;
    
    if (!p_task_node) return;
    
    while (p_task_node) {
        if (p_task_node->time_tick == 0) {
            p_task_node->pfun_task(p_task_node->p_arg);
            p_task_node->complete_flag = 1;

            e_task_node_remove(p_task_node);
        }
        
        p_task_node = p_task_node->next;
    }
    if(__p_task_queue_head)
        --(__p_task_queue_head->time_tick);   //update queue head node time tick;
}
/*****************************************************************************
 * Private functions
 ****************************************************************************/
/**
 * \brief alloc one task node
 */
static e_task_node_t *__alloc_task_node (void)
{
    int i = 0;
    for (i = 0; i < E_TASK_NODE_NUM; i++) {
        if (!__task_node_used[i]) {
            __task_node_used[i] = 1;
            return &(__task_node_pool[i]);
        }
    }

    return NULL;
}

/**
 * \brief free the task node
 */
static void __free_task_node (e_task_node_t *p_node)
{
    int i = 0;

    if (p_node == NULL) return;
    
    for (i = 0; i < E_TASK_NODE_NUM; i++) {
        if (p_node == (&(__task_node_pool[i]))) {
            __task_node_used[i] = 0;
            p_node->pfun_task = NULL;
            p_node->next = NULL;
            p_node->p_arg = NULL;
            p_node->complete_flag = 0;
            return;
        }
    }
}

static int __task_node_on_the_list (e_task_node_t *p_node)
{
    e_task_node_t *p_task_node = __p_task_queue_head;
    while (p_task_node && p_task_node != p_node) {
        p_task_node = p_task_node->next;
    }
    if (p_task_node) {
        return eStatus_Success;
    }

    return eStatus_OutOfRange;
}
/*****************************************************************************
 * Public functions
 ****************************************************************************/
/**
 * \brief init one task node
 */
e_task_node_t *e_task_node_init(pfun_task_t pfun_task, void *p_arg, uint32_t time_tick)
{
    e_task_node_t *p_node;

    if (pfun_task == NULL) {
        return NULL;
    }

    p_node = __alloc_task_node();
    if (p_node == NULL) {
        return NULL;
    }
    
    p_node->time_tick = time_tick;
    p_node->p_arg = p_arg;
    p_node->pfun_task = pfun_task;
    p_node->next = NULL;
    p_node->complete_flag = 0;

    return p_node;
}
/**
 * \brief add one note in work queue
 */
int e_task_node_add (e_task_node_t *p_node)
{
    e_task_node_t **pp_task_node = &__p_task_queue_head;

    if (p_node == NULL) return -1;
    
    e_task_node_remove (p_node);

    __disable_irq();

    if(*pp_task_node == NULL) {
        *pp_task_node = p_node;
        
        __enable_irq();
        return eStatus_Success;
    }

    while (*pp_task_node) {
        if (p_node->time_tick <= (*pp_task_node)->time_tick) {
            (*pp_task_node)->time_tick -= p_node->time_tick;

            p_node->next = *pp_task_node;  //insert node

            *pp_task_node = p_node;

            __enable_irq();
            return eStatus_Success;
        }
        p_node->time_tick -= (*pp_task_node)->time_tick;
        pp_task_node = & ((*pp_task_node)->next);
    }

    __enable_irq();

    return eStatus_Fail;
}
/**
 * \brief remove the task node
 */
int e_task_node_remove (e_task_node_t *p_node)
{
    e_task_node_t **p_task_node = &__p_task_queue_head;

    if (p_task_node == NULL || p_node == NULL) {
        return eStatus_Fail;
    }

    if (__task_node_on_the_list(p_node) != eStatus_Success)
        return eStatus_Fail;

    __disable_irq();
        
    while(*p_task_node != p_node) {
        
        p_task_node = (&(*p_task_node)->next);
    }
    if (p_node->next != NULL)
        p_node->next->time_tick += (*p_task_node)->time_tick;
    
    *p_task_node = p_node->next;
    p_node->next = NULL;

    __enable_irq();

    return eStatus_Success;
}


/**
 * \brief delete the task node
 */
int e_task_node_delete (e_task_node_t *p_node)
{
    e_task_node_remove(p_node);
    __free_task_node();

    return eStatus_Success;
}


/*******************************************************************************
 * main code region: function implement                                        
 ******************************************************************************/


/* end of file */


