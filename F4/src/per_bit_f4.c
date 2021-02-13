/**
 * @file per_bit_f4.c
 *
 * This file contains the peripheral BITBAND register functions
 *
 * Copyright (c) 2021 admaunaloa admaunaloa@gmail.com
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

#include "per_bit_f4.h"

#include "per_log_f4.h"

/// Set the contents of a number of bit band bits
bool per_bit_set_bits(per_bit_bitband_t* addr, uint_fast8_t size, uint_fast16_t val)
{
    while (size > 0)
    {
        addr->Bit16 = val & (uint_fast16_t)1;
        val >>= 1;
        ++addr;
        --size;
    }

    return true;
}

/// Set the contents of a number of bit band bits and check it afterwards
bool per_bit_set_bits_check(per_bit_bitband_t* addr, uint_fast8_t size, uint_fast16_t val)
{
    per_bit_set_bits(addr, size, val);

    if (PER_BIT_BITS_GET(addr, size) != val)
    {
        per_log_err(PER_LOG_BITBAND, PER_BIT_ERR_SET, (uint_fast32_t) addr); // Address is error value
        return false;
    }

    return true;
}
