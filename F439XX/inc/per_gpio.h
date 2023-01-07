/**
 * @file per_gpio.h
 *
 * This file contains the peripheral GPIO
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

#ifndef per_gpio_h_
#define per_gpio_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_gpio_f4.h"

static per_inline per_gpio_in_t* const per_gpio_a_in(per_gpio_pin_e pin)
{
    return &PER_GPIOA->Id[pin];
}

static per_inline per_gpio_out_t* const per_gpio_a_out(per_gpio_pin_e pin)
{
    return &PER_GPIOA->Od[pin];
}

static per_inline per_gpio_in_t* const per_gpio_b_in(per_gpio_pin_e pin)
{
    return &PER_GPIOB->Id[pin];
}

static per_inline per_gpio_out_t* const per_gpio_b_out(per_gpio_pin_e pin)
{
    return &PER_GPIOB->Od[pin];
}

static per_inline per_gpio_in_t* const per_gpio_c_in(per_gpio_pin_e pin)
{
    return &PER_GPIOC->Id[pin];
}

static per_inline per_gpio_out_t* const per_gpio_c_out(per_gpio_pin_e pin)
{
    return &PER_GPIOC->Od[pin];
}

static per_inline per_gpio_in_t* const per_gpio_d_in(per_gpio_pin_e pin)
{
    return &PER_GPIOD->Id[pin];
}

static per_inline per_gpio_out_t* const per_gpio_d_out(per_gpio_pin_e pin)
{
    return &PER_GPIOD->Od[pin];
}

static per_inline per_gpio_in_t* const per_gpio_e_in(per_gpio_pin_e pin)
{
    return &PER_GPIOE->Id[pin];
}

static per_inline per_gpio_out_t* const per_gpio_e_out(per_gpio_pin_e pin)
{
    return &PER_GPIOE->Od[pin];
}

static per_inline per_gpio_in_t* const per_gpio_f_in(per_gpio_pin_e pin)
{
    return &PER_GPIOF->Id[pin];
}

static per_inline per_gpio_out_t* const per_gpio_f_out(per_gpio_pin_e pin)
{
    return &PER_GPIOF->Od[pin];
}

static per_inline per_gpio_in_t* const per_gpio_g_in(per_gpio_pin_e pin)
{
    return &PER_GPIOG->Id[pin];
}

static per_inline per_gpio_out_t* const per_gpio_g_out(per_gpio_pin_e pin)
{
    return &PER_GPIOG->Od[pin];
}

static per_inline per_gpio_in_t* const per_gpio_h_in(per_gpio_pin_e pin)
{
    return &PER_GPIOH->Id[pin];
}

static per_inline per_gpio_out_t* const per_gpio_h_out(per_gpio_pin_e pin)
{
    return &PER_GPIOH->Od[pin];
}

static per_inline per_gpio_in_t* const per_gpio_i_in(per_gpio_pin_e pin)
{
    return &PER_GPIOI->Id[pin];
}

static per_inline per_gpio_out_t* const per_gpio_i_out(per_gpio_pin_e pin)
{
    return &PER_GPIOI->Od[pin];
}

static per_inline per_gpio_in_t* const per_gpio_j_in(per_gpio_pin_e pin)
{
    return &PER_GPIOJ->Id[pin];
}

static per_inline per_gpio_out_t* const per_gpio_j_out(per_gpio_pin_e pin)
{
    return &PER_GPIOJ->Od[pin];
}

static per_inline per_gpio_in_t* const per_gpio_k_in(per_gpio_pin_e pin)
{
    return &PER_GPIOK->Id[pin];
}

static per_inline per_gpio_out_t* const per_gpio_k_out(per_gpio_pin_e pin)
{
    return &PER_GPIOK->Od[pin];
}

#ifdef __cplusplus
}
#endif

#endif // per_gpio_h_
