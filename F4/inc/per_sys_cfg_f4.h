/**
 * @file per_sys_cfg_f4.h
 *
 * This file contains the peripheral system configuration (SYSCFG)
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

#ifndef per_sys_cfg_f4_h_
#define per_sys_cfg_f4_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_bit_f4.h"

/// SYSCFG base address
#define PER_SYSCFG ((per_sys_cfg_t*)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB2 + (uintptr_t)0x3800))

typedef struct
{
    // SYSCFG memory re-map register (SYSCFG_MEMRMP)
    per_bit_rw3_t MemMode; ///< Memory mapping selection
    per_bit_n5_t MemRmpBit3; ///< Reserved
    per_bit_rw1_t Fb_mode; ///< Flash Bank mode selection
    per_bit_n1_t MemRmpBit9; ///< Reserved
    per_bit_rw2_t Swp_fmc; ///< FMC memory mapping swap
    per_bit_n20_t MemRmpBit12; ///< Reserved

    // SYSCFG peripheral mode configuration register (SYSCFG_PMC)
    per_bit_n16_t PmcBit0; ///< Reserved
    per_bit_rw3_t Adcxdc2; ///< Refer to AN4073 on how to use this bit.
    per_bit_n4_t PmcBit19; ///< Reserved
    per_bit_rw1_t MiiRmiiSel; ///< Ethernet PHY interface selection
    per_bit_n8_t PmcBit24; ///< Reserved

    // SYSCFG external interrupt configuration register 1 (SYSCFG_EXTICR1)
    per_bit_rw4_t Exti0; ///< EXTI 0 configuration
    per_bit_rw4_t Exti1; ///< EXTI 1 configuration
    per_bit_rw4_t Exti2; ///< EXTI 2 configuration
    per_bit_rw4_t Exti3; ///< EXTI 3 configuration
    per_bit_n16_t Exti1ReservedBit16; ///< Reserved

    // SYSCFG external interrupt configuration register 2 (SYSCFG_EXTICR2)
    per_bit_rw4_t Exti4; ///< EXTI 4 configuration
    per_bit_rw4_t Exti5; ///< EXTI 5 configuration
    per_bit_rw4_t Exti6; ///< EXTI 6 configuration
    per_bit_rw4_t Exti7; ///< EXTI 7 configuration
    per_bit_n16_t Exti2Bit16; ///< Reserved

    // SYSCFG external interrupt configuration register 3 (SYSCFG_EXTICR3)
    per_bit_rw4_t Exti8; ///< EXTI 8 configuration
    per_bit_rw4_t Exti9; ///< EXTI 9 configuration
    per_bit_rw4_t Exti10; ///< EXTI 10 configuration
    per_bit_rw4_t Exti11; ///< EXTI 11 configuration
    per_bit_n16_t Exti3Bit16; ///< Reserved

    // SYSCFG external interrupt configuration register 4 (SYSCFG_EXTICR4)
    per_bit_rw4_t Exti12; ///< EXTI 12 configuration
    per_bit_rw4_t Exti13; ///< EXTI 13 configuration
    per_bit_rw4_t Exti14; ///< EXTI 14 configuration
    per_bit_rw4_t Exti15; ///< EXTI 15 configuration
    per_bit_n16_t Exti4Bit16; ///< Reserved

    // SYSCFG Reserved
    per_bit_n32_t Reserved_0x18; ///< Reserved
    per_bit_n32_t Reserved_0x1C; ///< Reserved

    // Compensation cell control register (SYSCFG_CMPCR)
    per_bit_rw1_t CmpPd; ///< Compensation cell power-down
    per_bit_n7_t CmpCrBit1; ///< Reserved
    per_bit_r1_t Ready; ///< Compensation cell ready flag
    per_bit_n23_t CmpCrBit9; ///< Reserved
} per_sys_cfg_t;

#ifdef __cplusplus
}
#endif

#endif // per_sys_cfg_f4_h_
