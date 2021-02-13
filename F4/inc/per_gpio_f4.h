/**
 * @file per_gpio_f4.h
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
 *
 * For each GPIO peripheral bit the possible get and set functions are provided.
 * per_gpio_xxx()           Get
 * per_gpio_set_xxx()       Set
 *
 * First define the GPIO
 * static per_inline const per_gpio_out_t* const bsp_gpio_led_green(void)
 * {
 *    static const per_gpio_out_t gpio =
 *    {
 *        .Per = PER_GPIOB,
 *        .Pin = PER_GPIO_PIN_0,
 *    };
 *    return &gpio;
 * }
 *
 * Initialize it as output
 * per_gpio_init_out(bsp_gpio_led_green(), PER_GPIO_OTYPE_PUSH_PULL, PER_GPIO_OSPEED_LOW);
 *
 * Set it to a value
 * bool value = true;
 * per_gpio_set_out(bsp_gpio_led_green(), value);
 *
 * This example results in a minimal number of instructions because
 * all functions are inlined and bitband is used. These functions also make it
 * type-safe.
 *
 */

#ifndef per_gpio_f4_h_
#define per_gpio_f4_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_bit_f4.h"

/// Number of GPIO per register
#define PER_GPIO_MAX (16)

/// GPIO pin enumeration
typedef enum
{
    PER_GPIO_PIN_0  = 0,
    PER_GPIO_PIN_1  = 1,
    PER_GPIO_PIN_2  = 2,
    PER_GPIO_PIN_3  = 3,
    PER_GPIO_PIN_4  = 4,
    PER_GPIO_PIN_5  = 5,
    PER_GPIO_PIN_6  = 6,
    PER_GPIO_PIN_7  = 7,
    PER_GPIO_PIN_8  = 8,
    PER_GPIO_PIN_9  = 9,
    PER_GPIO_PIN_10 = 10,
    PER_GPIO_PIN_11 = 11,
    PER_GPIO_PIN_12 = 12,
    PER_GPIO_PIN_13 = 13,
    PER_GPIO_PIN_14 = 14,
    PER_GPIO_PIN_15 = 15,
} per_gpio_pin_e;

/// GPIO mode enumeration
typedef enum
{
    PER_GPIO_MODE_INPUT     = 0b00, ///< Input (reset state)
    PER_GPIO_MODE_OUTPUT    = 0b01, ///< General purpose output mode
    PER_GPIO_MODE_ALTERNATE = 0b10, ///< Alternate function mode
    PER_GPIO_MODE_ANALOG    = 0b11, ///< Analog mode
} per_gpio_mode_e;

/// GPIO output type enumeration
typedef enum
{
    PER_GPIO_OTYPE_PUSH_PULL  = 0, ///< Output push-pull (reset state)
    PER_GPIO_OTYPE_OPEN_DRAIN = 1, ///< Output open-drain
} per_gpio_otype_e;

/// GPIO output speed enumeration
typedef enum
{
    PER_GPIO_OSPEED_LOW    = 0b00, ///< Low speed
    PER_GPIO_OSPEED_MEDIUM = 0b01, ///< Medium speed
    PER_GPIO_OSPEED_FAST   = 0b10, ///< Fast speed
    PER_GPIO_OSPEED_HIGH   = 0b11, ///< High speed
} per_gpio_ospeed_e; // The values depend on VDD range and external load

/// GPIO pull up/down enumeration
typedef enum
{
    PER_GPIO_PUPD_NONE      = 0b00, ///< No pull-up, pull-down
    PER_GPIO_PUPD_PULL_UP   = 0b01, ///< Pull-up
    PER_GPIO_PUPD_PULL_DOWN = 0b10, ///< Pull-down
} per_gpio_pupd_e;

/// GPIO alternating function enumeration
typedef enum
{
    PER_GPIO_AF_NONE     = 0, ///< AF0
    PER_GPIO_AF_RTC_50Hz = 0, ///< AF0
    PER_GPIO_AF_MCO      = 0, ///< AF0
    PER_GPIO_AF_TAMPER   = 0, ///< AF0
    PER_GPIO_AF_SWJ      = 0, ///< AF0
    PER_GPIO_AF_TRACE    = 0, ///< AF0
    PER_GPIO_AF_TIM1     = 1, ///< AF1
    PER_GPIO_AF_TIM2     = 1, ///< AF1
    PER_GPIO_AF_TIM3     = 2, ///< AF2
    PER_GPIO_AF_TIM4     = 2, ///< AF2
    PER_GPIO_AF_TIM5     = 2, ///< AF2
    PER_GPIO_AF_TIM8     = 3, ///< AF3
    PER_GPIO_AF_TIM9     = 3, ///< AF3
    PER_GPIO_AF_TIM10    = 3, ///< AF3
    PER_GPIO_AF_TIM11    = 3, ///< AF3
    PER_GPIO_AF_I2C1     = 4, ///< AF4
    PER_GPIO_AF_I2C2     = 4, ///< AF4
    PER_GPIO_AF_I2C3     = 4, ///< AF4
    PER_GPIO_AF_SPI1     = 5, ///< AF5
    PER_GPIO_AF_SPI2     = 5, ///< AF5
    PER_GPIO_AF_I2S3EXT5 = 5, ///< AF5
    PER_GPIO_AF_SPI3     = 6, ///< AF6
    PER_GPIO_AF_6I2S2EXT = 6, ///< AF6
    PER_GPIO_AF_USART1   = 7, ///< AF7
    PER_GPIO_AF_USART2   = 7, ///< AF7
    PER_GPIO_AF_USART3   = 7, ///< AF7
    PER_GPIO_AF_I2S3EXT7 = 7, ///< AF7
    PER_GPIO_AF_UART4    = 8, ///< AF8
    PER_GPIO_AF_UART5    = 8, ///< AF8
    PER_GPIO_AF_USART6   = 8, ///< AF8
    PER_GPIO_AF_CAN1     = 9, ///< AF9
    PER_GPIO_AF_CAN2     = 9, ///< AF9
    PER_GPIO_AF_TIM12    = 9, ///< AF9
    PER_GPIO_AF_TIM13    = 9, ///< AF9
    PER_GPIO_AF_TIM14    = 9, ///< AF9
    PER_GPIO_AF_OTGFS    = 10, ///< AF10
    PER_GPIO_AF_OTGHS    = 10, ///< AF10
    PER_GPIO_AF_ETH      = 11, ///< AF11
    PER_GPIO_AF_FSMC     = 12, ///< AF12
    PER_GPIO_AF_OTGHSFS  = 12, ///< AF12
    PER_GPIO_AF_SDIO     = 12, ///< AF12
    PER_GPIO_AF_DCMI     = 13, ///< AF13
    PER_GPIO_AF_14       = 14, ///< AF14
    PER_GPIO_AF_EVENTOUT = 15, ///< AF15
} per_gpio_af_e;

typedef struct
{
    // MODER port mode register
    per_bit_rw2_t Moder[PER_GPIO_MAX]; ///< Configure the I/O direction mode

    // OTYPER port output type register
    per_bit_rw1_t Otyper[PER_GPIO_MAX]; ///< configure the output type of the I/O port
    per_bit_n16_t OtyperBit16;          ///< Reserved

    // OSPEEDR port output speed register
    per_bit_rw2_t Ospeedr[PER_GPIO_MAX]; ///< Configure the I/O output speed

    // PUPDR port pull-up/pull-down register
    per_bit_rw2_t Pupdr[PER_GPIO_MAX]; ///< Configure the I/O pull-up or pull-down

    // IDR port input data register
    per_bit_r1_t Idr[PER_GPIO_MAX]; ///< The input value of the corresponding I/O port.
    per_bit_n16_t IdrBit16;         ///< Reserved

    // ODR port output data register
    per_bit_rw1_t Odr[PER_GPIO_MAX]; ///< Port output data
    per_bit_n16_t OdrBit16;          ///< Reserved

    // BSRR port bit set/reset register
    per_bit_w1_t Bs[PER_GPIO_MAX]; ///< Port set bit
    per_bit_w1_t Br[PER_GPIO_MAX]; ///< Port reset bit

    // LCK port configuration lock register
    per_bit_rw1_t Lck[PER_GPIO_MAX]; ///< Lock bit
    per_bit_rw1_t Lckk;              ///< Lock key
    per_bit_n15_t LckBit17;          ///< Reserved

    // AFRL AFRH alternate function low/high register
    per_bit_rw4_t Afr[PER_GPIO_MAX]; ///< Alternate function selection
} __attribute__((packed)) per_gpio_t;

/// GPIO Input type
typedef struct
{
    per_gpio_t* const Per;    ///< Peripheral
    const per_gpio_pin_e Pin; ///< Pin number
} per_gpio_in_t;

/// GPIO Output type
typedef struct
{
    per_gpio_t* const Per;    ///< Peripheral
    const per_gpio_pin_e Pin; ///< Pin number
} per_gpio_out_t;

/// GPIO Input alternate function type
typedef struct
{
    per_gpio_t* const Per;    ///< Peripheral
    const per_gpio_pin_e Pin; ///< Pin number
} per_gpio_in_af_t;

/// GPIO Output alternate function type
typedef struct
{
    per_gpio_t* const Per;    ///< Peripheral
    const per_gpio_pin_e Pin; ///< Pin number
} per_gpio_out_af_t;

/// GPIO set mode input, output or alternate
static per_inline bool per_gpio_set_mode(per_gpio_t* gpio, per_gpio_pin_e pin, per_gpio_mode_e mode)
{
    return per_bit_rw2_set(&gpio->Moder[pin], (uint_fast16_t)mode);
}

/// GPIO set output type
static per_inline void per_gpio_set_otype(per_gpio_t* gpio, per_gpio_pin_e pin, per_gpio_otype_e otype)
{
    per_bit_rw1_set(&gpio->Otyper[pin], (bool)otype);
}

/// GPIO set output speed
static per_inline bool per_gpio_set_ospeed(per_gpio_t* gpio, per_gpio_pin_e pin, per_gpio_ospeed_e ospeed)
{
    return per_bit_rw2_set(&gpio->Ospeedr[pin], (uint_fast16_t)ospeed);
}

/// GPIO set pull-up pull-down
static per_inline bool per_gpio_set_pupd(per_gpio_t* gpio, per_gpio_pin_e pin, per_gpio_pupd_e pupd)
{
    return per_bit_rw2_set(&gpio->Pupdr[pin], (uint_fast16_t)pupd);
}

/// GPIO get input data register
static per_inline bool per_gpio_idr(const per_gpio_t* const gpio, per_gpio_pin_e pin)
{
    return per_bit_r1(&gpio->Idr[pin]);
}

/// GPIO get output data register
static per_inline bool per_gpio_odr(const per_gpio_t* const gpio, per_gpio_pin_e pin)
{
    return per_bit_rw1(&gpio->Odr[pin]);
}

/// GPIO set output data register
static per_inline void per_gpio_set_odr(per_gpio_t* gpio, per_gpio_pin_e pin, bool val)
{
    per_bit_rw1_set(&gpio->Odr[pin], val);
}

/// GPIO set output set/reset data register
static per_inline void per_gpio_set_bsrr(const per_gpio_t* const gpio, per_gpio_pin_e pin, bool val)
{
    uint32_t mask;

    if (!val)
    {
        mask = (uint32_t)1 << (pin + PER_GPIO_MAX);
    }
    else
    {
        mask =  (uint32_t)1 << pin;
    }

    PER_BIT_BIT_BAND_TO_REG(&gpio->Bs[0])->Reg32 = mask;
}

/// GPIO set alternate function
static per_inline bool per_gpio_set_af(per_gpio_t* gpio, per_gpio_pin_e pin, per_gpio_af_e af)
{
    return per_bit_rw4_set(&gpio->Afr[pin], (uint_fast16_t)af);
}

/// GPIO get alternate function
static per_inline per_gpio_af_e per_gpio_af(per_gpio_t* gpio, per_gpio_pin_e pin)
{
    return (per_gpio_af_e)per_bit_rw4(&gpio->Afr[pin]);
}

/// GPIO get input
static per_inline bool per_gpio_in(const per_gpio_in_t* const in)
{
    return per_bit_r1(&in->Per->Idr[in->Pin]);
}

/// GPIO get output
static per_inline bool per_gpio_out(const per_gpio_out_t* const out)
{
    return per_bit_rw1(&out->Per->Odr[out->Pin]);
}

/// GPIO set output
static per_inline void per_gpio_set_out(const per_gpio_out_t* const out, bool val)
{
    per_bit_rw1_set(&out->Per->Odr[out->Pin], val); // one cycle faster compared to per_gpio_set_bsrr()
}

bool per_gpio_init_in(const per_gpio_in_t* const in, per_gpio_pupd_e pupd);

bool per_gpio_init_in_af(const per_gpio_in_af_t* const in, per_gpio_pupd_e pupd, per_gpio_af_e af);

bool per_gpio_init_out(const per_gpio_out_t* const, per_gpio_otype_e otype, per_gpio_ospeed_e ospeed);

bool per_gpio_init_out_af(const per_gpio_out_af_t* const out, per_gpio_otype_e otype, per_gpio_ospeed_e ospeed, per_gpio_af_e af);

#ifdef __cplusplus
}
#endif

#endif // per_gpio_f4_h_
