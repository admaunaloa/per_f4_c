/**
 * @file per_adc.h
 *
 * This file contains the analog digital converter (ADC)
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

#ifndef per_adc_h_
#define per_adc_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_adc_f4.h"

/// ADC pointer to adc 1
static per_inline const per_adc_t* const per_adc_1(void)
{
    static const per_adc_t adc =
    {
        .Per = PER_ADC_1,
        .Err = PER_LOG_ADC_1
    };
    return &adc;
}

/// ADC pointer to adc 2
static per_inline const per_adc_t* const per_adc_2(void)
{
    static const per_adc_t adc =
    {
        .Per = PER_ADC_2,
        .Err = PER_LOG_ADC_2
    };
    return &adc;
}

/// ADC pointer to adc 3
static per_inline const per_adc_t* const per_adc_3(void)
{
    static const per_adc_t adc =
    {
        .Per = PER_ADC_3,
        .Err = PER_LOG_ADC_3
    };
    return &adc;
}

/// ADC pointer to adc com
static per_inline const per_adc_com_t* const per_adc_com(void)
{
    static const per_adc_com_t adc =
    {
        .Per = PER_ADC_COM,
        .Err = PER_LOG_ADC_COM
    };
    return &adc;
}

#ifdef __cplusplus
}
#endif

#endif // per_adc_h_
