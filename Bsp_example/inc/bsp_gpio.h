/**
 * @file bsp_gpio.h
 *
 * This file contains the Board Support Package (BSP) General Purpose Input Output (GPIO)
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

#ifndef bsp_gpio_h_
#define bsp_gpio_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_gpio.h"

/// GPIOB
#define bsp_gpio_led_green()        (&PER_GPIOB->Od[PER_GPIO_PIN_0])
#define bsp_gpio_led_blue()         (&PER_GPIOB->Od[PER_GPIO_PIN_7])
#define bsp_gpio_led_red()          (&PER_GPIOB->Od[PER_GPIO_PIN_14])

/// GPIOC
#define bsp_user_button_1()         (&PER_GPIOC->Id[PER_GPIO_PIN_13])

/// GPIOD
#define bsp_gpio_usart3_tx()        (&PER_GPIOD->Od[PER_GPIO_PIN_8])
#define bsp_gpio_usart3_rx()        (&PER_GPIOD->Id[PER_GPIO_PIN_9])

void bsp_gpio_init(void);

#ifdef __cplusplus
}
#endif

#endif // bsp_gpio_h_
