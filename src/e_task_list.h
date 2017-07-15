/*******************************************************************************
* -----------------------------------------------------------------------------
*									     									 
* e_task_list.h - definitions for the emebd task list interface				 
*									     
* -----------------------------------------------------------------------------
* Copyright (C) Damon Zhang
* All rights reserved.
*
* Author : Damon Zhang
* Website: https://damon-yun.github.io/blog.github.io/
* E-mail : damoncheung@foxmail.com
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


#ifndef __E_TASK_LIST_H
#define __E_TASK_LIST_H


#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
 * Header file
 ******************************************************************************/
#include "board.h"

#include "core_cmFunc.h"
/**
 * \addtogroup am_if_uart
 * \copydoc am_uart.h
 * @{
 */


#define E_TASK_NODE_NUM            10
/**
 * \name Embed Task Quete Node Struct Define
 * \note 
 * @{
 */
typedef void (* pfun_task_t)(void *p_arg);

typedef struct e_task_node {

    pfun_task_t pfun_task;
    void *p_arg;
    struct e_task_node *next;

    uint32_t time_tick;
    uint8_t  complete_flag;      //reserve
} e_task_node_t;

/** @} */
 
/*******************************************************************************
 * Public define region: constant & MACRO defined here                              
 ******************************************************************************/

/*******************************************************************************
 * extern region: extern global variable & function prototype                 
 ******************************************************************************/

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/


/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/


/*****************************************************************************
 * Private functions
 ****************************************************************************/
 
 
/*****************************************************************************
 * Public functions:ISR
 ****************************************************************************/
extern void e_task_list_isr(uint32_t system_tick);

/*****************************************************************************
 * Public functions
 ****************************************************************************/
 
/**
 * \brief init one task node
 */
extern e_task_node_t *e_task_node_init(pfun_task_t pfun_task, void *p_arg, uint32_t time_tick);


/**
 * \brief add one note in work queue
 */
extern int e_task_node_add (e_task_node_t *p_node);

/**
 * \brief remove the task node
 */
extern int e_task_node_remove (e_task_node_t *p_node);

/**
 * \brief delete the task node
 */
extern int e_task_node_delete (e_task_node_t *p_node);

/**
 * \brief UART数据发送（查询模式）
 *
 * \param[in] handle  : UART标准服务操作句柄
 *
 * \return 成功发送数据的个数
 */


/**
 * @}
 */
 
#ifdef __cplusplus
}
#endif

#endif /* __E_TASK_LIST_H */

/* end of file */


