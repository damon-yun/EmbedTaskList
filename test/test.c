/*
 * @brief Blinky example using SysTick and interrupt
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"

#include "e_task_list.h"
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
static uint32_t g_task0_complete = 0;
static uint32_t g_task1_complete = 0;
static uint32_t g_task2_complete = 0;

/*****************************************************************************
 * Private functions
 ****************************************************************************/
static void task(void *p_arg)
{
    *((uint32_t *)p_arg) = 1;
}

static void task1(void *p_arg)
{
    *((uint32_t *)p_arg) = 1;
}

static void task2(void *p_arg)
{
    *((uint32_t *)p_arg) = 1;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/
void SysTick_Init(void)
{
    SysTick_Config(SystemCoreClock / TICKRATE_HZ);
}
/*
 *  Systick time ISR
 */
void SysTick_Handler(void)
{
    e_task_queue_isr(tick_ct);
}

/*****************************************************************************
 * main function
 ****************************************************************************/
int main(void)
{
    e_task_node_t *node0;
    e_task_node_t *node1;
    e_task_node_t *node2;
    
    SystemCoreClockUpdate();
    Board_Init();
    Board_LED_RGB_Off();

    SysTick_Init();

    node0 = e_task_node_init(task,(void *)&g_task0_complete, 30);
    node1 = e_task_node_init(task1,(void *)&g_task1_complete, 10);
    node2 = e_task_node_init(task2,(void *)&g_task2_complete, 20);
    
    e_task_node_add(node0);
    e_task_node_add(node1);
    e_task_node_add(node2);
    
    while(1){
        if(g_task1_complete) {
            g_task1_complete = 0;
            node1->time_tick = 5;
            node1->complete_flag = 0;
            
            e_task_node_add(node1);
        }
		myDelay(50);
    }
}
