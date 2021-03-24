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


/// FLASH error enumeration
typedef enum
{
    PER_FLASH_OK_ERR = PER_LOG_FLASH * PER_LOG_MULT, ///< No error
    PER_FLASH_LATENCY_ERR,
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

typedef struct
{
    // Flash access control register (FLASH_ACR)
    per_bit_rw4_t Latency; ///< Latency
    per_bit_n4_t AcrBit3; ///< Reserved
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

} __attribute__((packed)) per_flash_per_t;

/// FLASH descriptor
typedef struct
{
    per_flash_per_t* const Per;                 ///< Interface
    const per_log_e Err;                        ///< Peripheral error number
    const per_flash_latency_size_e LatencySize; ///< number of bits for latency
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
static per_inline void per_flash_set_rften(const per_flash_t* const flash, bool val)
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












///// FLASH
//static per_inline bool per_flash_(const per_flash_t* const flash)
//{
//    return per_bit_rw1(&flash->Per->);
//}
//
///// FLASH
//static per_inline void per_flash_set_(const per_flash_t* const flash, bool val)
//{
//    per_bit_rw1_set(&flash->Per->, val);
//}
//



#ifdef __cplusplus
}
#endif

#endif // per_flash_f4_h_
