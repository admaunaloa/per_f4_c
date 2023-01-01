/**
 * @file per_adc_f4.h
 *
 * This file contains the analog digital converter (ADC)
 *
 * Copyright (c) 2023 admaunaloa admaunaloa@gmail.com
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

#ifndef per_adc_f4_h_
#define per_adc_f4_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_bit_f4.h"
#include "per_log_f4.h"

/// ADC1 base address
#define PER_ADC_1 ((per_adc_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB2 + (uintptr_t)0x2000))

/// ADC2 base address
#define PER_ADC_2 ((per_adc_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB2 + (uintptr_t)0x2100))

/// ADC3 base address
#define PER_ADC_3 ((per_adc_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB2 + (uintptr_t)0x2200))

/// ADC_COMMON base address
#define PER_ADC_COM ((per_adc_com_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB2 + (uintptr_t)0x2300))

/// Maximum number of channels
#define PER_ADC_CHAN_MAX (18)

/// Maximum number of injected channels
#define PER_ADC_JOFFSET_CHAN_MAX (4)

/// 12 bit
#define PER_ADC_JOFFSET_OFFSET_MAX (((uint_fast32_t)1 << 12) - 1)

/// 12 bit
#define PER_ADC_TRESHOLD_MAX (((uint_fast32_t)1 << 12) - 1)

/// Maximum number of SMP2 channels
#define PER_ADC_SMP2_CHAN_MAX (9)

/// Number of sequences in one register
#define PER_ADC_SQ_REG_MAX (6)

/// Maximum number of regular conversion channels
#define PER_ADC_SQ_MAX (16)

/// Maximum number of injected conversion channels
#define PER_ADC_JSQ_MAX (4)

/// Delay between 2 sampling phases minimum
#define PER_ADC_DELAY_MIN (5)

/// Delay between 2 sampling phases maximum
#define PER_ADC_DELAY_MAX (20)

/// Discontinuous mode channel count maximum
#define PER_ADC_DISCNUM_MAX (8)

/// ADC prescaler maximum
#define PER_ADC_COM_ADCPRE_MAX (8)

/// ADC error enumeration
typedef enum
{
    PER_ADC_ERR_OK = PER_LOG_ADC * PER_LOG_MULT, ///< No error
    PER_ADC_ERR_ADCPRE, ///< ADC prescaler invalid
    PER_ADC_ERR_AWDCH, ///< Analog watchdog channel invalid
    PER_ADC_ERR_SMP_SET, ///< Sample time select channel set invalid
    PER_ADC_ERR_SMP_GET, ///< Sample time select channel get invalid
    PER_ADC_ERR_JOFFSET_GET, ///< Injected channel offset get, invalid channel value
    PER_ADC_ERR_JOFFSET_SET, ///< Injected channel offset set, invalid channel value
    PER_ADC_ERR_JOFFSET_OFF, ///< Injected channel offset, invalid offset value
    PER_ADC_ERR_HT, ///< Higher level threshold value invalid
    PER_ADC_ERR_LT, ///< Lower level threshold value invalid
    PER_ADC_ERR_L_LEN, ///< Regular sequence length invalid
    PER_ADC_ERR_SQ_CHAN, ///< Regular sequence channel invalid
    PER_ADC_ERR_SQ_SET, ///< Regular sequence sequence set invalid
    PER_ADC_ERR_SQ_GET, ///< Regular sequence sequence get invalid
    PER_ADC_ERR_JL_LEN, ///< Injected sequence length invalid
    PER_ADC_ERR_JSQ_CHAN, ///< Injected sequence channel invalid
    PER_ADC_ERR_JSQ_SET, ///< Injected sequence sequence set invalid
    PER_ADC_ERR_JSQ_GET, ///< Injected sequence sequence get invalid
    PER_ADC_ERR_JD_GET, ///< Injected sequence data get sequence invalid
    PER_ADC_ERR_DELAY, ///< Delay between 2 samples set delay value invalid
    PER_ADC_ERR_DISCNUM, ///< Discontinuous mode channel count value invalid
} per_adc_error_e;

/// ADC resolution enumeration
typedef enum
{
    PER_ADC_RES_12 = 0b00, ///< 12-bit (15 ADCCLK cycles)
    PER_ADC_RES_10 = 0b01, ///< 10-bit (13 ADCCLK cycles)
    PER_ADC_RES_8  = 0b10, ///< 8-bit (11 ADCCLK cycles)
    PER_ADC_RES_6  = 0b11, ///< 6-bit (9 ADCCLK cycles)
} per_adc_res_e;

/// ADC sample time enumeration
typedef enum
{
    PER_ADC_SMP_3   = 0b000, ///< 3 cycles
    PER_ADC_SMP_15  = 0b001, ///< 15 cycles
    PER_ADC_SMP_28  = 0b010, ///< 28 cycles
    PER_ADC_SMP_56  = 0b011, ///< 56 cycles
    PER_ADC_SMP_84  = 0b100, ///< 84 cycles
    PER_ADC_SMP_112 = 0b101, ///< 112 cycles
    PER_ADC_SMP_144 = 0b110, ///< 144 cycles
    PER_ADC_SMP_480 = 0b111, ///< 480 cycles
} per_adc_smp_e;

/// ADC external trigger enumeration
typedef enum
{
    PER_ADC_EXTEN_DISABLED = 0b00, ///< Trigger detection disabled
    PER_ADC_EXTEN_RISING   = 0b01, ///< Trigger detection on the rising edge
    PER_ADC_EXTEN_FALLING  = 0b10, ///< Trigger detection on the falling edge
    PER_ADC_EXTEN_BOTH     = 0b11, ///< Trigger detection on both the rising and falling
} per_adc_exten_e;

/// ADC external selection enumeration
typedef enum
{
    PER_ADC_EXTSEL_TIM_1_CC_1 = 0b0000, ///< Timer 1 CC1 event
    PER_ADC_EXTSEL_TIM_1_CC_2 = 0b0001, ///< Timer 1 CC2 event
    PER_ADC_EXTSEL_TIM_1_CC_3 = 0b0010, ///< Timer 1 CC3 event
    PER_ADC_EXTSEL_TIM_2_CC_2 = 0b0011, ///< Timer 2 CC2 event
    PER_ADC_EXTSEL_TIM_2_CC_3 = 0b0100, ///< Timer 2 CC3 event
    PER_ADC_EXTSEL_TIM_2_CC_4 = 0b0101, ///< Timer 2 CC4 event
    PER_ADC_EXTSEL_TIM_2_TRGO = 0b0110, ///< Timer 2 TRGO event
    PER_ADC_EXTSEL_TIM_3_CC_1 = 0b0111, ///< Timer 3 CC1 event
    PER_ADC_EXTSEL_TIM_3_TRGO = 0b1000, ///< Timer 3 TRGO event
    PER_ADC_EXTSEL_TIM_4_CC_4 = 0b1001, ///< Timer 4 CC4 event
    PER_ADC_EXTSEL_TIM_5_CC_1 = 0b1010, ///< Timer 5 CC1 event
    PER_ADC_EXTSEL_TIM_5_CC_2 = 0b1011, ///< Timer 5 CC2 event
    PER_ADC_EXTSEL_TIM_5_CC_3 = 0b1100, ///< Timer 5 CC3 event
    PER_ADC_EXTSEL_TIM_8_CC_1 = 0b1101, ///< Timer 8 CC1 event
    PER_ADC_EXTSEL_TIM_8_TRGO = 0b1110, ///< Timer 8 TRGO event
    PER_ADC_EXTSEL_EXTI_11    = 0b1111, ///< Exti line11
} per_adc_extsel_e;

/// ADC injected external trigger enumeration
typedef enum
{
    PER_ADC_JEXTEN_DISABLED = 0b00, ///< Trigger detection disabled
    PER_ADC_JEXTEN_RISING   = 0b01, ///< Trigger detection on the rising edge
    PER_ADC_JEXTEN_FALLING  = 0b10, ///< Trigger detection on the falling edge
    PER_ADC_JEXTEN_BOTH     = 0b11, ///< Trigger detection on both the rising and falling
} per_adc_jexten_e;

/// ADC injected external selection enumeration
typedef enum
{
    PER_ADC_JEXTSEL_TIM_1_CC_4 = 0b0000, ///< Timer 1 CC4 event
    PER_ADC_JEXTSEL_TIM_1_TRGO = 0b0001, ///< Timer 1 TRGO event
    PER_ADC_JEXTSEL_TIM_2_CC_1 = 0b0010, ///< Timer 2 CC1 event
    PER_ADC_JEXTSEL_TIM_2_TRGO = 0b0011, ///< Timer 2 TRGO event
    PER_ADC_JEXTSEL_TIM_3_CC_2 = 0b0100, ///< Timer 3 CC2 event
    PER_ADC_JEXTSEL_TIM_3_CC_4 = 0b0101, ///< Timer 3 CC4 event
    PER_ADC_JEXTSEL_TIM_4_CC_1 = 0b0110, ///< Timer 4 CC1 event
    PER_ADC_JEXTSEL_TIM_4_CC_2 = 0b0111, ///< Timer 4 CC2 event
    PER_ADC_JEXTSEL_TIM_4_CC_3 = 0b1000, ///< Timer 4 CC3 event
    PER_ADC_JEXTSEL_TIM_4_TRGO = 0b1001, ///< Timer 4 TRGO event
    PER_ADC_JEXTSEL_TIM_5_CC_4 = 0b1010, ///< Timer 5 CC4 event
    PER_ADC_JEXTSEL_TIM_5_TRGO = 0b1011, ///< Timer 5 TRGO event
    PER_ADC_JEXTSEL_TIM_8_CC_2 = 0b1100, ///< Timer 8 CC2 event
    PER_ADC_JEXTSEL_TIM_8_CC_3 = 0b1101, ///< Timer 8 CC3 event
    PER_ADC_JEXTSEL_TIM_8_CC_4 = 0b1110, ///< Timer 8 CC4 event
    PER_ADC_JEXTSEL_EXTI_15    = 0b1111, ///< Exti line15
} per_adc_jextsel_e;

/// ADC mode enumeration
typedef enum
{
    // Independent modes
    PER_ADC_MULTI_IND_REG_SIM_INJ_SIM = 0b00001, ///< Combined regular simultaneous + injected simultaneous
    PER_ADC_MULTI_IND_REG_SIM_ALT_TRIG = 0b00010, ///< Combined regular simultaneous + alternate trigger mode
    PER_ADC_MULTI_IND_INJ_SIM = 0b00101, ///< Injected simultaneous mode only
    PER_ADC_MULTI_IND_REG_SIM = 0b00110, ///< Regular simultaneous mode only
    PER_ADC_MULTI_IND_INT = 0b00111, ///< Interleaved mode only
    PER_ADC_MULTI_IND_ALT = 0b01001, ///< Alternate trigger mode only
    // Triple modes
    PER_ADC_MULTI_TRI_REG_SIM_INJ_SIM = 0b00001, ///< Combined regular simultaneous + injected simultaneous
    PER_ADC_MULTI_TRI_REG_SIM_ALT_TRIG = 0b00010, ///< Combined regular simultaneous + alternate trigger mode
    PER_ADC_MULTI_TRI_INJ_SIM = 0b00101, ///< Injected simultaneous mode only
    PER_ADC_MULTI_TRI_REG_SIM = 0b00110, ///< Regular simultaneous mode only
    PER_ADC_MULTI_TRI_INT = 0b00111, ///< Interleaved mode only
    PER_ADC_MULTI_TRI_ALT = 0b01001, ///< Alternate trigger mode only
} per_adc_multi_e;

/// ADC dma enumeration
typedef enum
{
    PER_ADC_DMA_DISABLED = 0b00, ///< Mode disabled
    PER_ADC_DMA_MODE_1   = 0b01, ///< Mode 1 enabled (2 / 3 half-words one by one - 1 then 2 then 3)
    PER_ADC_DMA_MODE_2   = 0b10, ///< Mode 2 enabled (2 / 3 half-words by pairs - 2&1 then 1&3 then 3&2)
    PER_ADC_DMA_MODE_3   = 0b11, ///< Mode 3 enabled (2 / 3 bytes by pairs - 2&1 then 1&3 then 3&2)
} per_adc_dma_e;

/// ADC csr enumeration
typedef enum
{
    PER_ADC_COM_ADC_1 = 0, ///< Common CSR ADC 1
    PER_ADC_COM_ADC_2 = 1, ///< Common CSR ADC 2
    PER_ADC_COM_ADC_3 = 2, ///< Common CSR ADC 3
} per_adc_com_adc_e;

/// ADC Data offset for injected channel structure
typedef struct
{
    per_bit_rw12_t Off; ///< Offset
    per_bit_n20_t Bit12; ///< Reserved
} per_adc_jofr_t;

/// ADC Data register structure
typedef struct
{
    per_bit_r16_reg_t Data ; ///< Data register
} per_adc_dr_t;

/// ADC channel structure
typedef struct
{
    // status register (ADC_SR)
    per_bit_rc1_w0_t Awd; ///< Analog watchdog flag
    per_bit_rc1_w0_t Eoc; ///< Regular channel end of conversion
    per_bit_rc1_w0_t Jeoc; ///< Injected channel end of conversion
    per_bit_rc1_w0_t Jstrt; ///< Injected channel start flag
    per_bit_rc1_w0_t Strt; ///< Regular channel start flag
    per_bit_rc1_w0_t Ovr; ///< Overrun
    per_bit_n26_t AdcsrBit6; ///< Reserved

    // control register 1 (ADC_CR1)
    per_bit_rw5_t Awdch; ///< Analog watchdog channel select bits
    per_bit_rw1_t Eocie; ///< Interrupt enable for EOC
    per_bit_rw1_t Awdie; ///< Analog watchdog interrupt enable
    per_bit_rw1_t Jeocie; ///< Interrupt enable for injected channels
    per_bit_rw1_t Scan; ///< Scan mode
    per_bit_rw1_t Awdsgl; ///< Enable the watchdog on a single channel in scan mode
    per_bit_rw1_t Jauto; ///< Automatic injected group conversion
    per_bit_rw1_t Discen; ///< Discontinuous mode on regular channels
    per_bit_rw1_t Jdiscen; ///< Discontinuous mode on injected channels
    per_bit_rw3_t Discnum; ///< Discontinuous mode channel count
    per_bit_n6_t Adccr1Bit16; ///< Reserved
    per_bit_rw1_t Jawden; ///< Analog watchdog enable on injected channels
    per_bit_rw1_t Awden; ///< Analog watchdog enable on regular channels
    per_bit_rw2_t Res; ///< Resolution
    per_bit_rw1_t Ovrie; ///< Overrun interrupt enable
    per_bit_n5_t Adccr1Bit27; ///< Reserved

    // control register 2 (ADC_CR2)
    per_bit_rw1_t Adon; ///< A/D Converter ON / OFF
    per_bit_rw1_t Cont; ///< Continuous conversion
    per_bit_n6_t Cr2Bit2; ///< Reserved
    per_bit_rw1_t Dma; ///< Direct memory access mode (for single ADC mode)
    per_bit_rw1_t Dds; ///< DMA disable selection (for single ADC mode)
    per_bit_rw1_t Eocs; ///< End of conversion selection
    per_bit_rw1_t Align; ///< Data alignment
    per_bit_n4_t Cr2Bit12; ///< Reserved
    per_bit_rw4_t Jextsel; ///< External event select for injected group
    per_bit_rw2_t Jexten; ///< External trigger enable for injected channels
    per_bit_rw1_t Jswstart; ///< Start conversion of injected channels
    per_bit_n1_t Cr2Bit23; ///< Reserved
    per_bit_rw4_t Extsel; ///< External event select for regular group
    per_bit_rw2_t Exten; ///< External trigger enable for regular channels
    per_bit_rw1_t Swstart; ///< Start conversion of regular channels
    per_bit_n1_t Cr2Bit31; ///< Reserved

    // sample time register 1 (ADC_SMPR1)
    per_bit_rw3_t Smp_10[PER_ADC_CHAN_MAX - PER_ADC_SMP2_CHAN_MAX]; ///< SMP 10...18
    per_bit_n5_t Smpr1Bit27; ///< Reserved

    // sample time register 2 (ADC_SMPR2)
    per_bit_rw3_t Smp_0[PER_ADC_SMP2_CHAN_MAX + 1]; ///< SMP 0...9
    per_bit_n2_t Smpr2Bit30; ///< Reserved

    // injected channel data offset register x (ADC_JOFRx) (x=1..4)
    per_adc_jofr_t Joffset[PER_ADC_JOFFSET_CHAN_MAX]; ///< Data offset for injected channel x

    // watchdog higher threshold register (ADC_HTR)
    per_bit_rw12_t Ht; ///< Analog watchdog higher threshold
    per_bit_n20_t HtrBit12; ///< Reserved

    // watchdog lower threshold register (ADC_LTR)
    per_bit_rw12_t Lt; ///< Analog watchdog higher threshold
    per_bit_n20_t LtrBit12; ///< Reserved

    // regular sequence register 1 (ADC_SQR1)
    per_bit_rw5_t Sq1[PER_ADC_SQ_MAX - (PER_ADC_SQ_REG_MAX + PER_ADC_SQ_REG_MAX)]; ///< Conversion in regular sequence
    per_bit_rw4_t L; ///< Regular channel sequence length
    per_bit_n8_t Sqr1Bit24; ///< Reserved

    // regular sequence register 2 (ADC_SQR2)
    per_bit_rw5_t Sq2[PER_ADC_SQ_REG_MAX]; ///< Conversion in regular sequence
    per_bit_n2_t Sqr2Bit30; ///< Reserved

    // regular sequence register 3 (ADC_SQR3)
    per_bit_rw5_t Sq3[PER_ADC_SQ_REG_MAX]; ///< Conversion in regular sequence
    per_bit_n2_t Sqr3Bit30; ///< Reserved

    // injected sequence register (ADC_JSQR)
    per_bit_rw5_t Jsq[PER_ADC_JSQ_MAX]; ///< Conversion in injected sequence
    per_bit_rw2_t Jl; ///< Injected sequence length
    per_bit_n10_t JsqBit22; ///< Reserved

    // injected data register x (ADC_JDRx) (x= 1..4)
    per_adc_dr_t Jd[PER_ADC_JSQ_MAX]; ///< Injected data

    // regular data register (ADC_DR)
    per_adc_dr_t D; ///< Regular data
} per_adc_per_t;

/// ADC Common status register structure
typedef struct
{
    per_bit_r1_t Awd; ///< Analog watchdog flag
    per_bit_r1_t Eoc; ///< End of conversion
    per_bit_r1_t Jeoc; ///< Injected channel end of conversion
    per_bit_r1_t Jstrt; ///< Injected channel Start flag
    per_bit_r1_t Strt; ///< Regular channel Start flag
    per_bit_r1_t Ovr; ///< Overrun flag
    per_bit_n2_t CsrBit6; ///< Reserved
} per_adc_csr_t;

/// ADC descriptor
typedef struct
{
    per_adc_per_t* const Per; ///< Peripheral
    const per_log_e Err;      ///< Peripheral error number
} per_adc_t;

typedef struct
{
    // Common status register (ADC_CSR)
    per_adc_csr_t Adc[PER_ADC_COM_ADC_3 + 1]; ///< Common status register ADC1...3
    per_bit_n8_t CsrBit22; ///< Reserved

    // common control register (ADC_CCR)
    per_bit_rw5_t Multi; ///< Multi ADC mode selection
    per_bit_n3_t CcrBit5; ///< Reserved
    per_bit_rw4_t Delay; ///< Delay between 2 sampling phases
    per_bit_n1_t CcrBit12; ///< Reserved
    per_bit_rw1_t Dds; ///< DMA disable selection (for multi-ADC mode)
    per_bit_rw2_t Dma; ///< Direct memory access mode for multi ADC mode
    per_bit_rw2_t Adcpre; ///< ADC prescaler
    per_bit_n4_t CcrBit18; ///< Reserved
    per_bit_rw1_t Vbate; ///< VBAT enable
    per_bit_rw1_t Tsvrefe; ///< Temperature sensor and VREFINT enable
    per_bit_n8_t CcrBit24; ///< Reserved

    // common regular data register for dual and triple modes (ADC_CDR)
    per_bit_r16_t Data1; ///< 1st Data item of a pair of regular conversions
    per_bit_r16_t Data2; ///< 2 Data item of a pair of regular conversions
} per_adc_com_per_t;

/// ADC common descriptor
typedef struct
{
    per_adc_com_per_t* const Per; ///< Peripheral
    const per_log_e Err;          ///< Peripheral error number
} per_adc_com_t;

/// ADC Analog watchdog flag
static per_inline bool per_adc_awd(const per_adc_t* const adc)
{
    return per_bit_rc1_w0(&adc->Per->Awd);
}

/// ADC Analog watchdog flag
static per_inline bool per_adc_rdclr_awd(const per_adc_t* const adc)
{
    return per_bit_rc1_w0_rdclr(&adc->Per->Awd);
}

/// ADC Regular channel end of conversion
static per_inline bool per_adc_eoc(const per_adc_t* const adc)
{
    return per_bit_rc1_w0(&adc->Per->Eoc);
}

/// ADC Regular channel end of conversion
static per_inline bool per_adc_rdclr_eoc(const per_adc_t* const adc)
{
    return per_bit_rc1_w0_rdclr(&adc->Per->Eoc);
}

/// ADC Injected channel end of conversion
static per_inline bool per_adc_jeoc(const per_adc_t* const adc)
{
    return per_bit_rc1_w0(&adc->Per->Jeoc);
}

/// ADC Injected channel end of conversion
static per_inline bool per_adc_rdclr_jeoc(const per_adc_t* const adc)
{
    return per_bit_rc1_w0_rdclr(&adc->Per->Jeoc);
}

/// ADC Injected channel start flag
static per_inline bool per_adc_jstrt(const per_adc_t* const adc)
{
    return per_bit_rc1_w0(&adc->Per->Jstrt);
}

/// ADC Injected channel start flag
static per_inline bool per_adc_rdclr_jstrt(const per_adc_t* const adc)
{
    return per_bit_rc1_w0_rdclr(&adc->Per->Jstrt);
}

/// ADC Regular channel start flag
static per_inline bool per_adc_strt(const per_adc_t* const adc)
{
    return per_bit_rc1_w0(&adc->Per->Strt);
}

/// ADC Regular channel start flag
static per_inline bool per_adc_rdclr_strt(const per_adc_t* const adc)
{
    return per_bit_rc1_w0_rdclr(&adc->Per->Strt);
}

/// ADC Overrun
static per_inline bool per_adc_ovr(const per_adc_t* const adc)
{
    return per_bit_rc1_w0(&adc->Per->Ovr);
}

/// ADC Overrun
static per_inline bool per_adc_rdclr_ovr(const per_adc_t* const adc)
{
    return per_bit_rc1_w0_rdclr(&adc->Per->Ovr);
}

/// ADC Analog watchdog channel select bits
static per_inline uint_fast16_t per_adc_awdch(const per_adc_t* const adc)
{
    return per_bit_rw5(&adc->Per->Awdch);
}

/// ADC Analog watchdog channel select bits
static per_inline bool per_adc_set_awdch(const per_adc_t* const adc, uint_fast16_t chan)
{
    if (chan > PER_ADC_CHAN_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_AWDCH, chan);
        return false;
    }

    return per_bit_rw5_set(&adc->Per->Awdch, chan);
}

/// ADC Interrupt enable for EOC
static per_inline bool per_adc_eocie(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Eocie);
}

/// ADC Interrupt enable for EOC
static per_inline void per_adc_set_eocie(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Eocie, val);
}

/// ADC Analog watchdog interrupt enable
static per_inline bool per_adc_awdie(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Awdie);
}

/// ADC Analog watchdog interrupt enable
static per_inline void per_adc_set_awdie(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Awdie, val);
}

/// ADC Interrupt enable for injected channels
static per_inline bool per_adc_jeocie(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Jeocie);
}

/// ADC Interrupt enable for injected channels
static per_inline void per_adc_set_jeocie(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Jeocie, val);
}

/// ADC Scan mode
static per_inline bool per_ad(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Scan);
}

/// ADC Scan mode
static per_inline void per_adc_set_scan(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Scan, val);
}

/// ADC Enable the watchdog on a single channel in scan mode
static per_inline bool per_adc_awdsgl(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Awdsgl);
}

/// ADC Enable the watchdog on a single channel in scan mode
static per_inline void per_adc_set_awdsgl(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Awdsgl, val);
}

/// ADC Automatic injected group conversion
static per_inline bool per_adc_jauto(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Jauto);
}

/// ADC Automatic injected group conversion
static per_inline void per_adc_set_jauto(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Jauto, val);
}

/// ADC Discontinuous mode on regular channels
static per_inline bool per_adc_discen(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Discen);
}

/// ADC Discontinuous mode on regular channels
static per_inline void per_adc_set_discen(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Discen, val);
}

/// ADC Discontinuous mode on injected channels
static per_inline bool per_adc_j(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Jdiscen);
}

/// ADC Discontinuous mode on injected channels
static per_inline void per_adc_set_jdiscen(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Jdiscen, val);
}

/// ADC Discontinuous mode channel count
static per_inline uint_fast16_t per_adc_discnum(const per_adc_t* const adc)
{
    return per_bit_rw3(&adc->Per->Discnum) + 1;
}

/// ADC Discontinuous mode channel count
static per_inline bool per_adc_set_discnum(const per_adc_t* const adc, uint_fast16_t count)
{
    if (count > PER_ADC_DISCNUM_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_DISCNUM, count);
        return false;
    }

    return per_bit_rw3_set(&adc->Per->Discnum, count - 1);
}

/// ADC Analog watchdog enable on injected channels
static per_inline bool per_adc_jawden(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Jawden);
}

/// ADC Analog watchdog enable on injected channels
static per_inline void per_adc_set_jawden(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Jawden, val);
}

/// ADC Analog watchdog enable on regular channels
static per_inline bool per_adc_awden(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Awden);
}

/// ADC Analog watchdog enable on regular channels
static per_inline void per_adc_set_awden(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Awden, val);
}

/// ADC Resolution
static per_inline per_adc_res_e per_adc_res(const per_adc_t* const adc)
{
    return (per_adc_res_e)per_bit_rw2(&adc->Per->Res);
}

/// ADC Resolution
static per_inline bool per_adc_set_res(const per_adc_t* const adc, per_adc_res_e res)
{
    return per_bit_rw2_set(&adc->Per->Res, (uint_fast16_t)res);
}

/// ADC Overrun interrupt enable
static per_inline bool per_adc_ovrie(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Ovrie);
}

/// ADC Overrun interrupt enable
static per_inline void per_adc_set_ovrie(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Ovrie, val);
}

/// ADC A/D Converter ON / OFF
static per_inline bool per_adc_adon(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Adon);
}

/// ADC A/D Converter ON / OFF
static per_inline void per_adc_set_adon(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Adon, val);
}

/// ADC Continuous conversion
static per_inline bool per_adc_cont(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Cont);
}

/// ADC Continuous conversion
static per_inline void per_adc_set_cont(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Cont, val);
}

/// ADC Direct memory access mode (for single ADC mode)
static per_inline bool per_adc_dma(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Dma);
}

/// ADC Direct memory access mode (for single ADC mode)
static per_inline void per_adc_set_dma(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Dma, val);
}

/// ADC DMA disable selection (for single ADC mode)
static per_inline bool per_adc_dds(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Dds);
}

/// ADC DMA disable selection (for single ADC mode)
static per_inline void per_adc_set_dds(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Dds, val);
}

/// ADC End of conversion selection
static per_inline bool per_adc_eocs(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Eocs);
}

/// ADC End of conversion selection
static per_inline void per_adc_set_eocs(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Eocs, val);
}

/// ADC Data alignment
static per_inline bool per_adc_align(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Align);
}

/// ADC Data alignment
static per_inline void per_adc_set_align(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Align, val);
}

/// ADC External event select for injected group
static per_inline per_adc_jextsel_e per_adc_jextsel(const per_adc_t* const adc)
{
    return (per_adc_jextsel_e)per_bit_rw4(&adc->Per->Jextsel);
}

/// ADC External event select for injected group
static per_inline bool per_adc_set_jextsel(const per_adc_t* const adc, per_adc_jextsel_e sel)
{
    return per_bit_rw4_set(&adc->Per->Jextsel, (uint_fast16_t)sel);
}

/// ADC External trigger enable for injected channels
static per_inline per_adc_jexten_e per_adc_jexten(const per_adc_t* const adc)
{
    return (per_adc_jexten_e)per_bit_rw2(&adc->Per->Jexten);
}

/// ADC External trigger enable for injected channels
static per_inline bool per_adc_set_jexten(const per_adc_t* const adc, per_adc_jexten_e en)
{
    return per_bit_rw2_set(&adc->Per->Jexten, (uint_fast16_t)en);
}

/// ADC Start conversion of injected channels
static per_inline bool per_adc_jswstart(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Jswstart);
}

/// ADC Start conversion of injected channels
static per_inline void per_adc_set_jswstart(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Jswstart, val);
}

/// ADC External event select for regular group
static per_inline per_adc_extsel_e per_adc_extsel(const per_adc_t* const adc)
{
    return (per_adc_extsel_e)per_bit_rw4(&adc->Per->Extsel);
}

/// ADC External event select for regular group
static per_inline bool per_adc_set_extsel(const per_adc_t* const adc, per_adc_extsel_e sel)
{
    return per_bit_rw4_set(&adc->Per->Extsel, (uint_fast16_t)sel);
}

/// ADC External trigger enable for regular channels
static per_inline per_adc_exten_e per_adc_exten(const per_adc_t* const adc)
{
    return (per_adc_exten_e)per_bit_rw2(&adc->Per->Exten);
}

/// ADC External trigger enable for regular channels
static per_inline bool per_adc_set_exten(const per_adc_t* const adc, per_adc_exten_e en)
{
    return per_bit_rw2_set(&adc->Per->Exten, (uint_fast16_t)en);
}

/// ADC Start conversion of regular channels
static per_inline bool per_adc_swstart(const per_adc_t* const adc)
{
    return per_bit_rw1(&adc->Per->Swstart);
}

/// ADC Start conversion of regular channels
static per_inline void per_adc_set_swstart(const per_adc_t* const adc, bool val)
{
    per_bit_rw1_set(&adc->Per->Swstart, val);
}

/// ADC Sample time selection pointer
static per_inline per_bit_rw3_t* per_adc_ptr_smp(const per_adc_t* const adc, uint_fast16_t chan)
{
    if (chan <= PER_ADC_SMP2_CHAN_MAX)
    {
        return &adc->Per->Smp_0[chan];
    }

    return &adc->Per->Smp_10[chan - (PER_ADC_SMP2_CHAN_MAX + 1)];
}

/// ADC Sample time selection
static per_inline uint_fast16_t per_adc_smp(const per_adc_t* const adc, uint_fast16_t chan)
{
    if (chan > PER_ADC_CHAN_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_SMP_GET, chan);
        return 0;
    }

    return per_bit_rw3(per_adc_ptr_smp(adc, chan));
}

/// ADC Sample time selection
static per_inline bool per_adc_set_smp(const per_adc_t* const adc, uint_fast16_t chan, per_adc_smp_e smp)
{
    if (chan > PER_ADC_CHAN_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_SMP_SET, chan);
        return false;
    }

    return per_bit_rw3_set(per_adc_ptr_smp(adc, chan), (uint_fast16_t)smp);
}

/// ADC Data offset for injected channel
static per_inline uint_fast16_t per_adc_joffset(const per_adc_t* const adc, uint_fast16_t chan)
{
    if (chan > PER_ADC_JOFFSET_CHAN_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_JOFFSET_GET, chan);
        return 0;
    }

    return per_bit_rw12(&adc->Per->Joffset[chan - 1].Off);
}

/// ADC Data offset for injected channel
static per_inline bool per_adc_set_joffset(const per_adc_t* const adc, uint_fast16_t chan, uint_fast16_t off)
{
    if (chan > PER_ADC_JOFFSET_CHAN_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_JOFFSET_SET, chan);
        return false;
    }

    if (off > PER_ADC_JOFFSET_OFFSET_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_JOFFSET_OFF, off);
        return false;
    }

    return per_bit_rw12_set(&adc->Per->Joffset[chan - 1].Off, off);;
}

/// ADC Analog watchdog higher threshold
static per_inline uint_fast16_t per_adc_ht(const per_adc_t* const adc)
{
    return per_bit_rw12(&adc->Per->Ht);
}

/// ADC Analog watchdog higher threshold
static per_inline bool per_adc_set_ht(const per_adc_t* const adc, uint_fast16_t lev)
{
    if (lev > PER_ADC_TRESHOLD_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_HT, lev);
        return false;
    }

    return per_bit_rw12_set(&adc->Per->Ht, lev);
}

/// ADC Analog watchdog lower threshold
static per_inline uint_fast16_t per_adc_lt(const per_adc_t* const adc)
{
    return per_bit_rw12(&adc->Per->Lt);
}

/// ADC Analog watchdog lower threshold
static per_inline bool per_adc_set_lt(const per_adc_t* const adc, uint_fast16_t lev)
{
    if (lev > PER_ADC_TRESHOLD_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_LT, lev);
        return false;
    }

    return per_bit_rw12_set(&adc->Per->Lt, lev);
}

/// ADC Regular channel sequence length
static per_inline uint_fast16_t per_adc_l(const per_adc_t* const adc)
{
    return per_bit_rw4(&adc->Per->L) + 1;
}

/// ADC Regular channel sequence length
static per_inline bool per_adc_set_l(const per_adc_t* const adc, uint_fast16_t len)
{
    if (len > PER_ADC_SQ_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_L_LEN, len);
        return false;
    }

    return per_bit_rw4_set(&adc->Per->L, len - 1);
}

/// ADC Conversion in regular sequence pointer to sequence
static per_inline per_bit_rw5_t* per_adc_ptr_sq(const per_adc_t* const adc, uint_fast16_t seq)
{
    if (seq < PER_ADC_SQ_REG_MAX)
    {
        return &adc->Per->Sq3[seq];
    }

    if (seq < (PER_ADC_SQ_REG_MAX + PER_ADC_SQ_REG_MAX))
    {
        return &adc->Per->Sq2[seq - PER_ADC_SQ_REG_MAX];
    }

    return &adc->Per->Sq1[seq - (PER_ADC_SQ_REG_MAX + PER_ADC_SQ_REG_MAX)];
}

/// ADC Conversion in regular sequence
static per_inline uint_fast16_t per_adc_sq(const per_adc_t* const adc, uint_fast16_t seq)
{
    if (seq > PER_ADC_SQ_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_SQ_GET, seq);
        return 0;
    }

    return per_bit_rw5(per_adc_ptr_sq(adc, seq - 1));
}

/// ADC Conversion in regular sequence
static per_inline bool per_adc_set_sq(const per_adc_t* const adc, uint_fast16_t seq, uint_fast16_t chan)
{
    if (seq > PER_ADC_SQ_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_SQ_SET, seq);
        return false;
    }

    if (chan > PER_ADC_CHAN_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_SQ_CHAN, chan);
        return false;
    }

    return per_bit_rw5_set(per_adc_ptr_sq(adc, seq - 1), chan);
}

/// ADC Injected channel sequence length
static per_inline uint_fast16_t per_adc_jl(const per_adc_t* const adc)
{
    return per_bit_rw2(&adc->Per->Jl) + 1;
}

/// ADC Injected channel sequence length
static per_inline bool per_adc_set_jl(const per_adc_t* const adc, uint_fast16_t len)
{
    if (len > PER_ADC_JSQ_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_JL_LEN, len);
        return false;
    }

    return per_bit_rw2_set(&adc->Per->Jl, len - 1);
}

/// ADC Conversion in injected sequence get channel number
static per_inline uint_fast16_t per_adc_jsq(const per_adc_t* const adc, uint_fast16_t seq)
{
    if (seq > PER_ADC_JSQ_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_JSQ_GET, seq);
        return 0;
    }

    return per_bit_rw5(&adc->Per->Jsq[seq - 1]);
}

/// ADC Conversion in injected sequence channel number
static per_inline bool per_adc_set_jsq(const per_adc_t* const adc, uint_fast16_t seq, uint_fast16_t chan)
{
    if (seq > PER_ADC_JSQ_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_JSQ_SET, seq);
        return false;
    }

    if (chan > PER_ADC_CHAN_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_JSQ_CHAN, chan);
        return false;
    }

    return per_bit_rw5_set(&adc->Per->Jsq[seq - 1], chan);
}

/// ADC Injected sequence data
static per_inline uint_fast16_t per_adc_jdata(const per_adc_t* const adc, uint_fast8_t seq)
{
    if (seq > PER_ADC_JSQ_MAX)
    {
        per_log_err(adc->Err, PER_ADC_ERR_JD_GET, seq);
        return 0;
    }

    return per_bit_r16_reg(&adc->Per->Jd[seq - 1].Data);
}

/// ADC Regular sequence data
static per_inline uint_fast16_t per_adc_data(const per_adc_t* const adc)
{
    return per_bit_r16_reg(&adc->Per->D.Data);
}

/// ADC address Data value register address
static per_inline volatile uint_fast16_t* per_usart_addr_data(const per_adc_t* const adc)
{
    return &PER_BIT_BIT_BAND_TO_REG(&adc->Per->D)->Reg16;
}

/// ADC common get Analog watchdog flag
static per_inline bool per_adc_com_awd(const per_adc_com_t* const com, per_adc_com_adc_e adc)
{
    return per_bit_r1(&com->Per->Adc[adc].Awd);
}

/// ADC common get Regular channel end of conversion
static per_inline bool per_adc_com_eoc(const per_adc_com_t* const com, per_adc_com_adc_e adc)
{
    return per_bit_r1(&com->Per->Adc[adc].Eoc);
}

/// ADC common get Injected channel end of conversion
static per_inline bool per_adc_com_jeoc(const per_adc_com_t* const com, per_adc_com_adc_e adc)
{
    return per_bit_r1(&com->Per->Adc[adc].Jeoc);
}

/// ADC common get Injected channel start flag
static per_inline bool per_adc_com_jstrt(const per_adc_com_t* const com, per_adc_com_adc_e adc)
{
    return per_bit_r1(&com->Per->Adc[adc].Jstrt);
}

/// ADC common get Regular channel start flag
static per_inline bool per_adc_com_strt(const per_adc_com_t* const com, per_adc_com_adc_e adc)
{
    return per_bit_r1(&com->Per->Adc[adc].Strt);
}

/// ADC common get Overrun
static per_inline bool per_adc_com_ovr(const per_adc_com_t* const com, per_adc_com_adc_e adc)
{
    return per_bit_r1(&com->Per->Adc[adc].Ovr);
}

/// ADC Multi ADC mode selection
static per_inline per_adc_multi_e per_adc_com_multi(const per_adc_com_t* const com)
{
    return (per_adc_multi_e)per_bit_rw5(&com->Per->Multi);
}

/// ADC Multi ADC mode selection
static per_inline bool per_adc_com_set_multi(const per_adc_com_t* const com, per_adc_multi_e mode)
{
    return per_bit_rw5_set(&com->Per->Multi, (uint_fast16_t)mode);
}

/// ADC Common delay between 2 sampling phases
static per_inline uint_fast16_t per_adc_com_delay(const per_adc_com_t* const com)
{
    return per_bit_rw4(&com->Per->Delay) + PER_ADC_DELAY_MIN;
}

/// ADC Common delay between 2 sampling phases
static per_inline bool per_adc_com_set_delay(const per_adc_com_t* const com, uint_fast16_t del)
{
    if (del > PER_ADC_DELAY_MAX)
    {
        per_log_err(com->Err, PER_ADC_ERR_DELAY, del);
        return false;
    }

    return per_bit_rw4_set(&com->Per->Delay, del - PER_ADC_DELAY_MIN);
}

/// ADC DMA disable selection (for multi-ADC mode)
static per_inline bool per_adc_com_dds(const per_adc_com_t* const com)
{
    return per_bit_rw1(&com->Per->Dds);
}

/// ADC DMA disable selection (for multi-ADC mode)
static per_inline void per_adc_com_set_dds(const per_adc_com_t* const com, bool val)
{
    per_bit_rw1_set(&com->Per->Dds, val);
}

/// ADC Direct memory access mode for multi ADC mode
static per_inline per_adc_dma_e per_adc_com_dma(const per_adc_com_t* const com)
{
    return (per_adc_dma_e)per_bit_rw2(&com->Per->Dma);
}

/// ADC Direct memory access mode for multi ADC mode
static per_inline bool per_adc_com_set_dma(const per_adc_com_t* const com, per_adc_dma_e mode)
{
    return per_bit_rw2_set(&com->Per->Dma, (uint_fast16_t)mode);
}

/// ADC prescaler
static per_inline uint_fast16_t per_adc_com_adcpre(const per_adc_com_t* const com)
{
    return (per_bit_rw2(&com->Per->Adcpre) << 1) + 2;
}

/// ADC prescaler
static per_inline bool per_adc_com_set_adcpre(const per_adc_com_t* const com, uint_fast16_t div)
{
    if ((div > PER_ADC_COM_ADCPRE_MAX) || ((div & 0b01) != 0)) // Only even values
    {
        per_log_err(com->Err, PER_ADC_ERR_ADCPRE, div);
        return false;
    }

    return per_bit_rw2_set(&com->Per->Adcpre, (div - 2) >> 1);
}

/// ADC VBat enable
static per_inline bool per_adc_com_vbate(const per_adc_com_t* const com)
{
    return per_bit_rw1(&com->Per->Vbate);
}

/// ADC VBat enable
static per_inline void per_adc_com_set_vbate(const per_adc_com_t* const com, bool val)
{
    per_bit_rw1_set(&com->Per->Vbate, val);
}

/// ADC Temperature sensor and VREFINT enable
static per_inline bool per_adc_com_tsvrefe(const per_adc_com_t* const com)
{
    return per_bit_rw1(&com->Per->Tsvrefe);
}

/// ADC Temperature sensor and VREFINT enable
static per_inline void per_adc_com_set_tsvrefe(const per_adc_com_t* const com, bool val)
{
    per_bit_rw1_set(&com->Per->Tsvrefe, val);
}

/// ADC 1st data item of a pair of regular conversions
static per_inline uint_fast16_t per_adc_com_data1(const per_adc_com_t* const com)
{
    return per_bit_r16(&com->Per->Data1);
}

/// ADC 2 data item of a pair of regular conversions
static per_inline uint_fast16_t per_adc_com_data2(const per_adc_com_t* const com)
{
    return per_bit_r16(&com->Per->Data2);
}

#ifdef __cplusplus
}
#endif

#endif // per_adc_f4_h_
