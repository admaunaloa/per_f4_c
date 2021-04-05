/**
 * @file per_pwr.h
 *
 * This file contains the power controller (PWR)
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

#ifndef per_pwr_h_
#define per_pwr_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_pwr_f4.h"

/// PWR base address
#define PER_PWR ((per_pwr_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB2 + (uintptr_t)0x3800))

/// PWR pointer to pwr
static per_inline const per_pwr_t* const per_pwr(void)
{
    static const per_pwr_t pwr =
    {
        .Per = PER_PWR,
        .Err = PER_LOG_PWR,
        .Adcdc = true,
        .Drive = true,
        .Vos = true,
    };
    return &pwr;
}

#ifdef __cplusplus
}
#endif

#endif // per_pwr_h_
