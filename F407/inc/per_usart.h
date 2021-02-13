/**
 * @file per_usart.h
 *
 * This file contains the peripheral Universal Synchronous Asynchronous Receiver Transmitter (USART)
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

#ifndef per_usart_h_
#define per_usart_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_usart_f4.h"
#include "per_rcc.h"

/// USART1 base address
#define PER_USART_1 (PER_ADDR_APB2 + (uintptr_t)0x1000)

/// USART2 base address
#define PER_USART_2 (PER_ADDR_APB1 + (uintptr_t)0x4400)

/// USART3 base address
#define PER_USART_3 (PER_ADDR_APB1 + (uintptr_t)0x4800)

/// UART4 base address
#define PER_UART_4  (PER_ADDR_APB1 + (uintptr_t)0x4C00)

/// UART5 base address
#define PER_UART_5  (PER_ADDR_APB1 + (uintptr_t)0x5000)

/// USART6 base address
#define PER_USART_6 (PER_ADDR_APB2 + (uintptr_t)0x1400)

/// USART get pointer to usart 1
static per_inline const per_usart_t* const per_usart_1(void)
{
    static const per_usart_t usart =
    {
        .Per = (per_usart_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_USART_1),
        .Err = PER_LOG_USART_1,
        .Freq = &per_rcc_apb2_per_freq,
        .Uart = false,
    };
    return &usart;
}

/// USART get pointer to usart 2
static per_inline const per_usart_t* const per_usart_2(void)
{
    static const per_usart_t usart =
    {
        .Per = (per_usart_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_USART_2),
        .Err = PER_LOG_USART_2,
        .Freq = &per_rcc_apb1_per_freq,
        .Uart = false,
    };
    return &usart;
}

/// USART get pointer to usart 3
static per_inline const per_usart_t* const per_usart_3(void)
{
    static const per_usart_t usart =
    {
        .Per = (per_usart_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_USART_3),
        .Err = PER_LOG_USART_3,
        .Freq = &per_rcc_apb1_per_freq,
        .Uart = false,
    };
    return &usart;
}

/// UART get pointer to uart 4
static per_inline const per_usart_t* const per_uart_4(void)
{
    static const per_usart_t usart =
    {
        .Per = (per_usart_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_UART_4),
        .Err = PER_LOG_UART_4,
        .Freq = &per_rcc_apb1_per_freq,
        .Uart = true,
    };
    return &usart;
}

/// UART get pointer to uart 5
static per_inline const per_usart_t* const per_uart_5(void)
{
    static const per_usart_t usart =
    {
        .Per = (per_usart_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_UART_5),
        .Err = PER_LOG_UART_5,
        .Freq = &per_rcc_apb1_per_freq,
        .Uart = true,
    };
    return &usart;
}

/// USART get pointer to usart 6
static per_inline const per_usart_t* const per_usart_6(void)
{
    static const per_usart_t usart =
    {
        .Per = (per_usart_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_USART_6),
        .Err = PER_LOG_USART_6,
        .Freq = &per_rcc_apb2_per_freq,
        .Uart = false,
    };
    return &usart;
}

#ifdef __cplusplus
}
#endif

#endif // per_usart_h_
