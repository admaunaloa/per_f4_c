/**
 * @file per_rcc_f4.h
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

#ifndef per_rcc_f4_h_
#define per_rcc_f2_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_bit_f4.h"
#include "per_log_f4.h"

/// RCC APBx to TIMERS fixed multiplier
#define PER_RCC_APB_PER_TO_TIM_MUL ((uint32_t)2)

/// RCC low-speed external clock
#define PER_RCC_LSE ((uint32_t)32768)

/// RCC low-speed internal rc clock
#define PER_RCC_LSI_RC ((uint32_t)32000)

/// RCC high-speed external clock
#define PER_RCC_HSE ((uint32_t)8000000)

/// RCC high-speed internal rc clock
#define PER_RCC_HSI_RC ((uint32_t)16000000)

/// RCC PLL minimum value
#define PER_RCC_PLL_MIN (2)

/// RCC Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock
#define PER_RCC_PLLM_MAX (63)

/// RCC Main PLL (PLL) multiplication factor for VCO
#define PER_RCC_PLLN_MAX (432)

/// RCC Main PLL (PLL) division factor for main system clock
#define PER_RCC_PLLP_MAX (8)

/// Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks
#define PER_RCC_PLLQ_MAX (15)

/// RCC AHB prescaler maximum
#define PER_RCC_HPRE_MAX (512)

/// RCC AHB prescaler invalid
#define PER_RCC_HPRE_INV ((uint_fast16_t)32)

/// RCC AHB prescaler highest bit
#define PER_RCC_HPRE_MSB ((uint_fast16_t)0b1000)

/// RCC APB prescaler maximum
#define PER_RCC_PPRE_MAX (16)

/// RCC APB prescaler highest bit
#define PER_RCC_PPRE_MSB ((uint_fast16_t)0b0100)

/// RCC HSE division factor for RTC clock
#define PER_RCC_RTCPRE_MAX (31)

/// RCC HSE division factor for RTC clock
#define PER_RCC_RTCPRE_MIN (2)

/// RCC MCO prescaler maximum
#define PER_RCC_MCO_MAX (5)

/// RCC MCO prescaler highest bit
#define PER_RCC_MCO_MSB ((uint_fast16_t)0b0100)

/// RCC MCO prescaler base
#define PER_RCC_MCO_BASE ((uint_fast16_t)2)

/// RCC PLLI2S multiplication factor for VCO
#define PER_RCC_PLLI2SN_MAX ((uint_fast16_t)432)

/// RCC PLLI2S division factor for SAI1 clock
#define PER_RCC_PLLI2SQ_MAX ((uint_fast16_t)15)

/// RCC PLLI2S division factor for I2S clocks
#define PER_RCC_PLLI2SR_MAX ((uint_fast16_t)7)

/// RCC PLLSAI multiplication factor for VCO
#define PER_RCC_PLLSAIN_MAX ((uint_fast16_t)432)

/// RCC PLLSAI division factor for SAI1 clock
#define PER_RCC_PLLSAIQ_MAX ((uint_fast16_t)15)

/// RCC PLLSAI division factor for I2S clocks
#define PER_RCC_PLLSAIR_MAX ((uint_fast16_t)7)

/// PLLI2S division factor for SAI1 clock
#define PER_RCC_PLLI2SDIVQ_MAX ((uint_fast16_t)32)

/// PLLSAI division factor for SAI1 clock
#define PER_RCC_PLLSAIDIVQ_MAX ((uint_fast16_t)32)

/// division factor for LCD_CLK
#define PER_RCC_PLLSAIDIVR_MAX ((uint_fast16_t)16)

/// RCC error enumeration
typedef enum
{
    PER_RCC_OK_ERR = PER_LOG_RCC * PER_LOG_MULT, ///< No error
    PER_RCC_PLLM_ERR,      ///< Division factor for the main PLL (PLL) invalid
    PER_RCC_PLLN_ERR,      ///< Main PLL (PLL) multiplication factor for VCO invalid
    PER_RCC_PLLP_ERR,      ///< Main PLL (PLL) division factor for main system clock invalid
    PER_RCC_PLLQ_ERR,      ///< RCC Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks
    PER_RCC_HPRE_ERR,      ///< AHB prescaler invalid
    PER_RCC_PPRE1_ERR,     ///< APB1 prescaler invalid
    PER_RCC_PPRE2_ERR,     ///< APB2 prescaler invalid
    PER_RCC_RTCPRE_ERR,    ///< HSE division factor for RTC clock invalid
    PER_RCC_MCO1PRE_ERR,   ///< MCO1 prescaler invalid
    PER_RCC_MCO2PRE_ERR,   ///< MCO2 prescaler invalid
    PER_RCC_PLLI2SN_ERR,   ///< PLLI2S multiplication factor for VCO
    PER_RCC_PLLI2SQ_ERR,   ///< PLLI2S division factor for SAI1 clock
    PER_RCC_PLLI2SR_ERR,   ///< PLLI2S division factor for I2S clocks
    PER_RCC_PLLSAIN_ERR,   ///< PLLSAI multiplication factor for VCO
    PER_RCC_PLLSAIQ_ERR,   ///< PLLSAI division factor for SAI1 clock
    PER_RCC_PLLSAIR_ERR,   ///< PLLSAI division factor for I2S clocks
    PER_RCC_PLLI2SDIVQ_ERR,///< PLLI2S division factor for SAI1 clock
    PER_RCC_PLLSAIDIVQ_ERR,///< PLLSAI division factor for SAI1 clock
    PER_RCC_PLLSAIDIVR_ERR,///< division factor for LCD_CLK

} per_rcc_error_e;

/// RCC ADC peripherals number
typedef enum
{
    PER_RCC_ADC_1 = 1,
    PER_RCC_ADC_2,
    PER_RCC_ADC_3,
} per_rcc_adc_e;

/// RCC CAN peripherals number
typedef enum
{
    PER_RCC_CAN_0 = 0,
    PER_RCC_CAN_1,
    PER_RCC_CAN_2,
    PER_RCC_CAN_3,
} per_rcc_can_e;

/// RCC I2C peripherals number
typedef enum
{
    PER_RCC_I2C_0 = 0,
    PER_RCC_I2C_1,
    PER_RCC_I2C_2,
    PER_RCC_I2C_3,
    PER_RCC_I2C_4,
} per_rcc_i2c_e;

/// RCC I2S peripherals number
typedef enum
{
    PER_RCC_I2S_0 = 0,
    PER_RCC_I2S_1,
    PER_RCC_I2S_2,
    PER_RCC_I2S_3,
    PER_RCC_I2S_4,
    PER_RCC_I2S_5,
} per_rcc_i2s_e;

/// RCC GPIO peripherals number
typedef enum
{
    PER_RCC_GPIO_0  = 0,
    PER_RCC_GPIO_A,
    PER_RCC_GPIO_B,
    PER_RCC_GPIO_C,
    PER_RCC_GPIO_D,
    PER_RCC_GPIO_E,
    PER_RCC_GPIO_F,
    PER_RCC_GPIO_G,
    PER_RCC_GPIO_H,
    PER_RCC_GPIO_I,
    PER_RCC_GPIO_J,
    PER_RCC_GPIO_K,
} per_rcc_gpio_e;

/// RCC SPI peripherals number
typedef enum
{
    PER_RCC_SPI_0 = 0,
    PER_RCC_SPI_1,
    PER_RCC_SPI_2,
    PER_RCC_SPI_3,
    PER_RCC_SPI_4,
    PER_RCC_SPI_5,
    PER_RCC_SPI_6,
} per_rcc_spi_e;

/// RCC UART peripherals number
typedef enum
{
    PER_RCC_UART_0 = 0,
    PER_RCC_UART_1,
    PER_RCC_UART_2,
    PER_RCC_UART_3,
    PER_RCC_UART_4,
    PER_RCC_UART_5,
    PER_RCC_UART_6,
} per_rcc_uart_e;

/// RCC USART peripherals number
typedef enum
{
    PER_RCC_USART_0 = 0,
    PER_RCC_USART_1,
    PER_RCC_USART_2,
    PER_RCC_USART_3,
    PER_RCC_USART_4,
} per_rcc_usart_e;

/// RCC System clock switch
typedef enum
{
    PER_RCC_SW_HSI = 0b00, ///< HSI clock selected
    PER_RCC_SW_HSE = 0b01, ///< HSE oscillator clock selected
    PER_RCC_SW_PLL = 0b10, ///< PLL clock selected
} per_rcc_sw_e;

/// RCC MCO 1 clock source
typedef enum
{
    PER_RCC_MCO_1_HSI = 0b00, ///< HSI clock selected
    PER_RCC_MCO_1_LSE = 0b01, ///< LSE oscillator selected
    PER_RCC_MCO_1_HSE = 0b10, ///< HSE oscillator clock selected
    PER_RCC_MCO_1_PLL = 0b11, ///< PLL clock selected
} per_rcc_mco_1_e;

/// RCC MCO 2 clock source
typedef enum
{
    PER_RCC_MCO_2_SYSCLK = 0b00, ///< System clock (SYSCLK) selected
    PER_RCC_MCO_2_PLLI2S = 0b01, ///< PLLI2S clock selected
    PER_RCC_MCO_2_HSE    = 0b10, ///< HSE oscillator clock selected
    PER_RCC_MCO_2_PLL    = 0b11, ///< PLL clock selected
} per_rcc_mco_2_e;

/// RCC RTC clock source selection
typedef enum
{
    PER_RCC_RTCSEL_NO  = 0b00, ///< No clock
    PER_RCC_RTCSEL_LSE = 0b01, ///< LSE oscillator clock used as the RTC clock
    PER_RCC_RTCSEL_LSI = 0b10, ///< LSI oscillator clock used as the RTC clock
    PER_RCC_RTCSEL_HSE = 0b11, ///< HSE oscillator clock divided by a programmable prescaler
} per_rcc_rtcsel_e;

/// RCC SAI1 clock source selection
typedef enum
{
    PER_RCC_SAI1ASRC_SAI = 0b00, ///< f(PLLSAI_Q) / PLLSAIDIVQ
    PER_RCC_SAI1ASRC_I2S = 0b01, ///< f(PLLI2S_Q) / PLLI2SDIVQ
    PER_RCC_SAI1ASRC_ALT = 0b10, ///< Alternate function input frequency
} per_rcc_sai1src_e;

/// RCC Peripheral Read-write enable bit
typedef struct
{
    per_bit_bitband_t Rw; ///< One read write bit
} per_rcc_en1_t;

/// RCC One read and write enable bit get
static per_inline bool per_rcc_en1(const per_rcc_en1_t* self)
{
    return self->Rw.Bit8 != PER_BIT_0;
}

/// RCC One read and write enable bit set
static per_inline void per_rcc_en1_set(per_rcc_en1_t* self, bool val)
{
    self->Rw.Bit8 = (uint_fast8_t)val; // Cast is fast
    val = self->Rw.Bit8 != PER_BIT_0;  // Wait read back
}

/// RCC Peripheral 3 bit Prescaler
typedef union
{
    per_bit_rw3_t Pre; ///< prescaler
    struct
    {
        per_bit_n2_t Fill; ///< value
        per_bit_w1_t Msb;  ///< most significant bit
    };
}per_rcc_pre3_t;

/// RCC Peripheral 4 bit Prescaler
typedef union
{
    per_bit_rw4_t Pre; ///< prescaler
    struct
    {
        per_bit_n3_t Fill; ///< value
        per_bit_w1_t Msb;  ///< most significant bit
    };
}per_rcc_pre4_t;

typedef struct
{
    // Control register (RCC_CR)
    per_bit_rw1_t Hsion; ///< Internal high-speed clock enable
    per_bit_r1_t Hsirdy; ///< Internal high-speed clock ready flag
    per_bit_n1_t CrBit2; ///< Reserved
    per_bit_rw5_t Hsitrim; ///< Internal high-speed clock trimming
    per_bit_r8_t Hsical; ///< Internal high-speed clock calibration
    per_bit_rw1_t Hseon; ///< HSE clock enable
    per_bit_r1_t Hserdy; ///< HSE clock ready flag
    per_bit_rw1_t Hsebyp; ///< HSE clock bypass
    per_bit_rw1_t Csson; ///< Clock security system enable
    per_bit_n4_t CrBit20; ///< Reserved
    per_bit_rw1_t Pllon; ///< Main PLL (PLL) enable
    per_bit_r1_t Pllrdy; ///< Main PLL (PLL) clock ready flag
    per_bit_rw1_t Plli2son; ///< PLLI2S enable
    per_bit_r1_t Plli2srdy; ///< PLLI2S clock ready flag
    per_bit_rw1_t Pllsaion; ///< PLLSAI enable
    per_bit_r1_t Pllsairdy; ///< PLLSAI clock ready flag
    per_bit_n2_t CrBit30; ///< Reserved

    // PLL configuration register (RCC_PLLCFGR)
    per_bit_rw6_t Pllm; ///< Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock
    per_bit_rw9_t Plln ; ///< Main PLL (PLL) multiplication factor for VCO
    per_bit_n1_t PllcfgrBit15; ///< Reserved
    per_bit_rw2_t Pllp; ///< Main PLL (PLL) division factor for main system clock
    per_bit_n4_t PllcfgrBit18; ///< Reserved
    per_bit_rw1_t Pllscr; ///< Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
    per_bit_n1_t PllcfgrBit23; ///< Reserved
    per_bit_rw4_t Pllq; ///< Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks
    per_bit_n4_t PllcfgrBit28; ///< Reserved

    // clock configuration register (RCC_CFGR)
    per_bit_rw2_t Sw; ///< System clock switch
    per_bit_r2_t Sws; ///< System clock switch status
    per_rcc_pre4_t Hpre; ///< AHB prescaler
    per_bit_n2_t CirBit8; ///< Reserved
    per_rcc_pre3_t Ppre1; ///< APB Low speed prescaler (APB1)
    per_rcc_pre3_t Ppre2; ///< ///< APB high-speed prescaler (APB2)
    per_bit_rw5_t Rtcpre; ///< HSE division factor for RTC clock
    per_bit_rw2_t Mco1; ///< Microcontroller clock output 1
    per_bit_rw1_t I2sscr; ///< I2S clock selection
    per_rcc_pre3_t Mco1pre; ///< MCO1 prescaler
    per_rcc_pre3_t Mco2pre; ///< MCO2 prescaler
    per_bit_rw2_t Mco2; ///< Microcontroller clock output 2

    // clock interrupt register (RCC_CIR)
    per_bit_r1_t Lsirdyf; ///< LSI ready interrupt flag
    per_bit_r1_t Lserdyf; ///< LSE ready interrupt flag
    per_bit_r1_t Hsirdyf; ///< HSI ready interrupt flag
    per_bit_r1_t Hserdyf; ///< HSE ready interrupt flag
    per_bit_r1_t Pllrdyf; ///< Main PLL (PLL) ready interrupt flag
    per_bit_r1_t Plli2srdyf; ///< PLLI2S ready interrupt flag
    per_bit_r1_t Pllsairdyf; ///< PLLSAI Ready Interrupt flag
    per_bit_r1_t Cssf; ///< Clock security system interrupt flag
    per_bit_rw1_t Lsirdyie; ///< LSI ready interrupt enable
    per_bit_rw1_t Lserdyie; ///< LSE ready interrupt enable
    per_bit_rw1_t Hsirdyie; ///< HSI ready interrupt enable
    per_bit_rw1_t Hserdyie; ///< HSE ready interrupt enable
    per_bit_rw1_t Pllrdyie; ///< Main PLL (PLL) ready interrupt enable
    per_bit_rw1_t Plli2srdyie; ///< PLLI2S ready interrupt enable
    per_bit_rw1_t Pllsairdyie; ///< PLLSAI Ready Interrupt Enable
    per_bit_n1_t CirBit15; ///< Reserved.
    per_bit_w1_t Lsirdyc; ///< LSI ready interrupt clear
    per_bit_w1_t Lserdyc; ///< LSE ready interrupt clear
    per_bit_w1_t Hsirdyc; ///< HSI ready interrupt clear
    per_bit_w1_t Hserdyc; ///< HSE ready interrupt clear
    per_bit_w1_t Pllrdyc; ///< Main PLL(PLL) ready interrupt clear
    per_bit_w1_t Plli2srdyc; ///< PLLI2S ready interrupt clear
    per_bit_w1_t Pllsairdyc; ///< PLLSAI Ready Interrupt Clear
    per_bit_w1_t Cssc; ///< Clock security system interrupt clear
    per_bit_n8_t CirBit24; ///< Reserved.

    // RCC AHB1 peripheral reset register (RCC_AHB1RSTR)
    per_bit_rw1_t Gpioarst; ///< IO port A reset
    per_bit_rw1_t Gpiobrst; ///< IO port B reset
    per_bit_rw1_t Gpiocrst; ///< IO port C reset
    per_bit_rw1_t Gpiodrst; ///< IO port D reset
    per_bit_rw1_t Gpioerst; ///< IO port E reset
    per_bit_rw1_t Gpiofrst; ///< IO port F reset
    per_bit_rw1_t Gpiogrst; ///< IO port G reset
    per_bit_rw1_t Gpiohrst; ///< IO port H reset
    per_bit_rw1_t Gpioirst; ///< IO port I reset
    per_bit_rw1_t Gpiojrst; ///< IO port J reset
    per_bit_rw1_t Gpiokrst; ///< IO port K reset
    per_bit_n1_t Ahb1rstrBit11; ///< Reserved
    per_bit_rw1_t Crcrst; ///< CRC reset
    per_bit_n8_t Bit13_Reserved; ///< Reserved
    per_bit_rw1_t Dma1rst; ///< DMA1 reset
    per_bit_rw1_t Dma2rst; ///< DMA2 reset
    per_bit_rw1_t Dma2drst; ///< DMA2D reset
    per_bit_n1_t Ahb1rstrBit24; ///< Reserved
    per_bit_rw1_t Ethmacrst; ///< Ethernet MAC reset
    per_bit_n3_t Ahb1rstrBit26; ///< Reserved
    per_bit_rw1_t Otghsrst; ///< USB OTG HS module reset
    per_bit_n2_t Ahb1rstrBit30; ///< Reserved

    // RCC AHB2 peripheral reset register (RCC_AHB2RSTR)
    per_bit_rw1_t Dcmirst; ///< Camera interface reset
    per_bit_n3_t Ahb2rstrBit1; ///< Reserved
    per_bit_rw1_t Cryprst; ///< Cryptographic module reset
    per_bit_rw1_t Hashrst; ///< Hash module reset
    per_bit_rw1_t Rngrst; ///< Random number generator module reset
    per_bit_rw1_t Otgfsrst; ///< USB OTG FS module reset
    per_bit_n24_t Ahb2rstrBit8; ///< Reserved

    // RCC AHB3 peripheral reset register (RCC_AHB3RSTR)
    per_bit_rw1_t Fmcrst; ///< Flexible memory controller module reset
    per_bit_n31_t Ahb3rstrBit1; ///< Reserved

    per_bit_n32_t Reserved_0x1C;

    // RCC APB1 peripheral reset register (RCC_APB1RSTR)
    per_bit_rw1_t Tim2rst; ///< TIM2 reset
    per_bit_rw1_t Tim3rst; ///< TIM3 reset
    per_bit_rw1_t Tim4rst; ///< TIM4 reset
    per_bit_rw1_t Tim5rst; ///< TIM5 reset
    per_bit_rw1_t Tim6rst; ///< TIM6 reset
    per_bit_rw1_t Tim7rst; ///< TIM7 reset
    per_bit_rw1_t Tim12rst; ///< TIM12 reset
    per_bit_rw1_t Tim13rst; ///< TIM13 reset
    per_bit_rw1_t Tim14rst; ///< TIM14 reset
    per_bit_n2_t Apb1rstrBit9; ///< Reserved
    per_bit_rw1_t Wwdgrst; ///< Window watchdog reset
    per_bit_n2_t Apb1rstrBit12; ///< Reserved
    per_bit_rw1_t Spi2rst; ///< SPI2 reset
    per_bit_rw1_t Spi3rst; ///< SPI3 reset
    per_bit_n1_t Apb1rstrBitBit16; ///< Reserved
    per_bit_rw1_t Usart2rst; ///< USART2 reset
    per_bit_rw1_t Usart3rst; ///< USART3 reset
    per_bit_rw1_t Uart4rst; ///< UART4 reset
    per_bit_rw1_t Uart5rst; ///< UART5 reset
    per_bit_rw1_t I2c1rst; ///< I2C1 reset
    per_bit_rw1_t I2c2rst; ///< I2C2 reset
    per_bit_rw1_t I2c3rst; ///< I2C3 reset
    per_bit_n1_t Apb1rstrBit24; ///< Reserved
    per_bit_rw1_t Can1rst; ///< CAN1 reset
    per_bit_rw1_t Can2rst; ///< CAN2 reset
    per_bit_n1_t Apb1rstrBit27; ///< Reserved
    per_bit_rw1_t Pwrrst; ///< Power interface reset
    per_bit_rw1_t Dacrst; ///< DAC reset
    per_bit_rw1_t Uart7rst; ///< UART7 reset
    per_bit_rw1_t Uart8rst; ///< UART8 reset

    // RCC APB2 peripheral reset register (RCC_APB2RSTR)
    per_bit_rw1_t Tim1rst; ///< TIM1 reset
    per_bit_rw1_t Tim8rst; ///< TIM8 reset
    per_bit_n2_t Apb2rstBit2; ///< Reserved
    per_bit_rw1_t Usart1rst; ///< USART1 reset
    per_bit_rw1_t Usart6rst; ///< USART6 reset
    per_bit_n2_t Apb2rstBit6; ///< Reserved
    per_bit_rw1_t Adcrst; ///< ADC1 reset
    per_bit_n2_t Apb2rstBit9; ///< Reserved
    per_bit_rw1_t Sdiorst; ///< SDIO reset
    per_bit_rw1_t Spi1rst; ///< SPI1 reset
    per_bit_rw1_t Spi4rst; ///< SPI4 reset
    per_bit_rw1_t Syscfgrst; ///< SYSCFGEN reset
    per_bit_n1_t Apb2rstBit15; ///< Reserved
    per_bit_rw1_t Tim9rst; ///< TIM9 reset
    per_bit_rw1_t Tim10rst; ///< TIM10 reset
    per_bit_rw1_t Tim11rst; ///< TIM11 reset
    per_bit_n1_t Apb2rstBit19; ///< Reserved
    per_bit_rw1_t Spi5rst; ///< SPI5 reset
    per_bit_rw1_t Spi6rst; ///< SPI6 reset
    per_bit_rw1_t Sai1rst; ///< SAI1 reset
    per_bit_n3_t Apb2rstBit23; ///< Reserved
    per_bit_rw1_t Ltdcrst; ///< LTDC reset
    per_bit_n5_t Apb2rstBit27; ///< Reserved

    per_bit_n32_t Reserved_0x28; ///< Reserved
    per_bit_n32_t Reserved_0x2C; ///< Reserved

    // RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)
    per_rcc_en1_t Gpioaen; ///< IO port A clock enable
    per_rcc_en1_t Gpioben; ///< IO port B clock enable
    per_rcc_en1_t Gpiocen; ///< IO port C clock enable
    per_rcc_en1_t Gpioden; ///< IO port D clock enable
    per_rcc_en1_t Gpioeen; ///< IO port E clock enable
    per_rcc_en1_t Gpiofen; ///< IO port F clock enable
    per_rcc_en1_t Gpiogen; ///< IO port G clock enable
    per_rcc_en1_t Gpiohen; ///< IO port H clock enable
    per_rcc_en1_t Gpioien; ///< IO port I clock enable
    per_rcc_en1_t Gpiojen; ///< IO port J clock enable
    per_rcc_en1_t Gpioken; ///< IO port K clock enable
    per_bit_n1_t Ahb1enrBit11; ///< Reserved
    per_rcc_en1_t Crcen; ///< CRC clock enable
    per_bit_n5_t Ahb1enrBit13; ///< Reserved
    per_rcc_en1_t Bkpsramen; ///< Backup SRAM interface clock enable
    per_bit_n1_t Ahb1enrBit19; ///< Reserved.
    per_rcc_en1_t Ccmdataramen; ///< CCM data RAM clock enable
    per_rcc_en1_t Dma1en; ///< DMA1 clock enable
    per_rcc_en1_t Dma2en; ///< DMA2 clock enable
    per_rcc_en1_t Dma2den; ///< DMA2D clock enable
    per_bit_n1_t Ahb1enrBit24; ///< Reserved
    per_rcc_en1_t Ethmacen; ///< Ethernet MAC clock enable
    per_rcc_en1_t Ethmactxen; ///< Ethernet Transmission clock enable
    per_rcc_en1_t Ethmacrxen; ///< Ethernet Reception clock enable
    per_rcc_en1_t Ethmacptpen; ///< Ethernet PTP clock enable
    per_rcc_en1_t Otghsen; ///< USB OTG HS clock enable
    per_rcc_en1_t Otghsulpien; ///< USB OTG HSULPI clock enable
    per_bit_n1_t Ahb1enrBit31; ///< Reserved

    // RCC AHB2 peripheral clock enable register (RCC_AHB2ENR)
    per_rcc_en1_t Dcmien; ///< Camera interface enable
    per_bit_n3_t Ahb2enrBit1; ///< Reserved.
    per_rcc_en1_t Crypen; ///< Cryptographic modules clock enable
    per_rcc_en1_t Hashen; ///< Hash modules clock enable
    per_rcc_en1_t Rngen; ///< Random number generator clock enable
    per_rcc_en1_t Otgfsen; ///< USB OTG FS clock enable
    per_bit_n24_t Ahb2enrBit8; ///< Reserved

    // RCC AHB3 peripheral clock enable register (RCC_AHB3ENR)
    per_rcc_en1_t Fmcen; ///< Flexible memory controller module clock enable
    per_bit_n31_t Ahb3enrBit1; ///< Reserved

    per_bit_n32_t Reserved_0x3C; ///< Reserved

    // RCC APB1 peripheral clock enable register (RCC_APB1ENR)
    per_rcc_en1_t Tim2en; ///< TIM2 clock enable
    per_rcc_en1_t Tim3en; ///< TIM3 clock enable
    per_rcc_en1_t Tim4en; ///< TIM4 clock enable
    per_rcc_en1_t Tim5en; ///< TIM5 clock enable
    per_rcc_en1_t Tim6en; ///< TIM6 clock enable
    per_rcc_en1_t Tim7en; ///< TIM7 clock enable
    per_rcc_en1_t Tim12en; ///< TIM12 clock enable
    per_rcc_en1_t Tim13en; ///< TIM13 clock enable
    per_rcc_en1_t Tim14en; ///< TIM14 clock enable
    per_bit_n2_t Apb1enrBit9; ///< Reserved
    per_rcc_en1_t Wwdgen; ///< Window watchdog clock enable
    per_bit_n2_t Apb1enrBit12; ///< Reserved
    per_rcc_en1_t Spi2en; ///< SPI2 clock enable
    per_rcc_en1_t Spi3en; ///< SPI3 clock enable
    per_bit_n1_t Apb1enrBit16; ///< Reserved
    per_rcc_en1_t Usart2en; ///< USART2 clock enable
    per_rcc_en1_t Usart3en; ///< USART3 clock enable
    per_rcc_en1_t Uart4en; ///< UART4 clock enable
    per_rcc_en1_t Uart5en; ///< UART5 clock enable
    per_rcc_en1_t I2c1en; ///< I2C1 clock enable
    per_rcc_en1_t I2c2en; ///< I2C2 clock enable
    per_rcc_en1_t I2c3en; ///< I2C3 clock enable
    per_bit_n1_t Apb1enrBit24; ///< Reserved
    per_rcc_en1_t Can1en; ///< CAN1 clock enable
    per_rcc_en1_t Can2en; ///< CAN2 clock enable
    per_bit_n1_t Apb1enrBit27; ///< Reserved
    per_rcc_en1_t Pwren; ///< Power interface clock enable
    per_rcc_en1_t Dacen; ///< DAC interface clock enable
    per_rcc_en1_t Uart7en; ///< UART7 clock enable
    per_rcc_en1_t Uart8en; ///< UART8 clock enable

    // RCC APB2 peripheral clock enable register (RCC_APB2ENR)
    per_rcc_en1_t Tim1en; ///< TIM1 clock enable
    per_rcc_en1_t Tim8en; ///< TIM8 clock enable
    per_bit_n2_t Apb2enrBit2; ///< Reserved
    per_rcc_en1_t Usart1en; ///< USART1 clock enable
    per_rcc_en1_t Usart6en; ///< USART6 clock enable
    per_bit_n2_t Apb2enrBit6; ///< Reserved
    per_rcc_en1_t Adc1en; ///< ADC1 clock enable
    per_rcc_en1_t Adc2en; ///< ADC2 clock enable
    per_rcc_en1_t Adc3en; ///< ADC3 clock enable
    per_rcc_en1_t Sdioen; ///< SDIO clock enable
    per_rcc_en1_t Spi1en; ///< SPI1 clock enable
    per_rcc_en1_t Spi4en; ///< SPI4 clock enable
    per_rcc_en1_t Syscfgen; ///< SYSCFGEN clock enable
    per_bit_n1_t Apb2enrBit15; ///< Reserved
    per_rcc_en1_t Tim9en; ///< TIM9 clock enable
    per_rcc_en1_t Tim10en; ///< TIM10 clock enable
    per_rcc_en1_t Tim11en; ///< TIM11 clock enable
    per_bit_n1_t Apb2enrBit19; ///< Reserved
    per_rcc_en1_t Spi5en; ///< SPI5 clock enable
    per_rcc_en1_t Spi6en; ///< SPI6 clock enable
    per_rcc_en1_t Sai1en; ///< SAI1 clock enable
    per_bit_n3_t Apb2enrBit23; ///< Reserved
    per_rcc_en1_t Ltdcen; ///< LTDC clock enable
    per_bit_n5_t Apb2enrBit27; ///< Reserved

    per_bit_n32_t Reserved_0x48; ///< Reserved
    per_bit_n32_t Reserved_0x4C; ///< Reserved

    // RCC AHB1 peripheral clock enable in low power mode register (RCC_AHB1LPENR)
    per_rcc_en1_t Gpioalpen; ///< IO port A clock enable during Sleep mode
    per_rcc_en1_t Gpioblpen; ///< IO port B clock enable during Sleep mode
    per_rcc_en1_t Gpioclpen; ///< IO port C clock enable during Sleep mode
    per_rcc_en1_t Gpiodlpen; ///< IO port D clock enable during Sleep mode
    per_rcc_en1_t Gpioelpen; ///< IO port E clock enable during Sleep mode
    per_rcc_en1_t Gpioflpen; ///< IO port F clock enable during Sleep mode
    per_rcc_en1_t Gpioglpen; ///< IO port G clock enable during Sleep mode
    per_rcc_en1_t Gpiohlpen; ///< IO port H clock enable during Sleep mode
    per_rcc_en1_t Gpioilpen; ///< IO port I clock enable during Sleep mode
    per_rcc_en1_t Gpiojlpen; ///< IO port J clock enable during Sleep mode
    per_rcc_en1_t Gpioklpen; ///< IO port K clock enable during Sleep mode
    per_bit_n1_t Ahb1lpenrBit11; ///< Reserved.
    per_rcc_en1_t Crclpen; ///< CRC clock enable during Sleep mode
    per_bit_n2_t Ahb1lpenrBit13; ///< Reserved.
    per_rcc_en1_t Flitflpen; ///< Flash interface clock enable during Sleep mode
    per_rcc_en1_t Sram1lpen; ///< SRAM 1 interface clock enable during Sleep mode
    per_rcc_en1_t Sram2lpen; ///< SRAM 2 interface clock enable during Sleep mode
    per_rcc_en1_t Bkpsramlpen; ///< Backup SRAM interface clock enable during Sleep mode
    per_rcc_en1_t Sram3lpen; ///< SRAM 3 interface clock enable during Sleep mode
    per_bit_n1_t Ahb1lpenrBit20; ///< Reserved
    per_rcc_en1_t Dma1lpen; ///< DMA1 clock enable during Sleep mode
    per_rcc_en1_t Dma2lpen; ///< DMA2 clock enable during Sleep mode
    per_rcc_en1_t Dma2dlpen; ///< DMA2D clock enable during Sleep mode
    per_bit_n1_t Ahb1lpenrBit24; ///< Reserved
    per_rcc_en1_t Ethmaclpen; ///< Ethernet MAC clock enable during Sleep mode
    per_rcc_en1_t Ethmactxlpen; ///< Ethernet Transmission clock enable during Sleep mode
    per_rcc_en1_t Ethmacrxlpen; ///< Ethernet Reception clock enable during Sleep mode
    per_rcc_en1_t Ethmacptplpen; ///< Ethernet PTP clock enable during Sleep mode
    per_rcc_en1_t Otghslpen; ///< USB OTG HS clock enable during Sleep mode
    per_rcc_en1_t Otghsulpilpen; ///< USB OTG HSULPI clock enable during Sleep mode
    per_bit_n1_t Ahb1lpenrBit31; ///< Reserved

    // RCC AHB2 peripheral clock enable in low power mode register (RCC_AHB2LPENR)
    per_rcc_en1_t Dcmilpen; ///< Camera interface clock enable during Sleep mode
    per_bit_n3_t Ahb2lpenrBit1; ///< Reserved.
    per_rcc_en1_t Cryplpen; ///< Cryptographic modules clock enable during Sleep mode
    per_rcc_en1_t Hashlpen; ///< Hash modules clock enable during Sleep mode
    per_rcc_en1_t Rnglpen; ///< Random number generator clock enable during Sleep mode
    per_rcc_en1_t Otgfslpen; ///< USB OTG FS clock enable during Sleep mode
    per_bit_n24_t Ahb2lpenrBit8; ///< Reserved.

    // RCC AHB3 peripheral clock enable in low power mode register (RCC_AHB3LPENR)
    per_rcc_en1_t Fmclpen; ///< Flexible memory controller module clock enable during Sleep mode
    per_bit_n31_t Ahb3lpenrBit1; ///< Reserved.

    per_bit_n32_t Reserved_0x5C; ///< Reserved

    // RCC APB1 peripheral clock enable in low power mode register (RCC_APB1LPENR)
    per_rcc_en1_t Tim2lpen; ///< TIM2 clock enable during Sleep mode
    per_rcc_en1_t Tim3lpen; ///< TIM3 clock enable during Sleep mode
    per_rcc_en1_t Tim4lpen; ///< TIM4 clock enable during Sleep mode
    per_rcc_en1_t Tim5lpen; ///< TIM5 clock enable during Sleep mode
    per_rcc_en1_t Tim6lpen; ///< TIM6 clock enable during Sleep mode
    per_rcc_en1_t Tim7lpen; ///< TIM7 clock enable during Sleep mode
    per_rcc_en1_t Tim12lpen; ///< TIM12 clock enable during Sleep mode
    per_rcc_en1_t Tim13lpen; ///< TIM13 clock enable during Sleep mode
    per_rcc_en1_t Tim14lpen; ///< TIM14 clock enable during Sleep mode
    per_bit_n2_t Apb1lpenrBit9; ///< Reserved
    per_rcc_en1_t Wwdglpen; ///< Window watchdog clock enable during Sleep mode
    per_bit_n2_t Apb1lpenrBit12; ///< Reserved
    per_rcc_en1_t Spi2lpen; ///< SPI2 clock enable during Sleep mode
    per_rcc_en1_t Spi3lpen; ///< SPI3 clock enable during Sleep mode
    per_bit_n1_t Apb1lpenrBit16; ///< Reserved
    per_rcc_en1_t Usart2lpen; ///< USART2 clock enable during Sleep mode
    per_rcc_en1_t Usart3lpen; ///< USART3 clock enable during Sleep mode
    per_rcc_en1_t Uart4lpen; ///< UART4 clock enable during Sleep mode
    per_rcc_en1_t Uart5lpen; ///< UART5 clock enable during Sleep mode
    per_rcc_en1_t I2c1lpen; ///< I2C1 clock enable during Sleep mode
    per_rcc_en1_t I2c2lpen; ///< I2C2 clock enable during Sleep mode
    per_rcc_en1_t I2c3lpen; ///< I2C3 clock enable during Sleep mode
    per_bit_n1_t Apb1lpenrBit24; ///< Reserved
    per_rcc_en1_t Can1lpen; ///< CAN1 clock enable during Sleep mode
    per_rcc_en1_t Can2lpen; ///< CAN2 clock enable during Sleep mode
    per_bit_n1_t Apb1lpenrBit27; ///< Reserved
    per_rcc_en1_t Pwrlpen; ///< Power interface clock enable during Sleep mode
    per_rcc_en1_t Daclpen; ///< DAC interface clock enable during Sleep mode
    per_rcc_en1_t Uart7lpen; ///< UART7 clock enable during Sleep mode
    per_rcc_en1_t Uart8lpen; ///< UART8 clock enable during Sleep mode

    // RCC APB2 peripheral clock enabled in low power mode register (RCC_APB2LPENR)
    per_rcc_en1_t Tim1lpen; ///< TIM1 clock enable during Sleep mode
    per_rcc_en1_t Tim8lpen; ///< TIM8 clock enable during Sleep mode
    per_bit_n2_t Apb2lpenrBit2; ///< Reserved
    per_rcc_en1_t Usart1lpen; ///< USART1 clock enable during Sleep mode
    per_rcc_en1_t Usart6lpen; ///< USART6 clock enable during Sleep mode
    per_bit_n2_t Apb2lpenrBit6; ///< Reserved
    per_rcc_en1_t Adc1lpen; ///< ADC1 clock enable during Sleep mode
    per_rcc_en1_t Adc2lpen; ///< ADC2 clock enable during Sleep mode
    per_rcc_en1_t Adc3lpen; ///< ADC3 clock enable during Sleep mode
    per_rcc_en1_t Sdiolpen; ///< SDIO clock enable during Sleep mode
    per_rcc_en1_t Spi1lpen; ///< SPI1 clock enable during Sleep mode
    per_rcc_en1_t Spi4lpen; ///< SPI4 clock enable during Sleep mode
    per_rcc_en1_t Syscfglpen; ///< SYSCFGEN clock enable during Sleep mode
    per_bit_n1_t Apb2lpenrBit15; ///< Reserved
    per_rcc_en1_t Tim9lpen; ///< TIM9 clock enable during Sleep mode
    per_rcc_en1_t Tim10lpen; ///< TIM10 clock enable during Sleep mode
    per_rcc_en1_t Tim11lpen; ///< TIM11 clock enable during Sleep mode
    per_bit_n1_t Apb2lpenrBit19; ///< Reserved
    per_rcc_en1_t Spi5lpen; ///< SPI5 clock enable during Sleep mode
    per_rcc_en1_t Spi6lpen; ///< SPI6 clock enable during Sleep mode
    per_rcc_en1_t Sai1lpen; ///< SAI1 clock enable during Sleep mode
    per_bit_n3_t Apb2lpenrBit23; ///< Reserved
    per_rcc_en1_t Ltdclpen; ///< LTDC clock enable during Sleep mode
    per_bit_n5_t Apb2lpenrBit27; ///< Reserved

    per_bit_n32_t Reserved_0x68; ///< Reserved
    per_bit_n32_t Reserved_0x6C; ///< Reserved

    // Backup domain control register (RCC_BDCR)
    per_bit_rw1_t Lseon; ///< Independent watchdog reset flag
    per_bit_r1_t Lserdy; ///< Window watchdog reset flag
    per_bit_rw1_t Lsebyp; ///< Low-power reset flag
    per_bit_n5_t BdcrBit3; ///< Reserved
    per_bit_rw2_t Rtsel; ///< RTC clock source selection
    per_bit_n5_t BdcrBit10; ///< Reserved
    per_bit_rw1_t Rtcen; ///< RTC clock enable
    per_bit_rw1_t Bdrst; ///< Backup domain software reset
    per_bit_n15_t BdcrBit17; ///< Reserved

    // clock control & status register (RCC_CSR)
    per_bit_rw1_t Lsion; ///< Internal low-speed oscillator enable
    per_bit_r1_t Lsirdy; ///< Internal low-speed oscillator ready
    per_bit_n22_t CsrBit2; ///< Reserved
    per_bit_rw1_t Rmvf; ///< Remove reset flag
    per_bit_r1_t Borrstf; ///< BOR reset flag
    per_bit_r1_t Pinrstf; ///< PIN reset flag
    per_bit_r1_t Porrstf; ///< POR/PDR reset flag
    per_bit_r1_t Sftrstf; ///< Software reset flag
    per_bit_r1_t Iwdgrstf; ///< Independent watchdog reset flag
    per_bit_r1_t Wwdgrstf; ///< Window watchdog reset flag
    per_bit_r1_t Lpwrrstf; ///< Low-power reset flag

    per_bit_n32_t Reserved_0x78; ///< Reserved
    per_bit_n32_t Reserved_0x7C; ///< Reserved

    // spread spectrum clock generation register (RCC_SSCGR)
    per_bit_rw13_t Modper; ///< Modulation period
    per_bit_rw15_t Incstep; ///< Incrementation step
    per_bit_n2_t SscgrBit28; ///< Reserved
    per_bit_rw1_t Spreadsel; ///< Spread Select
    per_bit_rw1_t Sscgen; ///< Spread spectrum modulation enable

    // PLLI2S configuration register (RCC_PLLI2SCFGR)
    per_bit_n6_t Plli2scfgrBit0; ///< Reserved
    per_bit_rw9_t Plli2sn; ///< PLLI2S multiplication factor for VCO
    per_bit_n9_t Plli2scfgrBit15; ///< Reserved
    per_bit_rw4_t Plli2sq; ///< PLLI2S division factor for SAI1 clock
    per_bit_rw3_t Plli2sr; ///< PLLI2S division factor for I2S clocks
    per_bit_n1_t Plli2scfgrBit31; ///< Reserved

    // PLLSAI configuration register (RCC_PLLSAICFGR)
    per_bit_n6_t PllsaicfgrBit0; ///< Reserved
    per_bit_rw9_t Pllisain; ///< PLLSAI division factor for VCO
    per_bit_n9_t PllsaicfgrBit15; ///< Reserved
    per_bit_rw4_t Pllsaiq; ///< PLLSAI division factor for SAI1 clock
    per_bit_rw3_t Pllsair; ///< PLLSAI division factor for LCD clock
    per_bit_n1_t PllsaicfgrBit31; ///< Reserved

    // DCKCFGR Dedicated Clock Configuration Register (RCC_DCKCFGR)
    per_bit_rw5_t Plli2sdivq; ///< PLLI2S division factor for SAI1 clock
    per_bit_n3_t DckcfgrBit5; ///< Reserved
    per_bit_rw5_t Pllsaidivq; ///< PLLSAI division factor for SAI1 clock
    per_bit_n3_t DckcfgrBit13; ///< Reserved
    per_bit_rw2_t Pllsaidivr; ///< division factor for LCD_CLK
    per_bit_n2_t DckcfgrBit18; ///< Reserved
    per_bit_rw2_t Sai1asrc; ///< SAI1-A clock source selection
    per_bit_rw2_t Sai1bsrc; ///< SAI1-B clock source selection
    per_bit_rw1_t Timpre; ///< Timers clocks prescalers selection
    per_bit_n7_t DckcfgrBit25; ///< Reserved
} __attribute__((packed)) per_rcc_per_t;

/// RCC descriptor
typedef struct
{
    per_rcc_per_t* const Per;     ///< Peripheral
    const per_log_e Err;          ///< Peripheral error number
    const per_rcc_adc_e Adc;      ///< Number of ADC peripherals
    const per_rcc_can_e Can;      ///< Number of CAN peripherals
    const per_rcc_i2c_e I2c;      ///< Number of I2C peripherals
    const per_rcc_i2s_e I2s;      ///< Number of I2S peripherals
    const per_rcc_gpio_e Gpio;    ///< Number of GPIO ports
    const per_rcc_spi_e Spi;      ///< Number of SPI peripherals
    const per_rcc_uart_e Uart;    ///< Number of UART peripherals
    const per_rcc_usart_e Usart;  ///< Number of USART peripherals
    const bool Eth;               ///< Ethernet present
} per_rcc_t;

/// RCC Internal high-speed clock enable
static per_inline bool per_rcc_hsion(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Hsion);
}

/// RCC Internal high-speed clock enable
static per_inline void per_rcc_set_hsion(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Hsion, val);
}

/// RCC Internal high-speed clock ready flag
static per_inline bool per_rcc_hsirdy(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Hsirdy);
}

/// RCC Internal high-speed clock trimming
static per_inline uint_fast16_t per_rcc_hsitrim(const per_rcc_t* const rcc)
{
    return per_bit_rw5(&rcc->Per->Hsitrim);
}

/// RCC Internal high-speed clock trimming
static per_inline bool per_rcc_set_hsitrim(const per_rcc_t* const rcc, uint_fast16_t val)
{
    return per_bit_rw5_set(&rcc->Per->Hsitrim, val);
}

/// RCC Internal high-speed clock calibration
static per_inline uint_fast16_t per_rcc_hsical(const per_rcc_t* const rcc)
{
    return per_bit_r8(&rcc->Per->Hsical);
}

/// RCC HSE clock enable
static per_inline bool per_rcc_hseon(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Hseon);
}

/// RCC HSE clock enable
static per_inline void per_rcc_set_hseon(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Hseon, val);
}

/// RCC HSE clock ready flag
static per_inline bool per_rcc_hserdy(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Hserdy);
}

/// RCC HSE clock bypass
static per_inline bool per_rcc_hsebyp(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Hsebyp);
}

/// RCC HSE clock bypass
static per_inline void per_rcc_set_hsebyp(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Hsebyp, val);
}

/// RCC Clock security system enable
static per_inline bool per_rcc_csson(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Csson);
}

/// RCC Clock security system enable
static per_inline void per_rcc_set_csson(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Csson, val);
}

/// RCC Main PLL (PLL) enable
static per_inline bool per_rcc_pllon(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Pllon);
}

/// RCC Main PLL (PLL) enable
static per_inline void per_rcc_set_pllon(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Pllon, val);
}

/// RCC Main PLL (PLL) clock ready flag
static per_inline bool per_rcc_pllrdy(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Pllrdy);
}

/// RCC PLLI2S enable
static per_inline bool per_rcc_plli2son(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Plli2son);
}

/// RCC PLLI2S enable
static per_inline void per_rcc_set_plli2son(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Plli2son, val);
}

/// RCC PLLI2S clock ready flag
static per_inline bool per_rcc_plli2srdy(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Plli2srdy);
}

/// RCC PLLSAI enable
static per_inline bool per_rcc_pllsaion(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Pllsaion);
}

/// RCC PLLSAI enable
static per_inline void per_rcc_set_pllsaion(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Pllsaion, val);
}

/// RCC PLLSAI clock ready flag
static per_inline bool per_rcc_pllsairdy(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Pllsairdy);
}

/// RCC Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock
static per_inline uint_fast16_t per_rcc_pllm(const per_rcc_t* const rcc)
{
    return per_bit_rw6(&rcc->Per->Pllm);
}

/// RCC Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock
static per_inline bool per_rcc_set_pllm(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PLLM_MAX) ||
        (val < PER_RCC_PLL_MIN))
    {
        per_log_err(rcc->Err, PER_RCC_PLLM_ERR, val);
        return false;
    }

    return per_bit_rw6_set(&rcc->Per->Pllm, val);
}

/// RCC Main PLL (PLL) multiplication factor for VCO
static per_inline uint_fast16_t per_rcc_plln(const per_rcc_t* const rcc)
{
    return per_bit_rw9(&rcc->Per->Plln);
}

/// RCC Main PLL (PLL) multiplication factor for VCO
static per_inline bool per_rcc_set_plln(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PLLN_MAX) ||
        (val < PER_RCC_PLL_MIN))
    {
        per_log_err(rcc->Err, PER_RCC_PLLN_ERR, val);
        return false;
    }

    return per_bit_rw9_set(&rcc->Per->Plln, val);
}

/// RCC Main PLL (PLL) division factor for main system clock
static per_inline uint_fast16_t per_rcc_pllp(const per_rcc_t* const rcc)
{
    return (uint_fast16_t)((per_bit_rw2(&rcc->Per->Pllp) + 1) << 1);
}

/// RCC Main PLL (PLL) division factor for main system clock
static per_inline bool per_rcc_set_pllp(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PLLP_MAX) ||
        (val < PER_RCC_PLL_MIN) ||
        ((val & 0b01) != 0)) // odd
    {
        per_log_err(rcc->Err, PER_RCC_PLLP_ERR, val);
        return false;
    }

    return per_bit_rw2_set(&rcc->Per->Pllp, (val >> 1) - 1);
}

/// RCC Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
static per_inline bool per_rcc_pllscr(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Pllscr);
}

/// RCC Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
static per_inline void per_rcc_set_pllscr(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Pllscr, val);
}

/// RCC Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks
static per_inline uint_fast16_t per_rcc_pllq(const per_rcc_t* const rcc)
{
    return per_bit_rw4(&rcc->Per->Pllq);
}

/// RCC Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks
static per_inline bool per_rcc_set_pllq(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PLLQ_MAX) ||
        (val < PER_RCC_PLL_MIN))
    {
        per_log_err(rcc->Err, PER_RCC_PLLQ_ERR, val);
        return false;
    }

    return per_bit_rw4_set(&rcc->Per->Pllq, val);
}

/// RCC System clock switch
static per_inline per_rcc_sw_e per_rcc_sw(const per_rcc_t* const rcc)
{
    return (per_rcc_sw_e)per_bit_rw2(&rcc->Per->Sw);
}

/// RCC System clock switch
static per_inline void per_rcc_set_sw(const per_rcc_t* const rcc, per_rcc_sw_e val)
{
    per_bit_rw2_set(&rcc->Per->Sw, (uint_fast16_t)val);
}

/// RCC System clock switch status
static per_inline per_rcc_sw_e per_rcc_sws(const per_rcc_t* const rcc)
{
    return (per_rcc_sw_e)per_bit_r2(&rcc->Per->Sws);
}

/// RCC AHB prescaler
static per_inline uint_fast16_t per_rcc_hpre(const per_rcc_t* const rcc)
{
    uint_fast16_t hpre = per_bit_rw4(&rcc->Per->Hpre.Pre);
    uint_fast16_t val = 1;

    if ((hpre & PER_RCC_HPRE_MSB) != 0) // highest bit
    {
        val = (uint_fast16_t)per_bit_inv_log2(hpre & ~PER_RCC_HPRE_MSB); // inverse log of lowest three bits

        val <<= 1; // multiply by 2

        if (val >= PER_RCC_HPRE_INV)
        {
            val <<= 1; // multiply by 2
        }
    }

    return val;
}

/// RCC AHB prescaler
static per_inline bool per_rcc_set_hpre(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_HPRE_MAX) ||
        (val == PER_RCC_HPRE_INV) ||
        !per_bit_is_log2(val))
    {
        per_log_err(rcc->Err, PER_RCC_HPRE_ERR, val);
        return false;
    }

    uint_fast16_t hpre = 0; // one

    if (val > 1)
    {
        val >>= 1; // divide by 2

        if (val > PER_RCC_HPRE_INV)
        {
            val >>= 1; // divide by 2
        }

        hpre = PER_RCC_HPRE_MSB | per_bit_log2(val);
    }

    per_bit_w1_set(&rcc->Per->Hpre.Msb, true); // Set this to prevent temporary illegal values during the next write

    return per_bit_rw4_set(&rcc->Per->Hpre.Pre, hpre);
}

/// RCC APB Low speed prescaler (APB1)
static per_inline uint_fast16_t per_rcc_ppre1(const per_rcc_t* const rcc)
{
    uint_fast16_t pre = per_bit_rw3(&rcc->Per->Ppre1.Pre);
    uint_fast16_t val = 1;

    if ((pre & PER_RCC_PPRE_MSB) != 0) // highest bit
    {
        val = (uint_fast16_t)per_bit_inv_log2(pre & ~PER_RCC_PPRE_MSB); // inverse log of lowest two bits

        val <<= 1; // multiply by 2
    }

    return val;
}

/// RCC APB Low speed prescaler (APB1)
static per_inline bool per_rcc_set_ppre1(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PPRE_MAX) ||
        !per_bit_is_log2(val))
    {
        per_log_err(rcc->Err, PER_RCC_PPRE1_ERR, val);
        return false;
    }

    uint_fast16_t pre = 0; // one

    if (val > 1)
    {
        val >>= 1; // divide by 2

        pre = PER_RCC_PPRE_MSB | per_bit_log2(val);
    }

    per_bit_w1_set(&rcc->Per->Ppre2.Msb, true); // Set this to prevent temporary illegal values during the next write

    return per_bit_rw3_set(&rcc->Per->Ppre2.Pre, pre);
}

/// RCC APB high-speed prescaler (APB2)
static per_inline uint_fast16_t per_rcc_ppre2(const per_rcc_t* const rcc)
{
    uint_fast16_t pre = per_bit_rw3(&rcc->Per->Ppre2.Pre);
    uint_fast16_t val = 1;

    if ((pre & PER_RCC_PPRE_MSB) != 0) // highest bit
    {
        val = (uint_fast16_t)per_bit_inv_log2(pre & ~PER_RCC_PPRE_MSB); // inverse log of lowest two bits

        val <<= 1; // multiply by 2
    }

    return val;
}

/// RCC APB high-speed prescaler (APB2)
static per_inline bool per_rcc_set_ppre2(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PPRE_MAX) ||
        !per_bit_is_log2(val))
    {
        per_log_err(rcc->Err, PER_RCC_PPRE2_ERR, val);
        return false;
    }

    uint_fast16_t pre = 0; // one

    if (val > 1)
    {
        val >>= 1; // divide by 2

        pre = PER_RCC_PPRE_MSB | per_bit_log2(val);
    }

    per_bit_w1_set(&rcc->Per->Ppre2.Msb, true); // Set this to prevent temporary illegal values during the next write

    return per_bit_rw3_set(&rcc->Per->Ppre2.Pre, pre);
}

/// RCC HSE division factor for RTC clock
static per_inline uint_fast16_t per_rcc_rtcpre(const per_rcc_t* const rcc)
{
    return per_bit_rw5(&rcc->Per->Rtcpre);
}

/// RCC HSE division factor for RTC clock
static per_inline bool per_rcc_set_rtcpre(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_RTCPRE_MAX) ||
        (val < PER_RCC_RTCPRE_MIN))
    {
        per_log_err(rcc->Err, PER_RCC_RTCPRE_ERR, val);
        return false;
    }

    per_bit_rw5_set(&rcc->Per->Rtcpre, val);
}

/// RCC Microcontroller clock output 1
static per_inline per_rcc_mco_1_e per_rcc_mco1(const per_rcc_t* const rcc)
{
    return (per_rcc_mco_1_e)per_bit_rw2(&rcc->Per->Mco1);
}

/// RCC Microcontroller clock output 1
static per_inline bool per_rcc_set_mco1(const per_rcc_t* const rcc, per_rcc_mco_1_e val)
{
    return per_bit_rw2_set(&rcc->Per->Mco1, (uint_fast16_t)val);
}

/// RCC I2S clock selection
static per_inline bool per_rcc_i2sscr(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->I2sscr);
}

/// RCC I2S clock selection
static per_inline void per_rcc_set_i2sscr(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->I2sscr, val);
}

/// RCC MCO1 prescaler
static per_inline uint_fast16_t per_rcc_mco1pre(const per_rcc_t* const rcc)
{
    uint_fast16_t pre = per_bit_rw3(&rcc->Per->Mco1pre.Pre);
    uint_fast16_t val = 1;

    if ((pre & PER_RCC_MCO_MSB) != 0) // highest bit
    {
        val += (pre & ~PER_RCC_MCO_MSB) + 1;
    }

    return val;
}

/// RCC MCO1 prescaler
static per_inline bool per_rcc_set_mco1pre(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_MCO_MAX) ||
        (val == 0))
    {
        per_log_err(rcc->Err, PER_RCC_MCO1PRE_ERR, val);
        return false;
    }

    uint_fast16_t pre = 0; // one

    if (val > 1)
    {
        pre = PER_RCC_MCO_MSB | (val - PER_RCC_MCO_BASE);
    }

    per_bit_w1_set(&rcc->Per->Mco1pre.Msb, true); // Set this to prevent temporary illegal values during the next write

    return per_bit_rw3_set(&rcc->Per->Mco1pre.Pre, pre);
}

/// RCC MCO2 prescaler
static per_inline uint_fast16_t per_rcc_mco2pre(const per_rcc_t* const rcc)
{
    uint_fast16_t pre = per_bit_rw3(&rcc->Per->Mco2pre.Pre);
    uint_fast16_t val = 1;

    if ((pre & PER_RCC_MCO_MSB) != 0) // highest bit
    {
        val += (pre & ~PER_RCC_MCO_MSB) + 1;
    }

    return val;
}

/// RCC MCO2 prescaler
static per_inline bool per_rcc_set_mco2pre(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_MCO_MAX) ||
        (val == 0))
    {
        per_log_err(rcc->Err, PER_RCC_MCO2PRE_ERR, val);
        return false;
    }

    uint_fast16_t pre = 0; // one

    if (val > 1)
    {
        pre = PER_RCC_MCO_MSB | (val - PER_RCC_MCO_BASE);
    }

    per_bit_w1_set(&rcc->Per->Mco2pre.Msb, true); // Set this to prevent temporary illegal values during the next write

    return per_bit_rw3_set(&rcc->Per->Mco2pre.Pre, pre);
}

/// RCC Microcontroller clock output 2
static per_inline per_rcc_mco_2_e per_rcc_mco2(const per_rcc_t* const rcc)
{
    return (per_rcc_mco_2_e)per_bit_rw2(&rcc->Per->Mco2);
}

/// RCC Microcontroller clock output 2
static per_inline bool per_rcc_set_mco2(const per_rcc_t* const rcc, per_rcc_mco_2_e val)
{
    return per_bit_rw2_set(&rcc->Per->Mco2, (uint_fast16_t)val);
}

/// RCC LSI ready interrupt flag
static per_inline bool per_rcc_lsirdyf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Lsirdyf);
}

/// RCC LSE ready interrupt flag
static per_inline bool per_rcc_lserdyf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Lserdyf);
}

/// RCC HSI ready interrupt flag
static per_inline bool per_rcc_hsirdyf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Hsirdyf);
}

/// RCC HSE ready interrupt flag
static per_inline bool per_rcc_hserdyf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Hserdyf);
}

/// RCC Main PLL (PLL) ready interrupt flag
static per_inline bool per_rcc_pllrdyf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Pllrdyf);
}

/// RCC PLLI2S ready interrupt flag
static per_inline bool per_rcc_plli2srdyf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Plli2srdyf);
}

/// RCC PLLSAI Ready Interrupt flag
static per_inline bool per_rcc_pllsairdyf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Pllsairdyf);
}

/// RCC Clock security system interrupt flag
static per_inline bool per_rcc_cssf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Cssf);
}

/// RCC LSI ready interrupt enable
static per_inline bool per_rcc_lsirdyie(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Lsirdyie);
}

/// RCC LSI ready interrupt enable
static per_inline void per_rcc_set_lsirdyie(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Lsirdyie, val);
}
/// RCC LSE ready interrupt enable
static per_inline bool per_rcc_lserdyie(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Lserdyie);
}

/// RCC LSE ready interrupt enable
static per_inline void per_rcc_set_lserdyie(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Lserdyie, val);
}
/// RCC HSI ready interrupt enable
static per_inline bool per_rcc_hsirdyie(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Hsirdyie);
}

/// RCC HSI ready interrupt enable
static per_inline void per_rcc_set_hsirdyie(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Hsirdyie, val);
}
/// RCC HSE ready interrupt enable
static per_inline bool per_rcc_hserdyie(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Hserdyie);
}

/// RCC HSE ready interrupt enable
static per_inline void per_rcc_set_hserdyie(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Hserdyie, val);
}
/// RCC Main PLL (PLL) ready interrupt enable
static per_inline bool per_rcc_pllrdyie(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Pllrdyie);
}

/// RCC Main PLL (PLL) ready interrupt enable
static per_inline void per_rcc_set_pllrdyie(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Pllrdyie, val);
}
/// RCC PLLI2S ready interrupt enable
static per_inline bool per_rcc_plli2srdyie(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Plli2srdyie);
}

/// RCC PLLI2S ready interrupt enable
static per_inline void per_rcc_set_plli2srdyie(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Plli2srdyie, val);
}
/// RCC PLLSAI Ready Interrupt Enable
static per_inline bool per_rcc_pllsairdyie(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Pllsairdyie);
}

/// RCC PLLSAI Ready Interrupt Enable
static per_inline void per_rcc_set_pllsairdyie(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Pllsairdyie, val);
}

/// RCC LSI ready interrupt clear
static per_inline void per_rcc_set_lsirdyc(const per_rcc_t* const rcc, bool val)
{
    per_bit_w1_set(&rcc->Per->Lsirdyc, val);
}

/// RCC LSE ready interrupt clear
static per_inline void per_rcc_set_lserdyc(const per_rcc_t* const rcc, bool val)
{
    per_bit_w1_set(&rcc->Per->Lserdyc, val);
}

/// RCC HSI ready interrupt clear
static per_inline void per_rcc_set_hsirdyc(const per_rcc_t* const rcc, bool val)
{
    per_bit_w1_set(&rcc->Per->Hsirdyc, val);
}

/// RCC HSE ready interrupt clear
static per_inline void per_rcc_set_hserdyc(const per_rcc_t* const rcc, bool val)
{
    per_bit_w1_set(&rcc->Per->Hserdyc, val);
}

/// RCC Main PLL(PLL) ready interrupt clear
static per_inline void per_rcc_set_pllrdyc(const per_rcc_t* const rcc, bool val)
{
    per_bit_w1_set(&rcc->Per->Pllrdyc, val);
}

/// RCC PLLI2S ready interrupt clear
static per_inline void per_rcc_set_plli2srdyc(const per_rcc_t* const rcc, bool val)
{
    per_bit_w1_set(&rcc->Per->Plli2srdyc, val);
}

/// RCC PLLSAI Ready Interrupt Clear
static per_inline void per_rcc_set_pllsairdyc(const per_rcc_t* const rcc, bool val)
{
    per_bit_w1_set(&rcc->Per->Pllsairdyc, val);
}

/// RCC Clock security system interrupt clear
static per_inline void per_rcc_set_cssc(const per_rcc_t* const rcc, bool val)
{
    per_bit_w1_set(&rcc->Per->Cssc, val);
}

/// RCC IO port A clock reset
static per_inline bool per_rcc_gpioarst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Gpioarst);
}

/// RCC IO port A clock reset
static per_inline void per_rcc_set_gpioarst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Gpioarst, val);
}

/// RCC IO port B clock reset
static per_inline bool per_rcc_gpiobrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Gpiobrst);
}

/// RCC IO port B clock reset
static per_inline void per_rcc_set_gpiobrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Gpiobrst, val);
}

/// RCC IO port C clock reset
static per_inline bool per_rcc_gpiocrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Gpiocrst);
}

/// RCC IO port C clock reset
static per_inline void per_rcc_set_gpiocrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Gpiocrst, val);
}

/// RCC IO port D clock reset
static per_inline bool per_rcc_gpiodrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Gpiodrst);
}

/// RCC IO port D clock reset
static per_inline void per_rcc_set_gpiodrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Gpiodrst, val);
}

/// RCC IO port E clock reset
static per_inline bool per_rcc_gpioerst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Gpioerst);
}

/// RCC IO port E clock reset
static per_inline void per_rcc_set_gpioerst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Gpioerst, val);
}

/// RCC IO port F clock reset
static per_inline bool per_rcc_gpiofrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Gpiofrst);
}

/// RCC IO port F clock reset
static per_inline void per_rcc_set_gpiofrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Gpiofrst, val);
}

/// RCC IO port G clock reset
static per_inline bool per_rcc_gpiogrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Gpiogrst);
}

/// RCC IO port G clock reset
static per_inline void per_rcc_set_gpiogrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Gpiogrst, val);
}

/// RCC IO port H clock reset
static per_inline bool per_rcc_gpiohrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Gpiohrst);
}

/// RCC IO port H clock reset
static per_inline void per_rcc_set_gpiohrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Gpiohrst, val);
}

/// RCC IO port I clock reset
static per_inline bool per_rcc_gpioirst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Gpioirst);
}

/// RCC IO port I clock reset
static per_inline void per_rcc_set_gpioirst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Gpioirst, val);
}

/// RCC IO port J clock reset
static per_inline bool per_rcc_gpiojrst(const per_rcc_t* const rcc)
{
    if (rcc->Gpio < PER_RCC_GPIO_J)
    {
        per_log_err_function_not_supported();
    }

    return per_bit_rw1(&rcc->Per->Gpiojrst);
}

/// RCC IO port J clock reset
static per_inline void per_rcc_set_gpiojrst(const per_rcc_t* const rcc, bool val)
{
    if (rcc->Gpio < PER_RCC_GPIO_J)
    {
        per_log_err_function_not_supported();
    }

    per_bit_rw1_set(&rcc->Per->Gpiojrst, val);
}

/// RCC IO port K clock reset
static per_inline bool per_rcc_gpiokrst(const per_rcc_t* const rcc)
{
    if (rcc->Gpio < PER_RCC_GPIO_K)
    {
        per_log_err_function_not_supported();
    }

    return per_bit_rw1(&rcc->Per->Gpiokrst);
}

/// RCC IO port K clock reset
static per_inline void per_rcc_set_gpiokrst(const per_rcc_t* const rcc, bool val)
{
    if (rcc->Gpio < PER_RCC_GPIO_K)
    {
        per_log_err_function_not_supported();
    }

    per_bit_rw1_set(&rcc->Per->Gpiokrst, val);
}

/// RCC CRC clock reset
static per_inline bool per_rcc_crcrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Crcrst);
}

/// RCC CRC clock reset
static per_inline void per_rcc_set_crcrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Crcrst, val);
}

/// RCC DMA1 clock reset
static per_inline bool per_rcc_dma1rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Dma1rst);
}

/// RCC DMA1 clock reset
static per_inline void per_rcc_set_dma1rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Dma1rst, val);
}

/// RCC DMA2 clock reset
static per_inline bool per_rcc_dma2rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Dma2rst);
}

/// RCC DMA2 clock reset
static per_inline void per_rcc_set_dma2rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Dma2rst, val);
}

/// RCC DMA2D clock reset
static per_inline bool per_rcc_dma2drst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Dma2drst);
}

/// RCC DMA2D clock reset
static per_inline void per_rcc_set_dma2drst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Dma2drst, val);
}

/// RCC Ethernet MAC clock reset
static per_inline bool per_rcc_ethmacrst(const per_rcc_t* const rcc)
{
    if (!rcc->Eth)
    {
        per_log_err_function_not_supported();
    }

    return per_bit_rw1(&rcc->Per->Ethmacrst);
}

/// RCC Ethernet MAC clock reset
static per_inline void per_rcc_set_ethmacrst(const per_rcc_t* const rcc, bool val)
{
    if (!rcc->Eth)
    {
        per_log_err_function_not_supported();
    }

    per_bit_rw1_set(&rcc->Per->Ethmacrst, val);
}

/// RCC USB OTG HS clock reset
static per_inline bool per_rcc_otghsrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Otghsrst);
}

/// RCC USB OTG HS clock reset
static per_inline void per_rcc_set_otghsrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Otghsrst, val);
}

/// RCC Camera interface reset
static per_inline bool per_rcc_dcmirst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Dcmirst);
}

/// RCC Camera interface reset
static per_inline void per_rcc_set_dcmirst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Dcmirst, val);
}

/// RCC Cryptographic modules clock reset
static per_inline bool per_rcc_cryprst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Cryprst);
}

/// RCC Cryptographic modules clock reset
static per_inline void per_rcc_set_cryprst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Cryprst, val);
}

/// RCC Hash modules clock reset
static per_inline bool per_rcc_hashrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Hashrst);
}

/// RCC Hash modules clock reset
static per_inline void per_rcc_set_hashrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Hashrst, val);
}

/// RCC Random number generator clock reset
static per_inline bool per_rcc_rngrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Rngrst);
}

/// RCC Random number generator clock reset
static per_inline void per_rcc_set_rngrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Rngrst, val);
}

/// RCC USB OTG FS clock reset
static per_inline bool per_rcc_otgfsrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Otgfsrst);
}

/// RCC USB OTG FS clock reset
static per_inline void per_rcc_set_otgfsrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Otgfsrst, val);
}

/// RCC Flexible memory controller module clock reset
static per_inline bool per_rcc_fmcrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Fmcrst);
}

/// RCC Flexible memory controller module clock reset
static per_inline void per_rcc_set_fmcrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Fmcrst, val);
}

/// RCC TIM2 clock reset
static per_inline bool per_rcc_tim2rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim2rst);
}

/// RCC TIM2 clock reset
static per_inline void per_rcc_set_tim2rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim2rst, val);
}

/// RCC TIM3 clock reset
static per_inline bool per_rcc_tim3rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim3rst);
}

/// RCC TIM3 clock reset
static per_inline void per_rcc_set_tim3rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim3rst, val);
}
per_bit_rw1_t Tim4en; ///< TIM4 clock reset
/// RCC TIM4 clock reset
static per_inline bool per_rcc_tim4rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim4rst);
}

/// RCC TIM4 clock reset
static per_inline void per_rcc_set_tim4rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim4rst, val);
}

/// RCC TIM5 clock reset
static per_inline bool per_rcc_tim5rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim5rst);
}

/// RCC TIM5 clock reset
static per_inline void per_rcc_set_tim5rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim5rst, val);
}

/// RCC TIM6 clock reset
static per_inline bool per_rcc_tim6rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim6rst);
}

/// RCC TIM6 clock reset
static per_inline void per_rcc_set_tim6rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim6rst, val);
}

/// RCC TIM7 clock reset
static per_inline bool per_rcc_tim7rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim7rst);
}

/// RCC TIM7 clock reset
static per_inline void per_rcc_set_tim7rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim7rst, val);
}

/// RCC TIM12 clock reset
static per_inline bool per_rcc_tim12rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim12rst);
}

/// RCC TIM12 clock reset
static per_inline void per_rcc_set_tim12rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim12rst, val);
}

/// RCC TIM13 clock reset
static per_inline bool per_rcc_tim13rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim13rst);
}

/// RCC TIM13 clock reset
static per_inline void per_rcc_set_tim13rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim13rst, val);
}

/// RCC TIM14 clock reset
static per_inline bool per_rcc_tim14rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim14rst);
}

/// RCC TIM14 clock reset
static per_inline void per_rcc_set_tim14rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim14rst, val);
}

/// RCC Window watchdog clock reset
static per_inline bool per_rcc_wwdgrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Wwdgrst);
}

/// RCC Window watchdog clock reset
static per_inline void per_rcc_set_wwdgrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Wwdgrst, val);
}

/// RCC SPI2 clock reset
static per_inline bool per_rcc_spi2rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Spi2rst);
}

/// RCC SPI2 clock reset
static per_inline void per_rcc_set_spi2rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Spi2rst, val);
}

/// RCC SPI3 clock reset
static per_inline bool per_rcc_spi3rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Spi3rst);
}

/// RCC SPI3 clock reset
static per_inline void per_rcc_set_spi3rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Spi3rst, val);
}

/// RCC USART2 clock reset
static per_inline bool per_rcc_usart2rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Usart2rst);
}

/// RCC USART2 clock reset
static per_inline void per_rcc_set_usart2rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Usart2rst, val);
}

/// RCC USART3 clock reset
static per_inline bool per_rcc_usart3rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Usart3rst);
}

/// RCC USART3 clock reset
static per_inline void per_rcc_set_usart3rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Usart3rst, val);
}

/// RCC UART4 clock reset
static per_inline bool per_rcc_uart4rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Uart4rst);
}

/// RCC UART4 clock reset
static per_inline void per_rcc_set_uart4rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Uart4rst, val);
}

/// RCC UART5 clock reset
static per_inline bool per_rcc_uart5rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Uart5rst);
}

/// RCC UART5 clock reset
static per_inline void per_rcc_set_uart5rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Uart5rst, val);
}

/// RCC I2C1 clock reset
static per_inline bool per_rcc_i2c1rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->I2c1rst);
}

/// RCC I2C1 clock reset
static per_inline void per_rcc_set_i2c1rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->I2c1rst, val);
}

/// RCC I2C2 clock reset
static per_inline bool per_rcc_i2c2rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->I2c2rst);
}

/// RCC I2C2 clock reset
static per_inline void per_rcc_set_i2c2rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->I2c2rst, val);
}

/// RCC I2C3 clock reset
static per_inline bool per_rcc_i2c3rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->I2c3rst);
}

/// RCC I2C3 clock reset
static per_inline void per_rcc_set_i2c3rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->I2c3rst, val);
}

/// RCC CAN1 clock reset
static per_inline bool per_rcc_can1rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Can1rst);
}

/// RCC CAN1 clock reset
static per_inline void per_rcc_set_can1rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Can1rst, val);
}

/// RCC CAN2 clock reset
static per_inline bool per_rcc_can2rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Can2rst);
}

/// RCC CAN2 clock reset
static per_inline void per_rcc_set_can2rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Can2rst, val);
}

/// RCC Power interface clock reset
static per_inline bool per_rcc_pwrrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Pwrrst);
}

/// RCC Power interface clock reset
static per_inline void per_rcc_set_pwrrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Pwrrst, val);
}

/// RCC DAC interface clock reset
static per_inline bool per_rcc_dacrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Dacrst);
}

/// RCC DAC interface clock reset
static per_inline void per_rcc_set_dacrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Dacrst, val);
}

/// RCC UART7 clock reset
static per_inline bool per_rcc_uart7rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Uart7rst);
}

/// RCC UART7 clock reset
static per_inline void per_rcc_set_uart7rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Uart7rst, val);
}

/// RCC UART8 clock reset
static per_inline bool per_rcc_uart8rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Uart8rst);
}

/// RCC UART8 clock reset
static per_inline void per_rcc_set_uart8rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Uart8rst, val);
}

/// RCC TIM1 clock reset
static per_inline bool per_rcc_tim1rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim1rst);
}

/// RCC TIM1 clock reset
static per_inline void per_rcc_set_tim1rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim1rst, val);
}

/// RCC TIM8 clock reset
static per_inline bool per_rcc_tim8rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim8rst);
}

/// RCC TIM8 clock reset
static per_inline void per_rcc_set_tim8rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim8rst, val);
}

/// RCC USART1 clock reset
static per_inline bool per_rcc_usart1rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Usart1rst);
}

/// RCC USART1 clock reset
static per_inline void per_rcc_set_usart1rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Usart1rst, val);
}

/// RCC USART6 clock reset
static per_inline bool per_rcc_usart6rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Usart6rst);
}

/// RCC USART6 clock reset
static per_inline void per_rcc_set_usart6rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Usart6rst, val);
}

/// RCC ADC1 clock reset
static per_inline bool per_rcc_adcrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Adcrst);
}

/// RCC ADC1 clock reset
static per_inline void per_rcc_set_adcrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Adcrst, val);
}

/// RCC SDIO clock reset
static per_inline bool per_rcc_sdiorst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Sdiorst);
}

/// RCC SDIO clock reset
static per_inline void per_rcc_set_sdiorst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Sdiorst, val);
}

/// RCC SPI1 clock reset
static per_inline bool per_rcc_spi1rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Spi1rst);
}

/// RCC SPI1 clock reset
static per_inline void per_rcc_set_spi1rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Spi1rst, val);
}

/// RCC SPI4 clock reset
static per_inline bool per_rcc_spi4rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Spi4rst);
}

/// RCC SPI4 clock reset
static per_inline void per_rcc_set_spi4rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Spi4rst, val);
}

/// RCC SYSCFGEN clock reset
static per_inline bool per_rcc_syscfgrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Syscfgrst);
}

/// RCC SYSCFGEN clock reset
static per_inline void per_rcc_set_syscfgrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Syscfgrst, val);
}

/// RCC TIM9 clock reset
static per_inline bool per_rcc_tim9rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim9rst);
}

/// RCC TIM9 clock reset
static per_inline void per_rcc_set_tim9rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim9rst, val);
}

/// RCC TIM10 clock reset
static per_inline bool per_rcc_tim10rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim10rst);
}

/// RCC TIM10 clock reset
static per_inline void per_rcc_set_tim10rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim10rst, val);
}

/// RCC TIM11 clock reset
static per_inline bool per_rcc_tim11rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Tim11rst);
}

/// RCC TIM11 clock reset
static per_inline void per_rcc_set_tim11rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Tim11rst, val);
}

/// RCC SPI5 clock reset
static per_inline bool per_rcc_spi5rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Spi5rst);
}

/// RCC SPI5 clock reset
static per_inline void per_rcc_set_spi5rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Spi5rst, val);
}

/// RCC SPI6 clock reset
static per_inline bool per_rcc_spi6rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Spi6rst);
}

/// RCC SPI6 clock reset
static per_inline void per_rcc_set_spi6rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Spi6rst, val);
}

/// RCC SAI1 clock reset
static per_inline bool per_rcc_sai1rst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Sai1rst);
}

/// RCC SAI1 clock reset
static per_inline void per_rcc_set_sai1rst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Sai1rst, val);
}

/// RCC LTDC clock reset
static per_inline bool per_rcc_ltdcrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Ltdcrst);
}

/// RCC LTDC clock reset
static per_inline void per_rcc_set_ltdcrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Ltdcrst, val);
}

/// RCC IO port A clock enable
static per_inline bool per_rcc_gpioaen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpioaen);
}

/// RCC IO port A clock enable
static per_inline void per_rcc_set_gpioaen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpioaen, val);
}

/// RCC IO port B clock enable
static per_inline bool per_rcc_gpioben(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpioben);
}

/// RCC IO port B clock enable
static per_inline void per_rcc_set_gpioben(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpioben, val);
}

/// RCC IO port C clock enable
static per_inline bool per_rcc_gpiocen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpiocen);
}

/// RCC IO port C clock enable
static per_inline void per_rcc_set_gpiocen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpiocen, val);
}

/// RCC IO port D clock enable
static per_inline bool per_rcc_gpioden(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpioden);
}

/// RCC IO port D clock enable
static per_inline void per_rcc_set_gpioden(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpioden, val);
}

/// RCC IO port E clock enable
static per_inline bool per_rcc_gpioeen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpioeen);
}

/// RCC IO port E clock enable
static per_inline void per_rcc_set_gpioeen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpioeen, val);
}

/// RCC IO port F clock enable
static per_inline bool per_rcc_gpiofen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpiofen);
}

/// RCC IO port F clock enable
static per_inline void per_rcc_set_gpiofen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpiofen, val);
}

/// RCC IO port G clock enable
static per_inline bool per_rcc_gpiogen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpiogen);
}

/// RCC IO port G clock enable
static per_inline void per_rcc_set_gpiogen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpiogen, val);
}

/// RCC IO port H clock enable
static per_inline bool per_rcc_gpiohen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpiohen);
}

/// RCC IO port H clock enable
static per_inline void per_rcc_set_gpiohen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpiohen, val);
}

/// RCC IO port I clock enable
static per_inline bool per_rcc_gpioien(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpioien);
}

/// RCC IO port I clock enable
static per_inline void per_rcc_set_gpioien(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpioien, val);
}

/// RCC IO port J clock enable
static per_inline bool per_rcc_gpiojen(const per_rcc_t* const rcc)
{
    if (rcc->Gpio < PER_RCC_GPIO_J)
    {
        per_log_err_function_not_supported();
    }

    return per_rcc_en1(&rcc->Per->Gpiojen);
}

/// RCC IO port J clock enable
static per_inline void per_rcc_set_gpiojen(const per_rcc_t* const rcc, bool val)
{
    if (rcc->Gpio < PER_RCC_GPIO_J)
    {
        per_log_err_function_not_supported();
    }

    per_rcc_en1_set(&rcc->Per->Gpiojen, val);
}

/// RCC IO port K clock enable
static per_inline bool per_rcc_gpioken(const per_rcc_t* const rcc)
{
    if (rcc->Gpio < PER_RCC_GPIO_K)
    {
        per_log_err_function_not_supported();
    }

    return per_rcc_en1(&rcc->Per->Gpioken);
}

/// RCC IO port K clock enable
static per_inline void per_rcc_set_gpioken(const per_rcc_t* const rcc, bool val)
{
    if (rcc->Gpio < PER_RCC_GPIO_K)
    {
        per_log_err_function_not_supported();
    }

    per_rcc_en1_set(&rcc->Per->Gpioken, val);
}

/// RCC CRC clock enable
static per_inline bool per_rcc_crcen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Crcen);
}

/// RCC CRC clock enable
static per_inline void per_rcc_set_crcen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Crcen, val);
}

/// RCC Backup SRAM interface clock enable
static per_inline bool per_rcc_bkpsramen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Bkpsramen);
}

/// RCC Backup SRAM interface clock enable
static per_inline void per_rcc_set_bkpsramen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Bkpsramen, val);
}

/// RCC CCM data RAM clock enable
static per_inline bool per_rcc_ccmdataramen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Ccmdataramen);
}

/// RCC CCM data RAM clock enable
static per_inline void per_rcc_set_ccmdataramen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Ccmdataramen, val);
}

/// RCC DMA1 clock enable
static per_inline bool per_rcc_dma1en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Dma1en);
}

/// RCC DMA1 clock enable
static per_inline void per_rcc_set_dma1en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Dma1en, val);
}

/// RCC DMA2 clock enable
static per_inline bool per_rcc_dma2en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Dma2en);
}

/// RCC DMA2 clock enable
static per_inline void per_rcc_set_dma2en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Dma2en, val);
}

/// RCC DMA2D clock enable
static per_inline bool per_rcc_dma2den(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Dma2den);
}

/// RCC DMA2D clock enable
static per_inline void per_rcc_set_dma2den(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Dma2den, val);
}

/// RCC Ethernet MAC clock enable
static per_inline bool per_rcc_ethmacen(const per_rcc_t* const rcc)
{
    if (!rcc->Eth)
    {
        per_log_err_function_not_supported();
    }

    return per_rcc_en1(&rcc->Per->Ethmacen);
}

/// RCC Ethernet MAC clock enable
static per_inline void per_rcc_set_ethmacen(const per_rcc_t* const rcc, bool val)
{
    if (!rcc->Eth)
    {
        per_log_err_function_not_supported();
    }

    per_rcc_en1_set(&rcc->Per->Ethmacen, val);
}

/// RCC Ethernet Transmission clock enable
static per_inline bool per_rcc_ethmactxen(const per_rcc_t* const rcc)
{
    if (!rcc->Eth)
    {
        per_log_err_function_not_supported();
    }

    return per_rcc_en1(&rcc->Per->Ethmactxen);
}

/// RCC Ethernet Transmission clock enable
static per_inline void per_rcc_set_ethmactxen(const per_rcc_t* const rcc, bool val)
{
    if (!rcc->Eth)
    {
        per_log_err_function_not_supported();
    }

    per_rcc_en1_set(&rcc->Per->Ethmactxen, val);
}

/// RCC Ethernet Reception clock enable
static per_inline bool per_rcc_ethmacrxen(const per_rcc_t* const rcc)
{
    if (!rcc->Eth)
    {
        per_log_err_function_not_supported();
    }

    return per_rcc_en1(&rcc->Per->Ethmacrxen);
}

/// RCC Ethernet Reception clock enable
static per_inline void per_rcc_set_ethmacrxen(const per_rcc_t* const rcc, bool val)
{
    if (!rcc->Eth)
    {
        per_log_err_function_not_supported();
    }

    per_rcc_en1_set(&rcc->Per->Ethmacrxen, val);
}

/// RCC Ethernet PTP clock enable
static per_inline bool per_rcc_ethmacptpen(const per_rcc_t* const rcc)
{
    if (!rcc->Eth)
    {
        per_log_err_function_not_supported();
    }

    return per_rcc_en1(&rcc->Per->Ethmacptpen);
}

/// RCC Ethernet PTP clock enable
static per_inline void per_rcc_set_ethmacptpen(const per_rcc_t* const rcc, bool val)
{
    if (!rcc->Eth)
    {
        per_log_err_function_not_supported();
    }

    per_rcc_en1_set(&rcc->Per->Ethmacptpen, val);
}

/// RCC USB OTG HS clock enable
static per_inline bool per_rcc_otghsen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Otghsen);
}

/// RCC USB OTG HS clock enable
static per_inline void per_rcc_set_otghsen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Otghsen, val);
}

/// RCC USB OTG HSULPI clock enable
static per_inline bool per_rcc_otghsulpien(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Otghsulpien);
}

/// RCC USB OTG HSULPI clock enable
static per_inline void per_rcc_set_otghsulpien(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Otghsulpien, val);
}

/// RCC Camera interface enable
static per_inline bool per_rcc_dcmien(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Dcmien);
}

/// RCC Camera interface enable
static per_inline void per_rcc_set_dcmien(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Dcmien, val);
}

/// RCC Cryptographic modules clock enable
static per_inline bool per_rcc_crypen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Crypen);
}

/// RCC Cryptographic modules clock enable
static per_inline void per_rcc_set_crypen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Crypen, val);
}

/// RCC Hash modules clock enable
static per_inline bool per_rcc_hashen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Hashen);
}

/// RCC Hash modules clock enable
static per_inline void per_rcc_set_hashen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Hashen, val);
}

/// RCC Random number generator clock enable
static per_inline bool per_rcc_rngen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Rngen);
}

/// RCC Random number generator clock enable
static per_inline void per_rcc_set_rngen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Rngen, val);
}

/// RCC USB OTG FS clock enable
static per_inline bool per_rcc_otgfsen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Otgfsen);
}

/// RCC USB OTG FS clock enable
static per_inline void per_rcc_set_otgfsen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Otgfsen, val);
}

/// RCC Flexible memory controller module clock enable
static per_inline bool per_rcc_fmcen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Fmcen);
}

/// RCC Flexible memory controller module clock enable
static per_inline void per_rcc_set_fmcen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Fmcen, val);
}

/// RCC TIM2 clock enable
static per_inline bool per_rcc_tim2en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim2en);
}

/// RCC TIM2 clock enable
static per_inline void per_rcc_set_tim2en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim2en, val);
}

/// RCC TIM3 clock enable
static per_inline bool per_rcc_tim3en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim3en);
}

/// RCC TIM3 clock enable
static per_inline void per_rcc_set_tim3en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim3en, val);
}

/// RCC TIM4 clock enable
static per_inline bool per_rcc_tim4en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim4en);
}

/// RCC TIM4 clock enable
static per_inline void per_rcc_set_tim4en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim4en, val);
}

/// RCC TIM5 clock enable
static per_inline bool per_rcc_tim5en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim5en);
}

/// RCC TIM5 clock enable
static per_inline void per_rcc_set_tim5en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim5en, val);
}

/// RCC TIM6 clock enable
static per_inline bool per_rcc_tim6en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim6en);
}

/// RCC TIM6 clock enable
static per_inline void per_rcc_set_tim6en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim6en, val);
}

/// RCC TIM7 clock enable
static per_inline bool per_rcc_tim7en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim7en);
}

/// RCC TIM7 clock enable
static per_inline void per_rcc_set_tim7en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim7en, val);
}

/// RCC TIM12 clock enable
static per_inline bool per_rcc_tim12en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim12en);
}

/// RCC TIM12 clock enable
static per_inline void per_rcc_set_tim12en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim12en, val);
}

/// RCC TIM13 clock enable
static per_inline bool per_rcc_tim13en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim13en);
}

/// RCC TIM13 clock enable
static per_inline void per_rcc_set_tim13en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim13en, val);
}

/// RCC TIM14 clock enable
static per_inline bool per_rcc_tim14en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim14en);
}

/// RCC TIM14 clock enable
static per_inline void per_rcc_set_tim14en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim14en, val);
}

/// RCC Window watchdog clock enable
static per_inline bool per_rcc_wwdgen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Wwdgen);
}

/// RCC Window watchdog clock enable
static per_inline void per_rcc_set_wwdgen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Wwdgen, val);
}

/// RCC SPI2 clock enable
static per_inline bool per_rcc_spi2en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Spi2en);
}

/// RCC SPI2 clock enable
static per_inline void per_rcc_set_spi2en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Spi2en, val);
}

/// RCC SPI3 clock enable
static per_inline bool per_rcc_spi3en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Spi3en);
}

/// RCC SPI3 clock enable
static per_inline void per_rcc_set_spi3en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Spi3en, val);
}

/// RCC USART2 clock enable
static per_inline bool per_rcc_usart2en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Usart2en);
}

/// RCC USART2 clock enable
static per_inline void per_rcc_set_usart2en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Usart2en, val);
}

/// RCC USART3 clock enable
static per_inline bool per_rcc_usart3en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Usart3en);
}

/// RCC USART3 clock enable
static per_inline void per_rcc_set_usart3en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Usart3en, val);
}

/// RCC UART4 clock enable
static per_inline bool per_rcc_uart4en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Uart4en);
}

/// RCC UART4 clock enable
static per_inline void per_rcc_set_uart4en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Uart4en, val);
}

/// RCC UART5 clock enable
static per_inline bool per_rcc_uart5en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Uart5en);
}

/// RCC UART5 clock enable
static per_inline void per_rcc_set_uart5en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Uart5en, val);
}

/// RCC I2C1 clock enable
static per_inline bool per_rcc_i2c1en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->I2c1en);
}

/// RCC I2C1 clock enable
static per_inline void per_rcc_set_i2c1en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->I2c1en, val);
}

/// RCC I2C2 clock enable
static per_inline bool per_rcc_i2c2en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->I2c2en);
}

/// RCC I2C2 clock enable
static per_inline void per_rcc_set_i2c2en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->I2c2en, val);
}

/// RCC I2C3 clock enable
static per_inline bool per_rcc_i2c3en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->I2c3en);
}

/// RCC I2C3 clock enable
static per_inline void per_rcc_set_i2c3en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->I2c3en, val);
}

/// RCC CAN1 clock enable
static per_inline bool per_rcc_can1en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Can1en);
}

/// RCC CAN1 clock enable
static per_inline void per_rcc_set_can1en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Can1en, val);
}

/// RCC CAN2 clock enable
static per_inline bool per_rcc_can2en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Can2en);
}

/// RCC CAN2 clock enable
static per_inline void per_rcc_set_can2en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Can2en, val);
}

/// RCC Power interface clock enable
static per_inline bool per_rcc_pwren(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Pwren);
}

/// RCC Power interface clock enable
static per_inline void per_rcc_set_pwren(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Pwren, val);
}

/// RCC DAC interface clock enable
static per_inline bool per_rcc_dacen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Dacen);
}

/// RCC DAC interface clock enable
static per_inline void per_rcc_set_dacen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Dacen, val);
}

/// RCC UART7 clock enable
static per_inline bool per_rcc_uart7en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Uart7en);
}

/// RCC UART7 clock enable
static per_inline void per_rcc_set_uart7en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Uart7en, val);
}

/// RCC UART8 clock enable
static per_inline bool per_rcc_uart8en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Uart8en);
}

/// RCC UART8 clock enable
static per_inline void per_rcc_set_uart8en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Uart8en, val);
}

/// RCC TIM1 clock enable
static per_inline bool per_rcc_tim1en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim1en);
}

/// RCC TIM1 clock enable
static per_inline void per_rcc_set_tim1en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim1en, val);
}

/// RCC TIM8 clock enable
static per_inline bool per_rcc_tim8en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim8en);
}

/// RCC TIM8 clock enable
static per_inline void per_rcc_set_tim8en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim8en, val);
}

/// RCC USART1 clock enable
static per_inline bool per_rcc_usart1en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Usart1en);
}

/// RCC USART1 clock enable
static per_inline void per_rcc_set_usart1en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Usart1en, val);
}

/// RCC USART6 clock enable
static per_inline bool per_rcc_usart6en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Usart6en);
}

/// RCC USART6 clock enable
static per_inline void per_rcc_set_usart6en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Usart6en, val);
}

/// RCC ADC1 clock enable
static per_inline bool per_rcc_adc1en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Adc1en);
}

/// RCC ADC1 clock enable
static per_inline void per_rcc_set_adc1en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Adc1en, val);
}

/// RCC ADC2 clock enable
static per_inline bool per_rcc_adc2en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Adc2en);
}

/// RCC ADC2 clock enable
static per_inline void per_rcc_set_adc2en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Adc2en, val);
}

/// RCC ADC3 clock enable
static per_inline bool per_rcc_adc3en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Adc3en);
}

/// RCC ADC3 clock enable
static per_inline void per_rcc_set_adc3en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Adc3en, val);
}

/// RCC SDIO clock enable
static per_inline bool per_rcc_sdioen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Sdioen);
}

/// RCC SDIO clock enable
static per_inline void per_rcc_set_sdioen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Sdioen, val);
}

/// RCC SPI1 clock enable
static per_inline bool per_rcc_spi1en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Spi1en);
}

/// RCC SPI1 clock enable
static per_inline void per_rcc_set_spi1en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Spi1en, val);
}

/// RCC SPI4 clock enable
static per_inline bool per_rcc_spi4en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Spi4en);
}

/// RCC SPI4 clock enable
static per_inline void per_rcc_set_spi4en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Spi4en, val);
}

/// RCC SYSCFGEN clock enable
static per_inline bool per_rcc_syscfgen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Syscfgen);
}

/// RCC SYSCFGEN clock enable
static per_inline void per_rcc_set_syscfgen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Syscfgen, val);
}

/// RCC TIM9 clock enable
static per_inline bool per_rcc_tim9en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim9en);
}

/// RCC TIM9 clock enable
static per_inline void per_rcc_set_tim9en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim9en, val);
}

/// RCC TIM10 clock enable
static per_inline bool per_rcc_tim10en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim10en);
}

/// RCC TIM10 clock enable
static per_inline void per_rcc_set_tim10en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim10en, val);
}

/// RCC TIM11 clock enable
static per_inline bool per_rcc_tim11en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim11en);
}

/// RCC TIM11 clock enable
static per_inline void per_rcc_set_tim11en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim11en, val);
}

/// RCC SPI5 clock enable
static per_inline bool per_rcc_spi5en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Spi5en);
}

/// RCC SPI5 clock enable
static per_inline void per_rcc_set_spi5en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Spi5en, val);
}

/// RCC SPI6 clock enable
static per_inline bool per_rcc_spi6en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Spi6en);
}

/// RCC SPI6 clock enable
static per_inline void per_rcc_set_spi6en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Spi6en, val);
}

/// RCC SAI1 clock enable
static per_inline bool per_rcc_sai1en(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Sai1en);
}

/// RCC SAI1 clock enable
static per_inline void per_rcc_set_sai1en(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Sai1en, val);
}

/// RCC LTDC clock enable
static per_inline bool per_rcc_ltdcen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Ltdcen);
}

/// RCC LTDC clock enable
static per_inline void per_rcc_set_ltdcen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Ltdcen, val);
}

/// RCC IO port A clock enable during Sleep mode
static per_inline bool per_rcc_gpioalpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpioalpen);
}

/// RCC IO port A clock enable during Sleep mode
static per_inline void per_rcc_set_gpioalpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpioalpen, val);
}

/// RCC IO port B clock enable during Sleep mode
static per_inline bool per_rcc_gpioblpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpioblpen);
}

/// RCC IO port B clock enable during Sleep mode
static per_inline void per_rcc_set_gpioblpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpioblpen, val);
}

/// RCC IO port C clock enable during Sleep mode
static per_inline bool per_rcc_gpioclpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpioclpen);
}

/// RCC IO port C clock enable during Sleep mode
static per_inline void per_rcc_set_gpioclpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpioclpen, val);
}

/// RCC IO port D clock enable during Sleep mode
static per_inline bool per_rcc_gpiodlpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpiodlpen);
}

/// RCC IO port D clock enable during Sleep mode
static per_inline void per_rcc_set_gpiodlpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpiodlpen, val);
}

/// RCC IO port E clock enable during Sleep mode
static per_inline bool per_rcc_gpioelpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpioelpen);
}

/// RCC IO port E clock enable during Sleep mode
static per_inline void per_rcc_set_gpioelpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpioelpen, val);
}

/// RCC IO port F clock enable during Sleep mode
static per_inline bool per_rcc_gpioflpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpioflpen);
}

/// RCC IO port F clock enable during Sleep mode
static per_inline void per_rcc_set_gpioflpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpioflpen, val);
}

/// RCC IO port G clock enable during Sleep mode
static per_inline bool per_rcc_gpioglpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpioglpen);
}

/// RCC IO port G clock enable during Sleep mode
static per_inline void per_rcc_set_gpioglpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpioglpen, val);
}

/// RCC IO port H clock enable during Sleep mode
static per_inline bool per_rcc_gpiohlpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpiohlpen);
}

/// RCC IO port H clock enable during Sleep mode
static per_inline void per_rcc_set_gpiohlpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpiohlpen, val);
}

/// RCC IO port I clock enable during Sleep mode
static per_inline bool per_rcc_gpioilpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Gpioilpen);
}

/// RCC IO port I clock enable during Sleep mode
static per_inline void per_rcc_set_gpioilpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Gpioilpen, val);
}

/// RCC IO port J clock enable during Sleep mode
static per_inline bool per_rcc_gpiojlpen(const per_rcc_t* const rcc)
{
    if (rcc->Gpio < PER_RCC_GPIO_J)
    {
        per_log_err_function_not_supported();
    }

    return per_rcc_en1(&rcc->Per->Gpiojlpen);
}

/// RCC IO port J clock enable during Sleep mode
static per_inline void per_rcc_set_gpiojlpen(const per_rcc_t* const rcc, bool val)
{
    if (rcc->Gpio < PER_RCC_GPIO_J)
    {
        per_log_err_function_not_supported();
    }

    per_rcc_en1_set(&rcc->Per->Gpiojlpen, val);
}

/// RCC IO port K clock enable during Sleep mode
static per_inline bool per_rcc_gpioklpen(const per_rcc_t* const rcc)
{
    if (rcc->Gpio < PER_RCC_GPIO_K)
    {
        per_log_err_function_not_supported();
    }

    return per_rcc_en1(&rcc->Per->Gpioklpen);
}

/// RCC IO port K clock enable during Sleep mode
static per_inline void per_rcc_set_gpioklpen(const per_rcc_t* const rcc, bool val)
{
    if (rcc->Gpio < PER_RCC_GPIO_K)
    {
        per_log_err_function_not_supported();
    }

    per_rcc_en1_set(&rcc->Per->Gpioklpen, val);
}

/// RCC CRC clock enable during Sleep mode
static per_inline bool per_rcc_crclpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Crclpen);
}

/// RCC CRC clock enable during Sleep mode
static per_inline void per_rcc_set_crclpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Crclpen, val);
}

/// RCC Flash interface clock enable during Sleep mode
static per_inline bool per_rcc_flitflpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Flitflpen);
}

/// RCC Flash interface clock enable during Sleep mode
static per_inline void per_rcc_set_flitflpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Flitflpen, val);
}

/// RCC SRAM 1 interface clock enable during Sleep mode
static per_inline bool per_rcc_sram1lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Sram1lpen);
}

/// RCC SRAM 1 interface clock enable during Sleep mode
static per_inline void per_rcc_set_sram1lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Sram1lpen, val);
}

/// RCC SRAM 2 interface clock enable during Sleep mode
static per_inline bool per_rcc_sram2lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Sram2lpen);
}

/// RCC SRAM 2 interface clock enable during Sleep mode
static per_inline void per_rcc_set_sram2lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Sram2lpen, val);
}

/// RCC Backup SRAM interface clock enable during Sleep mode
static per_inline bool per_rcc_bkpsramlpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Bkpsramlpen);
}

/// RCC Backup SRAM interface clock enable during Sleep mode
static per_inline void per_rcc_set_bkpsramlpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Bkpsramlpen, val);
}

/// RCC SRAM 3 interface clock enable during Sleep mode
static per_inline bool per_rcc_sram3lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Sram3lpen);
}

/// RCC SRAM 3 interface clock enable during Sleep mode
static per_inline void per_rcc_set_sram3lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Sram3lpen, val);
}

/// RCC DMA1 clock enable during Sleep mode
static per_inline bool per_rcc_dma1lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Dma1lpen);
}

/// RCC DMA1 clock enable during Sleep mode
static per_inline void per_rcc_set_dma1lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Dma1lpen, val);
}

/// RCC DMA2 clock enable during Sleep mode
static per_inline bool per_rcc_dma2lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Dma2lpen);
}

/// RCC DMA2 clock enable during Sleep mode
static per_inline void per_rcc_set_dma2lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Dma2lpen, val);
}

/// RCC DMA2D clock enable during Sleep mode
static per_inline bool per_rcc_dma2dlpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Dma2dlpen);
}

/// RCC DMA2D clock enable during Sleep mode
static per_inline void per_rcc_set_dma2dlpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Dma2dlpen, val);
}

/// RCC Ethernet MAC clock enable during Sleep mode
static per_inline bool per_rcc_ethmaclpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Ethmaclpen);
}

/// RCC Ethernet MAC clock enable during Sleep mode
static per_inline void per_rcc_set_ethmaclpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Ethmaclpen, val);
}

/// RCC Ethernet Transmission clock enable during Sleep mode
static per_inline bool per_rcc_ethmactxlpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Ethmactxlpen);
}

/// RCC Ethernet Transmission clock enable during Sleep mode
static per_inline void per_rcc_set_ethmactxlpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Ethmactxlpen, val);
}

/// RCC Ethernet Reception clock enable during Sleep mode
static per_inline bool per_rcc_ethmacrxlpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Ethmacrxlpen);
}

/// RCC Ethernet Reception clock enable during Sleep mode
static per_inline void per_rcc_set_ethmacrxlpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Ethmacrxlpen, val);
}

/// RCC Ethernet PTP clock enable during Sleep mode
static per_inline bool per_rcc_ethmacptplpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Ethmacptplpen);
}

/// RCC Ethernet PTP clock enable during Sleep mode
static per_inline void per_rcc_set_ethmacptplpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Ethmacptplpen, val);
}

/// RCC USB OTG HS clock enable during Sleep mode
static per_inline bool per_rcc_otghslpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Otghslpen);
}

/// RCC USB OTG HS clock enable during Sleep mode
static per_inline void per_rcc_set_otghslpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Otghslpen, val);
}

/// RCC USB OTG HSULPI clock enable during Sleep mode
static per_inline bool per_rcc_otghsulpilpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Otghsulpilpen);
}

/// RCC USB OTG HSULPI clock enable during Sleep mode
static per_inline void per_rcc_set_otghsulpilpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Otghsulpilpen, val);
}

/// RCC Camera interface enable during Sleep mode
static per_inline bool per_rcc_dcmilpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Dcmilpen);
}

/// RCC Camera interface enable during Sleep mode
static per_inline void per_rcc_set_dcmilpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Dcmilpen, val);
}

/// RCC Cryptographic modules clock enable during Sleep mode
static per_inline bool per_rcc_cryplpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Cryplpen);
}

/// RCC Cryptographic modules clock enable during Sleep mode
static per_inline void per_rcc_set_cryplpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Cryplpen, val);
}

/// RCC Hash modules clock enable during Sleep mode
static per_inline bool per_rcc_hashlpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Hashlpen);
}

/// RCC Hash modules clock enable during Sleep mode
static per_inline void per_rcc_set_hashlpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Hashlpen, val);
}

/// RCC Random number generator clock enable during Sleep mode
static per_inline bool per_rcc_rnglpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Rnglpen);
}

/// RCC Random number generator clock enable during Sleep mode
static per_inline void per_rcc_set_rnglpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Rnglpen, val);
}

/// RCC USB OTG FS clock enable during Sleep mode
static per_inline bool per_rcc_otgfslpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Otgfslpen);
}

/// RCC USB OTG FS clock enable during Sleep mode
static per_inline void per_rcc_set_otgfslpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Otgfslpen, val);
}

/// RCC Flexible memory controller module clock enable during Sleep mode
static per_inline bool per_rcc_fmclpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Fmclpen);
}

/// RCC Flexible memory controller module clock enable during Sleep mode
static per_inline void per_rcc_set_fmclpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Fmclpen, val);
}

/// RCC TIM2 clock enable during Sleep mode
static per_inline bool per_rcc_tim2lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim2lpen);
}

/// RCC TIM2 clock enable during Sleep mode
static per_inline void per_rcc_set_tim2lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim2lpen, val);
}

/// RCC TIM3 clock enable during Sleep mode
static per_inline bool per_rcc_tim3lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim3lpen);
}

/// RCC TIM3 clock enable during Sleep mode
static per_inline void per_rcc_set_tim3lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim3lpen, val);
}

/// RCC TIM4 clock enable during Sleep mode
static per_inline bool per_rcc_tim4lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim4lpen);
}

/// RCC TIM4 clock enable during Sleep mode
static per_inline void per_rcc_set_tim4lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim4lpen, val);
}

/// RCC TIM5 clock enable during Sleep mode
static per_inline bool per_rcc_tim5lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim5lpen);
}

/// RCC TIM5 clock enable during Sleep mode
static per_inline void per_rcc_set_tim5lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim5lpen, val);
}

/// RCC TIM6 clock enable during Sleep mode
static per_inline bool per_rcc_tim6lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim6lpen);
}

/// RCC TIM6 clock enable during Sleep mode
static per_inline void per_rcc_set_tim6lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim6lpen, val);
}

/// RCC TIM7 clock enable during Sleep mode
static per_inline bool per_rcc_tim7lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim7lpen);
}

/// RCC TIM7 clock enable during Sleep mode
static per_inline void per_rcc_set_tim7lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim7lpen, val);
}

/// RCC TIM12 clock enable during Sleep mode
static per_inline bool per_rcc_tim12lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim12lpen);
}

/// RCC TIM12 clock enable during Sleep mode
static per_inline void per_rcc_set_tim12lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim12lpen, val);
}

/// RCC TIM13 clock enable during Sleep mode
static per_inline bool per_rcc_tim13lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim13lpen);
}

/// RCC TIM13 clock enable during Sleep mode
static per_inline void per_rcc_set_tim13lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim13lpen, val);
}

/// RCC TIM14 clock enable during Sleep mode
static per_inline bool per_rcc_tim14lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim14lpen);
}

/// RCC TIM14 clock enable during Sleep mode
static per_inline void per_rcc_set_tim14lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim14lpen, val);
}

/// RCC Window watchdog clock enable during Sleep mode
static per_inline bool per_rcc_wwdglpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Wwdglpen);
}

/// RCC Window watchdog clock enable during Sleep mode
static per_inline void per_rcc_set_wwdglpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Wwdglpen, val);
}

/// RCC SPI2 clock enable during Sleep mode
static per_inline bool per_rcc_spi2lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Spi2lpen);
}

/// RCC SPI2 clock enable during Sleep mode
static per_inline void per_rcc_set_spi2lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Spi2lpen, val);
}

/// RCC SPI3 clock enable during Sleep mode
static per_inline bool per_rcc_spi3lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Spi3lpen);
}

/// RCC SPI3 clock enable during Sleep mode
static per_inline void per_rcc_set_spi3lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Spi3lpen, val);
}

/// RCC USART2 clock enable during Sleep mode
static per_inline bool per_rcc_usart2lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Usart2lpen);
}

/// RCC USART2 clock enable during Sleep mode
static per_inline void per_rcc_set_usart2lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Usart2lpen, val);
}

/// RCC USART3 clock enable during Sleep mode
static per_inline bool per_rcc_usart3lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Usart3lpen);
}

/// RCC USART3 clock enable during Sleep mode
static per_inline void per_rcc_set_usart3lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Usart3lpen, val);
}

/// RCC UART4 clock enable during Sleep mode
static per_inline bool per_rcc_uart4lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Uart4lpen);
}

/// RCC UART4 clock enable during Sleep mode
static per_inline void per_rcc_set_uart4lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Uart4lpen, val);
}

/// RCC UART5 clock enable during Sleep mode
static per_inline bool per_rcc_uart5lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Uart5lpen);
}

/// RCC UART5 clock enable during Sleep mode
static per_inline void per_rcc_set_uart5lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Uart5lpen, val);
}

/// RCC I2C1 clock enable during Sleep mode
static per_inline bool per_rcc_i2c1lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->I2c1lpen);
}

/// RCC I2C1 clock enable during Sleep mode
static per_inline void per_rcc_set_i2c1lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->I2c1lpen, val);
}

/// RCC I2C2 clock enable during Sleep mode
static per_inline bool per_rcc_i2c2lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->I2c2lpen);
}

/// RCC I2C2 clock enable during Sleep mode
static per_inline void per_rcc_set_i2c2lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->I2c2lpen, val);
}

/// RCC I2C3 clock enable during Sleep mode
static per_inline bool per_rcc_i2c3lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->I2c3lpen);
}

/// RCC I2C3 clock enable during Sleep mode
static per_inline void per_rcc_set_i2c3lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->I2c3lpen, val);
}

/// RCC CAN1 clock enable during Sleep mode
static per_inline bool per_rcc_can1lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Can1lpen);
}

/// RCC CAN1 clock enable during Sleep mode
static per_inline void per_rcc_set_can1lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Can1lpen, val);
}

/// RCC CAN2 clock enable during Sleep mode
static per_inline bool per_rcc_can2lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Can2lpen);
}

/// RCC CAN2 clock enable during Sleep mode
static per_inline void per_rcc_set_can2lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Can2lpen, val);
}

/// RCC Power interface clock enable during Sleep mode
static per_inline bool per_rcc_pwrlpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Pwrlpen);
}

/// RCC Power interface clock enable during Sleep mode
static per_inline void per_rcc_set_pwrlpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Pwrlpen, val);
}

/// RCC DAC interface clock enable during Sleep mode
static per_inline bool per_rcc_daclpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Daclpen);
}

/// RCC DAC interface clock enable during Sleep mode
static per_inline void per_rcc_set_daclpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Daclpen, val);
}

/// RCC UART7 clock enable during Sleep mode
static per_inline bool per_rcc_uart7lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Uart7lpen);
}

/// RCC UART7 clock enable during Sleep mode
static per_inline void per_rcc_set_uart7lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Uart7lpen, val);
}

/// RCC UART8 clock enable during Sleep mode
static per_inline bool per_rcc_uart8lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Uart8lpen);
}

/// RCC UART8 clock enable during Sleep mode
static per_inline void per_rcc_set_uart8lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Uart8lpen, val);
}

/// RCC TIM1 clock enable during Sleep mode
static per_inline bool per_rcc_tim1lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim1lpen);
}

/// RCC TIM1 clock enable during Sleep mode
static per_inline void per_rcc_set_tim1lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim1lpen, val);
}

/// RCC TIM8 clock enable during Sleep mode
static per_inline bool per_rcc_tim8lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim8lpen);
}

/// RCC TIM8 clock enable during Sleep mode
static per_inline void per_rcc_set_tim8lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim8lpen, val);
}

/// RCC USART1 clock enable during Sleep mode
static per_inline bool per_rcc_usart1lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Usart1lpen);
}

/// RCC USART1 clock enable during Sleep mode
static per_inline void per_rcc_set_usart1lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Usart1lpen, val);
}

/// RCC USART6 clock enable during Sleep mode
static per_inline bool per_rcc_usart6lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Usart6lpen);
}

/// RCC USART6 clock enable during Sleep mode
static per_inline void per_rcc_set_usart6lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Usart6lpen, val);
}

/// RCC ADC1 clock enable during Sleep mode
static per_inline bool per_rcc_adc1lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Adc1lpen);
}

/// RCC ADC1 clock enable during Sleep mode
static per_inline void per_rcc_set_adc1lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Adc1lpen, val);
}

/// RCC ADC2 clock enable during Sleep mode
static per_inline bool per_rcc_adc2lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Adc2lpen);
}

/// RCC ADC2 clock enable during Sleep mode
static per_inline void per_rcc_set_adc2lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Adc2lpen, val);
}

/// RCC ADC3 clock enable during Sleep mode
static per_inline bool per_rcc_adc3lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Adc3lpen);
}

/// RCC ADC3 clock enable during Sleep mode
static per_inline void per_rcc_set_adc3lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Adc3lpen, val);
}

/// RCC SDIO clock enable during Sleep mode
static per_inline bool per_rcc_sdiolpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Sdiolpen);
}

/// RCC SDIO clock enable during Sleep mode
static per_inline void per_rcc_set_sdiolpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Sdiolpen, val);
}

/// RCC SPI1 clock enable during Sleep mode
static per_inline bool per_rcc_spi1lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Spi1lpen);
}

/// RCC SPI1 clock enable during Sleep mode
static per_inline void per_rcc_set_spi1lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Spi1lpen, val);
}

/// RCC SPI4 clock enable during Sleep mode
static per_inline bool per_rcc_spi4lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Spi4lpen);
}

/// RCC SPI4 clock enable during Sleep mode
static per_inline void per_rcc_set_spi4lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Spi4lpen, val);
}

/// RCC SYSCFGEN clock enable during Sleep mode
static per_inline bool per_rcc_syscfglpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Syscfglpen);
}

/// RCC SYSCFGEN clock enable during Sleep mode
static per_inline void per_rcc_set_syscfglpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Syscfglpen, val);
}

/// RCC TIM9 clock enable during Sleep mode
static per_inline bool per_rcc_tim9lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim9lpen);
}

/// RCC TIM9 clock enable during Sleep mode
static per_inline void per_rcc_set_tim9lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim9lpen, val);
}

/// RCC TIM10 clock enable during Sleep mode
static per_inline bool per_rcc_tim10lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim10lpen);
}

/// RCC TIM10 clock enable during Sleep mode
static per_inline void per_rcc_set_tim10lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim10lpen, val);
}

/// RCC TIM11 clock enable during Sleep mode
static per_inline bool per_rcc_tim11lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Tim11lpen);
}

/// RCC TIM11 clock enable during Sleep mode
static per_inline void per_rcc_set_tim11lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Tim11lpen, val);
}

/// RCC SPI5 clock enable during Sleep mode
static per_inline bool per_rcc_spi5lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Spi5lpen);
}

/// RCC SPI5 clock enable during Sleep mode
static per_inline void per_rcc_set_spi5lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Spi5lpen, val);
}

/// RCC SPI6 clock enable during Sleep mode
static per_inline bool per_rcc_spi6lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Spi6lpen);
}

/// RCC SPI6 clock enable during Sleep mode
static per_inline void per_rcc_set_spi6lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Spi6lpen, val);
}

/// RCC SAI1 clock enable during Sleep mode
static per_inline bool per_rcc_sai1lpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Sai1lpen);
}

/// RCC SAI1 clock enable during Sleep mode
static per_inline void per_rcc_set_sai1lpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Sai1lpen, val);
}

/// RCC LTDC clock enable during Sleep mode
static per_inline bool per_rcc_ltdclpen(const per_rcc_t* const rcc)
{
    return per_rcc_en1(&rcc->Per->Ltdclpen);
}

/// RCC LTDC clock enable during Sleep mode
static per_inline void per_rcc_set_ltdclpen(const per_rcc_t* const rcc, bool val)
{
    per_rcc_en1_set(&rcc->Per->Ltdclpen, val);
}

/// RCC Independent watchdog reset flag
static per_inline bool per_rcc_lseon(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Lseon);
}

/// RCC Independent watchdog reset flag
static per_inline void per_rcc_set_lseon(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Lseon, val);
}

/// RCC Window watchdog reset flag
static per_inline bool per_rcc_lserdy(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Lserdy);
}


/// RCC Low-power reset flag
static per_inline bool per_rcc_lsebyp(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Lsebyp);
}

/// RCC Low-power reset flag
static per_inline void per_rcc_set_lsebyp(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Lsebyp, val);
}

/// RCC RTC clock source selection
static per_inline per_rcc_rtcsel_e per_rcc_rtsel(const per_rcc_t* const rcc)
{
    return (per_rcc_rtcsel_e)per_bit_rw2(&rcc->Per->Rtsel);
}

/// RCC RTC clock source selection
static per_inline bool per_rcc_set_rtsel(const per_rcc_t* const rcc, per_rcc_rtcsel_e val)
{
    return per_bit_rw2_set(&rcc->Per->Rtsel, (uint_fast16_t)val);
}

/// RCC RTC clock enable
static per_inline bool per_rcc_rtcen(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Rtcen);
}

/// RCC RTC clock enable
static per_inline void per_rcc_set_rtcen(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Rtcen, val);
}

/// RCC Backup domain software reset
static per_inline bool per_rcc_bdrst(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Bdrst);
}

/// RCC Backup domain software reset
static per_inline void per_rcc_set_bdrst(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Bdrst, val);
}

/// RCC Internal low-speed oscillator enable
static per_inline bool per_rcc_lsion(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Lsion);
}

/// RCC Internal low-speed oscillator enable
static per_inline void per_rcc_set_lsion(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Lsion, val);
}

/// RCC Internal low-speed oscillator ready
static per_inline bool per_rcc_lsirdy(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Lsirdy);
}


/// RCC Remove reset flag
static per_inline bool per_rcc_rmvf(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Rmvf);
}

/// RCC Remove reset flag
static per_inline void per_rcc_set_rmvf(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Rmvf, val);
}

/// RCC BOR reset flag
static per_inline bool per_rcc_borrstf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Borrstf);
}


/// RCC PIN reset flag
static per_inline bool per_rcc_pinrstf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Pinrstf);
}


/// RCC POR/PDR reset flag
static per_inline bool per_rcc_porrstf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Porrstf);
}


/// RCC Software reset flag
static per_inline bool per_rcc_sftrstf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Sftrstf);
}


/// RCC Independent watchdog reset flag
static per_inline bool per_rcc_iwdgrstf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Iwdgrstf);
}


/// RCC Window watchdog reset flag
static per_inline bool per_rcc_wwdgrstf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Wwdgrstf);
}


/// RCC Low-power reset flag
static per_inline bool per_rcc_lpwrrstf(const per_rcc_t* const rcc)
{
    return per_bit_r1(&rcc->Per->Lpwrrstf);
}

/// RCC Modulation period
static per_inline uint_fast16_t per_rcc_modper(const per_rcc_t* const rcc)
{
    return per_bit_rw13(&rcc->Per->Modper);
}

/// RCC Modulation period
static per_inline bool per_rcc_set_modper(const per_rcc_t* const rcc, uint_fast16_t val)
{
    return per_bit_rw13_set(&rcc->Per->Modper, val);
}

/// RCC Incrementation step
static per_inline uint_fast16_t per_rcc_incstep(const per_rcc_t* const rcc)
{
    return per_bit_rw15(&rcc->Per->Incstep);
}

/// RCC Incrementation step
static per_inline bool per_rcc_set_incstep(const per_rcc_t* const rcc, uint_fast16_t val)
{
    return per_bit_rw15_set(&rcc->Per->Incstep, val);
}

/// RCC Spread Select
static per_inline bool per_rcc_spreadsel(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Spreadsel);
}

/// RCC Spread Select
static per_inline void per_rcc_set_spreadsel(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Spreadsel, val);
}

/// RCC Spread spectrum modulation enable
static per_inline bool per_rcc_sscgen(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Sscgen);
}

/// RCC Spread spectrum modulation enable
static per_inline void per_rcc_set_sscgen(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Sscgen, val);
}

/// RCC PLLI2S multiplication factor for VCO
static per_inline uint_fast16_t per_rcc_plli2sn(const per_rcc_t* const rcc)
{
    return per_bit_rw9(&rcc->Per->Plli2sn);
}

/// RCC PLLI2S multiplication factor for VCO
static per_inline bool per_rcc_set_plli2sn(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PLLI2SN_MAX) ||
        (val < PER_RCC_PLL_MIN))
    {
        per_log_err(rcc->Err, PER_RCC_PLLI2SN_ERR, val);
        return false;
    }

    return per_bit_rw9_set(&rcc->Per->Plli2sn, val);
}

/// RCC PLLI2S division factor for SAI1 clock
static per_inline uint_fast16_t per_rcc_plli2sq(const per_rcc_t* const rcc)
{
    return per_bit_rw4(&rcc->Per->Plli2sq);
}

/// RCC PLLI2S division factor for SAI1 clock
static per_inline bool per_rcc_set_plli2sq(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PLLI2SQ_MAX) ||
        (val < PER_RCC_PLL_MIN))
    {
        per_log_err(rcc->Err, PER_RCC_PLLI2SQ_ERR, val);
        return false;
    }

   return per_bit_rw4_set(&rcc->Per->Plli2sq, val);
}

/// RCC PLLI2S division factor for I2S clocks
static per_inline uint_fast16_t per_rcc_plli2sr(const per_rcc_t* const rcc)
{
    return per_bit_rw3(&rcc->Per->Plli2sr);
}

/// RCC PLLI2S division factor for I2S clocks
static per_inline bool per_rcc_set_plli2sr(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PLLI2SR_MAX) ||
        (val < PER_RCC_PLL_MIN))
    {
        per_log_err(rcc->Err, PER_RCC_PLLI2SR_ERR, val);
        return false;
    }

    return per_bit_rw3_set(&rcc->Per->Plli2sr, val);
}

/// RCC PLLSAI division factor for VCO
static per_inline uint_fast16_t per_rcc_pllisain(const per_rcc_t* const rcc)
{
    return per_bit_rw9(&rcc->Per->Pllisain);
}

/// RCC PLLSAI division factor for VCO
static per_inline bool per_rcc_set_pllisain(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PLLSAIN_MAX) ||
        (val < PER_RCC_PLL_MIN))
    {
        per_log_err(rcc->Err, PER_RCC_PLLSAIN_ERR, val);
        return false;
    }

    return per_bit_rw9_set(&rcc->Per->Pllisain, val);
}

/// RCC PLLSAI division factor for SAI1 clock
static per_inline uint_fast16_t per_rcc_pllsaiq(const per_rcc_t* const rcc)
{
    return per_bit_rw4(&rcc->Per->Pllsaiq);
}

/// RCC PLLSAI division factor for SAI1 clock
static per_inline bool per_rcc_set_pllsaiq(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PLLSAIQ_MAX) ||
        (val < PER_RCC_PLL_MIN))
    {
        per_log_err(rcc->Err, PER_RCC_PLLSAIQ_ERR, val);
        return false;
    }

   return per_bit_rw4_set(&rcc->Per->Pllsaiq, val);
}

/// RCC PLLSAI division factor for LCD clock
static per_inline uint_fast16_t per_rcc_pllsair(const per_rcc_t* const rcc)
{
    return per_bit_rw3(&rcc->Per->Pllsair);
}

/// RCC PLLSAI division factor for LCD clock
static per_inline bool per_rcc_set_pllsair(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PLLSAIR_MAX) ||
        (val < PER_RCC_PLL_MIN))
    {
        per_log_err(rcc->Err, PER_RCC_PLLSAIR_ERR, val);
        return false;
    }

    return per_bit_rw3_set(&rcc->Per->Pllsair, val);
}

/// RCC PLLI2S division factor for SAI1 clock
static per_inline uint_fast16_t per_rcc_plli2sdivq(const per_rcc_t* const rcc)
{
    return per_bit_rw5(&rcc->Per->Plli2sdivq) + 1;
}

/// RCC PLLI2S division factor for SAI1 clock
static per_inline bool per_rcc_set_plli2sdivq(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PLLI2SDIVQ_MAX) ||
        (val == 0))
    {
        per_log_err(rcc->Err, PER_RCC_PLLI2SDIVQ_ERR, val);
        return false;
    }

    return per_bit_rw5_set(&rcc->Per->Plli2sdivq, val - 1);
}

/// RCC PLLSAI division factor for SAI1 clock
static per_inline uint_fast16_t per_rcc_pllsaidivq(const per_rcc_t* const rcc)
{
    return per_bit_rw5(&rcc->Per->Pllsaidivq) + 1;
}

/// RCC PLLSAI division factor for SAI1 clock
static per_inline bool per_rcc_set_pllsaidivq(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PLLSAIDIVQ_MAX) ||
        (val == 0))
    {
        per_log_err(rcc->Err, PER_RCC_PLLSAIDIVQ_ERR, val);
        return false;
    }

    return per_bit_rw5_set(&rcc->Per->Pllsaidivq, val - 1);
}

/// RCC division factor for LCD_CLK
static per_inline uint_fast16_t per_rcc_pllsaidivr(const per_rcc_t* const rcc)
{
    return per_bit_inv_log2(per_bit_rw2(&rcc->Per->Pllsaidivr) + 1);
}

/// RCC division factor for LCD_CLK
static per_inline bool per_rcc_set_pllsaidivr(const per_rcc_t* const rcc, uint_fast16_t val)
{
    if ((val > PER_RCC_PLLSAIDIVR_MAX) ||
        (val < PER_RCC_PLL_MIN) ||
        !per_bit_is_log2(val))
    {
        per_log_err(rcc->Err, PER_RCC_PLLSAIDIVR_ERR, val);
        return false;
    }

    return per_bit_rw2_set(&rcc->Per->Pllsaidivr, per_bit_log2(val) - 1);
}

/// RCC SAI1-A clock source selection
static per_inline per_rcc_sai1src_e per_rcc_sai1asrc(const per_rcc_t* const rcc)
{
    return (per_rcc_sai1src_e)per_bit_rw2(&rcc->Per->Sai1asrc);
}

/// RCC SAI1-A clock source selection
static per_inline bool per_rcc_set_sai1asrc(const per_rcc_t* const rcc, per_rcc_sai1src_e val)
{
    return per_bit_rw2_set(&rcc->Per->Sai1asrc, (uint_fast16_t)val);
}

/// RCC SAI1-B clock source selection
static per_inline per_rcc_sai1src_e per_rcc_sai1bsrc(const per_rcc_t* const rcc)
{
    return (per_rcc_sai1src_e)per_bit_rw2(&rcc->Per->Sai1bsrc);
}

/// RCC SAI1-B clock source selection
static per_inline bool per_rcc_set_sai1bsrc(const per_rcc_t* const rcc, per_rcc_sai1src_e val)
{
    return per_bit_rw2_set(&rcc->Per->Sai1bsrc, (uint_fast16_t)val);
}

/// RCC Timers clocks prescalers selection
static per_inline bool per_rcc_timpre(const per_rcc_t* const rcc)
{
    return per_bit_rw1(&rcc->Per->Timpre);
}

/// RCC Timers clocks prescalers selection
static per_inline void per_rcc_set_timpre(const per_rcc_t* const rcc, bool val)
{
    per_bit_rw1_set(&rcc->Per->Timpre, val);
}

#ifdef __cplusplus
}
#endif

#endif // per_rcc_f4_h_
