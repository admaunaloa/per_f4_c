/**
 * @file per_spi_f4.h
 *
 * This file contains the serial peripheral interface (SPI)
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

#ifndef per_spi_f4_h_
#define per_spi_f4_h_

#ifdef __cplusplus
extern "C"
{
#endif

#include "per_bit_f4.h"
#include "per_log_f4.h"

/// SPI1 base address
#define PER_SPI_1 ((per_spi_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB2 + (uintptr_t)0x3000))

/// SPI2 base address
#define PER_SPI_2 ((per_spi_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB1 + (uintptr_t)0x3800))

/// SPI3 base address
#define PER_SPI_3 ((per_spi_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB1 + (uintptr_t)0x3C00))

/// SPI4 base address
#define PER_SPI_4 ((per_spi_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB2 + (uintptr_t)0x3400))

/// SPI5 base address
#define PER_SPI_5 ((per_spi_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB2 + (uintptr_t)0x5000))

/// SPI6 base address
#define PER_SPI_6 ((per_spi_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB2 + (uintptr_t)0x5400))

/// Baudrate divider maximum value
#define PER_SPI_BR_MAX (256)

/// SPI error enumeration
typedef enum
{
    PER_SPI_OK_ERR = PER_LOG_SPI * PER_LOG_MULT, ///< No error
    PER_SPI_BR_ERR, ///< Baud-rate invalid
    PER_SPI_I2SDIV_ERR, ///< I2S divider value invalid
} per_spi_error_e;

/// SPI datalength to be transferred enumeration
typedef enum
{
    PER_SPI_DATLEN_16   = 0b00, ///< 16-bit data length
    PER_SPI_DATLEN_24   = 0b01, ///< 24-bit data length
    PER_SPI_DATLEN_32   = 0b10, ///< 32-bit data length
} per_spi_datlen_e;

/// SPI I2S standard selection enumeration
typedef enum
{
    PER_SPI_I2SSTD_PHILIPS   = 0b00, ///< Philips standard
    PER_SPI_I2SSTD_MSB       = 0b01, ///< MSB justified standard (left justified)
    PER_SPI_I2SSTD_LSB       = 0b10, ///< LSB justified standard (right justified)
    PER_SPI_I2SSTD_PCM       = 0b11, ///< PCM standard
} per_spi_i2sstd_e;

/// SPI I2S configuration mode
typedef enum
{
    PER_SPI_SLAVE_TX   = 0b00, ///< Slave - transmit
    PER_SPI_SLAVE_RX   = 0b01, ///< Slave - receive
    PER_SPI_MASTER_TX  = 0b10, ///< Master - transmit
    PER_SPI_MASTER_RX  = 0b11, ///< Master - receive
} per_spi_i2scfg_e;

typedef struct
{
    // control register 1 (SPI_CR1)
    per_bit_rw1_t Cpha; ///< Clock phase
    per_bit_rw1_t Cpol; ///< Clock polarity
    per_bit_rw1_t Mstr; ///< Master selection
    per_bit_rw3_t Br; ///< Baud rate control
    per_bit_rw1_t Spe; ///< SPI enable
    per_bit_rw1_t Lsbfirst; ///< Frame format
    per_bit_rw1_t Ssi; ///< Internal slave select
    per_bit_rw1_t Ssm; ///< Software slave management
    per_bit_rw1_t Rxonly; ///< Receive only
    per_bit_rw1_t Dff; ///< Data frame format
    per_bit_rw1_t Crcnext; ///< CRC transfer next
    per_bit_rw1_t Crcen; ///< Hardware CRC calculation enable
    per_bit_rw1_t Bidioe; ///< Output enable in bidirectional mode
    per_bit_rw1_t Bidimode; ///< Bidirectional data mode enable
    per_bit_n16_t Cr1Bit16; ///< Reserved

    // control register 2 (SPI_CR2)
    per_bit_rw1_t Rxdmaen; ///< Rx buffer DMA enable
    per_bit_rw1_t Txdmaen; ///< Tx buffer DMA enable
    per_bit_rw1_t Ssoe; ///< SS output enable
    per_bit_n1_t Cr2Bit3; ///< Reserved
    per_bit_rw1_t Frf; ///< Frame format
    per_bit_rw1_t Errie; ///< Error interrupt enable
    per_bit_rw1_t Rxneie; ///< RX buffer not empty interrupt enable
    per_bit_rw1_t Txeie; ///< Tx buffer empty interrupt enable
    per_bit_n24_t Cr2Bit8; ///< Reserved

    // status register (SPI_SR)
    per_bit_r1_t Rxne; ///< Receive buffer not empty
    per_bit_r1_t Txe; ///< Transmit buffer empty
    per_bit_r1_t Chside; ///< Channel side
    per_bit_r1_t Udr; ///< Underrun flag
    per_bit_rc1_w0_t Crcerr; ///< CRC error flag
    per_bit_r1_t Modf; ///< Mode fault
    per_bit_r1_t Ovr; ///< Overrun flag
    per_bit_r1_t Bsy; ///< Busy flag
    per_bit_r1_t Fre; ///< Frame format error
    per_bit_n23_t SrBit9; ///< Reserved

    // data register (SPI_DR)
    per_bit_rw16_reg_t Dr; ///< Data register

    // CRC polynomial register (SPI_CRCPR)
    per_bit_rw16_reg_t Crcpoly; ///< CRC polynomial register

    // RX CRC register (SPI_RXCRCR)
    per_bit_r16_reg_t Rxcrc; ///< Rx CRC register

    // TX CRC register (SPI_TXCRCR)
    per_bit_r16_reg_t Txcrc; ///< Tx CRC register

    // I2S configuration register (SPI_I2SCFGR)
    per_bit_rw1_t Chlen; ///< Channel length (number of bits per audio channel)
    per_bit_rw2_t Datlen; ///< Data length to be transferred
    per_bit_rw1_t Ckpol; ///< Steady state clock polarity
    per_bit_rw2_t I2sstd; ///< I2S standard selection
    per_bit_n1_t I2scfgrBit6; ///< Reserved
    per_bit_rw1_t Pcmsync; ///< PCM frame synchronization
    per_bit_rw2_t I2scfg; ///< I2S configuration mode
    per_bit_rw1_t I2se; ///< I2S Enable
    per_bit_rw1_t I2smod; ///< I2S mode selection
    per_bit_n20_t I2scfgrBit12; ///< Reserved

    // I2S prescaler register (SPI_I2SPR)
    per_bit_rw8_t I2sdiv; ///< I2S Linear prescaler
    per_bit_rw1_t Odd; ///< Odd factor for the prescaler
    per_bit_rw1_t Mckoe; ///< Master clock output enable
    per_bit_n22_t I2sprBit10; ///< Reserved
} __attribute__((packed)) per_spi_per_t;

/// SPI descriptor
typedef struct
{
    per_spi_per_t* const Per; ///< Peripheral
    const per_log_e Err; ///< Peripheral error number
} per_spi_t;

/// SPI Clock phase
static per_inline bool per_spi_cpha(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Cpha);
}

/// SPI Clock phase set
static per_inline void per_spi_set_cpha(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Cpha, val);
}

/// SPI Clock polarity
static per_inline bool per_spi_cpol(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Cpol);
}

/// SPI Clock polarity
static per_inline void per_spi_set_cpol(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Cpol, val);
}

/// SPI Master selection
static per_inline bool per_spi_mstr(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Mstr);
}

/// SPI Master selection
static per_inline void per_spi_set_mstr(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Mstr, val);
}

/// SPI Baud rate control
static per_inline uint_fast32_t per_spi_br(const per_spi_t* const spi)
{
    return per_bit_inv_log2(per_bit_rw3(&spi->Per->Br)) << 1;
}

/// SPI Baud rate control
static per_inline bool per_spi_set_br(const per_spi_t* const spi, uint_fast32_t div)
{
    if ((div > PER_SPI_BR_MAX) ||
        !per_bit_is_log2(div))
    {
        per_log_err(spi->Err, PER_SPI_BR_ERR, div);
        return false;
    }

    return per_bit_rw3_set(&spi->Per->Br, per_bit_log2(div >> 1));
}

/// SPI enable
static per_inline bool per_spi_spe(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Spe);
}

/// SPI enable
static per_inline void per_spi_set_spe(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Spe, val);
}

/// SPI Frame format
static per_inline bool per_spi_lsbfirst(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Lsbfirst);
}

/// SPI Frame format
static per_inline void per_spi_set_lsbfirst(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Lsbfirst, val);
}

/// SPI Internal slave select
static per_inline bool per_spi_ssi(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Ssi);
}

/// SPI Internal slave select
static per_inline void per_spi_set_ssi(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Ssi, val);
}

/// SPI Software slave management
static per_inline bool per_spi_ssm(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Ssm);
}

/// SPI Software slave management
static per_inline void per_spi_set_ssm(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Ssm, val);
}

/// SPI Receive only
static per_inline bool per_spi_rxonly(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Rxonly);
}

/// SPI Receive only
static per_inline void per_spi_set_rxonly(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Rxonly, val);
}

/// SPI Data frame format
static per_inline bool per_spi_dff(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Dff);
}

/// SPI Data frame format
static per_inline void per_spi_set_dff(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Dff, val);
}

/// SPI CRC transfer next
static per_inline bool per_spi_crcnext(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Crcnext);
}

/// SPI CRC transfer next
static per_inline void per_spi_set_crcnext(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Crcnext, val);
}

/// SPI Hardware CRC calculation enable
static per_inline bool per_spi_crcen(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Crcen);
}

/// SPI Hardware CRC calculation enable
static per_inline void per_spi_set_crcen(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Crcen, val);
}

/// SPI Output enable in bidirectional mode
static per_inline bool per_spi_bidioe(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Bidioe);
}

/// SPI Output enable in bidirectional mode
static per_inline void per_spi_set_bidioe(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Bidioe, val);
}

/// SPI Bidirectional data mode enable
static per_inline bool per_spi_bidimode(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Bidimode);
}

/// SPI Bidirectional data mode enable
static per_inline void per_spi_set_bidimode(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Bidimode, val);
}

/// SPI Rx buffer DMA enable
static per_inline bool per_spi_rxdmaen(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Rxdmaen);
}

/// SPI Rx buffer DMA enable
static per_inline void per_spi_set_rxdmaen(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Rxdmaen, val);
}

/// SPI Tx buffer DMA enable
static per_inline bool per_spi_txdmaen(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Txdmaen);
}

/// SPI Tx buffer DMA enable
static per_inline void per_spi_set_txdmaen(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Txdmaen, val);
}

/// SPI SS output enable
static per_inline bool per_spi_ssoe(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Ssoe);
}

/// SPI SS output enable
static per_inline void per_spi_set_ssoe(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Ssoe, val);
}

/// SPI Frame format
static per_inline bool per_spi_frf(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Frf);
}

/// SPI Frame format
static per_inline void per_spi_set_frf(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Frf, val);
}

/// SPI Error interrupt enable
static per_inline bool per_spi_errie(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Errie);
}

/// SPI Error interrupt enable
static per_inline void per_spi_set_errie(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Errie, val);
}

/// SPI RX buffer not empty interrupt enable
static per_inline bool per_spi_rxneie(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Rxneie);
}

/// SPI RX buffer not empty interrupt enable
static per_inline void per_spi_set_rxneie(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Rxneie, val);
}

/// SPI Tx buffer empty interrupt enable
static per_inline bool per_spi_txeie(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Txeie);
}

/// SPI Tx buffer empty interrupt enable
static per_inline void per_spi_set_txeie(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Txeie, val);
}

/// SPI Receive buffer not empty
static per_inline bool per_spi_rxne(const per_spi_t* const spi)
{
    return per_bit_r1(&spi->Per->Rxne);
}

/// SPI Transmit buffer empty
static per_inline bool per_spi_txe(const per_spi_t* const spi)
{
    return per_bit_r1(&spi->Per->Txe);
}

/// SPI Channel side
static per_inline bool per_spi_chside(const per_spi_t* const spi)
{
    return per_bit_r1(&spi->Per->Chside);
}

/// SPI Underrun flag
static per_inline bool per_spi_udr(const per_spi_t* const spi)
{
    return per_bit_r1(&spi->Per->Udr);
}

/// SPI CRC error flag
static per_inline bool per_spi_crcerr(const per_spi_t* const spi)
{
    return per_bit_rc1_w0(&spi->Per->Crcerr);
}

/// SPI clear CRC error flag
static per_inline bool per_spi_rdclr_crcerr(const per_spi_t* const spi)
{
    return per_bit_rc1_w0_rdclr(&spi->Per->Crcerr);
}

/// SPI Mode fault
static per_inline bool per_spi_modf(const per_spi_t* const spi)
{
    return per_bit_r1(&spi->Per->Modf);
}

/// SPI Overrun flag
static per_inline bool per_spi_ovr(const per_spi_t* const spi)
{
    return per_bit_r1(&spi->Per->Ovr);
}

/// SPI Busy flag
static per_inline bool per_spi_bsy(const per_spi_t* const spi)
{
    return per_bit_r1(&spi->Per->Bsy);
}

/// SPI Frame format error
static per_inline bool per_spi_fre(const per_spi_t* const spi)
{
    return per_bit_r1(&spi->Per->Fre);
}

/// SPI Data register
static per_inline uint_fast16_t per_spi_dr(const per_spi_t* const spi)
{
    return per_bit_rw16_reg(&spi->Per->Dr);
}

/// SPI Data register
static per_inline void per_spi_set_dr(const per_spi_t* const spi, uint16_t dr)
{
    per_bit_rw16_reg_set(&spi->Per->Dr, dr);
}

/// SPI address Data register
static per_inline volatile uint_fast16_t* per_spi_addr_dr(const per_spi_t* const spi)
{
    return &PER_BIT_BIT_BAND_TO_REG(&spi->Per->Dr)->Reg16;
}

/// SPI CRC polynomial register
static per_inline uint_fast16_t per_spi_crcpoly(const per_spi_t* const spi)
{
    return per_bit_rw16_reg(&spi->Per->Crcpoly);
}

/// SPI CRC polynomial register
static per_inline void per_spi_set_crcpoly(const per_spi_t* const spi, uint16_t poly)
{
    per_bit_rw16_reg_set(&spi->Per->Crcpoly, poly);
}

/// SPI Rx CRC register
static per_inline uint_fast16_t per_spi_rxcrc(const per_spi_t* const spi)
{
    return per_bit_r16_reg(&spi->Per->Rxcrc);
}

/// SPI Tx CRC register
static per_inline uint_fast16_t per_spi_txcrc(const per_spi_t* const spi)
{
    return per_bit_r16_reg(&spi->Per->Txcrc);
}

/// SPI Channel length (number of bits per audio channel)
static per_inline bool per_spi_chlen(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Chlen);
}

/// SPI Channel length (number of bits per audio channel)
static per_inline void per_spi_set_chlen(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Chlen, val);
}

/// SPI Data length to be transferred
static per_inline per_spi_datlen_e per_spi_datlen(const per_spi_t* const spi)
{
    return (per_spi_datlen_e)per_bit_rw2(&spi->Per->Datlen);
}

/// SPI Data length to be transferred
static per_inline bool per_spi_set_datlen(const per_spi_t* const spi, per_spi_datlen_e len)
{
    return per_bit_rw2_set(&spi->Per->Datlen, (uint_fast16_t)len);
}

/// SPI Steady state clock polarity
static per_inline bool per_spi_ckpol(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Ckpol);
}

/// SPI Steady state clock polarity
static per_inline void per_spi_set_ckpol(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Ckpol, val);
}

/// SPI I2S standard selection
static per_inline per_spi_i2sstd_e per_spi_i2sstd(const per_spi_t* const spi)
{
    return (per_spi_i2sstd_e)per_bit_rw2(&spi->Per->I2sstd);
}

/// SPI I2S standard selection
static per_inline bool per_spi_set_i2sstd(const per_spi_t* const spi, per_spi_i2sstd_e std)
{
    return per_bit_rw2_set(&spi->Per->I2sstd, (uint_fast16_t)std);
}

/// SPI PCM frame synchronization
static per_inline bool per_spi_pcmsync(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Pcmsync);
}

/// SPI PCM frame synchronization
static per_inline void per_spi_set_pcmsync(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Pcmsync, val);
}

/// SPI I2S configuration mode
static per_inline per_spi_i2scfg_e per_spi_i2scfg(const per_spi_t* const spi)
{
    return (per_spi_i2scfg_e)per_bit_rw2(&spi->Per->I2scfg);
}

/// SPI I2S configuration mode
static per_inline bool per_spi_set_i2scfg(const per_spi_t* const spi, per_spi_i2scfg_e cfg)
{
    return per_bit_rw2_set(&spi->Per->I2scfg, (uint_fast16_t)cfg);
}

/// SPI I2S Enable
static per_inline bool per_spi_i2se(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->I2se);
}

/// SPI I2S Enable
static per_inline void per_spi_set_i2se(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->I2se, val);
}

/// SPI I2S mode selection
static per_inline bool per_spi_i2smod(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->I2smod);
}

/// SPI I2S mode selection
static per_inline void per_spi_set_i2smod(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->I2smod, val);
}

/// SPI I2S Linear prescaler
static per_inline uint_fast16_t per_spi_i2sdiv(const per_spi_t* const spi)
{
    return per_bit_rw8(&spi->Per->I2sdiv);
}

/// SPI I2S Linear prescaler
static per_inline bool per_spi_set_i2sdiv(const per_spi_t* const spi, uint_fast16_t pre)
{
    if (pre < 2) // Values 0 and 1 are forbidden)
    {
        per_log_err(spi->Err, PER_SPI_I2SDIV_ERR, pre);
        return false;
    }

    return per_bit_rw8_set(&spi->Per->I2sdiv, pre);
}

/// SPI Odd factor for the prescaler
static per_inline bool per_spi_odd(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Odd);
}

/// SPI Odd factor for the prescaler
static per_inline void per_spi_set_odd(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Odd, val);
}

/// SPI Master clock output enable
static per_inline bool per_spi_mckoe(const per_spi_t* const spi)
{
    return per_bit_rw1(&spi->Per->Mckoe);
}

/// SPI Master clock output enable
static per_inline void per_spi_set_mckoe(const per_spi_t* const spi, bool val)
{
    per_bit_rw1_set(&spi->Per->Mckoe, val);
}

#ifdef __cplusplus
}
#endif

#endif // per_spi_f4_h_
