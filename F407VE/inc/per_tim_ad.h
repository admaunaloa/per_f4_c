/**
 * @file per_tim_ad.h
 *
 * This file contains the peripheral timer advanced (TIM_AD)
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

#ifndef per_tim_ad_h_
#define per_tim_ad_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_tim_ad_f4.h"
#include "per_rcc.h"

/// TIM_AD pointer to tim_ad 1
static per_inline const per_tim_ad_t* const per_tim_ad_1(void)
{
    static const per_tim_ad_t tim =
    {
        .Per = PER_TIM_1,
        .Err = PER_LOG_TIM_1,
        .Freq = &per_rcc_apb2_tim_freq,
    };
    return &tim;
}

/// TIM_AD pointer to tim_ad 8
static per_inline const per_tim_ad_t* const per_tim_ad_8(void)
{
    static const per_tim_ad_t tim =
    {
        .Per = PER_TIM_8,
        .Err = PER_LOG_TIM_8,
        .Freq = &per_rcc_apb2_tim_freq,
    };
    return &tim;
}

#ifdef __cplusplus
}
#endif

#endif // per_tim_ad_h_
