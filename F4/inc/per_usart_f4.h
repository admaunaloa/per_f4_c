/**
 * @file per_usart_f4.h
 *
 * This file contains the peripheral Universal Synchronous Asynchronous Receiver Transmitter (USART)
 * For the F4 series
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
 * For each USART peripheral bit the possible get and set functions are provided.
 * The syntax is
 * per_      Peripheral library prefix
 * _usart_   USART or UART type
 * _ue       Field name as in the manual. UE is Usart Enable.
 *
 * Example:
 * bool per_usart_ue(per_usart_t* )        returns the value of the Usart Enable bit.
 * void per_usart_set_ue(per_usart_t* , bool) modifies the value of Usart Enable bit.
 *
 * The per_usart_t pointers are provided in a function format
 * per_usart_t* per_usart_1(void)
 * per_usart_t* per_usart_2(void)
 *
 * Enabling USART3 comes down to:
 * per_usart_set_ue(per_usart_3(), true);
 *
 * This set UE example results in a minimal number of assembly instructions because
 * both functions are inlined and bitband is used. Both functions also make it
 * type-safe and they enable features such as zero-cost error checking.
 * For minimal size and optimal performance the per_usart_t* should be a compile time
 * constant, this is often implemented in the Board Support Package (bsp_) layer.
 *
 * Convenience functions:
 * per_usart_set_div(const per_usart_t* const usart, uint_fast32_t fract, uint_fast32_t mant)
 * per_usart_set_baudrate(const per_usart_t* const usart, uint_fast32_t rate)
 * per_usart_flag(const per_usart_t* const usart)
 */

#ifndef per_usart_f4_h_
#define per_usart_f4_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_bit_f4.h"
#include "per_log_f4.h"

/// USART maximum value for DR (9 bit)
#define PER_USART_DR_MAX PER_BIT_MAX(5)

/// USART error enumeration
typedef enum
{
    PER_USART_OK_ERR = PER_LOG_USART * PER_LOG_MULT, ///< No error
    PER_USART_LOCK_ERR,             ///< Peripheral was locked, invalid key
    PER_USART_BUSY_ERR,             ///< There was still an other action active
    PER_USART_OVERRUN_ERR,          ///< Overrun error
    PER_USART_NOISE_ERR,            ///< Noise detected
    PER_USART_FRAMING_ERR,          ///< Framing error
    PER_USART_PARITY_ERR,           ///< Parity error
    PER_USART_SET_DR_ERR,           ///< DR data invalid value
    PER_USART_SET_DIV_FRACTION_ERR, ///< DIV_Fraction error invalid value
    PER_USART_SET_DIV_FRACT_ERR,    ///< DIV_Fraction error invalid value
    PER_USART_SET_DIV_MANTISSA_ERR, ///< DIV_Mantissa error invalid value
    PER_USART_SET_DIV_MANT_ERR,     ///< DIV_Mantissa error invalid value
    PER_USART_SET_ADD_ERR,          ///< ADD address node invalid value
    PER_USART_SET_PSC_IRDA_MAX_ERR, ///< PSC data invalid value IrDA
    PER_USART_SET_PSC_SC_MAX_ERR,   ///< PSC data invalid value SmartCard SC
    PER_USART_SET_GT_MAX_ERR,       ///< GT data invalid value
} per_usart_error_e;

/// USART Status register flags
typedef enum
{
    PER_USART_SR_PE    = 0b000000000001, ///< Parity error
    PER_USART_SR_FE    = 0b000000000010, ///< Framing error
    PER_USART_SR_NF    = 0b000000000100, ///< Noise detected flag
    PER_USART_SR_ORE   = 0b000000001000, ///< Overrun error
    PER_USART_SR_IDLE  = 0b000000010000, ///< IDLE line detected
    PER_USART_SR_RXNE  = 0b000001000000, ///< Read data register not empty
    PER_USART_SR_TC    = 0b000010000000, ///< Transmission complete
    PER_USART_SR_TXE   = 0b000100000000, ///< Transmit data register empty
    PER_USART_SR_LBD   = 0b001000000000, ///< LIN break detection flag
    PER_USART_SR_CTS   = 0b010000000000, ///< CTS flag
    PER_USART_SR_CLEAR = PER_USART_SR_RXNE | ///< Clear flags
                         PER_USART_SR_TC |
                         PER_USART_SR_LBD |
                         PER_USART_SR_CTS,
    PER_USART_SR_ERR   = PER_USART_SR_PE | ///< Error flags
                         PER_USART_SR_FE |
                         PER_USART_SR_NF |
                         PER_USART_SR_ORE,
} per_usart_sr_e;

/// USART data bits enumeration
typedef enum
{
    PER_USART_M_8, ///< 1 Start bit, 8 Data bits, n Stop bit
    PER_USART_M_9,  ///< 1 Start bit, 9 Data bits, n Stop bit
} per_usart_m_e;

/// USART oversampling enumeration
typedef enum
{
    PER_USART_OVER_16 = 16, ///< oversampling by 16
    PER_USART_OVER_8  = 8,  ///< oversampling by 8
} per_usart_over_e;

/// USART parity mode enumeration
typedef enum
{
    PER_USART_PS_EVEN = 0b0, ///< Even parity
    PER_USART_PS_ODD  = 0b1, ///< Odd parity
    PER_USART_PS_NONE,       ///< No parity control
} per_usart_ps_e;

/// USART stop enumeration
typedef enum
{
    PER_USART_STOP_1_0 = 0b00, ///< 1 Stop bit
    PER_USART_STOP_0_5 = 0b01, ///< 0.5 Stop bit
    PER_USART_STOP_2   = 0b10, ///< 2 Stop bits
    PER_USART_STOP_1_5 = 0b11, ///< 1.5 Stop bit
} per_usart_stop_e;

typedef struct
{
    // USART status register (USART_SR)
    union
    {
        struct
        {
            per_bit_r1_t Pe; ///< Parity error
            per_bit_r1_t Fe; ///< Framing error
            per_bit_r1_t Nf; ///< Noise detected flag
            per_bit_r1_t Ore; ///< Overrun error
            per_bit_r1_t Idle; ///< IDLE line detected
            per_bit_rc1_t Rxne; ///< Read data register not empty
            per_bit_rc1_t Tc; ///< Transmission complete
            per_bit_r1_t Txe; ///< Transmit data register empty
            per_bit_rc1_t Lbd; ///< LIN break detection flag
            per_bit_rc1_t Cts; ///< CTS flag
            per_bit_n22_t SrBit10; ///< Reserved
        };
        per_bit_rw16_reg_t Sr; ///< Status register
    };

    // USART Data register (USART_DR)
    per_bit_rw16_reg_t Dr; ///< Data value

    // USART Baud rate register (USART_BRR)
    union
    {
        struct
        {
            per_bit_rw4_t Div_Fraction; ///< fraction of USARTDIV
            per_bit_rw12_t Div_Mantissa; ///< mantissa of USARTDIV
            per_bit_n16_t BrrBit16; ///< Reserved
        };
        per_bit_rw16_reg_t Div; ///< fraction and mantissa
    };

    // USART control register 1 (USART_CR1)
    per_bit_rw1_t Sbk; ///< Send break
    per_bit_rw1_t Rwu; ///< Receiver wake-up
    per_bit_rw1_t Re; ///< Receiver enable
    per_bit_rw1_t Te; ///< Transmitter enable
    per_bit_rw1_t Idleie; ///< IDLE interrupt enable
    per_bit_rw1_t Rxneie; ///< RXNE interrupt enable
    per_bit_rw1_t Tcie; ///< Transmission complete interrupt enable
    per_bit_rw1_t Txeie; ///< TXE interrupt enable
    per_bit_rw1_t Peie; ///< PE interrupt enable
    per_bit_rw1_t Ps; ///< Parity selection
    per_bit_rw1_t Pce; ///< Parity control enable
    per_bit_rw1_t Wake; ///< Wake-up method
    per_bit_rw1_t M; ///< Word length
    per_bit_rw1_t Ue; ///< USART enable
    per_bit_n1_t Cr1Bit14; ///< Reserved
    per_bit_rw1_t Over8; ///< Over-sampling mode
    per_bit_n16_t Cr1Bit16; ///< Reserved

    // USART control register 2 (USART_CR2)
    per_bit_rw4_t Add; ///< Address of the USART node
    per_bit_n1_t Cr2Bit1;
    per_bit_rw1_t Lbdl; ///< lIN break detection length
    per_bit_rw1_t Lbdie; ///< LIN break detection interrupt enable
    per_bit_n1_t Cr2Bit4;
    per_bit_rw1_t Lbcl; ///< Last bit clock pulse
    per_bit_rw1_t Cpha; ///< Clock phase
    per_bit_rw1_t Cpol; ///< Clock polarity
    per_bit_rw1_t Clken; ///< Clock enable
    per_bit_rw2_t Stop; ///< STOP bits
    per_bit_rw1_t Linen; ///< LIN mode enable
    per_bit_n17_t Cr2Bit15; ///< Reserved

    // USART control register 3 (USART_CR3)
    per_bit_rw1_t Eie; ///< Error interrupt enable
    per_bit_rw1_t Iren; ///< IrDA mode enable
    per_bit_rw1_t Irlp; ///< IrDA low-power
    per_bit_rw1_t Hdsel; ///< Half-duplex selection
    per_bit_rw1_t Nack; ///< Smartcard NACK enable
    per_bit_rw1_t Scen; ///< Smartcard mode enable
    per_bit_rw1_t Dmar; ///< DMA enable receiver
    per_bit_rw1_t Dmat; ///< DMA enable transmitter
    per_bit_rw1_t Rtse; ///< RTS enable
    per_bit_rw1_t Ctse; ///< CTS enable
    per_bit_rw1_t Ctsie; ///< CTS interrupt enable
    per_bit_rw1_t Onebit; ///< One sample bit method enable
    per_bit_n20_t Cr3Bit12; ///< Reserved

    // USART Guard time and pre-scaler register (USART_GTPR)
    per_bit_rw8_t Psc; ///< Pre-scaler value
    per_bit_rw8_t Gt; ///< Guard time value
    per_bit_n16_t GtprBit16; ///< Reserved
} __attribute__((packed)) per_usart_per_t;

/// USART descriptor
typedef struct
{
    per_usart_per_t* const Per;   ///< Peripheral
    const per_log_e Err;          ///< Peripheral error number
    uint_fast32_t(* const Freq)(void); ///< Pointer to function that resolves base frequency
    const bool Uart;              ///< UART type
} per_usart_t;

/// USART Parity error
static per_inline bool per_usart_pe(const per_usart_t* const usart)
{
    return per_bit_r1(&usart->Per->Pe);
}

/// USART Framing error
static per_inline bool per_usart_fe(const per_usart_t* const usart)
{
    return per_bit_r1(&usart->Per->Fe);
}

/// USART Noise detected flag
static per_inline bool per_usart_nf(const per_usart_t* const usart)
{
    return per_bit_r1(&usart->Per->Nf);
}

/// USART Overrun error
static per_inline bool per_usart_ore(const per_usart_t* const usart)
{
    return per_bit_r1(&usart->Per->Ore);
}

/// USART Idle line detected
static per_inline bool per_usart_idle(const per_usart_t* const usart)
{
    return per_bit_r1(&usart->Per->Idle);
}

/// USART Read data register not empty
static per_inline bool per_usart_rxne(const per_usart_t* const usart)
{
    return per_bit_rc1(&usart->Per->Rxne);
}

/// USART Clear read data register not empty
static per_inline bool per_usart_rdclr_rxne(const per_usart_t* const usart)
{
    return per_bit_rc1_rdclr(&usart->Per->Rxne);
}

/// USART Transmission complete
static per_inline bool per_usart_tc(const per_usart_t* const usart)
{
    return per_bit_rc1(&usart->Per->Tc);
}

/// USART clear transmission complete
static per_inline bool per_usart_rdclr_tc(const per_usart_t* const usart)
{
    return per_bit_rc1_rdclr(&usart->Per->Tc);
}

/// USART transmit data register empty
static per_inline bool per_usart_txe(const per_usart_t* const usart)
{
    return per_bit_r1(&usart->Per->Txe);
}

/// USART LIN break detection flag
static per_inline bool per_usart_lbd(const per_usart_t* const usart)
{
    return per_bit_rc1(&usart->Per->Lbd);
}

/// USART Clear LIN break detection flag
static per_inline bool per_usart_rdclr_lbd(const per_usart_t* const usart)
{
    return per_bit_rc1_rdclr(&usart->Per->Lbd);
}

/// USART CTS flag
static per_inline bool per_usart_cts(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rc1(&usart->Per->Cts);
}

/// USART Clear CTS flag
static per_inline bool per_usart_rdclr_cts(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rc1_rdclr(&usart->Per->Cts);
}

/// USART Status register
static per_inline uint_fast16_t per_usart_sr(const per_usart_t* const usart)
{
    return per_bit_rw16_reg(&usart->Per->Sr);
}

/// USART Status register
static per_inline void per_usart_set_sr(const per_usart_t* const usart, uint16_t val)
{
    per_bit_rw16_reg_set(&usart->Per->Sr, val);
}

/// USART Data value
static per_inline uint_fast16_t per_usart_dr(const per_usart_t* const usart)
{
    return per_bit_rw16_reg(&usart->Per->Dr);
}

/// USART set Data value
static per_inline bool per_usart_set_dr(const per_usart_t* const usart, uint16_t dr)
{
    if (dr > PER_USART_DR_MAX)
    {
        per_log_err(usart->Err, PER_USART_SET_DR_ERR, dr);
        return false;
    }

    per_bit_rw16_reg_set(&usart->Per->Dr, dr);
    return true;
}

/// USART address Data value register
static per_inline volatile uint_fast16_t* per_usart_addr_dr(const per_usart_t* const usart)
{
    return &PER_BIT_BIT_BAND_TO_REG(&usart->Per->Dr)->Reg16;
}

/// USART Fraction of USARTDIV get
static per_inline uint_fast16_t per_usart_div_fraction(const per_usart_t* const usart)
{
    return per_bit_rw4(&usart->Per->Div_Fraction);
}

/// USART Fraction of USARTDIV set
static per_inline bool per_usart_set_div_fraction(const per_usart_t* const usart, uint_fast32_t div)
{
    if (div > per_bit_rw4_max())
    {
        per_log_err(usart->Err, PER_USART_SET_DIV_FRACTION_ERR, div);
        return false;
    }

    return per_bit_rw4_set(&usart->Per->Div_Fraction, (uint_fast16_t)div);
}

/// USART Mantissa of USARTDIV get
static per_inline uint_fast16_t per_usart_div_mantissa(const per_usart_t* const usart)
{
    return per_bit_rw12(&usart->Per->Div_Mantissa);
}

/// USART Mantissa of USARTDIV set
static per_inline bool per_usart_set_div_mantissa(const per_usart_t* const usart, uint_fast32_t div)
{
    if (div > per_bit_rw12_max())
    {
        per_log_err(usart->Err, PER_USART_SET_DIV_MANTISSA_ERR, div);
        return false;
    }

    return per_bit_rw12_set(&usart->Per->Div_Mantissa, (uint_fast16_t)div);
}

/// USART Mantissa and fraction of USARTDIV
static per_inline bool per_usart_set_div(const per_usart_t* const usart, uint_fast32_t fract, uint_fast32_t mant)
{
    if (fract > per_bit_rw4_max())
    {
        per_log_err(usart->Err, PER_USART_SET_DIV_FRACT_ERR, fract);
        return false;
    }

    if (mant > per_bit_rw12_max())
    {
        per_log_err(usart->Err, PER_USART_SET_DIV_MANT_ERR, mant);
        return false;
    }

    per_bit_rw16_reg_set(&usart->Per->Div, (uint_fast16_t)(fract | (mant << per_bit_rw12_shift(&usart->Per->Div_Mantissa))));
    return true;
}

/// USART Send break get
static per_inline bool per_usart_sbk(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Sbk);
}

/// USART Send break set
static per_inline void per_usart_set_sbk(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Sbk, val);
}

/// USART Receiver wake-up get
static per_inline bool per_usart_rwu(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Rwu);
}

/// USART Receiver wake-up set
static per_inline void per_usart_set_rwu(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Rwu, val);
}

/// USART Receiver enable get
static per_inline bool per_usart_re(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Re);
}

/// USART Receiver enable set
static per_inline void per_usart_set_re(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Re, val);
}

/// USART Transmitter enable get
static per_inline bool per_usart_te(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Te);
}

/// USART Transmitter enable set
static per_inline void per_usart_set_te(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Te, val);
}

/// USART IDLE interrupt enable get
static per_inline bool per_usart_idleie(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Idleie);
}

/// USART IDLE interrupt enable set
static per_inline void per_usart_set_idleie(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Idleie, val);
}

/// USART RXNE interrupt enable get
static per_inline bool per_usart_rxneie(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Rxneie);
}

/// USART RXNE interrupt enable set
static per_inline void per_usart_set_rxneie(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Rxneie, val);
}

/// USART Transmission complete interrupt enable get
static per_inline bool per_usart_tcie(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Tcie);
}

/// USART Transmission complete interrupt enable set
static per_inline void per_usart_set_tcie(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Tcie, val);
}

/// USART TXE interrupt enable get
static per_inline bool per_usart_txeie(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Txeie);
}

/// USART TXE interrupt enable set
static per_inline void per_usart_set_txeie(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Txeie, val);
}

/// USART PE interrupt enable get
static per_inline bool per_usart_peie(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Peie);
}

/// USART PE interrupt enable set
static per_inline void per_usart_set_peie(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Peie, val);
}

/// USART Parity selection get
static per_inline bool per_usart_ps(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Ps);
}

/// USART Parity selection set
static per_inline void per_usart_set_ps(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Ps, val);
}

/// USART Parity control enable get
static per_inline bool per_usart_pce(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Pce);
}

/// USART Parity control enable set
static per_inline void per_usart_set_pce(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Pce, val);
}

/// USART Wake-up method get
static per_inline bool per_usart_wake(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Wake);
}

/// USART Wake-up method set
static per_inline void per_usart_set_wake(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Wake, val);
}

/// USART Word length get
static per_inline bool per_usart_m(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->M);
}

/// USART Word length set
static per_inline void per_usart_set_m(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->M, val);
}

/// USART enable get
static per_inline bool per_usart_ue(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Ue);
}

/// USART enable set
static per_inline void per_usart_set_ue(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Ue, val);
}

/// USART Oversampling mode get
static per_inline bool per_usart_over8(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Over8);
}

/// USART Oversampling mode set
static per_inline void per_usart_set_over8(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Over8, val);
}

/// USART Address of the USART node get
static per_inline uint_fast16_t per_usart_add(const per_usart_t* const usart)
{
    return per_bit_rw4(&usart->Per->Add);
}

/// USART Address of the USART node set
static per_inline bool per_usart_set_add(const per_usart_t* const usart, uint_fast16_t add)
{
    if (add > per_bit_rw4_max())
    {
        per_log_err(usart->Err, PER_USART_SET_ADD_ERR, add);
        return false;
    }

    return per_bit_rw4_set(&usart->Per->Add, add);
}

/// USART lIN break detection length get
static per_inline bool per_usart_lbdl(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Lbdl);
}

/// USART lIN break detection length set
static per_inline void per_usart_set_lbdl(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Lbdl, val);
}

/// USART LIN break detection interrupt enable get
static per_inline bool per_usart_lbdie(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Lbdie);
}

/// USART LIN break detection interrupt enable set
static per_inline void per_usart_set_lbdie(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Lbdie, val);
}

/// USART Last bit clock pulse get
static per_inline bool per_usart_lbcl(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rw1(&usart->Per->Lbcl);
}

/// USART Last bit clock pulse set
static per_inline void per_usart_set_lbcl(const per_usart_t* const usart, bool val)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&usart->Per->Lbcl, val);
}

/// USART Clock phase get
static per_inline bool per_usart_cpha(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rw1(&usart->Per->Cpha);
}

/// USART Clock phase set
static per_inline void per_usart_set_cpha(const per_usart_t* const usart, bool val)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&usart->Per->Cpha, val);
}

/// USART Clock polarity get
static per_inline bool per_usart_cpol(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rw1(&usart->Per->Cpol);
}

/// USART Clock polarity set
static per_inline void per_usart_set_cpol(const per_usart_t* const usart, bool val)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&usart->Per->Cpol, val);
}

/// USART Clock enable get
static per_inline bool per_usart_clken(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rw1(&usart->Per->Clken);
}

/// USART Clock enable set
static per_inline void per_usart_set_clken(const per_usart_t* const usart, bool val)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&usart->Per->Clken, val);
}

/// USART stop bits get
static per_inline per_usart_stop_e per_usart_stop(const per_usart_t* const usart)
{
    return (per_usart_stop_e)per_bit_rw2(&usart->Per->Stop);
}

/// USART stop bits set
static per_inline bool per_usart_set_stop(const per_usart_t* const usart, per_usart_stop_e stop)
{
    return per_bit_rw2_set(&usart->Per->Stop, (uint_fast16_t)stop);
}

/// USART LIN mode enable get
static per_inline bool per_usart_linen(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Linen);
}

/// USART LIN mode enable set
static per_inline void per_usart_set_linen(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Linen, val);
}

/// USART Error interrupt enable get
static per_inline bool per_usart_eie(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Eie);
}

/// USART Error interrupt enable set
static per_inline void per_usart_set_eie(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Eie, val);
}

/// USART IrDA mode enable get
static per_inline bool per_usart_iren(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Iren);
}

/// USART IrDA mode enable set
static per_inline void per_usart_set_iren(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Iren, val);
}

/// USART IrDA low-power get
static per_inline bool per_usart_irlp(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Irlp);
}

/// USART IrDA low-power set
static per_inline void per_usart_set_irlp(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Irlp, val);
}

/// USART Half-duplex selection get
static per_inline bool per_usart_hdsel(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Hdsel);
}

/// USART Half-duplex selection set
static per_inline void per_usart_set_hdsel(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Hdsel, val);
}

/// USART Smartcard NACK enable get
static per_inline bool per_usart_nack(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rw1(&usart->Per->Nack);
}

/// USART Smartcard NACK enable set
static per_inline void per_usart_set_nack(const per_usart_t* const usart, bool val)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&usart->Per->Nack, val);
}

/// USART Smartcard mode enable get
static per_inline bool per_usart_scen(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rw1(&usart->Per->Scen);
}

/// USART Smartcard mode enable set
static per_inline void per_usart_set_scen(const per_usart_t* const usart, bool val)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&usart->Per->Scen, val);
}

/// USART DMA enable receiver get
static per_inline bool per_usart_dmar(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Dmar);
}

/// USART DMA enable receiver set
static per_inline void per_usart_set_dmar(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Dmar, val);
}

/// USART DMA enable transmitter get
static per_inline bool per_usart_dmat(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Dmat);
}

/// USART DMA enable transmitter set
static per_inline void per_usart_set_dmat(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Dmat, val);
}

/// USART RTS enable get
static per_inline bool per_usart_rtse(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rw1(&usart->Per->Rtse);
}

/// USART RTS enable set
static per_inline void per_usart_set_rtse(const per_usart_t* const usart, bool val)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&usart->Per->Rtse, val);
}

/// USART CTS enable get
static per_inline bool per_usart_ctse(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rw1(&usart->Per->Ctse);
}

/// USART CTS enable set
static per_inline void per_usart_set_ctse(const per_usart_t* const usart, bool val)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&usart->Per->Ctse, val);
}

/// USART CTS interrupt enable get
static per_inline bool per_usart_ctsie(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rw1(&usart->Per->Ctsie);
}

/// USART CTS interrupt enable set
static per_inline void per_usart_set_ctsie(const per_usart_t* const usart, bool val)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }

    per_bit_rw1_set(&usart->Per->Ctsie, val);
}

/// USART One sample bit method enable get
static per_inline bool per_usart_onebit(const per_usart_t* const usart)
{
    return per_bit_rw1(&usart->Per->Onebit);
}

/// USART One sample bit method enable set
static per_inline void per_usart_set_onebit(const per_usart_t* const usart, bool val)
{
    per_bit_rw1_set(&usart->Per->Onebit, val);
}

/// USART IrDA Low-Power Baud Rate get
static per_inline uint_fast16_t per_usart_psc_irda(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rw8(&usart->Per->Psc);
}

/// USART IrDA Low-Power Baud Rate set
static per_inline bool per_usart_set_psc_irda(const per_usart_t* const usart, uint_fast16_t psc)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }

    if ((psc == 0) || (psc > per_bit_rw8_max()))
    {
        per_log_err(usart->Err, PER_USART_SET_PSC_IRDA_MAX_ERR, psc);
        return false;
    }

    return per_bit_rw8_set(&usart->Per->Psc, psc);
}

/// USART smartcard Prescaler value get
static per_inline uint_fast16_t per_usart_psc_sc(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rw8(&usart->Per->Psc) << 1; // multiply by 2
}

/// USART SmartCard prescaler set
static per_inline bool per_usart_set_psc_sc(const per_usart_t* const usart, uint_fast16_t psc)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }

    if ((psc < 2) || (psc > per_bit_rw8_max()))
    {
        per_log_err(usart->Err, PER_USART_SET_PSC_SC_MAX_ERR, psc);
        return false;
    }

    return per_bit_rw8_set(&usart->Per->Psc, psc >> 1); // divide by 2
}

/// USART Guard time value
static per_inline uint_fast16_t per_usart_gt(const per_usart_t* const usart)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }
    
    return per_bit_rw8(&usart->Per->Gt);
}

/// USART Guard time value
static per_inline bool per_usart_set_gt(const per_usart_t* const usart, uint_fast16_t gt)
{
    if (usart->Uart)
    {
        per_dep_err_unsupported();
    }

    if (gt > per_bit_rw8_max())
    {
        per_log_err(usart->Err, PER_USART_SET_GT_MAX_ERR, gt);
        return false;
    }

    return per_bit_rw8_set(&usart->Per->Gt, gt);
}

/// USART fetch and clear active flags and return the active flags
static per_inline per_usart_sr_e per_usart_flag(const per_usart_t* const usart)
{
    uint_fast16_t flag = per_usart_sr(usart);

    per_usart_set_sr(usart, ~(flag & (uint_fast16_t)PER_USART_SR_CLEAR)); // Clear

    return (per_usart_sr_e)flag;
}

/// USART Set parity
static per_inline void per_usart_set_parity(const per_usart_t* const usart, per_usart_ps_e par)
{
    per_usart_set_ps(usart, par == PER_USART_PS_ODD);   // Parity selection
    per_usart_set_pce(usart, par != PER_USART_PS_NONE); // Parity enable
}

/// USART Set baudrate value
static per_inline bool per_usart_set_baudrate(const per_usart_t* const usart, uint_fast32_t rate)
{
    uint_fast32_t over;                 ///< Over-sampling
    uint_fast32_t mant;                 ///< Mantissa
    uint_fast32_t fract;                ///< Fraction
    uint_fast32_t fract_mask;           ///< Fraction mask
    uint_fast32_t freq = usart->Freq(); ///< Base frequency

    if (per_usart_over8(usart))
    {
        over = PER_USART_OVER_8;
    }
    else
    {
        over = PER_USART_OVER_16;
    }

    fract_mask = (uint_fast32_t)over - 1;
    mant = freq / (rate * over); // Divider
    fract = ((freq - (mant * rate * over)) + (rate / 2)) / rate; // Rest + rounding / baudrate

    if ((fract & ~fract_mask) != 0) // Overrun because of rounding
    {
        fract &= fract_mask;
        mant += 1;
    }

    return per_usart_set_div(usart, fract, mant);
}

#ifdef __cplusplus
}
#endif

#endif // per_usart_f4_h_
