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

/// PWR base address
#define PER_PWR ((per_pwr_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB2 + (uintptr_t)0x3800))

/// PWR VOS 1 bit mask
#define PER_PWR_VOS_MASK (0b10)

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
    PER_PWR_U_DISABLED = 0b00, ///< Disabled
    PER_PWR_U_ACTIVATED = 0b11, ///< Activated in Stop mode.
} per_pwr_u_e;

typedef struct
{
    // power control register (PWR_CR)
    per_bit_rw1_t Lpds; ///< Low-power deepsleep
    per_bit_rw1_t Pdds; ///< Power-down deepsleep
    per_bit_rc1_w1_t Cwuf; ///< Clear wakeup flag
    per_bit_rc1_w1_t Csbf; ///< Clear standby flag
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
} __attribute__((packed)) per_pwr_per_t;

/// PWR descriptor
typedef struct
{
    per_pwr_per_t* const Per; ///< Peripheral
    const per_log_e Err;      ///< Peripheral error number
    const bool Adcdc;         ///< DC for ADC1
    const bool Drive;         ///< Over/Under
    const bool Vos;           ///< Regulator voltage scaling 2 bits
} per_pwr_t;

/// PWR Low-power deepsleep
static per_inline bool per_pwr_lpds(const per_pwr_t* const pwr)
{
    return per_bit_rw1(&pwr->Per->Lpds);
}

/// PWR Low-power deepsleep
static per_inline void per_pwr_set_lpds(const per_pwr_t* const pwr, bool val)
{
    per_bit_rw1_set(&pwr->Per->Lpds, val);
}

/// PWR Power-down deepsleep
static per_inline bool per_pwr_pdds(const per_pwr_t* const pwr)
{
    return per_bit_rw1(&pwr->Per->Pdds);
}

/// PWR Power-down deepsleep
static per_inline void per_pwr_set_pdds(const per_pwr_t* const pwr, bool val)
{
    per_bit_rw1_set(&pwr->Per->Pdds, val);
}

/// PWR Clear wakeup flag
static per_inline bool per_pwr_cwuf(const per_pwr_t* const pwr)
{
    return per_bit_rc1_w1(&pwr->Per->Cwuf);
}

/// PWR Clear wakeup flag
static per_inline bool per_pwr_clr_cwuf(const per_pwr_t* const pwr)
{
    return per_bit_rc1_w1_rdclr(&pwr->Per->Cwuf);
}

/// PWR Clear standby flag
static per_inline bool per_pwr_csbf(const per_pwr_t* const pwr)
{
    return per_bit_rc1_w1(&pwr->Per->Csbf);
}

/// PWR Clear standby flag
static per_inline bool per_pwr_set_csbf(const per_pwr_t* const pwr)
{
    return per_bit_rc1_w1_rdclr(&pwr->Per->Csbf);
}

/// PWR Power voltage detector enable
static per_inline bool per_pwr_pvde(const per_pwr_t* const pwr)
{
    return per_bit_rw1(&pwr->Per->Pvde);
}

/// PWR Power voltage detector enable
static per_inline void per_pwr_set_pvde(const per_pwr_t* const pwr, bool val)
{
    per_bit_rw1_set(&pwr->Per->Pvde, val);
}

/// PWR PVD level selection
static per_inline per_pwr_pls_e per_pwr_pls(const per_pwr_t* const pwr)
{
    return (per_pwr_pls_e)per_bit_rw3(&pwr->Per->Pls);
}

/// PWR PVD level selection
static per_inline void per_pwr_set_pls(const per_pwr_t* const pwr, per_pwr_pls_e val)
{
    per_bit_rw3_set(&pwr->Per->Pls, (uint_fast16_t)val);
}

/// PWR Disable backup domain write protection
static per_inline bool per_pwr_dbp(const per_pwr_t* const pwr)
{
    return per_bit_rw1(&pwr->Per->Dbp);
}

/// PWR Disable backup domain write protection
static per_inline void per_pwr_set_dbp(const per_pwr_t* const pwr, bool val)
{
    per_bit_rw1_set(&pwr->Per->Dbp, val);
}

/// PWR Flash power-down in Stop mode
static per_inline bool per_pwr_fpds(const per_pwr_t* const pwr)
{
    return per_bit_rw1(&pwr->Per->Fpds);
}

/// PWR Flash power-down in Stop mode
static per_inline void per_pwr_set_fpds(const per_pwr_t* const pwr, bool val)
{
    per_bit_rw1_set(&pwr->Per->Fpds, val);
}

/// PWR Low-power regulator in deepsleep under-drive mode
static per_inline bool per_pwr_lpuds(const per_pwr_t* const pwr)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&pwr->Per->Lpuds);
}

/// PWR Low-power regulator in deepsleep under-drive mode
static per_inline void per_pwr_set_lpuds(const per_pwr_t* const pwr, bool val)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&pwr->Per->Lpuds, val);
}

/// PWR Main regulator in deepsleep under-drive mode
static per_inline bool per_pwr_mruds(const per_pwr_t* const pwr)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&pwr->Per->Mruds);
}

/// PWR Main regulator in deepsleep under-drive mode
static per_inline void per_pwr_set_mruds(const per_pwr_t* const pwr, bool val)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&pwr->Per->Mruds, val);
}

/// PWR Improve ADC accuracy
static per_inline bool per_pwr_adcdc1(const per_pwr_t* const pwr)
{
    if (!pwr->Adcdc)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&pwr->Per->ADCDC1);
}

/// PWR Improve ADC accuracy
static per_inline void per_pwr_set_adcdc1(const per_pwr_t* const pwr, bool val)
{
    per_bit_rw1_set(&pwr->Per->ADCDC1, val);
}

/// PWR Regulator voltage scaling output selection
static per_inline per_pwr_vos_e per_pwr_vos(const per_pwr_t* const pwr)
{
    uint_fast16_t val = per_bit_rw2(&pwr->Per->Vos);

    if (!pwr->Vos)
    {
        val |= PER_PWR_VOS_MASK;
    }

    return (per_pwr_vos_e)val;
}

/// PWR Regulator voltage scaling output selection
static per_inline void per_pwr_set_vos(const per_pwr_t* const pwr, per_pwr_vos_e val)
{
     uint_fast16_t vos = (uint_fast16_t)val;

    if (!pwr->Vos)
    {
        vos &= ~PER_PWR_VOS_MASK;
    }

    per_bit_rw2_set(&pwr->Per->Vos, vos);
}

/// PWR Over-drive enable
static per_inline bool per_pwr_oden(const per_pwr_t* const pwr)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&pwr->Per->Oden);
}

/// PWR Over-drive enable
static per_inline void per_pwr_set_oden(const per_pwr_t* const pwr, bool val)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&pwr->Per->Oden, val);
}

/// PWR Over-drive switching enabled
static per_inline bool per_pwr_odswen(const per_pwr_t* const pwr)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&pwr->Per->Odswen);
}

/// PWR Over-drive switching enabled
static per_inline void per_pwr_set_odswen(const per_pwr_t* const pwr, bool val)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&pwr->Per->Odswen, val);
}

/// PWR Under-drive enable in stop mode
static per_inline per_pwr_u_e per_pwr_uden(const per_pwr_t* const pwr)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    return (per_pwr_u_e)per_bit_rw2(&pwr->Per->Uden);
}

/// PWR Under-drive enable in stop mode
static per_inline void per_pwr_set_uden(const per_pwr_t* const pwr, per_pwr_u_e val)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw2_set(&pwr->Per->Uden, (uint_fast16_t)val);
}

/// PWR Wakeup flag
static per_inline bool per_pwr_wuf(const per_pwr_t* const pwr)
{
    return per_bit_r1(&pwr->Per->Wuf);
}

/// PWR Standby flag
static per_inline bool per_pwr_sbf(const per_pwr_t* const pwr)
{
    return per_bit_r1(&pwr->Per->Sbf);
}

/// PWR PVD output
static per_inline bool per_pwr_pvdo(const per_pwr_t* const pwr)
{
    return per_bit_r1(&pwr->Per->Pvdo);
}

/// PWR Backup regulator ready
static per_inline bool per_pwr_brr(const per_pwr_t* const pwr)
{
    return per_bit_r1(&pwr->Per->Brr);
}

/// PWR Enable WKUP pin
static per_inline bool per_pwr_ewup(const per_pwr_t* const pwr)
{
    return per_bit_rw1(&pwr->Per->Ewup);
}

/// PWR Enable WKUP pin
static per_inline void per_pwr_set_ewup(const per_pwr_t* const pwr, bool val)
{
    per_bit_rw1_set(&pwr->Per->Ewup, val);
}

/// PWR Backup regulator enable
static per_inline bool per_pwr_bre(const per_pwr_t* const pwr)
{
    return per_bit_rw1(&pwr->Per->Bre);
}

/// PWR Backup regulator enable
static per_inline void per_pwr_set_bre(const per_pwr_t* const pwr, bool val)
{
    per_bit_rw1_set(&pwr->Per->Bre, val);
}

/// PWR Regulator voltage scaling output selection ready bit
static per_inline bool per_pwr_vosrdy(const per_pwr_t* const pwr)
{
    return per_bit_r1(&pwr->Per->Vosrdy);
}

/// PWR Over-drive mode ready
static per_inline bool per_pwr_ordy(const per_pwr_t* const pwr)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    return per_bit_r1(&pwr->Per->Ordy);
}

/// PWR Over-drive mode switching ready
static per_inline bool per_pwr_odswrdy(const per_pwr_t* const pwr)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    return per_bit_r1(&pwr->Per->Odswrdy);
}

/// PWR Under-drive ready flag
static per_inline per_pwr_u_e per_pwr_urdy(const per_pwr_t* const pwr)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    return (per_pwr_u_e)per_bit_rw2(&pwr->Per->Urdy);
}

/// PWR Under-drive ready flag
static per_inline void per_pwr_clr_urdy(const per_pwr_t* const pwr)
{
    if (!pwr->Drive)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw2_set(&pwr->Per->Urdy, (uint_fast16_t)PER_PWR_U_ACTIVATED);
}

#ifdef __cplusplus
}
#endif

#endif // per_pwr_f4_h_
