/**
 * @file per_tim_gp.h
 *
 * This file contains the peripheral timer general purpose 4 channel (TIM_GP)
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

#ifndef per_tim_gp_h_
#define per_tim_gp_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_tim_gp_f4.h"
#include "per_rcc.h"

/// TIM_AD pointer to tim_gp 2
static per_inline const per_tim_gp_t* const per_tim_gp_2(void)
{
    static const per_tim_gp_t tim =
    {
        .Per = PER_TIM_2,
        .Err = PER_LOG_TIM_2,
        .Chan = PER_TIM_GP_CHAN_4,
        .Size = PER_TIM_GP_SIZE_32,
        .Freq = &per_rcc_apb1_tim_freq,
        .Opt = PER_TIM_GP_OR_TIM2,
    };
    return &tim;
}

/// TIM_AD pointer to tim_gp 3
static per_inline const per_tim_gp_t* const per_tim_gp_3(void)
{
    static const per_tim_gp_t tim =
    {
        .Per = PER_TIM_3,
        .Err = PER_LOG_TIM_3,
        .Chan = PER_TIM_GP_CHAN_4,
        .Size = PER_TIM_GP_SIZE_16,
        .Freq = &per_rcc_apb1_tim_freq,
        .Opt = 0,
    };
    return &tim;
}

/// TIM_AD pointer to tim_gp 4
static per_inline const per_tim_gp_t* const per_tim_gp_4(void)
{
    static const per_tim_gp_t tim =
    {
        .Per = PER_TIM_4,
        .Err = PER_LOG_TIM_4,
        .Chan = PER_TIM_GP_CHAN_4,
        .Size = PER_TIM_GP_SIZE_16,
        .Freq = &per_rcc_apb1_tim_freq,
        .Opt = 0,
    };
    return &tim;
}

/// TIM_AD pointer to tim_gp 5
static per_inline const per_tim_gp_t* const per_tim_gp_5(void)
{
    static const per_tim_gp_t tim =
    {
        .Per = PER_TIM_5,
        .Err = PER_LOG_TIM_5,
        .Chan = PER_TIM_GP_CHAN_4,
        .Size = PER_TIM_GP_SIZE_32,
        .Freq = &per_rcc_apb1_tim_freq,
        .Opt = PER_TIM_GP_OR_TIM5,
    };
    return &tim;
}

/// TIM_AD pointer to tim_gp 9
static per_inline const per_tim_gp_t* const per_tim_gp_9(void)
{
    static const per_tim_gp_t tim =
    {
        .Per = PER_TIM_9,
        .Err = PER_LOG_TIM_9,
        .Chan = PER_TIM_GP_CHAN_2,
        .Size = PER_TIM_GP_SIZE_16,
        .Freq = &per_rcc_apb2_tim_freq,
        .Opt = 0,
    };
    return &tim;
}

/// TIM_AD pointer to tim_gp 10
static per_inline const per_tim_gp_t* const per_tim_gp_10(void)
{
    static const per_tim_gp_t tim =
    {
        .Per = PER_TIM_10,
        .Err = PER_LOG_TIM_10,
        .Chan = PER_TIM_GP_CHAN_1,
        .Size = PER_TIM_GP_SIZE_16,
        .Freq = &per_rcc_apb2_tim_freq,
        .Opt = 0,
    };
    return &tim;
}

/// TIM_AD pointer to tim_gp 11
static per_inline const per_tim_gp_t* const per_tim_gp_11(void)
{
    static const per_tim_gp_t tim =
    {
        .Per = PER_TIM_11,
        .Err = PER_LOG_TIM_11,
        .Chan = PER_TIM_GP_CHAN_1,
        .Size = PER_TIM_GP_SIZE_16,
        .Freq = &per_rcc_apb2_tim_freq,
    };
    return &tim;
}

/// TIM_AD pointer to tim_gp 12
static per_inline const per_tim_gp_t* const per_tim_gp_12(void)
{
    static const per_tim_gp_t tim =
    {
        .Per = PER_TIM_12,
        .Err = PER_LOG_TIM_12,
        .Chan = PER_TIM_GP_CHAN_2,
        .Size = PER_TIM_GP_SIZE_16,
        .Freq = &per_rcc_apb1_tim_freq,
        .Opt = 0,
    };
    return &tim;
}

/// TIM_AD pointer to tim_gp 13
static per_inline const per_tim_gp_t* const per_tim_gp_13(void)
{
    static const per_tim_gp_t tim =
    {
        .Per = PER_TIM_13,
        .Err = PER_LOG_TIM_13,
        .Chan = PER_TIM_GP_CHAN_1,
        .Size = PER_TIM_GP_SIZE_16,
        .Freq = &per_rcc_apb1_tim_freq,
        .Opt = 0,
    };
    return &tim;
}

/// TIM_AD pointer to tim_gp 14
static per_inline const per_tim_gp_t* const per_tim_gp_14(void)
{
    static const per_tim_gp_t tim =
    {
        .Per = PER_TIM_14,
        .Err = PER_LOG_TIM_14,
        .Chan = PER_TIM_GP_CHAN_1,
        .Size = PER_TIM_GP_SIZE_16,
        .Freq = &per_rcc_apb1_tim_freq,
        .Opt = 0,
    };
    return &tim;
}

#ifdef __cplusplus
}
#endif

#endif // per_tim_gp_h_
