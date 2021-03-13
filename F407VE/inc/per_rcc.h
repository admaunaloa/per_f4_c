/**
 * @file per_rcc.h
 *
 * This file contains the peripheral Reset and Clock Control (RCC)
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

#ifndef per_rcc_h_
#define per_rcc_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_rcc_f4.h"

/// RCC base address
#define PER_RCC (PER_ADDR_AHB1 + (uintptr_t)0x3800)

/// [Hz] Clock frequency
#define per_rcc_freq() ((uint32_t)168000000)

/// RCC pointer to rcc
static per_inline const per_rcc_t* const per_rcc(void)
{
    static const per_rcc_t rcc =
    {
        .Per = (per_rcc_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_RCC),
        .Err = PER_LOG_RCC,
        .Adc = PER_RCC_ADC_2,
        .Can = PER_RCC_CAN_2,
        .Cryp = false,
        .Dac = true,
        .Hash = false,
        .Eth = true,
        .I2c = PER_RCC_I2C_3,
        .Gpio = PER_RCC_GPIO_I,
        .Spi = PER_RCC_SPI_3,
        .Tim16 = PER_RCC_TIM16_14,
        .Tim32 = PER_RCC_TIM32_5,
        .Uart = PER_RCC_UART_5,
        .Usart = PER_RCC_USART_6,
    };
    return &rcc;
}

/// APB1 peripheral clock frequency
static per_inline uint_fast32_t per_rcc_apb1_per_freq(void)
{
    return per_rcc_freq() / per_rcc_ppre1(per_rcc());
}

/// APB1 timer clock frequency
static per_inline uint_fast32_t per_rcc_apb1_tim_freq(void)
{
    return per_rcc_apb1_per_freq() * PER_RCC_APB_PER_TO_TIM_MUL;
}

/// APB2 peripheral clock frequency
static per_inline uint_fast32_t per_rcc_apb2_per_freq(void)
{
    return per_rcc_freq() / per_rcc_ppre2(per_rcc());
}

/// APB2 timer clock frequency
static per_inline uint_fast32_t per_rcc_apb2_tim_freq(void)
{
    return per_rcc_apb2_per_freq() * PER_RCC_APB_PER_TO_TIM_MUL;
}

#ifdef __cplusplus
}
#endif

#endif // per_rcc_h_
