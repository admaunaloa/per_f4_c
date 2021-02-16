/**
 * @file per_dma.h
 *
 * This file contains the peripheral Direct Memory Access (DMA)
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

#ifndef per_dma_h_
#define per_dma_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_dma_f4.h"

/// DMA1 base address
#define PER_DMA_1 (PER_ADDR_AHB1 + (uintptr_t)0x6000)

/// DMA1 bit band base address
#define PER_DMA_1_BB ((per_dma_t*)PER_BIT_REG_TO_BIT_BAND(PER_DMA_1))

/// DMA2 base address
#define PER_DMA_2 (PER_ADDR_AHB1 + (uintptr_t)0x6400)

/// DMA2 bit band base address
#define PER_DMA_2_BB ((per_dma_t*)PER_BIT_REG_TO_BIT_BAND(PER_DMA_2))

static const per_dma_selection_t PER_DMA_1_STREAM_0_SPI3_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_0],
    .Chan = PER_DMA_CHANNEL_0,
};

static const per_dma_selection_t PER_DMA_1_STREAM_0_I2C1_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_0],
    .Chan = PER_DMA_CHANNEL_1,
};

static const per_dma_selection_t PER_DMA_1_STREAM_0_TIM4_CH1 =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_0],
    .Chan = PER_DMA_CHANNEL_2,
};

static const per_dma_selection_t PER_DMA_1_STREAM_0_I2S3_EXT_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_0],
    .Chan = PER_DMA_CHANNEL_3,
};

static const per_dma_selection_t PER_DMA_1_STREAM_0_UART5_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_0],
    .Chan = PER_DMA_CHANNEL_4,
};

static const per_dma_selection_t PER_DMA_1_STREAM_0_TIM5_CH3_UP =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_0],
    .Chan = PER_DMA_CHANNEL_6,
};

static const per_dma_selection_t PER_DMA_1_STREAM_1_TIM2_UP_CH3 =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_1],
    .Chan = PER_DMA_CHANNEL_3
};

static const per_dma_selection_t PER_DMA_1_STREAM_1_USART3_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_1],
    .Chan = PER_DMA_CHANNEL_4
};

static const per_dma_selection_t PER_DMA_1_STREAM_1_TIM5_CH4_TRIG =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_1],
    .Chan = PER_DMA_CHANNEL_6
};

static const per_dma_selection_t PER_DMA_1_STREAM_1_TIM6_UP =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_1],
    .Chan = PER_DMA_CHANNEL_7
};

static const per_dma_selection_t PER_DMA_1_STREAM_2_SPI3_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_0
};

static const per_dma_selection_t PER_DMA_1_STREAM_2_TIM7_UP =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_1
};

static const per_dma_selection_t PER_DMA_1_STREAM_2_I2S3_EXT_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_2
};

static const per_dma_selection_t PER_DMA_1_STREAM_2_I2C3_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_3
};

static const per_dma_selection_t PER_DMA_1_STREAM_2_UART4_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_4
};

static const per_dma_selection_t PER_DMA_1_STREAM_2_TIM3_CH4_UP =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_5
};

static const per_dma_selection_t PER_DMA_1_STREAM_2_TIM5_CH1 =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_6
};

static const per_dma_selection_t PER_DMA_1_STREAM_2_I2C2_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_7
};

static const per_dma_selection_t PER_DMA_1_STREAM_3_SPI2_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_3],
    .Chan = PER_DMA_CHANNEL_0
};

static const per_dma_selection_t PER_DMA_1_STREAM_3_TIM4_CH2 =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_3],
    .Chan = PER_DMA_CHANNEL_2
};

static const per_dma_selection_t PER_DMA_1_STREAM_3_I2S2_EXT_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_3],
    .Chan = PER_DMA_CHANNEL_3
};

static const per_dma_selection_t PER_DMA_1_STREAM_3_USART3_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_3],
    .Chan = PER_DMA_CHANNEL_4
};

static const per_dma_selection_t PER_DMA_1_STREAM_3_TIM5_CH4_TRIG =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_3],
    .Chan = PER_DMA_CHANNEL_6
};

static const per_dma_selection_t PER_DMA_1_STREAM_3_I2C2_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_3],
    .Chan = PER_DMA_CHANNEL_7
};

static const per_dma_selection_t PER_DMA_1_STREAM_4_SPI2_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_4],
    .Chan = PER_DMA_CHANNEL_0
};

static const per_dma_selection_t PER_DMA_1_STREAM_4_TIM7_UP =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_4],
    .Chan = PER_DMA_CHANNEL_1
};

static const per_dma_selection_t PER_DMA_1_STREAM_4_I2S2_EXT_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_4],
    .Chan = PER_DMA_CHANNEL_2
};

static const per_dma_selection_t PER_DMA_1_STREAM_4_I2C3_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_4],
    .Chan = PER_DMA_CHANNEL_3
};

static const per_dma_selection_t PER_DMA_1_STREAM_4_UART4_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_4],
    .Chan = PER_DMA_CHANNEL_4
};

static const per_dma_selection_t PER_DMA_1_STREAM_4_TIM3_CH1_TRIG =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_4],
    .Chan = PER_DMA_CHANNEL_5
};

static const per_dma_selection_t PER_DMA_1_STREAM_4_TIM5_CH2 =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_4],
    .Chan = PER_DMA_CHANNEL_6
};

static const per_dma_selection_t PER_DMA_1_STREAM_4_USART3_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_4],
    .Chan = PER_DMA_CHANNEL_7
};

static const per_dma_selection_t PER_DMA_1_STREAM_5_SPI3_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_5],
    .Chan = PER_DMA_CHANNEL_0
};

static const per_dma_selection_t PER_DMA_1_STREAM_5_I2C1_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_5],
    .Chan = PER_DMA_CHANNEL_1
};

static const per_dma_selection_t PER_DMA_1_STREAM_5_I2S3_EXT_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_5],
    .Chan = PER_DMA_CHANNEL_2
};

static const per_dma_selection_t PER_DMA_1_STREAM_5_TIM2_CH1 =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_5],
    .Chan = PER_DMA_CHANNEL_3
};

static const per_dma_selection_t PER_DMA_1_STREAM_5_USART2_RX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_5],
    .Chan = PER_DMA_CHANNEL_4
};

static const per_dma_selection_t PER_DMA_1_STREAM_5_TIM3_CH2 =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_5],
    .Chan = PER_DMA_CHANNEL_5
};

static const per_dma_selection_t PER_DMA_1_STREAM_5_DAC1 =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_5],
    .Chan = PER_DMA_CHANNEL_7
};

static const per_dma_selection_t PER_DMA_1_STREAM_6_I2C1_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_6],
    .Chan = PER_DMA_CHANNEL_1
};

static const per_dma_selection_t PER_DMA_1_STREAM_6_TIM4_UP =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_6],
    .Chan = PER_DMA_CHANNEL_2
};

static const per_dma_selection_t PER_DMA_1_STREAM_6_TIM2_CH2_CH4 =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_6],
    .Chan = PER_DMA_CHANNEL_3
};

static const per_dma_selection_t PER_DMA_1_STREAM_6_USART2_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_6],
    .Chan = PER_DMA_CHANNEL_4
};

static const per_dma_selection_t PER_DMA_1_STREAM_6_TIM5_UP =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_6],
    .Chan = PER_DMA_CHANNEL_6
};

static const per_dma_selection_t PER_DMA_1_STREAM_6_DAC2 =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_6],
    .Chan = PER_DMA_CHANNEL_7
};

static const per_dma_selection_t PER_DMA_1_STREAM_7_SPI3_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_7],
    .Chan = PER_DMA_CHANNEL_0
};

static const per_dma_selection_t PER_DMA_1_STREAM_7_I2C1_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_7],
    .Chan = PER_DMA_CHANNEL_1
};

static const per_dma_selection_t PER_DMA_1_STREAM_7_TIM4_CH3 =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_7],
    .Chan = PER_DMA_CHANNEL_2
};

static const per_dma_selection_t PER_DMA_1_STREAM_7_TIM2_UP_CH4 =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_7],
    .Chan = PER_DMA_CHANNEL_3
};

static const per_dma_selection_t PER_DMA_1_STREAM_7_UART5_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_7],
    .Chan = PER_DMA_CHANNEL_4
};

static const per_dma_selection_t PER_DMA_1_STREAM_7_TIM3_CH3 =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_7],
    .Chan = PER_DMA_CHANNEL_5
};

static const per_dma_selection_t PER_DMA_1_STREAM_7_I2C2_TX =
{
    .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_7],
    .Chan = PER_DMA_CHANNEL_7
};

static const per_dma_selection_t PER_DMA_2_STREAM_0_ADC1 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_0],
    .Chan = PER_DMA_CHANNEL_0
};

static const per_dma_selection_t PER_DMA_2_STREAM_0_ADC3 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_0],
    .Chan = PER_DMA_CHANNEL_2
};

static const per_dma_selection_t PER_DMA_2_STREAM_0_SPI1_RX =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_0],
    .Chan = PER_DMA_CHANNEL_3
};

static const per_dma_selection_t PER_DMA_2_STREAM_0_TIM1_TRIG =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_0],
    .Chan = PER_DMA_CHANNEL_6
};

static const per_dma_selection_t PER_DMA_2_STREAM_1_DCMI =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_1],
    .Chan = PER_DMA_CHANNEL_1
};

static const per_dma_selection_t PER_DMA_2_STREAM_1_ADC3 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_1],
    .Chan = PER_DMA_CHANNEL_2
};

static const per_dma_selection_t PER_DMA_2_STREAM_1_USART6_RX =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_1],
    .Chan = PER_DMA_CHANNEL_5
};

static const per_dma_selection_t PER_DMA_2_STREAM_1_TIM1_CH1 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_1],
    .Chan = PER_DMA_CHANNEL_6
};

static const per_dma_selection_t PER_DMA_2_STREAM_1_TIM8_UP =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_1],
    .Chan = PER_DMA_CHANNEL_7
};

static const per_dma_selection_t PER_DMA_2_STREAM_2_TIM8_CH1_CH2_CH3 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_0
};

static const per_dma_selection_t PER_DMA_2_STREAM_2_ADC2 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_1
};

static const per_dma_selection_t PER_DMA_2_STREAM_2_SPI1_RX =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_3
};

static const per_dma_selection_t PER_DMA_2_STREAM_2_USART1_RX =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_4
};

static const per_dma_selection_t PER_DMA_2_STREAM_2_USART6_RX =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_5
};

static const per_dma_selection_t PER_DMA_2_STREAM_2_TIM1_CH2 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_6
};

static const per_dma_selection_t PER_DMA_2_STREAM_2_TIM8_CH1 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_2],
    .Chan = PER_DMA_CHANNEL_7
};

static const per_dma_selection_t PER_DMA_2_STREAM_3_ADC2 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_3],
    .Chan = PER_DMA_CHANNEL_1
};

static const per_dma_selection_t PER_DMA_2_STREAM_3_SPI1_TX =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_3],
    .Chan = PER_DMA_CHANNEL_3
};

static const per_dma_selection_t PER_DMA_2_STREAM_3_SDIO =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_3],
    .Chan = PER_DMA_CHANNEL_4
};

static const per_dma_selection_t PER_DMA_2_STREAM_3_TIM1_CH1 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_3],
    .Chan = PER_DMA_CHANNEL_6
};

static const per_dma_selection_t PER_DMA_2_STREAM_3_TIM8_CH2 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_3],
    .Chan = PER_DMA_CHANNEL_7
};

static const per_dma_selection_t PER_DMA_2_STREAM_4_ADC1 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_4],
    .Chan = PER_DMA_CHANNEL_0
};

static const per_dma_selection_t PER_DMA_2_STREAM_4_TIM1_CH4_TRIG_COM =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_4],
    .Chan = PER_DMA_CHANNEL_6
};

static const per_dma_selection_t PER_DMA_2_STREAM_4_TIM8_CH3 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_4],
    .Chan = PER_DMA_CHANNEL_7
};

static const per_dma_selection_t PER_DMA_2_STREAM_5_CRYP_OUT =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_5],
    .Chan = PER_DMA_CHANNEL_2
};

static const per_dma_selection_t PER_DMA_2_STREAM_5_SPI1_TX =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_5],
    .Chan = PER_DMA_CHANNEL_3
};

static const per_dma_selection_t PER_DMA_2_STREAM_5_USART1_RX =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_5],
    .Chan = PER_DMA_CHANNEL_4
};

static const per_dma_selection_t PER_DMA_2_STREAM_5_TIM1_UP =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_5],
    .Chan = PER_DMA_CHANNEL_6
};

static const per_dma_selection_t PER_DMA_2_STREAM_6_TIM1_CH1_CH2_CH3 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_6],
    .Chan = PER_DMA_CHANNEL_0
};

static const per_dma_selection_t PER_DMA_2_STREAM_6_CRYP_IN =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_6],
    .Chan = PER_DMA_CHANNEL_2
};

static const per_dma_selection_t PER_DMA_2_STREAM_6_SDIO =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_6],
    .Chan = PER_DMA_CHANNEL_4
};

static const per_dma_selection_t PER_DMA_2_STREAM_6_USART6_TX =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_6],
    .Chan = PER_DMA_CHANNEL_5
};

static const per_dma_selection_t PER_DMA_2_STREAM_6_TIM1_CH3 =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_6],
    .Chan = PER_DMA_CHANNEL_6
};

static const per_dma_selection_t PER_DMA_2_STREAM_7_DCMI =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_7],
    .Chan = PER_DMA_CHANNEL_1
};

static const per_dma_selection_t PER_DMA_2_STREAM_7_HASH_IN =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_7],
    .Chan = PER_DMA_CHANNEL_2
};

static const per_dma_selection_t PER_DMA_2_STREAM_7_USART1_TX =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_7],
    .Chan = PER_DMA_CHANNEL_4
};

static const per_dma_selection_t PER_DMA_2_STREAM_7_USART6_TX =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_7],
    .Chan = PER_DMA_CHANNEL_5
};

static const per_dma_selection_t PER_DMA_2_STREAM_7_TIM8_CH4_TRIG_COM =
{
    .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_7],
    .Chan = PER_DMA_CHANNEL_7
};

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_1_stream_0(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_0],
        .Isr = &PER_DMA_1_BB->Isr0,
        .Ifcr = &PER_DMA_1_BB->Ifcr0,
        .Err = PER_LOG_DMA_1_STREAM_0,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_1_stream_1(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_1],
        .Isr = &PER_DMA_1_BB->Isr1,
        .Ifcr = &PER_DMA_1_BB->Ifcr1,
        .Err = PER_LOG_DMA_1_STREAM_1,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_1_stream_2(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_2],
        .Isr = &PER_DMA_1_BB->Isr2,
        .Ifcr = &PER_DMA_1_BB->Ifcr2,
        .Err = PER_LOG_DMA_1_STREAM_2,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* per_dma_1_stream_3(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_3],
        .Isr = &PER_DMA_1_BB->Isr3,
        .Ifcr = &PER_DMA_1_BB->Ifcr3,
        .Err = PER_LOG_DMA_1_STREAM_3,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_1_stream_4(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_4],
        .Isr = &PER_DMA_1_BB->Isr4,
        .Ifcr = &PER_DMA_1_BB->Ifcr4,
        .Err = PER_LOG_DMA_1_STREAM_4,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_1_stream_5(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_5],
        .Isr = &PER_DMA_1_BB->Isr5,
        .Ifcr = &PER_DMA_1_BB->Ifcr5,
        .Err = PER_LOG_DMA_1_STREAM_5,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_1_stream_6(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_6],
        .Isr = &PER_DMA_1_BB->Isr6,
        .Ifcr = &PER_DMA_1_BB->Ifcr6,
        .Err = PER_LOG_DMA_1_STREAM_6,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_1_stream_7(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_1_BB->Stream[PER_DMA_STREAM_7],
        .Isr = &PER_DMA_1_BB->Isr7,
        .Ifcr = &PER_DMA_1_BB->Ifcr7,
        .Err = PER_LOG_DMA_1_STREAM_7,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_2_stream_0(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_0],
        .Isr = &PER_DMA_2_BB->Isr0,
        .Ifcr = &PER_DMA_2_BB->Ifcr0,
        .Err = PER_LOG_DMA_2_STREAM_0,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_2_stream_1(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_1],
        .Isr = &PER_DMA_2_BB->Isr1,
        .Ifcr = &PER_DMA_2_BB->Ifcr1,
        .Err = PER_LOG_DMA_2_STREAM_1,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_2_stream_2(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_2],
        .Isr = &PER_DMA_2_BB->Isr2,
        .Ifcr = &PER_DMA_2_BB->Ifcr2,
        .Err = PER_LOG_DMA_2_STREAM_2,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_2_stream_3(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_3],
        .Isr = &PER_DMA_2_BB->Isr3,
        .Ifcr = &PER_DMA_2_BB->Ifcr3,
        .Err = PER_LOG_DMA_2_STREAM_3,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_2_stream_4(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_4],
        .Isr = &PER_DMA_2_BB->Isr4,
        .Ifcr = &PER_DMA_2_BB->Ifcr4,
        .Err = PER_LOG_DMA_2_STREAM_4,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_2_stream_5(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_5],
        .Isr = &PER_DMA_2_BB->Isr5,
        .Ifcr = &PER_DMA_2_BB->Ifcr5,
        .Err = PER_LOG_DMA_2_STREAM_5,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_2_stream_6(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_6],
        .Isr = &PER_DMA_2_BB->Isr6,
        .Ifcr = &PER_DMA_2_BB->Ifcr6,
        .Err = PER_LOG_DMA_2_STREAM_6,
    };
    return &dma_stream;
}

/// DMA pointer to stream
static per_inline const per_dma_stream_t* const per_dma_2_stream_7(void)
{
    static const per_dma_stream_t dma_stream =
    {
        .Conf = &PER_DMA_2_BB->Stream[PER_DMA_STREAM_7],
        .Isr = &PER_DMA_2_BB->Isr7,
        .Ifcr = &PER_DMA_2_BB->Ifcr7,
        .Err = PER_LOG_DMA_2_STREAM_7,
    };
    return &dma_stream;
}

#ifdef __cplusplus
}
#endif

#endif // per_dma_h_
