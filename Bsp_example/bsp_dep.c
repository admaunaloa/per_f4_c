/**
 * @file bsp_dep.c
 *
 * This file contains the Board Support Package (BSP) dependencies
 *
 * Copyright (c) 2023 admaunaloa admaunaloa@gmail.com
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
 */

#include "bsp_dep.h"

#include "cmsis_gcc.h" // for the LDREX and STREX
#include "per_des.h"

/// Get random key number
uint32_t bsp_dep_key_gen(void)
{
    static uint32_t key;
    key += per_des_uid()->Uid0;

    if (0 == key)
    {
        key += 1;
    }

    return key;
}

/// Lock a mutex
uint16_t bsp_dep_mut16_lock(uint16_t* mut)
{
    uint16_t res = 0; // no lock

    if (0 == __LDREXH(mut)) // Load with exclusive access, zero is free
    {
        uint16_t key = (uint16_t)bsp_dep_key_gen();

        if (0 == __STREXH(key, mut)) // Store with exclusive access
        {
            __DMB(); // Success, synchronize with data memory barrier
            res = key;
        }
    }

    return res;
}

/// Unlock a mutex
void bsp_dep_mut16_unlock(uint16_t* mut, uint16_t key)
{
    if (key == *mut)
    {
        *mut = 0; // Clear it
    }
}
