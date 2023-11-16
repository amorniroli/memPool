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
 * @file   main.c
 * @author Alessandro Morniroli <alessandro.morniroli@gmail.com>
 * @date   Thu Nov 16 2023
 *
 * @brief  Static memory pool utility implementation.
 */

/* ************************************************************************** *
 *                         Start of includes section                          *
 * ************************************************************************** */

/* Standard C. */
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
/* Module include. */
#include "memPool_conf.h"
#include "memPool.h"

/* ************************************************************************** *
 *                          End of includes section                           *
 * ************************************************************************** */


/* ************************************************************************** *
 *                    Start of private definitions section                    *
 * ************************************************************************** */

/**
 * Check parameters macro.
 */
#if (!defined MEM_POOL_CHECK_PARAMS || (MEM_POOL_CHECK_PARAMS == 0))
    #define memPool_checkParam(...)
#else
    #define memPool_checkParam(pX)           \
        if ((pX) == false)                   \
        {                                    \
            ret = MEM_POOL_ERROR_PARAMETERS; \
        }                                    \
        else
#endif /* MEM_POOL_CHECK_PARAMS && (MEM_POOL_CHECK_PARAMS == 1) */

/* ************************************************************************** *
 *                     End of private definitions section                     *
 * ************************************************************************** */


/* ************************************************************************** *
 *                    Start of external variables section                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *                     End of external variables section                      *
 * ************************************************************************** */


/* ************************************************************************** *
 *                     Start of private variables section                     *
 * ************************************************************************** */

/* ************************************************************************** *
 *                      End of private variables section                      *
 * ************************************************************************** */


/* ************************************************************************** *
 *                Start of private function prototypes section                *
 * ************************************************************************** */

/* ************************************************************************** *
 *                 End of private function prototypes section                 *
 * ************************************************************************** */


/* ************************************************************************** *
 *                     Start of private function section                      *
 * ************************************************************************** */

/* ************************************************************************** *
 *                      End of private function section                       *
 * ************************************************************************** */


/* ************************************************************************** *
 *                      Start of global function section                      *
 * ************************************************************************** */

memPool_error_t
memPool_init (memPool_handle_t* ptrHandle,
              uint8_t*          ptrStorage,
              uint32_t          slotSize,
              uint32_t          slotNumber)
{
    memPool_error_t ret;

    /* Assert block (if defined). */
    memPool_assert ((ptrHandle  != NULL) &&
                    (ptrStorage != NULL) &&
                    (slotSize   != 0U)   &&
                    (slotNumber != 0U));

    /* Check parameters (if defined). */
    memPool_checkParam ((ptrHandle  != NULL) &&
                        (ptrStorage != NULL) &&
                        (slotSize   != 0U)   &&
                        (slotNumber != 0U))
    {
        uint32_t i;

        /* Clear pool & storage (just in case). */
        (void) memset (ptrHandle,  0x00, sizeof (*ptrHandle));
        (void) memset (ptrStorage, 0x00, (slotSize * slotNumber));

        /* Copy pool info. */
        ptrHandle->slotSize   = slotSize;
        ptrHandle->slotNumber = slotNumber;

        /* Initialize loop variables (start from end, just to debug easily). */
        ret = MEM_POOL_OK;
        i   = slotNumber;

        /* Loop to set all slots as freed. */
        do
        {
            uint8_t* ptrSlot;

            /* Decrement index. */
            i--;

            /* Set pointer to slot. */
            ptrSlot = &ptrStorage[(i * slotSize)];

            /* Free block. */
            ret = memPool_free (ptrHandle, ptrSlot);
        } while ((ret == MEM_POOL_OK) && (i > 0U));
    }

    /* Assert block (if defined). */
    memPool_assert (ret == MEM_POOL_OK);

    /* Return the function result code. */
    return ret;
}

memPool_error_t
memPool_alloc (memPool_handle_t* ptrHandle, uint8_t** ptr2Slot)
{
    memPool_error_t ret;

    /* Assert block (if defined). */
    memPool_assert ((ptrHandle != NULL) && (ptr2Slot != NULL));

    /* Check parameters (if defined). */
    memPool_checkParam ((ptrHandle != NULL) && (ptr2Slot != NULL))
    {
        /* Empty? */
        if (ptrHandle->ptrHead == NULL)
        {
            /* Clear pointer. */
            *ptr2Slot = NULL;

            /* Error! No free slots! */
            ret = MEM_POOL_ERROR_SPACE;
        }
        else
        {
            uint8_t* ptrTemp;

            /* Temp store next slot of the current head. */
            ptrTemp = *(((uint8_t**) ptrHandle->ptrHead));

            /* Store pointer to dest (current head is the slot allocated). */
            *ptr2Slot = ptrHandle->ptrHead;

        #if (defined memPool_zeroize && (memPool_zeroize == 1))
            /* Zeroise the slot (as calloc). */
            (void) memset (*ptr2Slot, 0x00, ptrHandle->slotSize);
        #endif /* memPool_zeroize && (memPool_zeroize == 1) */

            /* Clear next. */
            *((uint8_t**) ptrHandle->ptrHead) = NULL;

            /* Update head. */
            ptrHandle->ptrHead = ptrTemp;

            /* Succeed! */
            ret = MEM_POOL_OK;
        }
    }

    memPool_assert (ret == MEM_POOL_OK);

    /* Return the function result code. */
    return ret;
}

memPool_error_t
memPool_free (memPool_handle_t* ptrHandle, uint8_t* ptrSlot)
{
    memPool_error_t ret;

    /* Assert block (if defined). */
    memPool_assert ((ptrHandle != NULL) && (ptrSlot != NULL));

    /* Check parameters (if defined). */
    memPool_checkParam ((ptrHandle != NULL) && (ptrSlot != NULL))
    {
        void* ptr;

        /* Clear error code. */
        ret = MEM_POOL_OK;

        /* Assert that item is not in list. */
        ptr = ptrHandle->ptrHead;

        while ((ret == MEM_POOL_OK) && (ptr != NULL))
        {
            memPool_assert (ptr != ptrSlot);

            /* Same address? */
            if (ptr != ptrSlot)
            {
                /* Update pointer. */
                ptr = *((uint8_t**) ptr);
            }
            else
            {
                /* Error! Slow was not allocated! */
                ret = MEM_POOL_ERROR_SLOT_NOT_ALLOCATED;
            }
        }

        /* Succeed? */
        if (ret == MEM_POOL_OK)
        {
            /* No slots available at the moment? */
            if (ptrHandle->ptrHead == NULL)
            {
                /* Just do nothing. */
            }
            else
            {
                /* Set item freed to point to current head of the list. */
                *((uint8_t**) ptrSlot) = ptrHandle->ptrHead;
            }

            /* Slot freed is the new head. */
            ptrHandle->ptrHead = ptrSlot;
        }
        else
        {
            /* Just do nothing. */
        }
    }

    memPool_assert (ret == MEM_POOL_OK);

    /* Return the function result code. */
    return ret;
}

/* ************************************************************************** *
 *                       End of global function section                       *
 * ************************************************************************** */
