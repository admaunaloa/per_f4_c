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

/// Ordered GPIO definitions GPIOA...GPIOK and 0...15
/////////////////////////////////////////////////////

static per_inline const per_gpio_out_t* const bsp_gpio_led_green(void)
{
    static const per_gpio_out_t gpio =
    {
        .Per = PER_GPIOB,
        .Pin = PER_GPIO_PIN_0,
    };
    return &gpio;
}

static per_inline const per_gpio_out_t* const bsp_gpio_led_blue(void)
{
    static const per_gpio_out_t gpio =
    {
        .Per = PER_GPIOB,
        .Pin = PER_GPIO_PIN_7,
    };
    return &gpio;
}

static per_inline const per_gpio_out_t* const bsp_gpio_led_red(void)
{
    static const per_gpio_out_t gpio =
    {
        .Per = PER_GPIOB,
        .Pin = PER_GPIO_PIN_14,
    };
    return &gpio;
}

static per_inline const per_gpio_in_t* const bsp_gpio_button_1(void)
{
    static const per_gpio_in_t gpio =
    {
        .Per = PER_GPIOC,
        .Pin = PER_GPIO_PIN_13,
    };
    return &gpio;
}

static per_inline const per_gpio_out_af_t* const bsp_gpio_usart3_tx(void)
{
    static const per_gpio_out_af_t gpio =
    {
        .Per = PER_GPIOD,
        .Pin = PER_GPIO_PIN_8,
    };
    return &gpio;
}

static per_inline const per_gpio_in_af_t* const bsp_gpio_usart3_rx(void)
{
    static const per_gpio_in_af_t gpio =
    {
        .Per = PER_GPIOD,
        .Pin = PER_GPIO_PIN_9,
    };
    return &gpio;
}

/// Descriptors
/////////////////////////////////////////////////////////////////////////

/// Descriptor alternate function
typedef struct
{
    bool (*Init)(void); //!< Initialize hardware
} bsp_gpio_af_t;

/// Descriptor input
typedef struct
{
    bool (*Init)(void); //!< Initialize hardware
    bool (*Get)(void); //!< Read current value
} bsp_gpio_in_t;

/// Descriptor output
typedef struct
{
    bool (*Init)(void); //!< Initialize hardware
    bool (*Get)(void); //!< Read current value
    void (*Set)(bool); //!< Write new value
} bsp_gpio_out_t;

/// Initialize user button
static per_inline bool bsp_user_button_1_init(void)
{
    return per_gpio_init_in(bsp_gpio_button_1(), PER_GPIO_PUPD_PULL_DOWN);
}

/// Get user button status
static per_inline bool bsp_user_button_1_get(void)
{
    return per_gpio_in(bsp_gpio_button_1());
}

static per_inline const bsp_gpio_in_t* bsp_user_button_1(void)
{
    static const bsp_gpio_in_t in =
    {
        .Init = bsp_user_button_1_init,
        .Get = bsp_user_button_1_get
    };
    return &in;
}

/// Initialize LED green
static per_inline bool bsp_led_green_init(void)
{
    return per_gpio_init_out(bsp_gpio_led_green(), PER_GPIO_OTYPE_PUSH_PULL, PER_GPIO_OSPEED_LOW);
}

/// Get LED green state
static per_inline bool bsp_led_green_get(void)
{
    return per_gpio_out(bsp_gpio_led_green());
}

/// Set LED green state
static per_inline void bsp_led_green_set(bool val)
{
    per_gpio_set_out(bsp_gpio_led_green(), val);
}

/// Descriptor LED green
static per_inline const bsp_gpio_out_t* bsp_led_green(void)
{
    static const bsp_gpio_out_t out =
    {
        .Init = bsp_led_green_init,
        .Get = bsp_led_green_get,
        .Set = bsp_led_green_set,
    };
    return &out;
}

/// Initialize LED blue
static per_inline bool bsp_led_blue_init(void)
{
    return per_gpio_init_out(bsp_gpio_led_blue(), PER_GPIO_OTYPE_PUSH_PULL, PER_GPIO_OSPEED_LOW);
}

/// Get LED blue state
static per_inline bool bsp_led_blue_get(void)
{
    return per_gpio_out(bsp_gpio_led_blue());
}

/// Set LED blue state
static per_inline void bsp_led_blue_set(bool val)
{
    per_gpio_set_out(bsp_gpio_led_blue(), val);
}

/// Descriptor LED blue
static per_inline const bsp_gpio_out_t* bsp_led_blue(void)
{
    static const bsp_gpio_out_t out =
    {
        .Init = bsp_led_blue_init,
        .Get = bsp_led_blue_get,
        .Set = bsp_led_blue_set,
    };
    return &out;
}

/// Initialize LED red
static per_inline bool bsp_led_red_init(void)
{
    return per_gpio_init_out(bsp_gpio_led_red(), PER_GPIO_OTYPE_PUSH_PULL, PER_GPIO_OSPEED_LOW);
}

/// Get LED red state
static per_inline bool bsp_led_red_get(void)
{
    return per_gpio_out(bsp_gpio_led_red());
}

// Set LED red state
static per_inline void bsp_led_red_set(bool value)
{
    per_gpio_set_out(bsp_gpio_led_red(), value);
}

/// Descriptor LED red
static per_inline const bsp_gpio_out_t* bsp_led_red(void)
{
    static const bsp_gpio_out_t out =
    {
        .Init = bsp_led_red_init,
        .Get = bsp_led_red_get,
        .Set = bsp_led_red_set,
    };
    return &out;
}

/// Initialize USART3_tx
static per_inline bool bsp_gpio_usart_3_tx_init(void)
{
    return per_gpio_init_out_af(bsp_gpio_usart3_tx(), PER_GPIO_OTYPE_PUSH_PULL, PER_GPIO_OSPEED_MEDIUM, PER_GPIO_AF_USART3);
}

static per_inline const bsp_gpio_af_t* bsp_gpio_usart_3_tx(void)
{
    static const bsp_gpio_af_t tx =
    {
        .Init = bsp_gpio_usart_3_tx_init,
    };
    return &tx;
}

/// Initialize USART3_rx
static per_inline bool bsp_gpio_usart_3_rx_init(void)
{
    return per_gpio_init_in_af(bsp_gpio_usart3_rx(), PER_GPIO_PUPD_PULL_UP, PER_GPIO_AF_USART3);
}

static per_inline const bsp_gpio_af_t* bsp_gpio_usart_3_rx(void)
{
    static const bsp_gpio_af_t rx =
    {
        .Init = bsp_gpio_usart_3_rx_init,
    };
    return &rx;
}

#ifdef __cplusplus
}
#endif

#endif // bsp_gpio_h_
