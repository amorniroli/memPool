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
 * @file   memPool_Conf.h
 * @author Alessandro Morniroli <alessandro.morniroli@gmail.com>
 * @date   Thu Nov 16 2023
 *
 * @brief  Memory pool configuration example.
 */

#ifndef MEM_POOL_CONF_H__
#define MEM_POOL_CONF_H__

/**********************************************************************************************************************
*           HEADER INCLUDE                                                                                            *
**********************************************************************************************************************/

/**
 * If eneabled, parameters function are checked (if not valid, \ref MEM_POOL_ERROR_PARAMETERS is returned)
 */
#define MEM_POOL_CHECK_PARAMS 1

/**
 * Assert disabled (for unit test purpose).
 */
#define memPool_assert(pX)

/**
 * Slot is 'zeroize' (as calloc standard routine) when \ref memPool_get allocates a valid one.
 */
#define memPool_zeroize 1

/**********************************************************************************************************************
*           PUBLIC DEFINES                                                                                            *
**********************************************************************************************************************/

/**********************************************************************************************************************
*           PUBLIC TYPES                                                                                              *
**********************************************************************************************************************/

/**********************************************************************************************************************
*           PUBLIC VARIABLES                                                                                          *
**********************************************************************************************************************/

/**********************************************************************************************************************
*           PUBLIC FUNCTIONS PROTOTYPES                                                                               *
**********************************************************************************************************************/

#endif /* MEM_POOL_CONF_TEMPLATE_H__ */

