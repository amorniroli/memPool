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
 * @file   main.h
 * @author Alessandro Morniroli <alessandro.morniroli@gmail.com>
 * @date   Thu Nov 16 2023
 *
 * @brief  Mem pool test.
 */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "memPool.h"

#define SLOTS 3U

typedef struct
{
    void*   ptr;
    uint8_t someData;
} test_t;

int
main (void)
{
    test_t           storage[SLOTS];
    memPool_handle_t pool;
    uint32_t         i;
    test_t*          ptrSlot;

    assert (memPool_init (&pool, ((uint8_t*) storage), sizeof(test_t), 0) != MEM_POOL_OK);

    assert (memPool_init (&pool, ((uint8_t*) storage), sizeof(test_t), SLOTS) == MEM_POOL_OK);

    assert (memPool_alloc (&pool, ((uint8_t**) ((uint8_t**) &ptrSlot))) == MEM_POOL_OK);
    assert (ptrSlot == &storage[0]);

    assert (memPool_alloc (&pool, ((uint8_t**) ((uint8_t**) &ptrSlot))) == MEM_POOL_OK);
    assert (ptrSlot != NULL);
    assert (ptrSlot == &storage[1]);

    assert (memPool_alloc (&pool, ((uint8_t**) ((uint8_t**) &ptrSlot))) == MEM_POOL_OK);
    assert (ptrSlot != NULL);
    assert (ptrSlot == &storage[2]);

    assert (memPool_alloc (&pool, ((uint8_t**) ((uint8_t**) &ptrSlot))) == MEM_POOL_ERROR_SPACE);
    assert (ptrSlot == NULL);

    assert (memPool_init (&pool, ((uint8_t*) storage), sizeof(test_t), 3) == MEM_POOL_OK);

    assert (memPool_alloc (&pool, ((uint8_t**) &ptrSlot)) == MEM_POOL_OK);
    assert (ptrSlot == &storage[0]);
    assert (memPool_free (&pool, ((uint8_t*) ptrSlot)) == MEM_POOL_OK);

    assert (memPool_alloc (&pool, ((uint8_t**) &ptrSlot)) == MEM_POOL_OK);
    assert (ptrSlot == &storage[0]);

    assert (memPool_alloc (&pool, ((uint8_t**) &ptrSlot)) == MEM_POOL_OK);
    assert (ptrSlot == &storage[1]);

    assert (memPool_alloc (&pool, ((uint8_t**) &ptrSlot)) == MEM_POOL_OK);
    assert (ptrSlot == &storage[2]);

    assert (memPool_alloc (&pool, ((uint8_t**) &ptrSlot)) == MEM_POOL_ERROR_SPACE);
    assert (ptrSlot == NULL);

    assert (memPool_free (&pool, ((uint8_t*) &storage[0])) == MEM_POOL_OK);
    assert (memPool_free (&pool, ((uint8_t*) &storage[1])) == MEM_POOL_OK);
    assert (memPool_free (&pool, ((uint8_t*) &storage[2])) == MEM_POOL_OK);

    assert (memPool_free (&pool, ((uint8_t*) &storage[0])) == MEM_POOL_ERROR_SLOT_NOT_ALLOCATED);

    return 0;
}

