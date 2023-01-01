/**
 * @file per_bit_f4.h
 *
 * This file contains the peripheral BIT BAND register macros
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

#ifndef per_bit_f4_h_
#define per_bit_f4_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_addr.h"
#include "per_dep.h"

/// BIT error enumeration
typedef enum
{
    PER_BIT_ERR_OK = 0, ///< No error
    PER_BIT_ERR_SET, ///< Set and check corrupted
} per_bit_error_e;

/// One peripheral bitband bit, size is 32 bit in the bitband area
typedef union
{
    volatile uint_fast8_t Bit8;   ///< One register bit presentation in the bitband region
    volatile uint_fast16_t Bit16; ///< One register bit presentation in the bitband region 16 bit access
    volatile uint32_t Bit32; ///< One register bit presentation in the bitband region 32 bit access
} per_bit_bitband_t;

/// One peripheral register, size is 32 bit in the peripheral register area
typedef union
{
    volatile uint_fast8_t Reg8;   ///< 8 bit value
    volatile uint_fast16_t Reg16; ///< 16 bit value
    volatile uint32_t Reg32; ///< 32 bit value
} per_bit_register_t;

/// False
#define PER_BIT_0 ((uint_fast8_t)0)

/// True
#define PER_BIT_1 ((uint_fast8_t)1)

/// Number of bits in the registers
#define PER_BIT_REG_BITS ((uint_fast8_t)32)

/// Register address shift
#define PER_BIT_BB_REG_SHIFT ((uint_fast8_t)5)

/// Bit offset shift
#define PER_BIT_BB_BIT_SHIFT ((uint_fast8_t)2)

/// Filter to leave bit offset
#define PER_BIT_MAX(SIZE) ((uint32_t)((1 << SIZE) - 1))

/// Bit offset mask
#define PER_BIT_BB_BIT_MASK (~PER_BIT_MAX(PER_BIT_BB_BIT_SHIFT))

/// Get a bit band address from a ram bit in the ram1 alias area
#define RAM_BIT_BAND_DATA1(REG,BIT) ((per_bit_bitband_t*)(SRAM1_BB_BASE | (((uintptr_t)REG - SRAM1_BASE) << PER_BIT_BB_REG_SHIFT) | ((uintptr_t)BIT << PER_BIT_BB_BIT_SHIFT)))

/// Get a bit band address from a ram bit in the ram2 alias area
#define RAM_BIT_BAND_DATA2(REG,BIT) ((per_bit_bitband_t*)(SRAM2_BB_BASE | (((uintptr_t)REG - SRAM2_BASE) << PER_BIT_BB_REG_SHIFT) | ((uintptr_t)BIT << PER_BIT_BB_BIT_SHIFT)))

/// Get a bit band address from a register address
#define PER_BIT_REG_TO_BIT_BAND(REG) (PER_ADDR_PERIPH_BB | (((uintptr_t)REG - PER_ADDR_PERIPH) << PER_BIT_BB_REG_SHIFT))

/// Get a bit offset in a register from a bit band address
#define PER_BIT_SHIFT(PBAND) ((uint_fast8_t)(((uintptr_t)PBAND >> PER_BIT_BB_BIT_SHIFT) & PER_BIT_MAX(PER_BIT_BB_REG_SHIFT)))

/// Get a register address from a bit band address
#define PER_BIT_BIT_BAND_TO_REG(PBAND) ((per_bit_register_t*)(((PER_ADDR_PERIPH - (PER_ADDR_PERIPH_BB >> PER_BIT_BB_REG_SHIFT)) + ((uintptr_t)PBAND >> PER_BIT_BB_REG_SHIFT)) & PER_BIT_BB_BIT_MASK))

/// Get the contents of a part of a register. Maximum 16 bits
#define PER_BIT_BITS_GET(PBAND,SIZE) ((uint_fast16_t)(PER_BIT_BIT_BAND_TO_REG(PBAND)->Reg32 >> PER_BIT_SHIFT(PBAND)) & PER_BIT_MAX(SIZE))

/// Filter to mask leave one bit
#define PER_BIT_REG_MASK_BIT(PBAND) ((uint32_t)(1 << PER_BIT_SHIFT(PBAND)))


/// Peripheral Read-write bit
typedef struct
{
    per_bit_bitband_t Rw; ///< One read write bit
} per_bit_rw1_t;

/// One read and write bit get
static per_inline bool per_bit_rw1(const per_bit_rw1_t* self)
{
    return self->Rw.Bit8 != PER_BIT_0;
}

/// One read and write bit set
static per_inline void per_bit_rw1_set(per_bit_rw1_t* self, bool val)
{
    self->Rw.Bit8 = (uint_fast8_t)val; // Cast is fast
}

/// One read and write bit mask
static per_inline uint32_t per_bit_rw1_mask(per_bit_rw1_t* self)
{
    return (uint32_t)(1 << PER_BIT_SHIFT(self));
}

/// One read and write bit shift
static per_inline uint_fast8_t per_bit_rw1_shift(per_bit_rw1_t* self)
{
    return PER_BIT_SHIFT(self);
}
/// Peripheral Read-set bit
typedef struct
{
    per_bit_bitband_t Rs; ///< One read set bit
} per_bit_rs1_t;

/// One read and set bit get
static per_inline bool per_bit_rs1(const per_bit_rs1_t* self)
{
    return self->Rs.Bit8 != PER_BIT_0;
}

/// One read and set bit set
/// Set by writing one
static per_inline void per_bit_rs1_set(per_bit_rs1_t* self)
{
    self->Rs.Bit8 = PER_BIT_1;
}

/// Peripheral Read-clear 0 bit
typedef struct
{
    per_bit_bitband_t Rc; ///< One read clear bit
} per_bit_rc1_w0_t;

/// One read and clear bit get
static per_inline bool per_bit_rc1_w0(const per_bit_rc1_w0_t* self)
{
    return self->Rc.Bit8 != PER_BIT_0;
}

/// One read and clear bit read and clear
/// Cleared by writing zero
/// Only if the bit was set it is cleared, safe, no misses
/// Register way handling because bitband is not safe in this specific case
static per_inline bool per_bit_rc1_w0_rdclr(per_bit_rc1_w0_t* self)
{
    volatile uint32_t* const reg = &PER_BIT_BIT_BAND_TO_REG(self)->Reg32; // Register pointer
    uint32_t val = *reg & PER_BIT_REG_MASK_BIT(self); // Mask current value

    *reg = ~val; // Only write, clear only one bit if it was set

    return val != 0;
}

/// Peripheral flash Read-clear 1 bit
typedef struct
{
    per_bit_bitband_t Rc; ///< One read clear bit
} per_bit_rc1_w1_t;

/// FLASH One read and clear bit get
static per_inline bool per_bit_rc1_w1(const per_bit_rc1_w1_t* self)
{
    return self->Rc.Bit8 != PER_BIT_0;
}

/// One read and clear bit read and clear
/// Cleared by writing one
/// Only if the bit was set it is cleared, safe, no misses
/// Register way handling because bitband is not safe in this specific case
static per_inline bool per_bit_rc1_w1_rdclr(per_bit_rc1_w1_t* self)
{
    volatile uint32_t* const reg = &PER_BIT_BIT_BAND_TO_REG(self)->Reg32; // Register pointer
    uint32_t val = *reg & PER_BIT_REG_MASK_BIT(self); // Mask current value

    *reg = val; // Only write, clear only one bit if it was set

    return val != 0;
}

/// Peripheral Read-only bit
typedef struct
{
    per_bit_bitband_t R; ///< One read only bit
} per_bit_r1_t;

/// One read bit get
static per_inline bool per_bit_r1(const per_bit_r1_t* self)
{
    return self->R.Bit8 != PER_BIT_0;
}

/// Peripheral Write-only bit
typedef struct
{
    per_bit_bitband_t W; ///< One write only bit
} per_bit_w1_t;

/// One write bit set
static per_inline void per_bit_w1_set(per_bit_w1_t* self, bool val)
{
    self->W.Bit8 = (uint_fast8_t)val; // Cast is fast
}

/// Peripheral Reserved bit
typedef struct
{
    per_bit_bitband_t N; ///< One no access bit
} per_bit_n1_t;

bool per_bit_set_bits(per_bit_bitband_t* addr, uint_fast8_t size,  uint_fast16_t val);
bool per_bit_set_bits_check(per_bit_bitband_t* addr, uint_fast8_t size,  uint_fast16_t val);

/// Multiple bit xxx_t read and write 16 bits maximum
#define PER_BIT_READ_WRITE(NAME,SIZE)  typedef struct { per_bit_bitband_t Rw[SIZE]; } NAME##_t;\
    static per_inline uint_fast16_t NAME (const NAME##_t* self) {return PER_BIT_BITS_GET(self, SIZE);};\
    static per_inline bool NAME##_set (NAME##_t* self, uint_fast16_t value) {return per_bit_set_bits(&self->Rw[0], SIZE, value);}\
    static per_inline uint32_t NAME##_max (void) {return PER_BIT_MAX(SIZE);};\
    static per_inline uint_fast8_t NAME##_shift (const NAME##_t* self) {return PER_BIT_SHIFT(self);};\
    static per_inline uint32_t NAME##_mask (const NAME##_t* self) {return PER_BIT_MAX(SIZE) << PER_BIT_SHIFT(self);};

PER_BIT_READ_WRITE(per_bit_rw2, 2); ///< per_bit_rw2_t 2 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw3, 3); ///< per_bit_rw3_t 3 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw4, 4); ///< per_bit_rw4_t 4 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw5, 5); ///< per_bit_rw5_t 5 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw6, 6); ///< per_bit_rw6_t 6 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw7, 7); ///< per_bit_rw7_t 7 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw8, 8); ///< per_bit_rw8_t 8 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw9, 9); ///< per_bit_rw9_t 9 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw10, 10); ///< per_bit_rw10_t 10 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw11, 11); ///< per_bit_rw11_t 11 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw12, 12); ///< per_bit_rw12_t 12 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw13, 13); ///< per_bit_rw13_t 13 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw14, 14); ///< per_bit_rw14_t 14 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw15, 15); ///< per_bit_rw15_t 15 bit peripheral read and write
PER_BIT_READ_WRITE(per_bit_rw16, 16); ///< per_bit_rw16_t 16 bit peripheral read and write

/// Multiple bit xxx_t read only
#define PER_BIT_READ(NAME,SIZE)  typedef struct { volatile const uint32_t BIT[SIZE]; } NAME##_t;\
    static per_inline uint_fast16_t NAME (const NAME##_t* self) {return PER_BIT_BITS_GET(self, SIZE);}

PER_BIT_READ(per_bit_r2, 2); ///< per_bit_r2_t 2 bit peripheral read only
PER_BIT_READ(per_bit_r3, 3); ///< per_bit_r3_t 3 bit peripheral read only
PER_BIT_READ(per_bit_r4, 4); ///< per_bit_r4_t 4 bit peripheral read only
PER_BIT_READ(per_bit_r5, 5); ///< per_bit_r5_t 5 bit peripheral read only
PER_BIT_READ(per_bit_r6, 6); ///< per_bit_r6_t 6 bit peripheral read only
PER_BIT_READ(per_bit_r7, 7); ///< per_bit_r7_t 7 bit peripheral read only
PER_BIT_READ(per_bit_r8, 8); ///< per_bit_r8_t 8 bit peripheral read only
PER_BIT_READ(per_bit_r9, 9); ///< per_bit_r9_t 9 bit peripheral read only
PER_BIT_READ(per_bit_r10, 10); ///< per_bit_r10_t 10 bit peripheral read only
PER_BIT_READ(per_bit_r11, 11); ///< per_bit_r11_t 11 bit peripheral read only
PER_BIT_READ(per_bit_r12, 12); ///< per_bit_r12_t 12 bit peripheral read only
PER_BIT_READ(per_bit_r13, 13); ///< per_bit_r13_t 13 bit peripheral read only
PER_BIT_READ(per_bit_r14, 14); ///< per_bit_r14_t 14 bit peripheral read only
PER_BIT_READ(per_bit_r15, 15); ///< per_bit_r15_t 15 bit peripheral read only
PER_BIT_READ(per_bit_r16, 16); ///< per_bit_r16_t 16 bit peripheral read only

/// Multiple bit xxx_t no actions, reserved
#define PER_BIT_NONE(NAME,SIZE)  typedef struct { per_bit_bitband_t N[SIZE]; } NAME##_t;

PER_BIT_NONE(per_bit_n2, 2); ///< per_bit_n2_t 2 bit peripheral no-operation
PER_BIT_NONE(per_bit_n3, 3); ///< per_bit_n3_t 3 bit peripheral no-operation
PER_BIT_NONE(per_bit_n4, 4); ///< per_bit_n4_t 4 bit peripheral no-operation
PER_BIT_NONE(per_bit_n5, 5); ///< per_bit_n5_t 5 bit peripheral no-operation
PER_BIT_NONE(per_bit_n6, 6); ///< per_bit_n6_t 6 bit peripheral no-operation
PER_BIT_NONE(per_bit_n7, 7); ///< per_bit_n7_t 7 bit peripheral no-operation
PER_BIT_NONE(per_bit_n8, 8); ///< per_bit_n8_t 8 bit peripheral no-operation
PER_BIT_NONE(per_bit_n9, 9); ///< per_bit_n9_t 9 bit peripheral no-operation
PER_BIT_NONE(per_bit_n10, 10); ///< per_bit_n10_t 10 bit peripheral no-operation
PER_BIT_NONE(per_bit_n11, 11); ///< per_bit_n11_t 11 bit peripheral no-operation
PER_BIT_NONE(per_bit_n12, 12); ///< per_bit_n12_t 12 bit peripheral no-operation
PER_BIT_NONE(per_bit_n13, 13); ///< per_bit_n13_t 13 bit peripheral no-operation
PER_BIT_NONE(per_bit_n14, 14); ///< per_bit_n14_t 14 bit peripheral no-operation
PER_BIT_NONE(per_bit_n15, 15); ///< per_bit_n15_t 15 bit peripheral no-operation
PER_BIT_NONE(per_bit_n16, 16); ///< per_bit_n16_t 16 bit peripheral no-operation
PER_BIT_NONE(per_bit_n17, 17); ///< per_bit_n17_t 17 bit peripheral no-operation
PER_BIT_NONE(per_bit_n18, 18); ///< per_bit_n18_t 18 bit peripheral no-operation
PER_BIT_NONE(per_bit_n19, 19); ///< per_bit_n19_t 19 bit peripheral no-operation
PER_BIT_NONE(per_bit_n20, 20); ///< per_bit_n20_t 20 bit peripheral no-operation
PER_BIT_NONE(per_bit_n21, 21); ///< per_bit_n21_t 21 bit peripheral no-operation
PER_BIT_NONE(per_bit_n22, 22); ///< per_bit_n22_t 22 bit peripheral no-operation
PER_BIT_NONE(per_bit_n23, 23); ///< per_bit_n23_t 23 bit peripheral no-operation
PER_BIT_NONE(per_bit_n24, 24); ///< per_bit_n24_t 24 bit peripheral no-operation
PER_BIT_NONE(per_bit_n25, 25); ///< per_bit_n25_t 25 bit peripheral no-operation
PER_BIT_NONE(per_bit_n26, 26); ///< per_bit_n26_t 26 bit peripheral no-operation
PER_BIT_NONE(per_bit_n27, 27); ///< per_bit_n27_t 27 bit peripheral no-operation
PER_BIT_NONE(per_bit_n28, 28); ///< per_bit_n28_t 28 bit peripheral no-operation
PER_BIT_NONE(per_bit_n29, 29); ///< per_bit_n29_t 29 bit peripheral no-operation
PER_BIT_NONE(per_bit_n30, 30); ///< per_bit_n30_t 30 bit peripheral no-operation
PER_BIT_NONE(per_bit_n31, 31); ///< per_bit_n31_t 31 bit peripheral no-operation
PER_BIT_NONE(per_bit_n32, 32); ///< per_bit_n32_t 32 bit peripheral no-operation

/// Peripheral register read-write 8 bit
typedef struct
{
    per_bit_bitband_t Rw[PER_BIT_REG_BITS];
} per_bit_rw8_reg_t;

/// Peripheral register 8 bit get
static per_inline uint_fast8_t per_bit_rw8_reg(const per_bit_rw8_reg_t* self)
{
    return PER_BIT_BIT_BAND_TO_REG(self)->Reg8;
}

/// Peripheral register 8 bit write
static per_inline void per_bit_rw8_reg_set(per_bit_rw8_reg_t* self, uint_fast8_t val)
{
    PER_BIT_BIT_BAND_TO_REG(self)->Reg8 = val;
}

/// Peripheral register read-write 16 bit
typedef struct
{
    per_bit_bitband_t Rw[PER_BIT_REG_BITS];
} per_bit_rw16_reg_t;

/// Peripheral register 16 bit get
static per_inline uint_fast16_t per_bit_rw16_reg(const per_bit_rw16_reg_t* self)
{
    return PER_BIT_BIT_BAND_TO_REG(self)->Reg16;
}

/// Peripheral register 16 bit write
static per_inline void per_bit_rw16_reg_set(per_bit_rw16_reg_t* self, uint_fast16_t val)
{
    PER_BIT_BIT_BAND_TO_REG(self)->Reg16 = val;
}

/// Peripheral register read-write 32 bit
typedef struct
{
    per_bit_bitband_t Rw[PER_BIT_REG_BITS];
} per_bit_rw32_reg_t;

/// Peripheral register 32 bit get
static per_inline uint32_t per_bit_rw32_reg(const per_bit_rw32_reg_t* self)
{
    return PER_BIT_BIT_BAND_TO_REG(self)->Reg32;
}

/// Peripheral register 32 bit write
static per_inline void per_bit_rw32_reg_set(per_bit_rw32_reg_t* self, uint32_t val)
{
    PER_BIT_BIT_BAND_TO_REG(self)->Reg32 = val;
}

/// Peripheral register read-only 8 bit
typedef struct
{
    per_bit_bitband_t R[PER_BIT_REG_BITS];
} per_bit_r8_reg_t;

/// Peripheral register 8 bit get
static per_inline uint_fast8_t per_bit_r8_reg(const per_bit_r8_reg_t* self)
{
    return PER_BIT_BIT_BAND_TO_REG(self)->Reg8;
}

/// Peripheral register read-only 16 bit
typedef struct
{
    per_bit_bitband_t R[PER_BIT_REG_BITS];
} per_bit_r16_reg_t;

/// Peripheral register 16 bit get
static per_inline uint_fast16_t per_bit_r16_reg(const per_bit_r16_reg_t* self)
{
    return PER_BIT_BIT_BAND_TO_REG(self)->Reg16;
}

/// Peripheral register read-only 32 bit
typedef struct
{
    per_bit_bitband_t R[PER_BIT_REG_BITS];
} per_bit_r32_reg_t;

/// Peripheral register 32 bit get
static per_inline uint32_t per_bit_r32_reg(const per_bit_r32_reg_t* self)
{
    return PER_BIT_BIT_BAND_TO_REG(self)->Reg32;
}

/// Peripheral register write-only 8 bits
typedef struct
{
    per_bit_bitband_t W[PER_BIT_REG_BITS];
} per_bit_w8_reg_t;

/// Peripheral register 8 bit write
static per_inline void per_bit_w8_reg_set(per_bit_w8_reg_t* self, uint_fast8_t val)
{
    PER_BIT_BIT_BAND_TO_REG(self)->Reg8 = val;
}

/// Peripheral register write-only 16 bits
typedef struct
{
    per_bit_bitband_t W[PER_BIT_REG_BITS];
} per_bit_w16_reg_t;

/// Peripheral register 16 bit write
static per_inline void per_bit_w16_reg_set(per_bit_w16_reg_t* self, uint_fast16_t val)
{
    PER_BIT_BIT_BAND_TO_REG(self)->Reg16 = val;
}

/// Peripheral register write-only 32 bits
typedef struct
{
    per_bit_bitband_t W[PER_BIT_REG_BITS];
} per_bit_w32_reg_t;

/// Peripheral register 32 bit write
static per_inline void per_bit_w32_reg_set(per_bit_w32_reg_t* self, uint32_t val)
{
    PER_BIT_BIT_BAND_TO_REG(self)->Reg32 = val;
}

/// Calculate log2
per_inline uint_fast16_t per_bit_log2(uint32_t x)
{
    return (uint_fast16_t)per_log2(x);
}

/// Calculate inverse log2
per_inline uint32_t per_bit_inv_log2(uint_fast16_t x)
{
    return (uint32_t)1 << x;
}

/// Check if value is a valid log2(power of 2)
per_inline bool per_bit_is_log2(uint32_t x)
{
    return ((x & (x - 1)) == 0) && (x != 0);
}

#ifdef __cplusplus
}
#endif

#endif // per_bit_f4_h_
