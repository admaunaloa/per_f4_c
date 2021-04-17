/**
 * @file per_i2c_f4.h
 *
 * This file contains the Inter-integrated circuit interface (I2C)
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
 * Convenience functions:
 * per_i2c_flag(const per_i2c_t* const i2c)
 */

#ifndef per_i2c_f4_h_
#define per_i2c_f4_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_bit_f4.h"

/// I2C1 base address
#define PER_I2C_1 ((per_i2c_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB1 + (uintptr_t)0x5400))

/// I2C2 base address
#define PER_I2C_2 ((per_i2c_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB1 + (uintptr_t)0x5800))

/// I2C3 base address
#define PER_I2C_3 ((per_i2c_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB1 + (uintptr_t)0x5C00))

/// I2C3 Peripheral clock frequency maximum
#define PER_I2C_FREQ_MAX ((uint_fast16_t)50)

/// I2C3 Peripheral clock frequency minimum
#define PER_I2C_FREQ_MIN ((uint_fast16_t)2)

/// I2C error enumeration
typedef enum
{
    PER_I2C_OK_ERR = PER_LOG_I2C * PER_LOG_MULT, ///< No error
    PER_I2C_FREQ_ERR,   ///< Peripheral clock frequency maximum value
    PER_I2C_ADD_ERR,    ///< Interface address maximum value
    PER_I2C_ADD_10_ERR, ///< Interface address 10 bit maximum value
    PER_I2C_ADD2_ERR,   ///< Interface address dual mode maximum value
    PER_I2C_CCR_ERR,    ///< Clock control register in Fm/Sm mode (Master mode) maximum value
    PER_I2C_TRISE_ERR,  ///< Maximum rise time in Fm/Sm mode (Master mode) maximum value
    PER_I2C_DNF_ERR,    ///< Digital noise filter maximum value
} per_i2c_error_e;

/// I2C Status register 1 (I2C_SR1)
typedef enum
{
    PER_I2C_SR_BERR      = 0b0000000100000000, ///< Bus error
    PER_I2C_SR_ARLO      = 0b0000001000000000, ///< Arbitration lost (master mode)
    PER_I2C_SR_AF        = 0b0000010000000000, ///< Acknowledge failure
    PER_I2C_SR_OVR       = 0b0000100000000000, ///< Overrun/Underrun
    PER_I2C_SR_PECERR    = 0b0001000000000000, ///< PEC Error in reception
    PER_I2C_SR_TIMEOUT   = 0b0100000000000000, ///< Timeout or Tlow error
    PER_I2C_SR_SMBALLERT = 0b1000000000000000, ///< SMBus alert
    PER_I2C_SR_CLEAR = PER_I2C_SR_BERR |
                       PER_I2C_SR_ARLO |
                       PER_I2C_SR_AF |
                       PER_I2C_SR_OVR |
                       PER_I2C_SR_PECERR |
                       PER_I2C_SR_TIMEOUT |
                       PER_I2C_SR_SMBALLERT,
} per_i2c_sr_e;

typedef struct
{
    // I2C Control register 1 (I2C_CR1)
    per_bit_rw1_t Pe; ///< Peripheral enable
    per_bit_rw1_t Smbus; ///< SMBus mode
    per_bit_n1_t Cr1Bit2; ///< Reserved
    per_bit_rw1_t Smbtype; ///< SMBus type
    per_bit_rw1_t Enarp; ///< ARP enable
    per_bit_rw1_t Enpec; ///< PEC enable
    per_bit_rw1_t Engc; ///< General call enable
    per_bit_rw1_t Nostretch; ///< Clock stretching disable (Slave mode)
    per_bit_rw1_t Start; ///< Start generation
    per_bit_rw1_t Stop; ///< Stop generation
    per_bit_rw1_t Ack; ///< Acknowledge enable
    per_bit_rw1_t Pos; ///< Acknowledge/PEC Position (for data reception)
    per_bit_rw1_t PecStrt; ///< Packet error checking start
    per_bit_rw1_t Alert; ///< SMBus alert
    per_bit_n1_t Cr1Bit14; ///< Reserved
    per_bit_rw1_t Swrst; ///< Software reset
    per_bit_n16_t Cr1Bit16; ///< Reserved

    // I2C Control register 2 (I2C_CR2)
    per_bit_rw6_t Freq; ///< Peripheral clock frequency
    per_bit_n2_t Cr2Bit6; ///< Reserved
    per_bit_rw1_t Iterren; ///< Error interrupt enable
    per_bit_rw1_t Itevten; ///< Event interrupt enable
    per_bit_rw1_t Itbufen; ///< Buffer interrupt enable
    per_bit_rw1_t Dmaen; ///< DMA requests enable
    per_bit_rw1_t Last; ///< DMA last transfer
    per_bit_n19_t Cr2Bit13; ///< Reserved

    // I2C Own address register 1 (I2C_OAR1)
    union
    {
        struct
        {
            per_bit_n1_t Oar1Bit0; ///< Reserved
            per_bit_rw7_t Add; ///< Interface address
            per_bit_n2_t Oar1Bit8; ///< Reserved
        };
        per_bit_rw10_t Add_10; ///< Interface address 10 bit
    };
    per_bit_n5_t Oar1Bit10; ///< Reserved
    per_bit_rw1_t Addmode; ///< Addressing mode (slave mode)
    per_bit_n16_t Oar1Bit16; ///< Reserved

    // I2C Own address register 2 (I2C_OAR2)
    per_bit_rw1_t Endual; ///< Dual addressing mode enable
    per_bit_rw7_t Add2; ///< Interface address 2
    per_bit_n24_t Oar2Bit8; ///< Reserved

    // I2C Data register (I2C_DR)
    per_bit_rw8_reg_t Dr; ///< 8-bit data register

    // I2C Status register 1 (I2C_SR1)
    union
    {
        struct
        {
            per_bit_r1_t Sb; ///< Start bit (Master mode)
            per_bit_r1_t Addr; ///< Address sent (master mode)/matched (slave mode)
            per_bit_r1_t Btf; ///< Byte transfer finished
            per_bit_r1_t Add10; ///< 10-bit header sent (Master mode)
            per_bit_r1_t Stopf; ///< Stop detection (slave mode)
            per_bit_n1_t Sr1Bit5; ///< Reserved
            per_bit_r1_t Rxne; ///< Data register not empty (receivers)
            per_bit_r1_t Txe; ///< Data register empty (transmitters)
            per_bit_rc1_w0_t Berr; ///< Bus error
            per_bit_rc1_w0_t Arlo; ///< Arbitration lost (master mode)
            per_bit_rc1_w0_t Af; ///< Acknowledge failure
            per_bit_rc1_w0_t Ovr; ///< Overrun/Underrun
            per_bit_rc1_w0_t Pecerr; ///< PEC Error in reception
            per_bit_n1_t Sr1Bit13; ///< Reserved
            per_bit_rc1_w0_t Timeout; ///< Timeout or Tlow error
            per_bit_rc1_w0_t Smballert; ///< SMBus alert
            per_bit_n16_t Sr1Bit16; ///< Reserved
        };
        per_bit_rw16_reg_t Sr; ///< Status register
    };

    // I2C Status register 2 (I2C_SR2)
    per_bit_r1_t Msl; ///< Master/slave
    per_bit_r1_t Busy; ///< Bus busy
    per_bit_r1_t Tra; ///< Transmitter/receiver
    per_bit_n1_t Sr2Bit; ///< Reserved
    per_bit_r1_t Gencall; ///< General call address (Slave mode)
    per_bit_r1_t Smbdefault; ///< SMBus device default address (Slave mode)
    per_bit_r1_t Smbhost; ///< SMBus host header (Slave mode)
    per_bit_r1_t Dualf; ///< Dual flag (Slave mode)
    per_bit_r8_t Pec; ///< Packet error checking register
    per_bit_n16_t Sr2Bit16; ///< Reserved

    // I2C Clock control register (I2C_CCR)
    per_bit_rw12_t Ccr; ///< Clock control register in Fm/Sm mode (Master mode)
    per_bit_n2_t CcrBit12; ///< Reserved
    per_bit_rw1_t Duty; ///< Fm mode duty cycle
    per_bit_rw1_t Fs; ///< I2C master mode selection
    per_bit_n16_t CcrBit16; ///< Reserved

    // I2C TRISE register (I2C_TRISE)
    per_bit_rw6_t Trise; ///< Maximum rise time in Fm/Sm mode (Master mode)
    per_bit_n26_t TriseBit6; ///< Reserved

    // I2C FLTR register (I2C_FLTR)
    per_bit_rw4_t Dnf; ///< Digital noise filter
    per_bit_rw1_t Anoff; ///< Analog noise filter OFF
    per_bit_n27_t FltrBit5; ///< Reserved
} __attribute__((packed)) per_i2c_per_t;

/// I2C descriptor
typedef struct
{
    per_i2c_per_t* const Per; ///< Peripheral
    const per_log_e Err;      ///< Peripheral error number
    const bool Nf;            ///< Digital noise filter
} per_i2c_t;

/// I2C Peripheral enable
static per_inline bool per_i2c_pe(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Pe);
}

/// I2C Peripheral enable
static per_inline void per_i2c_set_pe(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Pe, val);
}

/// I2C SMBus mode
static per_inline bool per_i2c_smbus(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Smbus);
}

/// I2C SMBus mode
static per_inline void per_i2c_set_smbus(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Smbus, val);
}

/// I2C SMBus type
static per_inline bool per_i2c_smbtype(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Smbtype);
}

/// I2C SMBus type
static per_inline void per_i2c_set_smbtype(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Smbtype, val);
}

/// I2C ARP enable
static per_inline bool per_i2c_enarp(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Enarp);
}

/// I2C ARP enable
static per_inline void per_i2c_set_enarp(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Enarp, val);
}

/// I2C PEC enable
static per_inline bool per_i2c_enpec(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Enpec);
}

/// I2C PEC enable
static per_inline void per_i2c_set_enpec(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Enpec, val);
}

/// I2C General call enable
static per_inline bool per_i2c_engc(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Engc);
}

/// I2C General call enable
static per_inline void per_i2c_set_engc(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Engc, val);
}

/// I2C Clock stretching disable (Slave mode)
static per_inline bool per_i2c_nostretch(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Nostretch);
}

/// I2C Clock stretching disable (Slave mode)
static per_inline void per_i2c_set_nostretch(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Nostretch, val);
}

/// I2C Start generation
static per_inline bool per_i2c_start(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Start);
}

/// I2C Start generation
static per_inline void per_i2c_set_start(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Start, val);
}

/// I2C Stop generation
static per_inline bool per_i2c_stop(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Stop);
}

/// I2C Stop generation
static per_inline void per_i2c_set_stop(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Stop, val);
}

/// I2C Acknowledge enable
static per_inline bool per_i2c_ack(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Ack);
}

/// I2C Acknowledge enable
static per_inline void per_i2c_set_ack(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Ack, val);
}

/// I2C Acknowledge/PEC Position (for data reception)
static per_inline bool per_i2c_pos(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Pos);
}

/// I2C Acknowledge/PEC Position (for data reception)
static per_inline void per_i2c_set_pos(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Pos, val);
}

/// I2C Packet error checking start
static per_inline bool per_i2c_pecstrt(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->PecStrt);
}

/// I2C Packet error checking start
static per_inline void per_i2c_set_pecstrt(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->PecStrt, val);
}

/// I2C SMBus alert
static per_inline bool per_i2c_alert(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Alert);
}

/// I2C SMBus alert
static per_inline void per_i2c_set_alert(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Alert, val);
}

/// I2C Software reset
static per_inline bool per_i2c_swrst(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Swrst);
}

/// I2C Software reset
static per_inline void per_i2c_set_swrst(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Swrst, val);
}

/// I2C Peripheral clock frequency
static per_inline uint_fast16_t per_i2c_freq(const per_i2c_t* const i2c)
{
    return per_bit_rw6(&i2c->Per->Freq);
}

/// I2C Peripheral clock frequency
static per_inline bool per_i2c_set_freq(const per_i2c_t* const i2c, uint_fast16_t val)
{
    if ((val > PER_I2C_FREQ_MAX) ||
        (val < PER_I2C_FREQ_MIN))
    {
        per_log_err(i2c->Err, PER_I2C_FREQ_ERR, val);
        return false;
    }

    return per_bit_rw6_set(&i2c->Per->Freq, val);
}

/// I2C Error interrupt enable
static per_inline bool per_i2c_iterren(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Iterren);
}

/// I2C Error interrupt enable
static per_inline void per_i2c_set_iterren(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Iterren, val);
}

/// I2C Event interrupt enable
static per_inline bool per_i2c_itevten(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Itevten);
}

/// I2C Event interrupt enable
static per_inline void per_i2c_set_itevten(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Itevten, val);
}

/// I2C Buffer interrupt enable
static per_inline bool per_i2c_itbufen(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Itbufen);
}

/// I2C Buffer interrupt enable
static per_inline void per_i2c_set_itbufen(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Itbufen, val);
}

/// I2C DMA requests enable
static per_inline bool per_i2c_dmaen(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Dmaen);
}

/// I2C DMA requests enable
static per_inline void per_i2c_set_dmaen(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Dmaen, val);
}

/// I2C DMA last transfer
static per_inline bool per_i2c_last(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Last);
}

/// I2C DMA last transfer
static per_inline void per_i2c_set_last(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Last, val);
}

/// I2C Interface address
static per_inline uint_fast16_t per_i2c_add(const per_i2c_t* const i2c)
{
    return per_bit_rw7(&i2c->Per->Add);
}

/// I2C Interface address
static per_inline bool per_i2c_set_add(const per_i2c_t* const i2c, uint_fast16_t val)
{
    if (val > per_bit_rw7_max())
    {
        per_log_err(i2c->Err, PER_I2C_ADD_ERR, val);
        return false;
    }

    return per_bit_rw7_set(&i2c->Per->Add, val);
}

/// I2C Interface address 10 bit
static per_inline uint_fast16_t per_i2c_add_10(const per_i2c_t* const i2c)
{
    return per_bit_rw10(&i2c->Per->Add_10);
}

/// I2C Interface address 10 bit
static per_inline bool per_i2c_set_add_10(const per_i2c_t* const i2c, uint_fast16_t val)
{
    if (val > per_bit_rw10_max())
    {
        per_log_err(i2c->Err, PER_I2C_ADD_10_ERR, val);
        return false;
    }

    return per_bit_rw10_set(&i2c->Per->Add_10, val);
}

/// I2C Addressing mode (slave mode)
static per_inline bool per_i2c_addmode(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Addmode);
}

/// I2C Addressing mode (slave mode)
static per_inline void per_i2c_set_addmode(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Addmode, val);
}

/// I2C Dual addressing mode enable
static per_inline bool per_i2c_endual(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Endual);
}

/// I2C Dual addressing mode enable
static per_inline void per_i2c_set_endual(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Endual, val);
}

/// I2C Interface address 2
static per_inline uint_fast16_t per_i2c_add2(const per_i2c_t* const i2c)
{
    return per_bit_rw7(&i2c->Per->Add2);
}

/// I2C Interface address 2
static per_inline bool per_i2c_set_add2(const per_i2c_t* const i2c, uint_fast16_t val)
{
    if (val > per_bit_rw7_max())
    {
        per_log_err(i2c->Err, PER_I2C_ADD2_ERR, val);
        return false;
    }

    return per_bit_rw7_set(&i2c->Per->Add2, val);
}

/// I2C 8-bit data register
static per_inline uint_fast8_t per_i2c_dr(const per_i2c_t* const i2c)
{
    return per_bit_rw8_reg(&i2c->Per->Dr);
}

/// I2C 8-bit data register
static per_inline void per_i2c_set_dr(const per_i2c_t* const i2c, uint8_t dr)
{
    per_bit_rw8_reg_set(&i2c->Per->Dr, dr);
}

/// I2C Start bit (Master mode)
static per_inline bool per_i2c_sb(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Sb);
}

/// I2C Address sent (master mode)/matched (slave mode)
static per_inline bool per_i2c_addr(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Addr);
}

/// I2C Byte transfer finished
static per_inline bool per_i2c_btf(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Btf);
}

/// I2C 10-bit header sent (Master mode)
static per_inline bool per_i2c_add10(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Add10);
}

/// I2C Stop detection (slave mode)
static per_inline bool per_i2c_stopf(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Stopf);
}

/// I2C Data register not empty (receivers)
static per_inline bool per_i2c_rxne(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Rxne);
}

/// I2C Data register empty (transmitters)
static per_inline bool per_i2c_txe(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Txe);
}

/// I2C Bus error
static per_inline bool per_i2c_berr(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0(&i2c->Per->Berr);
}

/// I2C Bus error
static per_inline bool per_i2c_rdclr_berr(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0_rdclr(&i2c->Per->Berr);
}

/// I2C Arbitration lost (master mode)
static per_inline bool per_i2c_arlo(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0(&i2c->Per->Arlo);
}

/// I2C Arbitration lost (master mode)
static per_inline bool per_i2c_rdclr_arlo(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0_rdclr(&i2c->Per->Arlo);
}

/// I2C Acknowledge failure
static per_inline bool per_i2c_af(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0(&i2c->Per->Af);
}

/// I2C Acknowledge failure
static per_inline bool per_i2c_rdclr_af(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0_rdclr(&i2c->Per->Af);
}

/// I2C Overrun/Underrun
static per_inline bool per_i2c_ovr(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0(&i2c->Per->Ovr);
}

/// I2C Overrun/Underrun
static per_inline bool per_i2c_rdclr_ovr(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0_rdclr(&i2c->Per->Ovr);
}

/// I2C PEC Error in reception
static per_inline bool per_i2c_pecerr(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0(&i2c->Per->Pecerr);
}

/// I2C PEC Error in reception
static per_inline bool per_i2c_rdclr_pecerr(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0_rdclr(&i2c->Per->Pecerr);
}

/// I2C Timeout or Tlow error
static per_inline bool per_i2c_timeout(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0(&i2c->Per->Timeout);
}

/// I2C Timeout or Tlow error
static per_inline bool per_i2c_rdclr_timeout(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0_rdclr(&i2c->Per->Timeout);
}

/// I2C SMBus alert
static per_inline bool per_i2c_smballert(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0(&i2c->Per->Smballert);
}

/// I2C SMBus alert
static per_inline bool per_i2c_rdclr_smballert(const per_i2c_t* const i2c)
{
    return per_bit_rc1_w0_rdclr(&i2c->Per->Smballert);
}

/// I2C Status register
static per_inline uint_fast16_t per_i2c_sr(const per_i2c_t* const i2c)
{
    return per_bit_rw16_reg(&i2c->Per->Sr);
}

/// I2C Status register
static per_inline void per_i2c_set_sr(const per_i2c_t* const i2c, uint16_t val)
{
    per_bit_rw16_reg_set(&i2c->Per->Sr, val);
}

/// I2C Master/slave
static per_inline bool per_i2c_msl(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Msl);
}

/// I2C Bus busy
static per_inline bool per_i2c_busy(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Busy);
}

/// I2C Transmitter/receiver
static per_inline bool per_i2c_tra(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Tra);
}

/// I2C General call address (Slave mode)
static per_inline bool per_i2c_gencall(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Gencall);
}

/// I2C SMBus device default address (Slave mode)
static per_inline bool per_i2c_smbdefault(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Smbdefault);
}

/// I2C SMBus host header (Slave mode)
static per_inline bool per_i2c_smbhost(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Smbhost);
}

/// I2C Dual flag (Slave mode)
static per_inline bool per_i2c_dualf(const per_i2c_t* const i2c)
{
    return per_bit_r1(&i2c->Per->Dualf);
}

/// I2C Packet error checking register
static per_inline bool per_i2c_pec(const per_i2c_t* const i2c)
{
    return per_bit_r8(&i2c->Per->Pec);
}

/// I2C Clock control register in Fm/Sm mode (Master mode)
static per_inline uint_fast16_t per_i2c_ccr(const per_i2c_t* const i2c)
{
    return per_bit_rw12(&i2c->Per->Ccr);
}

/// I2C Clock control register in Fm/Sm mode (Master mode)
static per_inline bool per_i2c_set_ccr(const per_i2c_t* const i2c, uint_fast16_t val)
{
    if (val > per_bit_rw12_max())
    {
        per_log_err(i2c->Err, PER_I2C_CCR_ERR, val);
        return false;
    }

    return per_bit_rw12_set(&i2c->Per->Ccr, val);
}

/// I2C Fm mode duty cycle
static per_inline bool per_i2c_duty(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Duty);
}

/// I2C Fm mode duty cycle
static per_inline void per_i2c_set_duty(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Duty, val);
}

/// I2C I2C master mode selection
static per_inline bool per_i2c_fs(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Fs);
}

/// I2C I2C master mode selection
static per_inline void per_i2c_set_fs(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Fs, val);
}

/// I2C Maximum rise time in Fm/Sm mode (Master mode)
static per_inline uint_fast16_t per_i2c_trise(const per_i2c_t* const i2c)
{
    return per_bit_rw6(&i2c->Per->Trise);
}

/// I2C Maximum rise time in Fm/Sm mode (Master mode)
static per_inline bool per_i2c_set_trise(const per_i2c_t* const i2c, uint_fast16_t val)
{
    if (val > per_bit_rw6_max())
    {
        per_log_err(i2c->Err, PER_I2C_TRISE_ERR, val);
        return false;
    }

    return per_bit_rw6_set(&i2c->Per->Trise, val);
}

/// I2C Digital noise filter
static per_inline uint_fast16_t per_i2c_dnf(const per_i2c_t* const i2c)
{
    return per_bit_rw4(&i2c->Per->Dnf);
}

/// I2C Digital noise filter
static per_inline bool per_i2c_set_dnf(const per_i2c_t* const i2c, uint_fast16_t val)
{
    if (val > per_bit_rw4_max())
    {
        per_log_err(i2c->Err, PER_I2C_DNF_ERR, val);
        return false;
    }

    return per_bit_rw4_set(&i2c->Per->Dnf, val);
}

static per_inline bool per_i2c_anoff(const per_i2c_t* const i2c)
{
    return per_bit_rw1(&i2c->Per->Anoff);
}

/// I2C Analog noise filter OFF
static per_inline void per_i2c_set_anoff(const per_i2c_t* const i2c, bool val)
{
    per_bit_rw1_set(&i2c->Per->Anoff, val);
}

/// I2C fetch and clear active flags and return the active flags
static per_inline per_i2c_sr_e per_i2c_flag(const per_i2c_t* const i2c)
{
    uint_fast16_t flag = per_i2c_sr(i2c);

    per_i2c_set_sr(i2c, ~(flag & (uint_fast16_t)PER_I2C_SR_CLEAR)); // Clear

    return (per_i2c_sr_e)flag;
}

#ifdef __cplusplus
}
#endif

#endif // per_i2c_f4_h_
