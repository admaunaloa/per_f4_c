/**
 * @file per_pwr_f4.h
 *
 * This file contains the power controller (PWR)
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

#ifndef per_pwr_f4_h_
#define per_pwr_f4_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_bit_f4.h"

/// PWR PVD level selection enumeration
typedef enum
{
    PER_PWR_PLS_2_0 = 0b000, ///< 2.0V
    PER_PWR_PLS_2_1 = 0b001, ///< 2.1V
    PER_PWR_PLS_2_3 = 0b010, ///< 2.3V
    PER_PWR_PLS_2_5 = 0b011, ///< 2.5V
    PER_PWR_PLS_2_6 = 0b100, ///< 2.6V
    PER_PWR_PLS_2_7 = 0b101, ///< 2.7V
    PER_PWR_PLS_2_8 = 0b110, ///< 2.8V
    PER_PWR_PLS_2_9 = 0b111, ///< 2.9V
} per_pwr_pls_e;

/// PWR Regulator voltage scaling output selection enumeration
typedef enum
{
    PER_PWR_VOS_3 = 0b01, ///< Scale 3 mode
    PER_PWR_VOS_2 = 0b10, ///< Scale 2 mode
    PER_PWR_VOS_1 = 0b11, ///< Scale 1 mode (default)
} per_pwr_vos_e;

/// PWR Under-drive ready enumeration
typedef enum
{
    PER_PWR_URDY_DISABLED = 0b00, ///< Disabled
    PER_PWR_URDY_ACTIVATED = 0b11, ///< Activated in Stop mode.
} per_pwr_urdy_e;

typedef struct
{
    // power control register (PWR_CR)
    per_bit_rw1_t Lpds; ///< Low-power deepsleep
    per_bit_rw1_t Pdds; ///< Power-down deepsleep
    per_bit_rc1_t Cwuf; ///< Clear wakeup flag
    per_bit_rc1_t Csbf; ///< Clear standby flag
    per_bit_rw1_t Pvde; ///< Power voltage detector enable
    per_bit_rw3_t Pls; ///< PVD level selection
    per_bit_rw1_t Dbp; ///< Disable backup domain write protection
    per_bit_rw1_t Fpds; ///< Flash power-down in Stop mode
    per_bit_rw1_t Lpuds; ///< Low-power regulator in deepsleep under-drive mode
    per_bit_rw1_t Mruds; ///< Main regulator in deepsleep under-drive mode
    per_bit_n1_t PwrcrBit12; ///< Reserved
    per_bit_rw1_t ADCDC1; ///< Improve ADC accuracy AN4073
    per_bit_rw2_t Vos; ///< Regulator voltage scaling output selection
    per_bit_rw1_t Oden; ///< Over-drive enable
    per_bit_rw1_t Odswen; ///< Over-drive switching enabled.
    per_bit_rw2_t Uden; ///< Under-drive enable in stop mode
    per_bit_n12_t PwrcrBit20; ///< Reserved

    // power control status register (PWR_CSR)
    per_bit_r1_t Wuf; ///< Wakeup flag
    per_bit_r1_t Sbf; ///< Standby flag
    per_bit_r1_t Pvdo; ///< PVD output
    per_bit_r1_t Brr; ///< Backup regulator ready
    per_bit_n4_t PwrcsrBit4; ///< Reserved
    per_bit_rw1_t Ewup; ///< Enable WKUP pin
    per_bit_rw1_t Bre; ///< Backup regulator enable
    per_bit_n4_t PwrcsrBit10; ///< Reserved
    per_bit_r1_t Vosrdy; ///< Regulator voltage scaling output selection ready bit
    per_bit_n1_t PwrcsrBit15; ///< Reserved
    per_bit_r1_t Ordy; ///< Over-drive mode ready
    per_bit_r1_t Odswrdy; ///< Over-drive mode switching ready
    per_bit_rw2_t Urdy; ///< Under-drive ready flag
    per_bit_n12_t PwrcsrBit20; ///< Reserved
} __attribute__((packed)) per_pwr_t;

#ifdef __cplusplus
}
#endif

#endif // per_pwr_f4_h_
