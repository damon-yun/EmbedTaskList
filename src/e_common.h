/*******************************************************************************
* -----------------------------------------------------------------------------
*									     									 
* i2c.h - definitions for the i2c-bus interface			     			 
*									     
* -----------------------------------------------------------------------------
* Copyright (C) Damon Zhang
* All rights reserved.
*
* Author : Damon Zhang
* Website: https://damon-yun.github.io/blog.github.io/
* E-mail : damoncheung@foxmail.com
*
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
* -----------------------------------------------------------------------------
* 
* @file
* Dynamic memory manager
*
* -----------------------------------------------------------------------------
*******************************************************************************/

/**
 * \file
 * \brief 模拟SPI Flash的操作实现
 * 
 * \internal
 * \par Modification History
 * - 1.00 16-10-13  damon.zhang, first implementation.
 * \endinternal
 */


#ifndef __E_COMMON_H
#define __E_COMMON_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
 * Header file
 ******************************************************************************/

/**
 * \addtogroup am_if_uart
 * \copydoc am_uart.h
 * @{
 */

/**
 * \name generic status define
 * \note 
 * @{
 */


/*! @brief Construct a status code value from a group and code number. */
#define MAKE_STATUS(group, code) ((((group)*100) + (code)))

/*! @brief Status group numbers. */
enum _e_status_groups
{
    eStatusGroup_Generic = 0,                 /*!< Group number for generic status codes. */
    eStatusGroup_FLASH = 1,                   /*!< Group number for FLASH status codes. */
    
    eStatusGroup_ApplicationRangeStart = 100, /*!< Starting number for application groups. */
};

/*! @brief Generic status return codes. */
enum _e_generic_status
{
    eStatus_Success = MAKE_STATUS(eStatusGroup_Generic, 0),
    eStatus_Fail = MAKE_STATUS(eStatusGroup_Generic, 1),
    eStatus_ReadOnly = MAKE_STATUS(eStatusGroup_Generic, 2),
    eStatus_OutOfRange = MAKE_STATUS(eStatusGroup_Generic, 3),
    eStatus_InvalidArgument = MAKE_STATUS(eStatusGroup_Generic, 4),
    eStatus_Timeout = MAKE_STATUS(eStatusGroup_Generic, 5),
    eStatus_NoTransferInProgress = MAKE_STATUS(eStatusGroup_Generic, 6),
};

/*! @brief Type used for all status and error return values. */
typedef int32_t status_t;

/** @} */

#define E_DEBUG(...) 




/**
 * @}
 */
 
 #ifdef __cplusplus
}
#endif

#endif /* __E_COMMON_H */

/* end of file */


