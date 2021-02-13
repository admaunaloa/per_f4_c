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

/// [Hz] Clock frequency
#define PER_RCC_FREQ ((uint32_t)168000000)

/// APBx to TIMERS fixed multiplier
#define PER_RCC_APB_PER_TO_TIM_MUL ((uint32_t)2)

/// low-speed external clock
#define PER_RCC_LSE ((uint32_t)32768)

/// low-speed internal rc clock
#define PER_RCC_LSI_RC ((uint32_t)32000)

/// high-speed external clock
#define PER_RCC_HSE ((uint32_t)8000000)

/// high-speed internal rc clock
#define PER_RCC_HSI_RC ((uint32_t)16000000)

/// RCC MCO divider enumeration
typedef enum
{
    PER_RCC_MCO_DIV_1 = 0b000, ///< Divide by 1
    PER_RCC_MCO_DIV_2 = 0b100, ///< Divide by 2
    PER_RCC_MCO_DIV_3 = 0b101, ///< Divide by 3
    PER_RCC_MCO_DIV_4 = 0b110, ///< Divide by 4
    PER_RCC_MCO_DIV_5 = 0b111, ///< Divide by 5
} per_rcc_mco_div_e;

/// RCC APB divider enumeration
typedef enum
{
    PER_RCC_APB_DIV_1  = 0b000, ///< Divide by 1
    PER_RCC_APB_DIV_2  = 0b100, ///< Divide by 2
    PER_RCC_APB_DIV_4  = 0b101, ///< Divide by 4
    PER_RCC_APB_DIV_8  = 0b110, ///< Divide by 8
    PER_RCC_APB_DIV_16 = 0b111, ///< Divide by 16
} per_rcc_apb_div_e;

typedef per_bit_rw1_t per_rcc_en1_t; ///< Peripheral clock enable on AHB and APB see ES0182. Needs delay after set

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
    per_bit_rw4_t Hpre; ///< AHB prescaler
    per_bit_n2_t CirBit8; ///< Reserved
    per_bit_rw3_t Ppre1; ///< APB Low speed prescaler (APB1)
    per_bit_rw3_t Ppre2; ///< APB high-speed prescaler (APB2)
    per_bit_rw5_t Rtcpre; ///< HSE division factor for RTC clock
    per_bit_rw2_t Mco1; ///< Microcontroller clock output 1
    per_bit_rw1_t I2sscr; ///< I2S clock selection
    per_bit_rw3_t Mco1pre; ///< MCO1 prescaler
    per_bit_rw3_t Mco2pre; ///< MCO2 prescaler
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
    per_rcc_en1_t Sram1lpen; ///< SRAM 1interface clock enable during Sleep mode
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
} __attribute__((packed)) per_rcc_per_t;

/// RCC descriptor
typedef struct
{
    per_rcc_per_t* const Per; ///< Peripheral
    const per_log_e Err; ///< Peripheral error number
} per_rcc_t;

/// Get peripheral clock frequency
static per_inline uint32_t per_rcc_freq(void)
{
    return PER_RCC_FREQ;
}

/// Enable a RCC item
static per_inline void per_rcc_enable(per_rcc_en1_t* reg, bool en)
{
    per_bit_rw1_set(reg, en);
    en = per_bit_rw1(reg); // Wait
}

/// Get MCO divider value
static per_inline uint32_t per_rcc_mco_div(per_bit_rw3_t* reg)
{
    uint32_t val = per_bit_rw3(reg);
    uint32_t b3 = (val >> 2) & 0b001; // bit three value
    uint32_t div = 1 + b3; // start at one and add bit three
    return div + (val & (b3 * 0b011)); // adder is least two bits
}

/// Set MCO divider value
static per_inline void per_rcc_set_mco_div(per_bit_rw3_t* reg, per_rcc_mco_div_e div)
{
    per_bit_rw3_set((per_bit_rw3_t*)reg, (uint32_t)div);
}

/// Get APB divider value
static per_inline uint32_t per_rcc_apb_div(per_bit_rw3_t* reg)
{
    uint32_t val = per_bit_rw3(reg);
    uint32_t b3 = (val >> 2) & 0b001; // bit three value
    uint32_t div = 1 + b3; // start at one and add bit three
    return div << (val & (b3 * 0b011)); // multiplier is least two bits
}

/// Set APB divider value
static per_inline void per_rcc_set_apb_div(per_bit_rw3_t* reg, per_rcc_apb_div_e div)
{
    per_bit_rw3_set(reg, (uint32_t)div);
}

#ifdef __cplusplus
}
#endif

#endif // per_rcc_f4_h_
