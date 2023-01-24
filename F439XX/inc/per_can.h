/**
 * @file per_can.h
 *
 * This file contains the CAN bus (CAN)
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

#ifndef per_can_h_
#define per_can_h_

#ifdef __cplusplus
extern "C"
{
#endif

#include "per_can_f4.h"

/// CAN pointer to can 1
static per_inline const per_can_t* const per_can_1(void)
{
    static const per_can_t can =
    {
        .Per = PER_CAN_1,
        .Err = PER_LOG_CAN_1,
    };
    return &can;
}

/// CAN pointer to can 2
static per_inline const per_can_t* const per_can_2(void)
{
    static const per_can_t can =
    {
        .Per = PER_CAN_2,
        .Err = PER_LOG_CAN_2,
    };
    return &can;
}

/// CAN pointer to can 3
static per_inline const per_can_t* const per_can_3(void)
{
    static const per_can_t can =
    {
        .Per = PER_CAN_3,
        .Err = PER_LOG_CAN_3,
    };
    return &can;
}

#ifdef __cplusplus
}
#endif

#endif // per_can_h_
