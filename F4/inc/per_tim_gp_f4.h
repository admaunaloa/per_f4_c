/**
 * @file per_tim_gp_f4.h
 *
 * This file contains the peripheral timer general purpose 4 channel (TIM_GP)
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
 * For each TIM peripheral bit the possible get and set functions are provided.
 * The syntax is
 * per_      Peripheral library prefix
 * _tim_gp_  Timer advanced type
 * _cen      Field name as in the manual. CEN is Timer Enable.
 *
 * Example:
 * bool per_tim_gp_cen(per_tim_gp_t* )        returns the value of the counter Enable bit.
 * void per_tim_gp_set_cen(per_tim_gp_t* , bool) modifies the value of counter Enable bit.
 *
 * The per_usart_t pointers are provided in a function format
 * per_tim_gp_t* per_tim_gp_2(void)
 * per_tim_gp_t* per_tim_gp_3(void)
 *
 * Enabling TIM3 comes down to:
 * per_tim_gp_set_cen(per_tim_gp_3(), true);
 *
 * This set CEN example results in a minimal number of instructions because
 * both functions are inlined and bitband is used. Both functions also make it
 * type-safe and they enable features such as zero-cost error checking.
 * For minimal size and optimal performance the per_tim_gp_t* should be a compile time
 * constant, this is often implemented in the Board Support Package (bsp_) layer.
 *
 * Convenience functions:
 * per_tim_gp_freq()            returns the base frequency
 * per_tim_gp_irq()             clears active interrupts and returns bitmask of the cleared ones
 * per_tim_gp_set_milli()       set milli second time update
 * per_tim_gp_32_set_milli()    set milli second time update
 * per_tim_gp_set_nano()        set nano second time update
 * per_tim_gp_32_set_nano()     set nano second time update
 *
 * There are two ways to handle interrupts
 * -per_tim_gp_irq() is intended for generic interrupt handling like in a RTOS
 * -per_tim_gp_rdclr_xxxf() is intended for bare-metal
 */

#ifndef per_tim_gp_f4_h_
#define per_tim_gp_f4_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_bit_f4.h"
#include "per_log_f4.h"

/// Clock division maximum
#define PER_TIM_GP_CKD_MAX (4)

/// External trigger prescaler maximum
#define PER_TIM_GP_ETPS_MAX (8)

/// DMA burst length maximum
#define PER_TIM_GP_DBL_MAX (18)

/// Input capture prescaler maximum
#define PER_TIM_GP_ICPSC_MAX (8)

/// Prescaler maximum
#define PER_TIM_GP_PSC_MAX (UINT16_MAX)

/// Auto reload maximum
#define PER_TIM_GP_ARR_MAX (UINT16_MAX)

/// Auto reload maximum
#define PER_TIM_GP_32_ARR_MAX ((uint64_t)UINT32_MAX)

/// Timer calculate milli divider
#define PER_TIM_GP_MILLI_DIV ((uint64_t)1000)

/// Timer calculate milli round
#define PER_TIM_GP_MILLI_ROUND ((uint64_t)500)

/// Timer calculate nano divider
#define PER_TIM_GP_NANO_DIV ((uint64_t)1000000000)

/// Timer calculate nano round
#define PER_TIM_GP_NANO_ROUND ((uint64_t)500000000)

/// ADC error enumeration
typedef enum
{
    PER_TIM_GP_OK_ERR = PER_LOG_TIM_GP * PER_LOG_MULT, ///< No error
    PER_TIM_GP_CKD_ERR,           ///< Clock division invalid
    PER_TIM_GP_ETPS_ERR,          ///< External trigger prescaler invalid
    PER_TIM_GP_DBA_ERR,           ///< DMA base address invalid
    PER_TIM_GP_DBL_ERR,           ///< DMA burst length invalid
    PER_TIM_GP_IC1PSC_ERR,        ///< Input capture 1 prescaler invalid
    PER_TIM_GP_IC2PSC_ERR,        ///< Input capture 1 prescaler invalid
    PER_TIM_GP_IC3PSC_ERR,        ///< Input capture 1 prescaler invalid
    PER_TIM_GP_IC4PSC_ERR,        ///< Input capture 1 prescaler invalid
    PER_TIM_GP_TIME_MILLI_PSC_ERR,///< Time milli psc value invalid
    PER_TIM_GP_TIME_MILLI_ERR,    ///< Time milli value invalid
    PER_TIM_GP_TIME_MILLI_32_PSC_ERR,///< Time milli psc value invalid
    PER_TIM_GP_TIME_MILLI_32_ERR, ///< Time milli 32 bit value invalid
    PER_TIM_GP_TIME_NANO_PSC_ERR,     ///< Time nano value invalid
    PER_TIM_GP_TIME_NANO_ERR,     ///< Time nano value invalid
    PER_TIM_GP_TIME_NANO_32_PSC_ERR,  ///< Time nano 32 bit value invalid
    PER_TIM_GP_TIME_NANO_32_ERR,  ///< Time nano 32 bit value invalid
} per_tim_gp_error_e;

/// TIM_GP channel variants
typedef enum
{
    PER_TIM_GP_CHAN_1 = 1, ///< One channel
    PER_TIM_GP_CHAN_2 = 2, ///< Two channel
    PER_TIM_GP_CHAN_4 = 3, ///< Four channel
} per_tim_gp_chan_e;

/// TIM_GP variants
typedef enum
{
    PER_TIM_GP_SIZE_16 = 16, ///< 16 bit
    PER_TIM_GP_SIZE_32 = 32, ///< 32 bit
} per_tim_gp_size_e;

/// TIM_GP option register
typedef enum
{
    PER_TIM_GP_OR_TIM2 = 2, ///< TIM2
    PER_TIM_GP_OR_TIM5 = 5, ///< TIM5
} per_tim_gp_or_e;

/// TIM_GP Center-aligned mode selection
typedef enum
{
    PER_TIM_GP_CMS_EDGE     = 0b00, ///< Edge-aligned mode
    PER_TIM_GP_CMS_CENTER_1 = 0b01, ///< Center-aligned mode 1
    PER_TIM_GP_CMS_CENTER_2 = 0b10, ///< Center-aligned mode 2
    PER_TIM_GP_CMS_CENTER_3 = 0b11, ///< Center-aligned mode 3.
} per_tim_gp_cms_e;

/// TIM_GP Master mode selection
typedef enum
{
    PER_TIM_GP_MMS_RESET       = 0b000, ///< The UG bit from TIMx_EGR
    PER_TIM_GP_MMS_ENABLE      = 0b001, ///< ounter Enable signal CNT_EN
    PER_TIM_GP_MMS_UPDATE      = 0b010, ///< update event
    PER_TIM_GP_MMS_COMP_PULSE  = 0b011, ///<
    PER_TIM_GP_MMS_COMP_OC1REF = 0b100, ///< OC1REF is trigger TRGO
    PER_TIM_GP_MMS_COMP_OC2REF = 0b101, ///< OC2REF is trigger TRGO
    PER_TIM_GP_MMS_COMP_OC3REF = 0b110, ///< OC3REF is trigger TRGO
    PER_TIM_GP_MMS_COMP_OC4REF = 0b111, ///< OC4REF is trigger TRGO
} per_tim_gp_mms_e;

/// TIM_GP Slave mode selection
typedef enum
{
    PER_TIM_GP_SMS_DISABLED  = 0b000, ///< Slave mode disabled
    PER_TIM_GP_SMS_ENCODER_1 = 0b001, ///< Up/down on TI2FP1 edge depending on TI1FP2
    PER_TIM_GP_SMS_ENCODER_2 = 0b010, ///< Up/down on TI2FP1 edge depending on TI1FP1
    PER_TIM_GP_SMS_ENCODER_3 = 0b011, ///< Up/down on both TI1FP1 and TI2FP2
    PER_TIM_GP_SMS_RESET     = 0b100, ///< Rising edge of  trigger input
    PER_TIM_GP_SMS_GATED     = 0b101, ///< Enabled when the trigger input (TRGI) is high
    PER_TIM_GP_SMS_TRIGGER   = 0b110, ///< Start at a rising edge of  TRGI
    PER_TIM_GP_SMS_EXTERNAL  = 0b111, ///< Rising edges of TRGI clock the counter
} per_tim_gp_sms_e;

/// TIM_GP Trigger selection
typedef enum
{
    PER_TIM_GP_TS_ITR0    = 0b000, ///< Internal Trigger 0 (ITR0)
    PER_TIM_GP_TS_ITR1    = 0b001, ///< Internal Trigger 1 (ITR1)
    PER_TIM_GP_TS_ITR2    = 0b010, ///< Internal Trigger 2 (ITR2)
    PER_TIM_GP_TS_ITR3    = 0b011, ///< Internal Trigger 3 (ITR3)
    PER_TIM_GP_TS_EDGE    = 0b100, ///< TI1 Edge Detector (TI1F_ED)
    PER_TIM_GP_TS_TI1FP1  = 0b101, ///< Filtered Timer Input 1 (TI1FP1)
    PER_TIM_GP_TS_TI1FP2  = 0b110, ///< Filtered Timer Input 2 (TI2FP2)
    PER_TIM_GP_TS_TRIGGER = 0b111, ///< External Trigger input (ETRF)
} per_tim_gp_ts_e;

/// TIM_GP External trigger filter
typedef enum
{
    PER_TIM_GP_ETF_DTS      = 0b0000, ///< No filter, sampling is done at fDTS
    PER_TIM_GP_ETF_INT_N2   = 0b0001, ///< fSAMPLING=fCK_INT, N=2
    PER_TIM_GP_ETF_INT_N4   = 0b0010, ///< fSAMPLING=fCK_INT, N=4
    PER_TIM_GP_ETF_INT_N8   = 0b0011, ///< fSAMPLING=fCK_INT, N=8
    PER_TIM_GP_ETF_DTS2_N6  = 0b0100, ///< fSAMPLING=fDTS/2, N=6
    PER_TIM_GP_ETF_DTS2_N8  = 0b0101, ///< fSAMPLING=fDTS/2, N=8
    PER_TIM_GP_ETF_DTS4_N6  = 0b0110, ///< fSAMPLING=fDTS/4, N=6
    PER_TIM_GP_ETF_DTS4_N8  = 0b0111, ///< fSAMPLING=fDTS/4, N=8
    PER_TIM_GP_ETF_DTS8_N6  = 0b1000, ///< fSAMPLING=fDTS/8, N=6
    PER_TIM_GP_ETF_DTS8_N8  = 0b1001, ///< fSAMPLING=fDTS/8, N=8
    PER_TIM_GP_ETF_DTS16_N5 = 0b1010, ///< fSAMPLING=fDTS/16, N=5
    PER_TIM_GP_ETF_DTS16_N6 = 0b1011, ///< fSAMPLING=fDTS/16, N=6
    PER_TIM_GP_ETF_DTS16_N8 = 0b1100, ///< fSAMPLING=fDTS/16, N=8
    PER_TIM_GP_ETF_DTS32_N5 = 0b1101, ///< fSAMPLING=fDTS/32, N=5
    PER_TIM_GP_ETF_DTS32_N6 = 0b1110, ///< fSAMPLING=fDTS/32, N=6
    PER_TIM_GP_ETF_DTS32_N8 = 0b1111, ///< fSAMPLING=fDTS/32, N=8
} per_tim_gp_etf_e;

/// TIM_GP Status register flags
typedef enum
{
    PER_TIM_GP_SR_UIF   = 0b00000001, ///< Update interrupt flag
    PER_TIM_GP_SR_CC1IF = 0b00000010, ///< Capture/Compare 1 interrupt flag
    PER_TIM_GP_SR_CC2IF = 0b00000100, ///< Capture/Compare 2 interrupt flag
    PER_TIM_GP_SR_CC3IF = 0b00001000, ///< Capture/Compare 3 interrupt flag
    PER_TIM_GP_SR_CC4IF = 0b00010000, ///< Capture/Compare 4 interrupt flag
    PER_TIM_GP_SR_TIF   = 0b01000000, ///< Trigger interrupt flag
    PER_TIM_GP_SR_MASK  = PER_TIM_GP_SR_UIF | ///< All interrupt flag
                          PER_TIM_GP_SR_CC1IF |
                          PER_TIM_GP_SR_CC2IF |
                          PER_TIM_GP_SR_CC3IF |
                          PER_TIM_GP_SR_CC4IF |
                          PER_TIM_GP_SR_TIF,
} per_tim_gp_sr_e;

/// TIM_GP Capture/Compare selection
typedef enum
{
    PER_TIM_GP_CCS_OUT    = 0b00, ///< Output
    PER_TIM_GP_CCS_IN_TI1 = 0b01, ///< Input, IC1 is mapped on TI1
    PER_TIM_GP_CCS_IN_TI2 = 0b10, ///< Input, IC1 is mapped on TI2
    PER_TIM_GP_CCS_IN_TRC = 0b11, ///< Input, IC1 is mapped on TRC
} per_tim_gp_ccs_e;

/// TIM_GP Input capture filter
typedef enum
{
    PER_TIM_GP_ICF_DTS      = 0b0000, ///< No filter, sampling is done at fDTS
    PER_TIM_GP_ICF_INT_N2   = 0b0001, ///< fSAMPLING=fCK_INT, N=2
    PER_TIM_GP_ICF_INT_N4   = 0b0010, ///< fSAMPLING=fCK_INT, N=4
    PER_TIM_GP_ICF_INT_N8   = 0b0011, ///< fSAMPLING=fCK_INT, N=8
    PER_TIM_GP_ICF_DTS2_N6  = 0b0100, ///< fSAMPLING=fDTS/2, N=6
    PER_TIM_GP_ICF_DTS2_N8  = 0b0101, ///< fSAMPLING=fDTS/2, N=8
    PER_TIM_GP_ICF_DTS4_N6  = 0b0110, ///< fSAMPLING=fDTS/4, N=6
    PER_TIM_GP_ICF_DTS4_N8  = 0b0111, ///< fSAMPLING=fDTS/4, N=8
    PER_TIM_GP_ICF_DTS8_N6  = 0b1000, ///< fSAMPLING=fDTS/8, N=6
    PER_TIM_GP_ICF_DTS8_N8  = 0b1001, ///< fSAMPLING=fDTS/8, N=8
    PER_TIM_GP_ICF_DTS16_N5 = 0b1010, ///< fSAMPLING=fDTS/16, N=5
    PER_TIM_GP_ICF_DTS16_N6 = 0b1011, ///< fSAMPLING=fDTS/16, N=6
    PER_TIM_GP_ICF_DTS16_N8 = 0b1100, ///< fSAMPLING=fDTS/16, N=8
    PER_TIM_GP_ICF_DTS32_N5 = 0b1101, ///< fSAMPLING=fDTS/32, N=5
    PER_TIM_GP_ICF_DTS32_N6 = 0b1110, ///< fSAMPLING=fDTS/32, N=6
    PER_TIM_GP_ICF_DTS32_N8 = 0b1111, ///< fSAMPLING=fDTS/32, N=8
} per_tim_gp_icf_e;

/// TIM_GP Output Compare mode
typedef enum
{
    PER_TIM_GP_OCM_FROZEN         = 0b000, ///< No effect
    PER_TIM_GP_OCM_MATCH_ACTIVE   = 0b001, ///< Active level on match
    PER_TIM_GP_OCM_MATCH_INACTIVE = 0b010, ///< Inactive level on match
    PER_TIM_GP_OCM_TOGGLE         = 0b011, ///< Toggles when TIMx_CNT=TIMx_CCRx
    PER_TIM_GP_OCM_FORCE_INACTIVE = 0b100, ///< Forced low
    PER_TIM_GP_OCM_FORCE_ACTIVE   = 0b101, ///< Forced high
    PER_TIM_GP_OCM_PWM_1          = 0b110, ///< High if TIMx_CNT < TIMx_CCRx
    PER_TIM_GP_OCM_PWM_2          = 0b111, ///< Low if TIMx_CNT < TIMx_CCRx
} per_tim_gp_ocm_e;

/// TIM_GP ITR1_RMP TIM2_ITR1 PER_TIM_GP_OR_TIM2 Internal trigger 1 remap
typedef enum
{
    PER_TIM_GP_ITR1_RMP_TIM8_TRG = 0b00, ///< TIM8_TRGOUT
    PER_TIM_GP_ITR1_RMP_PTP      = 0b01, ///< PTP trigger output
    PER_TIM_GP_ITR1_RMP_OTG_FS   = 0b10, ///< OTG FS SOF
    PER_TIM_GP_ITR1_RMP_OTG_HS   = 0b11, ///< OTG HS SOF
} per_tim_gp_itr1_rmp_e;

/// TIM_GP TI4_RMP TIM5_CH4 TIM5_OR Timer Input 4 remap
typedef enum
{
    PER_TIM_GP_TI4_RMP_GPIO = 0b00, ///< GPIO
    PER_TIM_GP_TI4_RMP_LSI  = 0b01, ///< LSI internal clock
    PER_TIM_GP_TI4_RMP_LSE  = 0b10, ///< LSE internal clock
    PER_TIM_GP_TI4_RMP_RTC  = 0b11, ///< RTC wakeup interrupt
} per_tim_gp_ti4_rmp_e;

/// capture/compare mode register (TIMx_CCMR)
typedef struct
{
    per_bit_rw2_t Ccs; ///< Capture/Compare selection
    union
    {
        struct  // output compare
        {
            per_bit_rw1_t Ocfe; ///< Output Compare fast enable
            per_bit_rw1_t Ocpe; ///< Output Compare preload enable
            per_bit_rw3_t Ocm; ///< Output Compare mode
            per_bit_rw1_t Occe; ///< Output Compare clear enable
        };
        struct // input capture
        {
            per_bit_rw2_t Icpsc; ///< Input capture prescaler
            per_bit_rw4_t Icf; ///< Input capture filter
        };
    };
} __attribute__((packed)) per_tim_gp_ccm_t;

typedef struct
{
    // control register 1 (TIMx_CR1)
    per_bit_rw1_t Cen; ///< Counter enable
    per_bit_rw1_t Udis; ///< Update disable
    per_bit_rw1_t Urs; ///< Update request source
    per_bit_rw1_t Opm; ///< One pulse mode
    per_bit_rw1_t Dir; ///< Direction
    per_bit_rw2_t Cms; ///< Center-aligned mode selection
    per_bit_rw1_t Arpe; ///< Auto-reload preload enable
    per_bit_rw2_t Ckd; ///< Clock division
    per_bit_n22_t Cr1bit10; ///< Reserved

    // control register 2 (TIMx_CR2)
    per_bit_n3_t Cr2bit0; ///< Reserved
    per_bit_rw1_t Ccds; ///< Capture/compare DMA selection
    per_bit_rw3_t Mms; ///< Master mode selection
    per_bit_rw1_t Ti1s; ///< TI1 selection
    per_bit_n24_t Cr2bit8; ///< Reserved

    // slave mode control register (TIMx_SMCR)
    per_bit_rw3_t Sms; ///< Slave mode selection
    per_bit_n1_t Smcrbit1; ///< Reserved
    per_bit_rw3_t Ts; ///< Trigger selection
    per_bit_rw1_t Msm; ///< Master/slave mode
    per_bit_rw4_t Etf; ///< External trigger filter
    per_bit_rw2_t Etps; ///< External trigger prescaler
    per_bit_rw1_t Ece; ///< External clock enable
    per_bit_rw1_t Etp; ///< External trigger polarity
    per_bit_n16_t Smcrbit16; ///< Reserved

    // DMA/interrupt enable register (TIMx_DIER)
    union
    {
        struct
        {
            per_bit_rw1_t Uie; ///< Update interrupt enable
            per_bit_rw1_t Cc1ie; ///< Capture/Compare 1 interrupt enable
            per_bit_rw1_t Cc2ie; ///< Capture/Compare 2 interrupt enable
            per_bit_rw1_t Cc3ie; ///< Capture/Compare 3 interrupt enable
            per_bit_rw1_t Cc4ie; ///< Capture/Compare 4 interrupt enable
            per_bit_n1_t Dierbit5; ///< Reserved
            per_bit_rw1_t Tie; ///< Trigger interrupt enable
            per_bit_n1_t Dierbit7; ///< Reserved
            per_bit_rw1_t Ude; ///< Update DMA request enable
            per_bit_rw1_t Cc1de; ///< Capture/Compare 1 DMA request enable
            per_bit_rw1_t Cc2de; ///< Capture/Compare 2 DMA request enable
            per_bit_rw1_t Cc3de; ///< Capture/Compare 3 DMA request enable
            per_bit_rw1_t Cc4de; ///< Capture/Compare 4 DMA request enable
            per_bit_n1_t Dierbit13; ///< Reserved
            per_bit_rw1_t Tde;  ///< Trigger DMA request enable
            per_bit_n17_t Dierbit15; ///< Reserved
        };
        per_bit_rw16_reg_t Dier; ///< DMA/interrupt enable register
    };

    // status register (TIMx_SR)
    union
    {
        struct
        {
            per_bit_rc1_t Uif; ///< Update interrupt flag
            per_bit_rc1_t Cc1if; ///< Capture/Compare 1 interrupt flag
            per_bit_rc1_t Cc2if; ///< Capture/Compare 2 interrupt flag
            per_bit_rc1_t Cc3if; ///< Capture/Compare 3 interrupt flag
            per_bit_rc1_t Cc4if; ///< Capture/Compare 4 interrupt flag
            per_bit_n1_t Srbit5; ///< Reserved
            per_bit_rc1_t Tif; ///< Trigger interrupt flag
            per_bit_n2_t Srbit7; ///< Reserved
            per_bit_rc1_t Cc1of; ///< Capture/Compare 1 overcapture flag
            per_bit_rc1_t Cc2of; ///< Capture/Compare 2 overcapture flag
            per_bit_rc1_t Cc3of; ///< Capture/Compare 3 overcapture flag
            per_bit_rc1_t Cc4of; ///< Capture/Compare 4 overcapture flag
            per_bit_n19_t Srbit13; ///< Reserved
        };
        per_bit_rw16_reg_t Sr; ///< Status register
    };

    // event generation register (TIMx_EGR)
    per_bit_w1_t Ug; ///< Update generation
    per_bit_w1_t Cc1g;  ///< Capture/Compare 1 generation
    per_bit_w1_t Cc2g; ///< Capture/Compare 2 generation
    per_bit_w1_t Cc3g; ///< Capture/Compare 3 generation
    per_bit_w1_t Cc4g; ///< Capture/Compare 4 generation
    per_bit_n1_t Egrbit5; ///< Reserved
    per_bit_w1_t Tg; ///< Trigger generation
    per_bit_n25_t Egrbit7; ///< Reserved

    // capture/compare mode register 1 (TIMx_CCMR1)
    per_tim_gp_ccm_t Ccm1; ///< Capture/Compare 1
    per_tim_gp_ccm_t Ccm2; ///< Capture/Compare 2
    per_bit_n16_t Ccmr1bit16; ///< Reserved

    // capture/compare mode register 2 (TIMx_CCMR2)
    per_tim_gp_ccm_t Ccm3; ///< Capture/Compare 3
    per_tim_gp_ccm_t Ccm4; ///< Capture/Compare 4
    per_bit_n16_t Ccmr2bit16; ///< Reserved

    // capture/compare enable register (TIMx_CCER)
    per_bit_rw1_t Cc1e; ///< Capture/Compare 1 output enable
    per_bit_rw1_t Cc1p; ///< Capture/Compare 1 output polarity
    per_bit_n1_t Ccerbit2; ///< Reserved
    per_bit_rw1_t Cc1np; ///< Capture/Compare 1 complementary output polarity
    per_bit_rw1_t Cc2e; ///< Capture/Compare 2 output enable
    per_bit_rw1_t Cc2p; ///< Capture/Compare 2 output polarity
    per_bit_n1_t Ccerbit6; ///< Reserved
    per_bit_rw1_t Cc2np; ///< Capture/Compare 2 complementary output polarity
    per_bit_rw1_t Cc3e; ///< Capture/Compare 3 output enable
    per_bit_rw1_t Cc3p; ///< Capture/Compare 3 output polarity
    per_bit_n1_t Ccerbit10; ///< Reserved
    per_bit_rw1_t Cc3np; ///< Capture/Compare 3 complementary output polarity
    per_bit_rw1_t Cc4e; ///< Capture/Compare 4 output enable
    per_bit_rw1_t Cc4p; ///< Capture/Compare 4 output polarity
    per_bit_n1_t Ccerbit14; ///< Reserved
    per_bit_rw1_t Cc4np; ///< Capture/Compare 4 complementary output polarity
    per_bit_n16_t Ccerbit16; ///< Reserved

    union
    {
        struct
        {
            // counter (TIMx_CNT)
            per_bit_rw16_reg_t Cnt; ///< Counter
            // prescaler (TIMx_PSC)
            per_bit_rw16_reg_t Psc; ///< Prescaler
            // auto-reload register (TIMx_ARR)
            per_bit_rw16_reg_t Arr; ///< Auto-reload
            // Address offset 0x30
            per_bit_n32_t Reserved0x30; ///< Reserved
            // capture/compare register 1 (TIMx_CCR1)
            per_bit_rw16_reg_t Ccr1; ///< Capture/compare 1
            // capture/compare register 2 (TIMx_CCR2)
            per_bit_rw16_reg_t Ccr2; ///< Capture/compare 2
            // capture/compare register 3 (TIMx_CCR3)
            per_bit_rw16_reg_t Ccr3; ///< Capture/compare register 3
            // capture/compare register 4 (TIMx_CCR4)
            per_bit_rw16_reg_t Ccr4; ///< Capture/compare register 4
        } Size16; // 16 bit default
        struct
        {
            // counter (TIMx_CNT)
            per_bit_rw32_reg_t Cnt; ///< Counter
            // prescaler (TIMx_PSC)
            per_bit_rw16_reg_t Psc; ///< Prescaler
            // auto-reload register (TIMx_ARR)
            per_bit_rw32_reg_t Arr; ///< Auto-reload
            // Address offset 0x30
            per_bit_n32_t Reserved0x30; ///< Reserved
            // capture/compare register 1 (TIMx_CCR1)
            per_bit_rw32_reg_t Ccr1; ///< Capture/compare 1
            // capture/compare register 2 (TIMx_CCR2)
            per_bit_rw32_reg_t Ccr2; ///< Capture/compare 2
            // capture/compare register 3 (TIMx_CCR3)
            per_bit_rw32_reg_t Ccr3; ///< Capture/compare register 3
            // capture/compare register 4 (TIMx_CCR4)
            per_bit_rw32_reg_t Ccr4; ///< Capture/compare register 4
        } Size32; // 32 bit
    };

    // Address offset 0x44
    per_bit_n32_t Reserved0x44; ///< Reserved

    // DMA control register (TIMx_DCR)
    per_bit_rw5_t Dba;      ///< DMA base address
    per_bit_n3_t Dcrbit5;   ///< Reserved
    per_bit_rw5_t Dbl;      ///< DMA burst length
    per_bit_n19_t Dcrbit13; ///< Reserved

    // DMA address for full transfer (TIMx_DMAR)
    per_bit_rw16_reg_t Dmab; ///< DMA register for burst accesses

    // DMA option register (TIMx_OR)
    per_bit_n6_t Dcrbit0;   ///< Reserved
    per_bit_rw2_t Ti4_rmp;  ///< TIM5 Timer Input 4 remap
    per_bit_n2_t Dcrbit8;   ///< Reserved
    per_bit_rw2_t Itr1_rmp; ///< TIM2 Internal trigger 1 remap
    per_bit_n20_t Dcrbit12; ///< Reserved
} __attribute__((packed)) per_tim_gp_per_t;

/// TIM_GP descriptor
typedef struct
{
    per_tim_gp_per_t* const Per;       ///< Peripheral
    const per_log_e Err;               ///< Peripheral error number
    const per_tim_gp_chan_e Chan;      ///< Number of channels
    const per_tim_gp_size_e Size;      ///< 32 bit or 16 bit size
    uint_fast32_t(* const Freq)(void); ///< Pointer to function that resolves base frequency
    const per_tim_gp_or_e Opt;         ///< Option register timer number
} per_tim_gp_t;

/// TIM_GP Counter enable
static per_inline bool per_tim_gp_cen(const per_tim_gp_t* const tim)
{
    return per_bit_rw1(&tim->Per->Cen);
}

/// TIM_GP Counter enable
static per_inline void per_tim_gp_set_cen(const per_tim_gp_t* const tim, bool val)
{
    per_bit_rw1_set(&tim->Per->Cen, val);
}

/// TIM_GP  Update event
static per_inline bool per_tim_gp_udis(const per_tim_gp_t* const tim)
{
    return per_bit_rw1(&tim->Per->Udis);
}

/// TIM_GP  Update event
static per_inline void per_tim_gp_set_udis(const per_tim_gp_t* const tim, bool val)
{
    per_bit_rw1_set(&tim->Per->Udis, val);
}

/// TIM_GP Update request source
static per_inline bool per_tim_gp_urs(const per_tim_gp_t* const tim)
{
    return per_bit_rw1(&tim->Per->Urs);
}

/// TIM_GP Update request source
static per_inline void per_tim_gp_set_urs(const per_tim_gp_t* const tim, bool val)
{
    per_bit_rw1_set(&tim->Per->Urs, val);
}

/// TIM_GP One pulse mode
static per_inline bool per_tim_gp_opm(const per_tim_gp_t* const tim)
{
    return per_bit_rw1(&tim->Per->Opm);
}

/// TIM_GP One pulse mode
static per_inline void per_tim_gp_set_opm(const per_tim_gp_t* const tim, bool val)
{
    per_bit_rw1_set(&tim->Per->Opm, val);
}

/// TIM_GP Direction
static per_inline bool per_tim_gp_dir(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Dir);
}

/// TIM_GP Direction
static per_inline void per_tim_gp_set_dir(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Dir, val);
}

/// TIM_GP Center-aligned mode selection
static per_inline per_tim_gp_cms_e per_tim_gp_cms(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_cms_e)per_bit_rw2(&tim->Per->Cms);
}

/// TIM_GP Center-aligned mode selection
static per_inline bool per_tim_gp_set_cms(const per_tim_gp_t* const tim, per_tim_gp_cms_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw2_set(&tim->Per->Cms, (uint_fast16_t)val);
}

/// TIM_GP Auto-reload preload enable
static per_inline bool per_tim_gp_arpe(const per_tim_gp_t* const tim)
{
    return per_bit_rw1(&tim->Per->Arpe);
}

/// TIM_GP Auto-reload preload enable
static per_inline void per_tim_gp_set_arpe(const per_tim_gp_t* const tim, bool val)
{
    per_bit_rw1_set(&tim->Per->Arpe, val);
}

/// TIM_GP Clock division
static per_inline uint_fast32_t per_tim_gp_ckd(const per_tim_gp_t* const tim)
{
    return per_bit_inv_log2(per_bit_rw2(&tim->Per->Ckd));
}

/// TIM_GP Clock division
static per_inline bool per_tim_gp_set_ckd(const per_tim_gp_t* const tim, uint_fast32_t val)
{
    if ((val > PER_TIM_GP_CKD_MAX) ||
        !per_bit_is_log2(val))
    {
        per_log_err(tim->Err, PER_TIM_GP_CKD_ERR, val);
        return false;
    }

    return per_bit_rw2_set(&tim->Per->Ckd, per_bit_log2(val));
}

/// TIM_GP Capture/compare DMA selection
static per_inline bool per_tim_gp_ccds(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ccds);
}

/// TIM_GP Capture/compare DMA selection
static per_inline void per_tim_gp_set_ccds(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ccds, val);
}

/// TIM_GP Master mode selection
static per_inline per_tim_gp_mms_e per_tim_gp_mms(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_mms_e)per_bit_rw3(&tim->Per->Mms);
}

/// TIM_GP Master mode selection
static per_inline bool per_tim_gp_set_mms(const per_tim_gp_t* const tim, per_tim_gp_mms_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw3_set(&tim->Per->Mms, (uint_fast16_t)val);
}

/// TIM_GP TI1 selection
static per_inline bool per_tim_gp_ti1s(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ti1s);
}

/// TIM_GP TI1 selection
static per_inline void per_tim_gp_set_ti1s(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ti1s, val);
}

/// TIM_GP Slave mode selection
static per_inline per_tim_gp_sms_e per_tim_gp_sms(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_sms_e)per_bit_rw3(&tim->Per->Sms);
}

/// TIM_GP Slave mode selection
static per_inline bool per_tim_gp_set_sms(const per_tim_gp_t* const tim, per_tim_gp_sms_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw3_set(&tim->Per->Sms, (uint_fast16_t)val);
}

/// TIM_GP Trigger selection
static per_inline per_tim_gp_ts_e per_tim_gp_ts(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_ts_e)per_bit_rw3(&tim->Per->Ts);
}

/// TIM_GP Trigger selection
static per_inline bool per_tim_gp_set_ts(const per_tim_gp_t* const tim, per_tim_gp_ts_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw3_set(&tim->Per->Ts, (uint_fast16_t)val);
}

/// TIM_GP Master/slave mode
static per_inline bool per_tim_gp_msm(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Msm);
}

/// TIM_GP Master/slave mode
static per_inline void per_tim_gp_set_msm(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Msm, val);
}

/// TIM_GP External trigger filter
static per_inline per_tim_gp_etf_e per_tim_gp_etf(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_etf_e)per_bit_rw4(&tim->Per->Etf);
}

/// TIM_GP External trigger filter
static per_inline bool per_tim_gp_set_etf(const per_tim_gp_t* const tim, per_tim_gp_etf_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw4_set(&tim->Per->Etf, (uint_fast16_t)val);
}

/// TIM_GP External trigger prescaler
static per_inline uint_fast32_t per_tim_gp_etps(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_inv_log2(per_bit_rw2(&tim->Per->Etps));
}

/// TIM_GP External trigger prescaler
static per_inline bool per_tim_gp_set_etps(const per_tim_gp_t* const tim, uint_fast32_t val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    if ((val > PER_TIM_GP_ETPS_MAX) ||
        !per_bit_is_log2(val))
    {
        per_log_err(tim->Err, PER_TIM_GP_ETPS_ERR, val);
        return false;
    }

    return per_bit_rw2_set(&tim->Per->Etps, per_bit_log2(val));
}

/// TIM_GP External clock enable
static per_inline bool per_tim_gp_ece(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ece);
}

/// TIM_GP External clock enable
static per_inline void per_tim_gp_set_ece(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ece, val);
}

/// TIM_GP External trigger polarity
static per_inline bool per_tim_gp_etp(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Etp);
}

/// TIM_GP External trigger polarity
static per_inline void per_tim_gp_set_etp(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Etp, val);
}

/// TIM_GP Update interrupt enable
static per_inline bool per_tim_gp_uie(const per_tim_gp_t* const tim)
{
    return per_bit_rw1(&tim->Per->Uie);
}

/// TIM_GP Update interrupt enable
static per_inline void per_tim_gp_set_uie(const per_tim_gp_t* const tim, bool val)
{
    per_bit_rw1_set(&tim->Per->Uie, val);
}

/// TIM_GP Capture/Compare 1 interrupt enable
static per_inline bool per_tim_gp_cc1ie(const per_tim_gp_t* const tim)
{
    return per_bit_rw1(&tim->Per->Cc1ie);
}

/// TIM_GP Capture/Compare 1 interrupt enable
static per_inline void per_tim_gp_set_cc1ie(const per_tim_gp_t* const tim, bool val)
{
    per_bit_rw1_set(&tim->Per->Cc1ie, val);
}

/// TIM_GP Capture/Compare 2 interrupt enable
static per_inline bool per_tim_gp_cc2ie(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc2ie);
}

/// TIM_GP Capture/Compare 2 interrupt enable
static per_inline void per_tim_gp_set_cc2ie(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc2ie, val);
}

/// TIM_GP Capture/Compare 3 interrupt enable
static per_inline bool per_tim_gp_cc3ie(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc3ie);
}

/// TIM_GP Capture/Compare 3 interrupt enable
static per_inline void per_tim_gp_set_cc3ie(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc3ie, val);
}

/// TIM_GP Capture/Compare 4 interrupt enable
static per_inline bool per_tim_gp_cc4ie(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc4ie);
}

/// TIM_GP Capture/Compare 4 interrupt enable
static per_inline void per_tim_gp_set_cc4ie(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc4ie, val);
}

/// TIM_GP Trigger interrupt enable
static per_inline bool per_tim_gp_tie(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Tie);
}

/// TIM_GP Trigger interrupt enable
static per_inline void per_tim_gp_set_tie(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Tie, val);
}

/// TIM_GP Update DMA request enable
static per_inline bool per_tim_gp_ude(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ude);
}

/// TIM_GP Update DMA request enable
static per_inline void per_tim_gp_set_ude(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ude, val);
}

/// TIM_GP Capture/Compare 1 DMA request enable
static per_inline bool per_tim_gp_cc1de(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc1de);
}

/// TIM_GP Capture/Compare 1 DMA request enable
static per_inline void per_tim_gp_set_cc1de(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc1de, val);
}

/// TIM_GP Capture/Compare 2 DMA request enable
static per_inline bool per_tim_gp_cc2de(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc2de);
}

/// TIM_GP Capture/Compare 2 DMA request enable
static per_inline void per_tim_gp_set_cc2de(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc2de, val);
}

/// TIM_GP Capture/Compare 3 DMA request enable
static per_inline bool per_tim_gp_cc3de(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc3de);
}

/// TIM_GP Capture/Compare 3 DMA request enable
static per_inline void per_tim_gp_set_cc3de(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc3de, val);
}

/// TIM_GP Capture/Compare 4 DMA request enable
static per_inline bool per_tim_gp_cc4de(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc4de);
}

/// TIM_GP Capture/Compare 4 DMA request enable
static per_inline void per_tim_gp_set_cc4de(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc4de, val);
}

/// TIM_GP Trigger DMA request enable
static per_inline bool per_tim_gp_tde(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Tde);
}

/// TIM_GP Trigger DMA request enable
static per_inline void per_tim_gp_set_tde(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Tde, val);
}

/// TIM_AD DMA/interrupt enable register
static per_inline uint_fast16_t per_tim_gp_dier(const per_tim_gp_t* const tim)
{
    return per_bit_rw16_reg(&tim->Per->Dier);
}

/// TIM_AD DMA/interrupt enable register
static per_inline void per_tim_gp_set_dier(const per_tim_gp_t* const tim, uint16_t val)
{
    per_bit_rw16_reg_set(&tim->Per->Dier, val);
}

/// TIM_GP Update interrupt flag
static per_inline bool per_tim_gp_uif(const per_tim_gp_t* const tim)
{
    return per_bit_rc1(&tim->Per->Uif);
}

/// TIM_GP Update interrupt flag
static per_inline bool per_tim_gp_rdclr_uif(const per_tim_gp_t* const tim)
{
    return per_bit_rc1_rdclr(&tim->Per->Uif);
}

/// TIM_GP Capture/Compare 1 interrupt flag
static per_inline bool per_tim_gp_cc1if(const per_tim_gp_t* const tim)
{
    return per_bit_rc1(&tim->Per->Cc1if);
}

/// TIM_GP Capture/Compare 1 interrupt flag
static per_inline bool per_tim_gp_rdclr_cc1if(const per_tim_gp_t* const tim)
{
    return per_bit_rc1_rdclr(&tim->Per->Cc1if);
}

/// TIM_GP Capture/Compare 2 interrupt flag
static per_inline bool per_tim_gp_cc2if(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1(&tim->Per->Cc2if);
}

/// TIM_GP Capture/Compare 2 interrupt flag
static per_inline bool per_tim_gp_rdclr_cc2if(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1_rdclr(&tim->Per->Cc2if);
}

/// TIM_GP Capture/Compare 3 interrupt flag
static per_inline bool per_tim_gp_cc3if(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1(&tim->Per->Cc3if);
}

/// TIM_GP Capture/Compare 3 interrupt flag
static per_inline bool per_tim_gp_rdclr_cc3if(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1_rdclr(&tim->Per->Cc3if);
}

/// TIM_GP Capture/Compare 4 interrupt flag
static per_inline bool per_tim_gp_cc4if(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1(&tim->Per->Cc4if);
}

/// TIM_GP Capture/Compare 4 interrupt flag
static per_inline bool per_tim_gp_rdclr_cc4if(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1_rdclr(&tim->Per->Cc4if);
}

/// TIM_GP Trigger interrupt flag
static per_inline bool per_tim_gp_tif(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1(&tim->Per->Tif);
}

/// TIM_GP Trigger interrupt flag
static per_inline bool per_tim_gp_rdclr_tif(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1_rdclr(&tim->Per->Tif);
}

/// TIM_GP Capture/Compare 1 overcapture flag
static per_inline bool per_tim_gp_cc1of(const per_tim_gp_t* const tim)
{
    return per_bit_rc1(&tim->Per->Cc1of);
}

/// TIM_GP Capture/Compare 1 overcapture flag
static per_inline bool per_tim_gp_rdclr_cc1of(const per_tim_gp_t* const tim)
{
    return per_bit_rc1_rdclr(&tim->Per->Cc1of);
}

/// TIM_GP Capture/Compare 2 overcapture flag
static per_inline bool per_tim_gp_cc2of(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1(&tim->Per->Cc2of);
}

/// TIM_GP Capture/Compare 2 overcapture flag
static per_inline bool per_tim_gp_rdclr_cc2of(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1_rdclr(&tim->Per->Cc2of);
}

/// TIM_GP Capture/Compare 3 overcapture flag
static per_inline bool per_tim_gp_cc3of(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1(&tim->Per->Cc3of);
}

/// TIM_GP Capture/Compare 3 overcapture flag
static per_inline bool per_tim_gp_rdclr_cc3of(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1_rdclr(&tim->Per->Cc3of);
}

/// TIM_GP Capture/Compare 4 overcapture flag
static per_inline bool per_tim_gp_cc4of(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1(&tim->Per->Cc4of);
}

/// TIM_GP Capture/Compare 4 overcapture flag
static per_inline bool per_tim_gp_rdclr_cc4of(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1_rdclr(&tim->Per->Cc4of);
}

/// TIM_AD Status register
static per_inline uint_fast16_t per_tim_gp_sr(const per_tim_gp_t* const tim)
{
    return per_bit_rw16_reg(&tim->Per->Sr);
}

/// TIM_AD Status register
static per_inline void per_tim_gp_set_sr(const per_tim_gp_t* const tim, uint16_t val)
{
    per_bit_rw16_reg_set(&tim->Per->Sr, val);
}

/// TIM_GP Update generation
static per_inline void per_tim_gp_set_ug(const per_tim_gp_t* const tim, bool val)
{
    per_bit_w1_set(&tim->Per->Ug, val);
}

/// TIM_GP Capture/Compare 1 generation
static per_inline void per_tim_gp_set_cc1g(const per_tim_gp_t* const tim, bool val)
{
    per_bit_w1_set(&tim->Per->Cc1g, val);
}

/// TIM_GP Capture/Compare 2 generation
static per_inline void per_tim_gp_set_cc2g(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_w1_set(&tim->Per->Cc2g, val);
}

/// TIM_GP Capture/Compare 3 generation
static per_inline void per_tim_gp_set_cc3g(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_w1_set(&tim->Per->Cc3g, val);
}

/// TIM_GP Capture/Compare 4 generation
static per_inline void per_tim_gp_set_cc4g(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_w1_set(&tim->Per->Cc4g, val);
}

/// TIM_GP Trigger generation
static per_inline void per_tim_gp_set_tg(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_w1_set(&tim->Per->Tg, val);
}

/// TIM_GP Capture/Compare 1 selection
static per_inline per_tim_gp_ccs_e per_tim_gp_cc1s(const per_tim_gp_t* const tim)
{
    return (per_tim_gp_ccs_e)per_bit_rw2(&tim->Per->Ccm1.Ccs);
}

/// TIM_GP Capture/Compare 1 selection
static per_inline void per_tim_gp_set_cc1s(const per_tim_gp_t* const tim, per_tim_gp_ccs_e val)
{
    per_bit_rw2_set(&tim->Per->Ccm1.Ccs, (uint_fast16_t)val);
}

/// TIM_GP Capture/Compare 2 selection
static per_inline per_tim_gp_ccs_e per_tim_gp_cc2s(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_ccs_e)per_bit_rw2(&tim->Per->Ccm2.Ccs);
}

/// TIM_GP Capture/Compare 2 selection
static per_inline void per_tim_gp_set_cc2s(const per_tim_gp_t* const tim, per_tim_gp_ccs_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw2_set(&tim->Per->Ccm2.Ccs, (uint_fast16_t)val);
}

/// TIM_GP Capture/Compare 3 selection
static per_inline per_tim_gp_ccs_e per_tim_gp_cc3s(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_ccs_e)per_bit_rw2(&tim->Per->Ccm3.Ccs);
}

/// TIM_GP Capture/Compare 3 selection
static per_inline void per_tim_gp_set_cc3s(const per_tim_gp_t* const tim, per_tim_gp_ccs_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw2_set(&tim->Per->Ccm3.Ccs, (uint_fast16_t)val);
}

/// TIM_GP Capture/Compare 4 selection
static per_inline per_tim_gp_ccs_e per_tim_gp_cc4s(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_ccs_e)per_bit_rw2(&tim->Per->Ccm4.Ccs);
}

/// TIM_GP Capture/Compare 4 selection
static per_inline void per_tim_gp_set_cc4s(const per_tim_gp_t* const tim, per_tim_gp_ccs_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw2_set(&tim->Per->Ccm4.Ccs, (uint_fast16_t)val);
}

/// TIM_GP Output Compare 1 fast enable
static per_inline bool per_tim_gp_oc1fe(const per_tim_gp_t* const tim)
{
    return per_bit_rw1(&tim->Per->Ccm1.Ocfe);
}

/// TIM_GP Output Compare 1 fast enable
static per_inline void per_tim_gp_set_oc1fe(const per_tim_gp_t* const tim, bool val)
{
    per_bit_rw1_set(&tim->Per->Ccm1.Ocfe, val);
}

/// TIM_GP Output Compare 2 fast enable
static per_inline bool per_tim_gp_oc2fe(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ccm2.Ocfe);
}

/// TIM_GP Output Compare 2 fast enable
static per_inline void per_tim_gp_set_oc2fe(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ccm2.Ocfe, val);
}

/// TIM_GP Output Compare 3 fast enable
static per_inline bool per_tim_gp_oc3fe(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ccm3.Ocfe);
}

/// TIM_GP Output Compare 3 fast enable
static per_inline void per_tim_gp_set_oc3fe(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ccm3.Ocfe, val);
}

/// TIM_GP Output Compare 4 fast enable
static per_inline bool per_tim_gp_oc4fe(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ccm4.Ocfe);
}

/// TIM_GP Output Compare 4 fast enable
static per_inline void per_tim_gp_set_oc4fe(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ccm4.Ocfe, val);
}

/// TIM_GP Output Compare 1 preload enable
static per_inline bool per_tim_gp_oc1pe(const per_tim_gp_t* const tim)
{
    return per_bit_rw1(&tim->Per->Ccm1.Ocpe);
}

/// TIM_GP Output Compare 1 preload enable
static per_inline void per_tim_gp_set_oc1pe(const per_tim_gp_t* const tim, bool val)
{
    per_bit_rw1_set(&tim->Per->Ccm1.Ocpe, val);
}

/// TIM_GP Output Compare 2 preload enable
static per_inline bool per_tim_gp_oc2pe(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ccm2.Ocpe);
}

/// TIM_GP Output Compare 2 preload enable
static per_inline void per_tim_gp_set_oc2pe(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ccm2.Ocpe, val);
}

/// TIM_GP Output Compare 3 preload enable
static per_inline bool per_tim_gp_oc3pe(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ccm3.Ocpe);
}

/// TIM_GP Output Compare 3 preload enable
static per_inline void per_tim_gp_set_oc3pe(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ccm3.Ocpe, val);
}

/// TIM_GP Output Compare 4 preload enable
static per_inline bool per_tim_gp_oc4pe(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ccm4.Ocpe);
}

/// TIM_GP Output Compare 4 preload enable
static per_inline void per_tim_gp_set_oc4pe(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ccm4.Ocpe, val);
}

// TIM_GP Output Compare 1 mode
static per_inline per_tim_gp_ocm_e per_tim_gp_oc1m(const per_tim_gp_t* const tim)
{
    return (per_tim_gp_ocm_e)per_bit_rw3(&tim->Per->Ccm1.Ocm);
}

// TIM_GP Output Compare 1 mode
static per_inline void per_tim_gp_set_oc1m(const per_tim_gp_t* const tim, per_tim_gp_ocm_e val)
{
    per_bit_rw3_set(&tim->Per->Ccm1.Ocm, (uint_fast16_t)val);
}

// TIM_GP Output Compare 2 mode
static per_inline per_tim_gp_ocm_e per_tim_gp_oc2m(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_ocm_e)per_bit_rw3(&tim->Per->Ccm2.Ocm);
}

// TIM_GP Output Compare 2 mode
static per_inline void per_tim_gp_set_oc2m(const per_tim_gp_t* const tim, per_tim_gp_ocm_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw3_set(&tim->Per->Ccm2.Ocm, (uint_fast16_t)val);
}

// TIM_GP Output Compare 3 mode
static per_inline per_tim_gp_ocm_e per_tim_gp_oc3m(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_ocm_e)per_bit_rw3(&tim->Per->Ccm3.Ocm);
}

// TIM_GP Output Compare 3 mode
static per_inline void per_tim_gp_set_oc3m(const per_tim_gp_t* const tim, per_tim_gp_ocm_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw3_set(&tim->Per->Ccm3.Ocm, (uint_fast16_t)val);
}

// TIM_GP Output Compare 4 mode
static per_inline per_tim_gp_ocm_e per_tim_gp_oc4m(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_ocm_e)per_bit_rw3(&tim->Per->Ccm4.Ocm);
}

// TIM_GP Output Compare 4 mode
static per_inline void per_tim_gp_set_oc4m(const per_tim_gp_t* const tim, per_tim_gp_ocm_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw3_set(&tim->Per->Ccm4.Ocm, (uint_fast16_t)val);
}

/// TIM_GP Output Compare 1 clear enable
static per_inline bool per_tim_gp_oc1ce(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ccm1.Occe);
}

/// TIM_GP Output Compare 1 clear enable
static per_inline void per_tim_gp_set_oc1ce(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ccm1.Occe, val);
}

/// TIM_GP Output Compare 2 clear enable
static per_inline bool per_tim_gp_oc2ce(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ccm2.Occe);
}

/// TIM_GP Output Compare 2 clear enable
static per_inline void per_tim_gp_set_oc2ce(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ccm2.Occe, val);
}

/// TIM_GP Output Compare 3 clear enable
static per_inline bool per_tim_gp_oc3ce(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ccm3.Occe);
}

/// TIM_GP Output Compare 3 clear enable
static per_inline void per_tim_gp_set_oc3ce(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ccm3.Occe, val);
}

/// TIM_GP Output Compare 4 clear enable
static per_inline bool per_tim_gp_oc4ce(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Ccm4.Occe);
}

/// TIM_GP Output Compare 4 clear enable
static per_inline void per_tim_gp_set_oc4ce(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Ccm4.Occe, val);
}

/// TIM_GP Input 1 capture prescaler
static per_inline uint_fast32_t per_tim_gp_ic1psc(const per_tim_gp_t* const tim)
{
    return per_bit_inv_log2(per_bit_rw2(&tim->Per->Ccm1.Icpsc));
}

/// TIM_GP Input 1 capture prescaler
static per_inline bool per_tim_gp_set_ic1psc(const per_tim_gp_t* const tim, uint_fast32_t div)
{
    if ((div > PER_TIM_GP_ICPSC_MAX) ||
        !per_bit_is_log2(div))
    {
        per_log_err(tim->Err, PER_TIM_GP_IC1PSC_ERR, div);
        return false;
    }

    return per_bit_rw2_set(&tim->Per->Ccm1.Icpsc, per_bit_log2(div));
}

/// TIM_GP Input 2 capture prescaler
static per_inline uint_fast32_t per_tim_gp_ic2psc(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_inv_log2(per_bit_rw2(&tim->Per->Ccm2.Icpsc));
}

/// TIM_GP Input 2 capture prescaler
static per_inline bool per_tim_gp_set_ic2psc(const per_tim_gp_t* const tim, uint_fast32_t div)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    if ((div > PER_TIM_GP_ICPSC_MAX) ||
        !per_bit_is_log2(div))
    {
        per_log_err(tim->Err, PER_TIM_GP_IC2PSC_ERR, div);
        return false;
    }

    return per_bit_rw2_set(&tim->Per->Ccm2.Icpsc, per_bit_log2(div));
}

/// TIM_GP Input 3 capture prescaler
static per_inline uint_fast32_t per_tim_gp_ic3psc(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_inv_log2(per_bit_rw2(&tim->Per->Ccm3.Icpsc));
}

/// TIM_GP Input 3 capture prescaler
static per_inline bool per_tim_gp_set_ic3psc(const per_tim_gp_t* const tim, uint_fast32_t div)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    if ((div > PER_TIM_GP_ICPSC_MAX) ||
        !per_bit_is_log2(div))
    {
        per_log_err(tim->Err, PER_TIM_GP_IC3PSC_ERR, div);
        return false;
    }

    return per_bit_rw2_set(&tim->Per->Ccm3.Icpsc, per_bit_log2(div));
}

/// TIM_GP Input 4 capture prescaler
static per_inline uint_fast32_t per_tim_gp_ic4psc(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_inv_log2(per_bit_rw2(&tim->Per->Ccm4.Icpsc));
}

/// TIM_GP Input 4 capture prescaler
static per_inline bool per_tim_gp_set_ic4psc(const per_tim_gp_t* const tim, uint_fast32_t div)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    if ((div > PER_TIM_GP_ICPSC_MAX) ||
        !per_bit_is_log2(div))
    {
        per_log_err(tim->Err, PER_TIM_GP_IC4PSC_ERR, div);
        return false;
    }

    return per_bit_rw2_set(&tim->Per->Ccm4.Icpsc, per_bit_log2(div));
}

/// TIM_GP Input capture 1 filter
static per_inline per_tim_gp_icf_e per_tim_gp_ic1f(const per_tim_gp_t* const tim)
{
    return (per_tim_gp_icf_e)per_bit_rw4(&tim->Per->Ccm1.Icf);
}

/// TIM_GP Input capture 1 filter
static per_inline bool per_tim_gp_set_ic1f(const per_tim_gp_t* const tim, per_tim_gp_icf_e val)
{
    return per_bit_rw4_set(&tim->Per->Ccm1.Icf, (uint_fast16_t)val);
}

/// TIM_GP Input capture 2 filter
static per_inline per_tim_gp_icf_e per_tim_gp_ic2f(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_icf_e)per_bit_rw4(&tim->Per->Ccm2.Icf);
}

/// TIM_GP Input capture 2 filter
static per_inline bool per_tim_gp_set_ic2f(const per_tim_gp_t* const tim, per_tim_gp_icf_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw4_set(&tim->Per->Ccm2.Icf, (uint_fast16_t)val);
}

/// TIM_GP Input capture 3 filter
static per_inline per_tim_gp_icf_e per_tim_gp_ic3f(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_icf_e)per_bit_rw4(&tim->Per->Ccm3.Icf);
}

/// TIM_GP Input capture 3 filter
static per_inline bool per_tim_gp_set_ic3f(const per_tim_gp_t* const tim, per_tim_gp_icf_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw4_set(&tim->Per->Ccm3.Icf, (uint_fast16_t)val);
}

/// TIM_GP Input capture 4 filter
static per_inline per_tim_gp_icf_e per_tim_gp_ic4f(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_icf_e)per_bit_rw4(&tim->Per->Ccm4.Icf);
}

/// TIM_GP Input capture 4 filter
static per_inline bool per_tim_gp_set_ic4f(const per_tim_gp_t* const tim, per_tim_gp_icf_e val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw4_set(&tim->Per->Ccm4.Icf, (uint_fast16_t)val);
}

/// TIM_GP Capture/Compare 1 output enable
static per_inline bool per_tim_gp_cc1e(const per_tim_gp_t* const tim)
{
    return per_bit_rw1(&tim->Per->Cc1e);
}

/// TIM_GP Capture/Compare 1 output enable
static per_inline void per_tim_gp_set_cc1e(const per_tim_gp_t* const tim, bool val)
{
    per_bit_rw1_set(&tim->Per->Cc1e, val);
}

/// TIM_GP Capture/Compare 1 output polarity
static per_inline bool per_tim_gp_cc1p(const per_tim_gp_t* const tim)
{
    return per_bit_rw1(&tim->Per->Cc1p);
}

/// TIM_GP Capture/Compare 1 output polarity
static per_inline void per_tim_gp_set_cc1p(const per_tim_gp_t* const tim, bool val)
{
    per_bit_rw1_set(&tim->Per->Cc1p, val);
}

/// TIM_GP Capture/Compare 1 complementary output polarity
static per_inline bool per_tim_gp_cc1np(const per_tim_gp_t* const tim)
{
    return per_bit_rw1(&tim->Per->Cc1np);
}

/// TIM_GP Capture/Compare 1 complementary output polarity
static per_inline void per_tim_gp_set_cc1np(const per_tim_gp_t* const tim, bool val)
{
    per_bit_rw1_set(&tim->Per->Cc1np, val);
}

/// TIM_GP Capture/Compare 2 output enable
static per_inline bool per_tim_gp_cc2e(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc2e);
}

/// TIM_GP Capture/Compare 2 output enable
static per_inline void per_tim_gp_set_cc2e(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc2e, val);
}

/// TIM_GP Capture/Compare 2 output polarity
static per_inline bool per_tim_gp_cc2p(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc2p);
}

/// TIM_GP Capture/Compare 2 output polarity
static per_inline void per_tim_gp_set_cc2p(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc2p, val);
}

/// TIM_GP Capture/Compare 2 complementary output polarity
static per_inline bool per_tim_gp_cc2np(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc2np);
}

/// TIM_GP Capture/Compare 2 complementary output polarity
static per_inline void per_tim_gp_set_cc2np(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc2np, val);
}

/// TIM_GP Capture/Compare 3 output enable
static per_inline bool per_tim_gp_cc3e(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc3e);
}

/// TIM_GP Capture/Compare 3 output enable
static per_inline void per_tim_gp_set_cc3e(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc3e, val);
}

/// TIM_GP Capture/Compare 3 output polarity
static per_inline bool per_tim_gp_cc3p(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc3p);
}

/// TIM_GP Capture/Compare 3 output polarity
static per_inline void per_tim_gp_set_cc3p(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc3p, val);
}

/// TIM_GP Capture/Compare 3 complementary output polarity
static per_inline bool per_tim_gp_cc3np(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc3np);
}

/// TIM_GP Capture/Compare 3 complementary output polarity
static per_inline void per_tim_gp_set_cc3np(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc3np, val);
}

/// TIM_GP Capture/Compare 4 output enable
static per_inline bool per_tim_gp_cc4e(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc4e);
}

/// TIM_GP Capture/Compare 4 output enable
static per_inline void per_tim_gp_set_cc4e(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc4e, val);
}

/// TIM_GP Capture/Compare 4 output polarity
static per_inline bool per_tim_gp_cc4p(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc4p);
}

/// TIM_GP Capture/Compare 4 output polarity
static per_inline void per_tim_gp_set_cc4p(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc4p, val);
}

/// TIM_GP Capture/Compare 4 complementary output polarity
static per_inline bool per_tim_gp_cc4np(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&tim->Per->Cc4np);
}

/// TIM_GP Capture/Compare 4 complementary output polarity
static per_inline void per_tim_gp_set_cc4np(const per_tim_gp_t* const tim, bool val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&tim->Per->Cc4np, val);
}

/// TIM_GP Counter
static per_inline uint_fast16_t per_tim_gp_cnt(const per_tim_gp_t* const tim)
{
    return per_bit_rw16_reg(&tim->Per->Size16.Cnt);
}

/// TIM_GP Counter
static per_inline void per_tim_gp_set_cnt(const per_tim_gp_t* const tim, uint16_t val)
{
    per_bit_rw16_reg_set(&tim->Per->Size16.Cnt, val);
}

/// TIM_GP Prescaler
static per_inline uint_fast16_t per_tim_gp_psc(const per_tim_gp_t* const tim)
{
    return per_bit_rw16_reg(&tim->Per->Size16.Psc);
}

/// TIM_GP Prescaler
static per_inline void per_tim_gp_set_psc(const per_tim_gp_t* const tim, uint16_t val)
{
    per_bit_rw16_reg_set(&tim->Per->Size16.Psc, val);
}

/// TIM_GP Auto-reload
static per_inline uint_fast16_t per_tim_gp_arr(const per_tim_gp_t* const tim)
{
    return per_bit_rw16_reg(&tim->Per->Size16.Arr);
}

/// TIM_GP Auto-reload
static per_inline void per_tim_gp_set_arr(const per_tim_gp_t* const tim, uint16_t val)
{
    per_bit_rw16_reg_set(&tim->Per->Size16.Arr, val);
}

/// TIM_GP Capture/compare 1
static per_inline uint_fast16_t per_tim_gp_ccr1(const per_tim_gp_t* const tim)
{
    return per_bit_rw16_reg(&tim->Per->Size16.Ccr1);
}

/// TIM_GP Capture/compare 1
static per_inline void per_tim_gp_set_ccr1(const per_tim_gp_t* const tim, uint16_t val)
{
    per_bit_rw16_reg_set(&tim->Per->Size16.Ccr1, val);
}

/// TIM_GP Capture/compare 2
static per_inline uint_fast16_t per_tim_gp_ccr2(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw16_reg(&tim->Per->Size16.Ccr2);
}

/// TIM_GP Capture/compare 2
static per_inline void per_tim_gp_set_ccr2(const per_tim_gp_t* const tim, uint16_t val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw16_reg_set(&tim->Per->Size16.Ccr2, val);
}

/// TIM_GP Capture/compare 3
static per_inline uint_fast16_t per_tim_gp_ccr3(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw16_reg(&tim->Per->Size16.Ccr3);
}

/// TIM_GP Capture/compare 3
static per_inline void per_tim_gp_set_ccr3(const per_tim_gp_t* const tim, uint16_t val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw16_reg_set(&tim->Per->Size16.Ccr3, val);
}

/// TIM_GP Capture/compare 4
static per_inline uint_fast16_t per_tim_gp_ccr4(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw16_reg(&tim->Per->Size16.Ccr4);
}

/// TIM_GP Capture/compare 4
static per_inline void per_tim_gp_set_ccr4(const per_tim_gp_t* const tim, uint16_t val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw16_reg_set(&tim->Per->Size16.Ccr4, val);
}

/// TIM_GP 32bit Counter
static per_inline uint_fast32_t per_tim_gp_32_cnt(const per_tim_gp_t* const tim)
{
    if (tim->Size != PER_TIM_GP_SIZE_32)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw32_reg(&tim->Per->Size32.Cnt);
}

/// TIM_GP 32bit Counter
static per_inline void per_tim_gp_32_set_cnt(const per_tim_gp_t* const tim, uint32_t val)
{
    if (tim->Size != PER_TIM_GP_SIZE_32)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw32_reg_set(&tim->Per->Size32.Cnt, val);
}

/// TIM_GP 32bit Auto-reload
static per_inline uint_fast32_t per_tim_gp_32_arr(const per_tim_gp_t* const tim)
{
    if (tim->Size != PER_TIM_GP_SIZE_32)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw32_reg(&tim->Per->Size32.Arr);
}

/// TIM_GP 32bit Auto-reload
static per_inline void per_tim_gp_32_set_arr(const per_tim_gp_t* const tim, uint32_t val)
{
    if (tim->Size != PER_TIM_GP_SIZE_32)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw32_reg_set(&tim->Per->Size32.Arr, val);
}

/// TIM_GP 32bit Capture/compare 1
static per_inline uint_fast32_t per_tim_gp_32_ccr1(const per_tim_gp_t* const tim)
{
    if (tim->Size != PER_TIM_GP_SIZE_32)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw32_reg(&tim->Per->Size32.Ccr1);
}

/// TIM_GP 32bit Capture/compare 1
static per_inline void per_tim_gp_32_set_ccr1(const per_tim_gp_t* const tim, uint32_t val)
{
    if (tim->Size != PER_TIM_GP_SIZE_32)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw32_reg_set(&tim->Per->Size32.Ccr1, val);
}

/// TIM_GP 32bit Capture/compare 2
static per_inline uint_fast32_t per_tim_gp_32_ccr2(const per_tim_gp_t* const tim)
{
    if ((tim->Size != PER_TIM_GP_SIZE_32) ||
        (tim->Chan < PER_TIM_GP_CHAN_2))
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw32_reg(&tim->Per->Size32.Ccr2);
}

/// TIM_GP 32bit Capture/compare 2
static per_inline void per_tim_gp_32_set_ccr2(const per_tim_gp_t* const tim, uint32_t val)
{
    if ((tim->Size != PER_TIM_GP_SIZE_32) ||
        (tim->Chan < PER_TIM_GP_CHAN_2))
    {
        per_dep_err_unsupported();
    }

    per_bit_rw32_reg_set(&tim->Per->Size32.Ccr2, val);
}

/// TIM_GP 32bit Capture/compare 3
static per_inline uint_fast32_t per_tim_gp_32_ccr3(const per_tim_gp_t* const tim)
{
    if ((tim->Size != PER_TIM_GP_SIZE_32) ||
        (tim->Chan < PER_TIM_GP_CHAN_4))
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw32_reg(&tim->Per->Size32.Ccr3);
}

/// TIM_GP 32bit Capture/compare 3
static per_inline void per_tim_gp_32_set_ccr3(const per_tim_gp_t* const tim, uint32_t val)
{
    if ((tim->Size != PER_TIM_GP_SIZE_32) ||
        (tim->Chan < PER_TIM_GP_CHAN_4))
    {
        per_dep_err_unsupported();
    }

    per_bit_rw32_reg_set(&tim->Per->Size32.Ccr3, val);
}

/// TIM_GP 32bit Capture/compare 4
static per_inline uint_fast32_t per_tim_gp_32_ccr4(const per_tim_gp_t* const tim)
{
    if ((tim->Size != PER_TIM_GP_SIZE_32) ||
        (tim->Chan < PER_TIM_GP_CHAN_4))
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw32_reg(&tim->Per->Size32.Ccr4);
}

/// TIM_GP 32bit Capture/compare 4
static per_inline void per_tim_gp_32_set_ccr4(const per_tim_gp_t* const tim, uint32_t val)
{
    if ((tim->Size != PER_TIM_GP_SIZE_32) ||
        (tim->Chan < PER_TIM_GP_CHAN_4))
    {
        per_dep_err_unsupported();
    }

    per_bit_rw32_reg_set(&tim->Per->Size32.Ccr4, val);
}

/// TIM_GP DMA base address
static per_inline uint_fast16_t per_tim_gp_dba(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw5(&tim->Per->Dba);
}

/// TIM_GP DMA base address
static per_inline bool per_tim_gp_set_dba(const per_tim_gp_t* const tim, uint_fast16_t val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    if (val > per_bit_rw5_max())
    {
        per_log_err(tim->Err, PER_TIM_GP_DBA_ERR, val);
        return false;
    }

    return per_bit_rw5_set(&tim->Per->Dba, val);
}

/// TIM_GP DMA burst length
static per_inline uint_fast16_t per_tim_gp_dbl(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw5(&tim->Per->Dbl) + 1;
}

/// TIM_GP DMA burst length
static per_inline bool per_tim_gp_set_dbl(const per_tim_gp_t* const tim, uint_fast16_t val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    if ((val > PER_TIM_GP_DBL_MAX) ||
        (val == 0))
    {
        per_log_err(tim->Err, PER_TIM_GP_DBL_ERR, val);
        return false;
    }

    return per_bit_rw5_set(&tim->Per->Dbl, val - 1);
}

/// TIM_GP DMA register for burst accesses
static per_inline uint_fast16_t per_tim_gp_dmab(const per_tim_gp_t* const tim)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw16_reg(&tim->Per->Dmab);
}

/// TIM_GP DMA register for burst accesses
static per_inline void per_tim_gp_set_dmab(const per_tim_gp_t* const tim, uint16_t val)
{
    if (tim->Chan < PER_TIM_GP_CHAN_4)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw16_reg_set(&tim->Per->Dmab, val);
}

/// TIM_GP Internal trigger 1 remap
static per_inline per_tim_gp_itr1_rmp_e per_tim_gp_itr1_rmp(const per_tim_gp_t* const tim)
{
    if (tim->Opt != PER_TIM_GP_OR_TIM2)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_itr1_rmp_e)per_bit_rw2(&tim->Per->Itr1_rmp);
}

/// TIM_GP Internal trigger 1 remap
static per_inline bool per_tim_gp_set_itr1_rmp(const per_tim_gp_t* const tim, per_tim_gp_itr1_rmp_e val)
{
    if (tim->Opt != PER_TIM_GP_OR_TIM2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw2_set(&tim->Per->Itr1_rmp, (uint_fast16_t)val);
}

/// TIM_GP Timer Input 4 remap
static per_inline per_tim_gp_ti4_rmp_e per_tim_gp_ti4_rmp(const per_tim_gp_t* const tim)
{
    if (tim->Opt != PER_TIM_GP_OR_TIM5)
    {
        per_dep_err_unsupported();
    }

    return (per_tim_gp_ti4_rmp_e)per_bit_rw2(&tim->Per->Ti4_rmp);
}

/// TIM_GP Timer Input 4 remap
static per_inline bool per_tim_gp_set_ti4_rmp(const per_tim_gp_t* const tim, per_tim_gp_ti4_rmp_e val)
{
    if (tim->Opt != PER_TIM_GP_OR_TIM5)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw2_set(&tim->Per->Ti4_rmp, (uint_fast16_t)val);
}

/// TIM_GP base frequency
static per_inline uint_fast32_t per_tim_gp_freq(const per_tim_gp_t* const tim)
{
    return tim->Freq();
}

/// TIM_GP fetch and clear active interrupts and return the active interrupts
static per_inline per_tim_gp_sr_e per_tim_gp_irq(const per_tim_gp_t* const tim)
{
    uint_fast16_t irq = per_tim_gp_dier(tim) & (uint_fast16_t)PER_TIM_GP_SR_MASK & per_tim_gp_sr(tim);

    per_tim_gp_set_sr(tim, ~irq); // Clear

    return (per_tim_gp_sr_e)irq;
}

/// TIM_GP set update time
/// time: [ms] time in milli seconds
static per_inline bool per_tim_gp_set_milli(const per_tim_gp_t* const tim, uint_fast32_t psc, uint_fast32_t milli)
{
    uint_fast32_t arr = (uint_fast32_t)((((uint64_t)tim->Freq() * (uint64_t)milli) + PER_TIM_GP_MILLI_ROUND) /
                   (PER_TIM_GP_MILLI_DIV * (uint64_t)psc));

    psc -= 1;
    arr -= 1;

    if (psc > PER_TIM_GP_PSC_MAX)
    {
        per_log_err(tim->Err, PER_TIM_GP_TIME_MILLI_PSC_ERR, psc);
        return false;
    }

    if (arr > PER_TIM_GP_ARR_MAX)
    {
        per_log_err(tim->Err, PER_TIM_GP_TIME_MILLI_ERR, milli);
        return false;
    }

    per_tim_gp_set_psc(tim, (uint16_t)psc);
    per_tim_gp_set_arr(tim, (uint16_t)arr);
    return true;
}

/// TIM_GP set update time for 32 bit size counters
/// time: [ms] time in milli seconds
static per_inline bool per_tim_gp_32_set_milli(const per_tim_gp_t* const tim, uint_fast32_t psc, uint_fast32_t milli)
{
    uint_fast64_t arr = (uint_fast32_t)((((uint64_t)tim->Freq() * (uint64_t)milli) + PER_TIM_GP_MILLI_ROUND) /
                   (PER_TIM_GP_MILLI_DIV * (uint64_t)psc));

    psc -= 1;
    arr -= 1;

    if (psc > PER_TIM_GP_PSC_MAX)
    {
        per_log_err(tim->Err, PER_TIM_GP_TIME_MILLI_32_PSC_ERR, psc);
        return false;
    }

    if (arr > PER_TIM_GP_32_ARR_MAX)
    {
        per_log_err(tim->Err, PER_TIM_GP_TIME_MILLI_32_ERR, milli);
        return false;
    }

    per_tim_gp_set_psc(tim, (uint16_t)psc);
    per_tim_gp_32_set_arr(tim, (uint32_t)arr);
    return true;
}

/// TIM_GP set update time
/// time: [ns] time in nano seconds
static per_inline bool per_tim_gp_set_nano(const per_tim_gp_t* const tim, uint_fast32_t psc, uint_fast32_t nano)
{
    uint_fast32_t arr = (uint_fast32_t)((((uint64_t)tim->Freq() * (uint64_t)nano) + PER_TIM_GP_NANO_ROUND) /
                   (PER_TIM_GP_NANO_DIV * (uint64_t)psc));

    psc -= 1;
    arr -= 1;

    if (psc > PER_TIM_GP_PSC_MAX)
    {
        per_log_err(tim->Err, PER_TIM_GP_TIME_NANO_PSC_ERR, psc);
        return false;
    }

    if (arr > PER_TIM_GP_ARR_MAX)
    {
        per_log_err(tim->Err, PER_TIM_GP_TIME_NANO_ERR, nano);
        return false;
    }

    per_tim_gp_set_psc(tim, (uint16_t)psc);
    per_tim_gp_set_arr(tim, (uint16_t)arr);
    return true;
}

/// TIM_GP set update time for 32 bit size counters
/// time: [ns] time in nano seconds
static per_inline bool per_tim_gp_32_set_nano(const per_tim_gp_t* const tim, uint_fast32_t psc, uint_fast32_t nano)
{
    uint_fast64_t arr = (uint_fast32_t)((((uint64_t)tim->Freq() * (uint64_t)nano) + PER_TIM_GP_NANO_ROUND) /
                   (PER_TIM_GP_NANO_DIV * (uint64_t)psc));

    psc -= 1;
    arr -= 1;

    if (psc > PER_TIM_GP_PSC_MAX)
    {
        per_log_err(tim->Err, PER_TIM_GP_TIME_NANO_32_PSC_ERR, psc);
        return false;
    }

    if (arr > PER_TIM_GP_32_ARR_MAX)
    {
        per_log_err(tim->Err, PER_TIM_GP_TIME_NANO_32_ERR, nano);
        return false;
    }

    per_tim_gp_set_psc(tim, (uint16_t)psc);
    per_tim_gp_32_set_arr(tim, (uint32_t)arr);
    return true;
}

#ifdef __cplusplus
}
#endif

#endif // per_tim_gp_f4_h_
