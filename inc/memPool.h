/**
 * MIT License
 *
 * Copyright (c) 2021 Alessandro Morniroli
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @file   memPool.h
 * @author Alessandro Morniroli <alessandro.morniroli@gmail.com>
 * @date   Thu Nov 16 2023
 *
 * @brief  Static memory pool utility interface.
 */

/* ************************************************************************** */
#ifndef MEM_POOL_H__
#define MEM_POOL_H__
/* ************************************************************************** */

/* ************************************************************************** *
 *                         Start of includes section                          *
 * ************************************************************************** */

/* Standard C. */
#include <stdint.h>

/* ************************************************************************** *
 *                          End of includes section                           *
 * ************************************************************************** */


/* ************************************************************************** *
 *                    Start of global definitions section                     *
 * ************************************************************************** */

/**
 * Memory pool errors.
 */
typedef enum
{
    MEM_POOL_OK,                      /**< No error occurred.         */
    MEM_POOL_ERROR_PARAMETERS,        /**< Wrong function parameters. */
    MEM_POOL_ERROR_SPACE,             /**< No more space to allocate. */
    MEM_POOL_ERROR_SLOT_NOT_ALLOCATED /**< Slot was not allocated.    */
} memPool_error_t;

/**
 * Memory pool handle.
 */
typedef struct
{
    uint8_t* ptrHead;    /**< Pointer to next available slot. */
    uint32_t slotSize;   /**< Single slot size (bytes).       */
    uint32_t slotNumber; /**< Total number of slots.          */
} memPool_handle_t;

/* ************************************************************************** *
 *                     End of global definitions section                      *
 * ************************************************************************** */


/* ************************************************************************** *
 *                     Start of global variables section                      *
 * ************************************************************************** */

/* ************************************************************************** *
 *                      End of global variables section                       *
 * ************************************************************************** */


/* ************************************************************************** *
 *                      Start of global function section                      *
 * ************************************************************************** */

/**
 * @brief Initialize mempool routine.
 *
 * When called, memory pool handle is initialized (all slots available).
 *
 * @return MEM_POOL_OK if no error occurred; anything else otherwise.
 */
memPool_error_t
memPool_init (memPool_handle_t* ptrHandle,
              uint8_t*          ptrStorage,
              uint32_t          slotSize,
              uint32_t          slotNumber);

/**
 * mempool alloc routine.
 *
 * @return MEM_POOL_OK if no error occurred; anything else otherwise.
 */
memPool_error_t
memPool_alloc (memPool_handle_t* ptrHandle, uint8_t** ptr2Slot);

/**
 * mempool free routine.
 */
memPool_error_t
memPool_free (memPool_handle_t* ptrHandle, uint8_t* ptrSlot);

/* ************************************************************************** *
 *                       End of global function section                       *
 * ************************************************************************** */

/* ************************************************************************** */
#endif /* MEM_POOL_H__ */
/* ************************************************************************** */
