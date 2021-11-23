/**
 * @file per_log_f4.h
 *
 * This file contains the peripheral logging identifiers
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

#ifndef per_log_f4_h_
#define per_log_f4_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_dep.h"

/// LOG peripheral enumeration
typedef enum
{
    PER_LOG_MULT = 1000, ///< INDEX multipier
    PER_LOG_OK = 0, ///< OK
    PER_LOG_ADC_1, ///< ADC1
    PER_LOG_ADC_2, ///< ADC2
    PER_LOG_ADC_3, ///< ADC3
    PER_LOG_ADC_COM, ///< ADC_COM
    PER_LOG_ADC, ///< ADC
    PER_LOG_BITBAND, ///< BITBAND
    PER_LOG_CAN_1, ///< CAN1
    PER_LOG_CAN_2, ///< CAN2
    PER_LOG_CAN, ///< CAN
    PER_LOG_DAC_CHANNEL_1, ///< DAC CHANNEL1
    PER_LOG_DAC_CHANNEL_2, ///< DAC CHANNEL2
    PER_LOG_DAC, ///< DAC
    PER_LOG_DBG, ///< DBG
    PER_LOG_DCMI, ///< DCMI
    PER_LOG_DES, ///< DES
    PER_LOG_DMA_1_STREAM_0, ///< DMA1 STREAM0
    PER_LOG_DMA_1_STREAM_1, ///< DMA1 STREAM1
    PER_LOG_DMA_1_STREAM_2, ///< DMA1 STREAM2
    PER_LOG_DMA_1_STREAM_3, ///< DMA1 STREAM3
    PER_LOG_DMA_1_STREAM_4, ///< DMA1 STREAM4
    PER_LOG_DMA_1_STREAM_5, ///< DMA1 STREAM5
    PER_LOG_DMA_1_STREAM_6, ///< DMA1 STREAM6
    PER_LOG_DMA_1_STREAM_7, ///< DMA1 STREAM7
    PER_LOG_DMA_1, ///< DMA1
    PER_LOG_DMA_2_STREAM_0, ///< DMA2 STREAM0
    PER_LOG_DMA_2_STREAM_1, ///< DMA2 STREAM1
    PER_LOG_DMA_2_STREAM_2, ///< DMA2 STREAM2
    PER_LOG_DMA_2_STREAM_3, ///< DMA2 STREAM3
    PER_LOG_DMA_2_STREAM_4, ///< DMA2 STREAM4
    PER_LOG_DMA_2_STREAM_5, ///< DMA2 STREAM5
    PER_LOG_DMA_2_STREAM_6, ///< DMA2 STREAM6
    PER_LOG_DMA_2_STREAM_7, ///< DMA2 STREAM7
    PER_LOG_DMA_2, ///< DMA2
    PER_LOG_DMA, ///< DMA
    PER_LOG_DMA2D, ///< DMA2D
    PER_LOG_ETH_DMA, ///< ETH_DMA
    PER_LOG_ETH_IEEE_1588, ///< ETH_IEEE_1588
    PER_LOG_ETH_MAC, ///< ETH_MAC
    PER_LOG_ETH_MMC, ///< ETH_MMC
    PER_LOG_ETH, ///< ETH
    PER_LOG_FLASH, ///< FLASH
    PER_LOG_FMC, ///< FMC
    PER_LOG_FSMC, ///< FSMC
    PER_LOG_GPIO_A, ///< GPIOA
    PER_LOG_GPIO_B, ///< GPIOB
    PER_LOG_GPIO_C, ///< GPIOC
    PER_LOG_GPIO_D, ///< GPIOD
    PER_LOG_GPIO_E, ///< GPIOE
    PER_LOG_GPIO_F, ///< GPIOF
    PER_LOG_GPIO_G, ///< GPIOG
    PER_LOG_GPIO_H, ///< GPIOH
    PER_LOG_GPIO_I, ///< GPIOI
    PER_LOG_GPIO_J, ///< GPIOJ
    PER_LOG_GPIO_K, ///< GPIOK
    PER_LOG_GPIO, ///< GPIO
    PER_LOG_HASH, ///< HASH
    PER_LOG_I2C, ///< I2C
    PER_LOG_I2C_1, ///< I2C
    PER_LOG_I2C_2, ///< I2C
    PER_LOG_I2C_3, ///< I2C
    PER_LOG_IWDG, ///< IWDG
    PER_LOG_LTDC, ///< LTDC
    PER_LOG_OTG_FS, ///< OTG_FS
    PER_LOG_OTG_HS, ///< OTG_HS
    PER_LOG_PER, ///< Peripheral unknown
    PER_LOG_PWR, ///< PWR
    PER_LOG_RCC, ///< RCC
    PER_LOG_RNG, ///< RNG
    PER_LOG_RTC, ///< RTC
    PER_LOG_SAI_A, ///< SAI_A
    PER_LOG_SAI_B, ///< SAI_B
    PER_LOG_SAI, ///< SAI
    PER_LOG_SDIO, ///< SDIO
    PER_LOG_SPI_1, ///< SPI1
    PER_LOG_SPI_2, ///< SPI2
    PER_LOG_SPI_3, ///< SPI3
    PER_LOG_SPI_4, ///< SPI4
    PER_LOG_SPI_5, ///< SPI5
    PER_LOG_SPI_6, ///< SPI6
    PER_LOG_SPI,   ///< SPI
    PER_LOG_SYS_CFG, ///< SYS_CFG
    PER_LOG_TIM_1,  ///< TIM1
    PER_LOG_TIM_10, ///< TIM10
    PER_LOG_TIM_11, ///< TIM11
    PER_LOG_TIM_12, ///< TIM12
    PER_LOG_TIM_13, ///< TIM13
    PER_LOG_TIM_14, ///< TIM14
    PER_LOG_TIM_2, ///< TIM2
    PER_LOG_TIM_3, ///< TIM3
    PER_LOG_TIM_4, ///< TIM4
    PER_LOG_TIM_5, ///< TIM5
    PER_LOG_TIM_6, ///< TIM6
    PER_LOG_TIM_7, ///< TIM7
    PER_LOG_TIM_8, ///< TIM8
    PER_LOG_TIM_9, ///< TIM9
    PER_LOG_TIM,   ///< TIM
    PER_LOG_TIM_AD, ///< TIM advanced
    PER_LOG_TIM_GP, ///< TIM general purpose
    PER_LOG_UART_4, ///< UART4
    PER_LOG_UART_5, ///< UART5
    PER_LOG_UART_7, ///< UART7
    PER_LOG_UART_8, ///< UART8
    PER_LOG_USART_1, ///< USART1
    PER_LOG_USART_2, ///< USART2
    PER_LOG_USART_3, ///< USART3
    PER_LOG_USART_6, ///< USART6
    PER_LOG_UART,  ///< UART
    PER_LOG_USART, ///< USART
    PER_LOG_WWDG,  ///< WWDG
} per_log_e;

typedef struct
{
    per_log_e peripheral;  //!< Last error peripheral number
    uint32_t event;  //!< Last error event number
    uint32_t value;  //!< Last error value
} per_log_event_t;

void per_log_err(per_log_e per, uint_fast32_t ev, uint_fast32_t val);

void per_log_set_callback(void (*fct)(uint_fast32_t per, uint_fast32_t ev, uint_fast32_t val));

void per_log_clr_callback(void);

uint32_t per_log_get(per_log_event_t* event);

#ifdef __cplusplus
}
#endif

#endif // per_log_f4_h_
