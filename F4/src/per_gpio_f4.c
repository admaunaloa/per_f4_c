/**
 * @file per_gpio_f4.c
 *
 * This file contains the peripheral GPIO
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

#include "per_gpio_f4.h"

/// GPIO register block size
#define PER_GPIO_GPIO_SIZE ((uintptr_t)0x0400)

/// Register address of bit band address
#define PER_GPIO_BIT_BAND_GPIO(REG) ((per_gpio_t*)((uintptr_t)REG & (~((PER_GPIO_GPIO_SIZE << PER_BIT_BB_REG_SHIFT) - 1))))

/// Pin number of bit band address IDR or ODR
#define PER_GPIO_BIT_BAND_PIN(REG) ((per_gpio_pin_e)PER_BIT_SHIFT(REG))

/// GPIO Configure GPIO pin
static bool per_gpio_init(per_gpio_t* gpio,
                          per_gpio_pin_e pin,
                          per_gpio_mode_e mode,
                          per_gpio_otype_e otype,
                          per_gpio_ospeed_e ospeed,
                          per_gpio_pupd_e pupd,
                          per_gpio_af_e af)
{
    per_gpio_set_otype(gpio, pin, otype);
    return per_gpio_set_mode(gpio, pin, mode) &&
           per_gpio_set_ospeed(gpio, pin, ospeed) &&
           per_gpio_set_pupd(gpio, pin, pupd) &&
           per_gpio_set_af(gpio, pin, af);
}

/// GPIO Configure input pin
bool per_gpio_init_in(per_gpio_in_t* in,
                      per_gpio_pupd_e pupd)
{
    per_gpio_t* gpio = PER_GPIO_BIT_BAND_GPIO(in);
    per_gpio_pin_e pin = PER_GPIO_BIT_BAND_PIN(in);

    return per_gpio_init(gpio, pin, PER_GPIO_MODE_INPUT, PER_GPIO_OTYPE_PUSH_PULL, PER_GPIO_OSPEED_LOW, pupd, PER_GPIO_AF_NONE);
}

/// GPIO Configure alternate function input pin
bool per_gpio_init_in_af(per_gpio_in_t* in,
                         per_gpio_pupd_e pupd,
                         per_gpio_af_e af)
{
    per_gpio_t* gpio = PER_GPIO_BIT_BAND_GPIO(in);
    per_gpio_pin_e pin = PER_GPIO_BIT_BAND_PIN(in);

    return per_gpio_init(gpio, pin, PER_GPIO_MODE_ALTERNATE, PER_GPIO_OTYPE_PUSH_PULL, PER_GPIO_OSPEED_LOW, pupd, af);
}

/// GPIO Configure output pin
bool per_gpio_init_out(per_gpio_out_t* out,
                       per_gpio_otype_e otype,
                       per_gpio_ospeed_e ospeed)
{
    per_gpio_t* gpio = PER_GPIO_BIT_BAND_GPIO(out);
    per_gpio_pin_e pin = PER_GPIO_BIT_BAND_PIN(out);

    return per_gpio_init(gpio, pin, PER_GPIO_MODE_OUTPUT, otype, ospeed, PER_GPIO_PUPD_NONE, PER_GPIO_AF_NONE);
}

/// GPIO Configure alternate function output pin
bool per_gpio_init_out_af(per_gpio_out_t* out,
                          per_gpio_otype_e otype,
                          per_gpio_ospeed_e ospeed,
                          per_gpio_af_e af)
{
    per_gpio_t* gpio = PER_GPIO_BIT_BAND_GPIO(out);
    per_gpio_pin_e pin = PER_GPIO_BIT_BAND_PIN(out);

    return per_gpio_init(gpio, pin, PER_GPIO_MODE_ALTERNATE, otype, ospeed, PER_GPIO_PUPD_NONE, af);
}
