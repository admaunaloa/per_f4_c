/**
 * @file per_flash_f4.h
 *
 * This file contains the flash interface (FLASH)
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

#ifndef per_flash_f4_h_
#define per_flash_f4_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_bit_f4.h"
#include "per_log_f4.h"

/// FLASH base address
#define PER_FLASH ((per_flash_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_AHB1 + (uintptr_t)0x3C00))

/// Program size psize multiplier
#define PER_FLASH_PSIZE_MULT (8)

/// Sector number maximum per bank
#define PER_FLASH_SNB_MAX (12)

/// Sector number Most Significant Bit
#define PER_FLASH_SNB_MSB (0b00010000)

/// FLASH error enumeration
typedef enum
{
    PER_FLASH_OK_ERR = PER_LOG_FLASH * PER_LOG_MULT, ///< No error
    PER_FLASH_LATENCY_ERR,
    PER_FLASH_SNB_ERR,
    PER_FLASH_PSIZE_ERR,
} per_flash_error_e;

/// FLASH Latency size
typedef enum
{
    PER_FLASH_LATENCY_SIZE_3 = 3,
    PER_FLASH_LATENCY_SIZE_4 = 4,
} per_flash_latency_size_e;

/// FLASH key enumeration
typedef enum
{
    PER_FLASH_KEY1 = 0x45670123,
    PER_FLASH_KEY2 = 0xCDEF89AB,
} per_flash_key_e;

/// FLASH optkey enumeration
typedef enum
{
    PER_FLASH_OPTKEY1 = 0x08192A3B,
    PER_FLASH_OPTKEY2 = 0x4C5D6E7F,
} per_flash_optkey_e;

/// FLASH Not write protect sector enumeration
typedef enum
{
    PER_FLASH_NWRP_0 =  0b000000000001,
    PER_FLASH_NWRP_1 =  0b000000000010,
    PER_FLASH_NWRP_2 =  0b000000000100,
    PER_FLASH_NWRP_3 =  0b000000001000,
    PER_FLASH_NWRP_4 =  0b000000010000,
    PER_FLASH_NWRP_5 =  0b000000100000,
    PER_FLASH_NWRP_6 =  0b000001000000,
    PER_FLASH_NWRP_7 =  0b000010000000,
    PER_FLASH_NWRP_8 =  0b000100000000,
    PER_FLASH_NWRP_9 =  0b001000000000,
    PER_FLASH_NWRP_10 = 0b010000000000,
    PER_FLASH_NWRP_11 = 0b100000000000,
} per_flash_nwrp_e;

typedef struct
{
    // Flash access control register (FLASH_ACR)
    per_bit_rw4_t Latency; ///< Latency
    per_bit_n4_t AcrBit4; ///< Reserved
    per_bit_rw1_t Prften; ///< Prefetch enable
    per_bit_rw1_t Icen; ///< Instruction cache enable
    per_bit_rw1_t Dcen; ///< Data cache enable
    per_bit_rw1_t Icrst; ///< Instruction cache reset
    per_bit_rw1_t Dcrst; ///< Data cache reset
    per_bit_n19_t AcrBit13; ///< Reserved

    // Flash key register (FLASH_KEYR)
    per_bit_w32_reg_t Key; ///< The Flash key register

    // Flash option key register (FLASH_OPTKEYR)
    per_bit_w32_reg_t Optkey; ///< The Flash option key register

    // Flash status register (FLASH_SR)
    per_bit_rc1_w1_t Eop; ///< End of operation
    per_bit_rc1_w1_t Operr; ///< Operation error
    per_bit_n2_t SrBit2; ///< Reserved
    per_bit_rc1_w1_t Wrperr; ///< Write protection error
    per_bit_rc1_w1_t Pgaerr; ///< Programming alignment error
    per_bit_rc1_w1_t Pgperr; ///< Programming parallelism error
    per_bit_rc1_w1_t Pgserr; ///< Programming sequence error
    per_bit_rc1_w1_t Rderr; ///< Proprietary readout protection (PCROP) error
    per_bit_n7_t SrBit9; ///< Reserved
    per_bit_r1_t Bsy; ///< Busy
    per_bit_n15_t SrBit17; ///< Reserved

    // Flash control register (FLASH_CR)
    per_bit_rw1_t Pg; ///< Programming
    per_bit_rw1_t Ser; ///< Sector Erase
    per_bit_rw1_t Mer; ///< Mass Erase of bank 1 sectors
    per_bit_rw5_t Snb; ///< Sector number
    per_bit_rw2_t Psize; ///< Program size
    per_bit_n5_t CrBit10; ///< Reserved
    per_bit_rw1_t Mer1; ///< Mass Erase of bank 2 sectors
    per_bit_rs1_t Strt; ///< Start
    per_bit_n7_t CrBit17; ///< Reserved
    per_bit_rw1_t Eopie; ///< End of operation interrupt enable
    per_bit_rw1_t Errie; ///< Error interrupt enable
    per_bit_n5_t CrBit26; ///< Reserved
    per_bit_rs1_t Lock; ///< Lock

    // Flash option control register (FLASH_OPTCR)
    per_bit_rs1_t Optlock; ///< Option lock
    per_bit_rs1_t Optstrt; ///< Option start
    per_bit_rw2_t Bor_lev; ///< BOR reset Level
    per_bit_rw1_t Bfb2; ///< Dual-bank Boot option byte
    per_bit_rw1_t Wdg_sw; ///< WDG_SW
    per_bit_rw1_t Nrst_stop; ///< nRST_STOP
    per_bit_rw1_t Nrst_stdby; ///< nRST_STDBY
    per_bit_r8_t Rdp; ///< Read protect
    per_bit_rw12_t Nwrp; ///< Not write protect
    per_bit_n2_t OptcrBit28; ///< Reserved
    per_bit_rw1_t Db1m; ///< Dual-bank on 1 Mbyte Flash memory devices
    per_bit_rw1_t Sprmod; ///< Selection of protection mode for nWPRi bits

    // Flash option control register (FLASH_OPTCR1)
    per_bit_n16_t Optcr1Bit0; ///< Reserved
    per_bit_rw12_t Nwrp1; ///< Not write protect bank 2
    per_bit_n4_t Optcr1Bit28; ///< Reserved
} __attribute__((packed)) per_flash_per_t;

/// FLASH descriptor
typedef struct
{
    per_flash_per_t* const Per;                 ///< Interface
    const per_log_e Err;                        ///< Peripheral error number
    const per_flash_latency_size_e LatencySize; ///< Nnumber of bits for latency
    const uint_fast16_t Banks;                  ///< Maximum family flash size value F41 = 1 Mbyte, F42 = 2 Mbyte
    const bool PropProt;                        ///< Proprietary code readout protection
} per_flash_t;

/// FLASH Latency
static per_inline uint_fast16_t per_flash_latency(const per_flash_t* const flash)
{
    return per_bit_rw4(&flash->Per->Latency);
}

/// FLASH Latency
static per_inline bool per_flash_set_latency(const per_flash_t* const flash, uint_fast16_t lat)
{
    uint_fast16_t max = per_bit_rw3_max();

    if (flash->LatencySize == PER_FLASH_LATENCY_SIZE_4)
    {
        max = per_bit_rw4_max();
    }

    if (lat > max)
    {
        per_log_err(flash->Err, PER_FLASH_LATENCY_ERR, lat);
        return false;
    }

    per_bit_rw4_set(&flash->Per->Latency, max); // Set this to prevent temporary illegal values during the next write

    return per_bit_rw4_set(&flash->Per->Latency, lat);
}

/// FLASH Prefetch enable
static per_inline bool per_flash_prften(const per_flash_t* const flash)
{
    return per_bit_rw1(&flash->Per->Prften);
}

/// FLASH Prefetch enable
static per_inline void per_flash_set_prften(const per_flash_t* const flash, bool val)
{
    per_bit_rw1_set(&flash->Per->Prften, val);
}

/// FLASH Instruction cache enable
static per_inline bool per_flash_icen(const per_flash_t* const flash)
{
    return per_bit_rw1(&flash->Per->Icen);
}

/// FLASH Instruction cache enable
static per_inline void per_flash_set_icen(const per_flash_t* const flash, bool val)
{
    per_bit_rw1_set(&flash->Per->Icen, val);
}

/// FLASH Data cache enable
static per_inline bool per_flash_dcen(const per_flash_t* const flash)
{
    return per_bit_rw1(&flash->Per->Dcen);
}

/// FLASH Data cache enable
static per_inline void per_flash_set_dcen(const per_flash_t* const flash, bool val)
{
    per_bit_rw1_set(&flash->Per->Dcen, val);
}

/// FLASH Instruction cache reset
static per_inline bool per_flash_icrst(const per_flash_t* const flash)
{
    return per_bit_rw1(&flash->Per->Icrst);
}

/// FLASH Instruction cache reset
static per_inline void per_flash_set_icrst(const per_flash_t* const flash, bool val)
{
    per_bit_rw1_set(&flash->Per->Icrst, val);
}

/// FLASH Data cache reset
static per_inline bool per_flash_dcrst(const per_flash_t* const flash)
{
    return per_bit_rw1(&flash->Per->Dcrst);
}

/// FLASH Data cache reset
static per_inline void per_flash_set_dcrst(const per_flash_t* const flash, bool val)
{
    per_bit_rw1_set(&flash->Per->Dcrst, val);
}

/// FLASH key register
static per_inline void per_flash_set_key(const per_flash_t* const flash, uint32_t val)
{
    per_bit_w32_reg_set(&flash->Per->Key, val);
}

/// FLASH optkey register
static per_inline void per_flash_set_optkey(const per_flash_t* const flash, uint32_t val)
{
    per_bit_w32_reg_set(&flash->Per->Optkey, val);
}

/// FLASH End of operation
static per_inline bool per_flash_eop(const per_flash_t* const flash)
{
    return per_bit_rc1_w1(&flash->Per->Eop);
}

/// FLASH End of operation
static per_inline bool per_flash_clr_eop(const per_flash_t* const flash)
{
    return per_bit_rc1_w1_rdclr(&flash->Per->Eop);
}

/// FLASH Operation error
static per_inline bool per_flash_operr(const per_flash_t* const flash)
{
    return per_bit_rc1_w1(&flash->Per->Operr);
}

/// FLASH Operation error
static per_inline bool per_flash_clr_operr(const per_flash_t* const flash)
{
    return per_bit_rc1_w1_rdclr(&flash->Per->Operr);
}

/// FLASH Write protection error
static per_inline bool per_flash_wrperr(const per_flash_t* const flash)
{
    return per_bit_rc1_w1(&flash->Per->Wrperr);
}

/// FLASH Write protection error
static per_inline bool per_flash_clr_wrperr(const per_flash_t* const flash)
{
    return per_bit_rc1_w1_rdclr(&flash->Per->Wrperr);
}

/// FLASH Programming alignment error
static per_inline bool per_flash_pgaerr(const per_flash_t* const flash)
{
    return per_bit_rc1_w1(&flash->Per->Pgaerr);
}

/// FLASH Programming alignment error
static per_inline bool per_flash_clr_pgaerr(const per_flash_t* const flash)
{
    return per_bit_rc1_w1_rdclr(&flash->Per->Pgaerr);
}

/// FLASH Programming parallelism error
static per_inline bool per_flash_pgperr(const per_flash_t* const flash)
{
    return per_bit_rc1_w1(&flash->Per->Pgperr);
}

/// FLASH Programming parallelism error
static per_inline bool per_flash_clr_pgperr(const per_flash_t* const flash)
{
    return per_bit_rc1_w1_rdclr(&flash->Per->Pgperr);
}

/// FLASH Programming sequence error
static per_inline bool per_flash_pgserr(const per_flash_t* const flash)
{
    return per_bit_rc1_w1(&flash->Per->Pgserr);
}

/// FLASH Programming sequence error
static per_inline bool per_flash_clr_pgserr(const per_flash_t* const flash)
{
    return per_bit_rc1_w1_rdclr(&flash->Per->Pgserr);
}

/// FLASH Proprietary readout protection (PCROP) error
static per_inline bool per_flash_rderr(const per_flash_t* const flash)
{
    if (!flash->PropProt)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1_w1(&flash->Per->Rderr);
}

/// FLASH Proprietary readout protection (PCROP) error
static per_inline bool per_flash_clr_rderr(const per_flash_t* const flash)
{
    if (!flash->PropProt)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rc1_w1_rdclr(&flash->Per->Rderr);
}

/// FLASH Busy
static per_inline bool per_flash_bsy(const per_flash_t* const flash)
{
    return per_bit_r1(&flash->Per->Bsy);
}

/// FLASH Programming
static per_inline bool per_flash_pg(const per_flash_t* const flash)
{
    return per_bit_rw1(&flash->Per->Pg);
}

/// FLASH Programming
static per_inline void per_flash_set_pg(const per_flash_t* const flash, bool val)
{
    per_bit_rw1_set(&flash->Per->Pg, val);
}

/// FLASH Sector Erase
static per_inline bool per_flash_ser(const per_flash_t* const flash)
{
    return per_bit_rw1(&flash->Per->Ser);
}

/// FLASH Sector Erase
static per_inline void per_flash_set_ser(const per_flash_t* const flash, bool val)
{
    per_bit_rw1_set(&flash->Per->Ser, val);
}

/// FLASH Mass Erase of bank 1 sectors
static per_inline bool per_flash_mer(const per_flash_t* const flash)
{
    return per_bit_rw1(&flash->Per->Mer);
}

/// FLASH Mass Erase of bank 1 sectors
static per_inline void per_flash_set_mer(const per_flash_t* const flash, bool val)
{
    per_bit_rw1_set(&flash->Per->Mer, val);
}

/// FLASH Sector number
static per_inline uint_fast16_t per_flash_snb(const per_flash_t* const flash)
{
    uint_fast16_t val = per_bit_rw5(&flash->Per->Snb);

    if ((val & PER_FLASH_SNB_MSB) != 0) // 12-23
    {
        val -= PER_FLASH_SNB_MSB + PER_FLASH_SNB_MAX;
    }

    return val;
}

/// FLASH Sector number
static per_inline bool per_flash_set_snb(const per_flash_t* const flash, uint_fast16_t val)
{
    if (val >= (PER_FLASH_SNB_MAX * flash->Banks))
    {
        per_log_err(flash->Err, PER_FLASH_SNB_ERR, val);
        return false;
    }

    if (val >= PER_FLASH_SNB_MAX)
    {
        val += PER_FLASH_SNB_MSB - PER_FLASH_SNB_MAX;
    }

    return per_bit_rw5_set(&flash->Per->Snb, val);
}

/// FLASH Program size
static per_inline uint_fast16_t per_flash_psize(const per_flash_t* const flash)
{
    return per_bit_inv_log2(per_bit_rw2(&flash->Per->Psize)) * PER_FLASH_PSIZE_MULT;
}

/// FLASH Program size
static per_inline bool per_flash_set_psize(const per_flash_t* const flash, uint_fast16_t val)
{
    uint_fast16_t psize = val / PER_FLASH_PSIZE_MULT;

    if ((psize > per_bit_inv_log2(per_bit_rw2_max())) ||
        (!per_bit_is_log2(psize)))
    {
        per_log_err(flash->Err, PER_FLASH_PSIZE_ERR, val);
        return false;
    }

    return per_bit_rw2_set(&flash->Per->Psize, per_bit_log2(psize));
}

/// FLASH Mass Erase of bank 2 sectors
static per_inline bool per_flash_mer1(const per_flash_t* const flash)
{
    if (flash->Banks < 2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&flash->Per->Mer1);
}

/// FLASH Mass Erase of bank 2 sectors
static per_inline void per_flash_set_mer1(const per_flash_t* const flash, bool val)
{
    if (flash->Banks < 2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&flash->Per->Mer1, val);
}

/// FLASH Start
static per_inline bool per_flash_strt(const per_flash_t* const flash)
{
    return per_bit_rs1(&flash->Per->Strt);
}

/// FLASH Start
static per_inline void per_flash_set_strt(const per_flash_t* const flash)
{
    per_bit_rs1_set(&flash->Per->Strt);
}

/// FLASH End of operation interrupt enable
static per_inline bool per_flash_eopie(const per_flash_t* const flash)
{
    return per_bit_rw1(&flash->Per->Eopie);
}

/// FLASH End of operation interrupt enable
static per_inline void per_flash_set_eopie(const per_flash_t* const flash, bool val)
{
    per_bit_rw1_set(&flash->Per->Eopie, val);
}

/// FLASH Error interrupt enable
static per_inline bool per_flash_errie(const per_flash_t* const flash)
{
    return per_bit_rw1(&flash->Per->Errie);
}

/// FLASH Error interrupt enable
static per_inline void per_flash_set_errie(const per_flash_t* const flash, bool val)
{
    per_bit_rw1_set(&flash->Per->Errie, val);
}

/// FLASH Lock
static per_inline bool per_flash_lock(const per_flash_t* const flash)
{
    return per_bit_rs1(&flash->Per->Lock);
}

/// FLASH Lock
static per_inline void per_flash_set_lock(const per_flash_t* const flash)
{
    per_bit_rs1_set(&flash->Per->Lock);
}

/// FLASH Option lock
static per_inline bool per_flash_optlock(const per_flash_t* const flash)
{
    return per_bit_rs1(&flash->Per->Optlock);
}

/// FLASH Option lock
static per_inline void per_flash_clr_optlock(const per_flash_t* const flash)
{
    per_bit_rs1_set(&flash->Per->Optlock);
}

/// FLASH Option start
static per_inline bool per_flash_optstrt(const per_flash_t* const flash)
{
    return per_bit_rs1(&flash->Per->Optstrt);
}

/// FLASH Option start
static per_inline void per_flash_clr_optstrt(const per_flash_t* const flash)
{
    per_bit_rs1_set(&flash->Per->Optstrt);
}

/// FLASH BOR reset Level
static per_inline uint_fast16_t per_flash_bor_lev(const per_flash_t* const flash)
{
    return per_bit_rw2(&flash->Per->Bor_lev);
}

/// FLASH BOR reset Level
static per_inline bool per_flash_set_bor_lev(const per_flash_t* const flash, uint_fast16_t val)
{
    return per_bit_rw2_set(&flash->Per->Bor_lev, val);
}

/// FLASH Dual-bank Boot option byte
static per_inline bool per_flash_bfb2(const per_flash_t* const flash)
{
    if (flash->Banks < 2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&flash->Per->Bfb2);
}

/// FLASH Dual-bank Boot option byte
static per_inline void per_flash_set_bfb2(const per_flash_t* const flash, bool val)
{
    if (flash->Banks < 2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&flash->Per->Bfb2, val);
}

/// FLASH WDG_SW
static per_inline bool per_flash_wdg_sw(const per_flash_t* const flash)
{
    return per_bit_rw1(&flash->Per->Wdg_sw);
}

/// FLASH WDG_SW
static per_inline void per_flash_set_wdg_sw(const per_flash_t* const flash, bool val)
{
    per_bit_rw1_set(&flash->Per->Wdg_sw, val);
}

/// FLASH nRST_STOP
static per_inline bool per_flash_nrst_stop(const per_flash_t* const flash)
{
    return per_bit_rw1(&flash->Per->Nrst_stop);
}

/// FLASH nRST_STOP
static per_inline void per_flash_set_nrst_stop(const per_flash_t* const flash, bool val)
{
    per_bit_rw1_set(&flash->Per->Nrst_stop, val);
}

/// FLASH nRST_STDBY
static per_inline bool per_flash_nrst_stdby(const per_flash_t* const flash)
{
    return per_bit_rw1(&flash->Per->Nrst_stdby);
}

/// FLASH nRST_STDBY
static per_inline void per_flash_set_nrst_stdby(const per_flash_t* const flash, bool val)
{
    per_bit_rw1_set(&flash->Per->Nrst_stdby, val);
}

/// FLASH Read protect
static per_inline uint_fast16_t per_flash_rdp(const per_flash_t* const flash)
{
    return per_bit_r8(&flash->Per->Rdp);
}

/// FLASH Not write protect
static per_inline per_flash_nwrp_e per_flash_nwrp(const per_flash_t* const flash)
{
    return (per_flash_nwrp_e)per_bit_rw12(&flash->Per->Nwrp);
}

/// FLASH Not write protect
static per_inline bool per_flash_set_nwrp(const per_flash_t* const flash, per_flash_nwrp_e val)
{
    return per_bit_rw12_set(&flash->Per->Nwrp, (uint_fast16_t)val);
}

/// FLASH Dual-bank on 1 Mbyte Flash memory devices
static per_inline bool per_flash_db1m(const per_flash_t* const flash)
{
    if (flash->Banks < 2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&flash->Per->Db1m);
}

/// FLASH Dual-bank on 1 Mbyte Flash memory devices
static per_inline void per_flash_set_db1m(const per_flash_t* const flash, bool val)
{
    if (flash->Banks < 2)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&flash->Per->Db1m, val);
}

/// FLASH Selection of protection mode for nWPRi bits
static per_inline bool per_flash_sprmod(const per_flash_t* const flash)
{
    if (!flash->PropProt)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw1(&flash->Per->Sprmod);
}

/// FLASH Selection of protection mode for nWPRi bits
static per_inline void per_flash_set_sprmod(const per_flash_t* const flash, bool val)
{
    if (!flash->PropProt)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&flash->Per->Sprmod, val);
}

/// FLASH Not write protect
static per_inline per_flash_nwrp_e per_flash_nwrp1(const per_flash_t* const flash)
{
    if (flash->Banks < 2)
    {
        per_dep_err_unsupported();
    }

    return (per_flash_nwrp_e)per_bit_rw12(&flash->Per->Nwrp1);
}

/// FLASH Not write protect
static per_inline bool per_flash_set_nwrp1(const per_flash_t* const flash, per_flash_nwrp_e val)
{
    if (flash->Banks < 2)
    {
        per_dep_err_unsupported();
    }

    return per_bit_rw12_set(&flash->Per->Nwrp1, (uint_fast16_t)val);
}

#ifdef __cplusplus
}
#endif

#endif // per_flash_f4_h_
