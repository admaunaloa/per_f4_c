/**
 * @file per_can_f4.h
 *
 * This file contains the can interface (CAN)
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
 *
 * Convenience functions:
 * per_can_mirq()            clears active master interrupts and returns bitmask of the cleared ones
 * per_can_tirq()            clears active transport interrupts and returns bitmask of the cleared ones
 */

#ifndef per_can_f4_h_
#define per_can_f4_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_bit_f4.h"
#include "per_log_f4.h"

/// CAN1 base address
#define PER_CAN_1 ((per_can_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB1 + (uintptr_t)0x6400))

/// CAN2 base address
#define PER_CAN_2 ((per_can_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB1 + (uintptr_t)0x6800))

/// CAN3 base address
#define PER_CAN_3 ((per_can_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB1 + (uintptr_t)0x6C00))

/// CAN master status register (CAN_MSR)
typedef enum
{
    PER_CAN_MSR_INAK  = 0b000000000001, ///< Initialization acknowledge
    PER_CAN_MSR_SLAK  = 0b000000000010, ///< Sleep acknowledge
    PER_CAN_MSR_ERRI  = 0b000000000100, ///< Error interrupt
    PER_CAN_MSR_WKUI  = 0b000000001000, ///< Wakeup interrupt
    PER_CAN_MSR_SLAKI = 0b000000010000, ///< Sleep acknowledge interrupt
    PER_CAN_MSR_TXM   = 0b000100000000, ///< Transmit mode
    PER_CAN_MSR_RXM   = 0b001000000000, ///< Receive mode
    PER_CAN_MSR_SAMP  = 0b010000000000, ///< Last sample point
    PER_CAN_MSR_RX    = 0b100000000000, ///< CAN Rx signal
    PER_CAN_MSR_MASK = PER_CAN_MSR_ERRI | ///< All interrupt flag
                       PER_CAN_MSR_WKUI |
                       PER_CAN_MSR_SLAKI,
} per_can_msr_e;

/// CAN transmit status register (CAN_TSR)
typedef enum
{
    PER_CAN_TSR_RQCP0 = 0x00000001, ///< Request completed mailbox0
    PER_CAN_TSR_TXOK0 = 0x00000002, ///< Transmission OK of mailbox0
    PER_CAN_TSR_ALST0 = 0x00000004, ///< Arbitration lost for mailbox0
    PER_CAN_TSR_TERR0 = 0x00000008, ///< Transmission error of mailbox0
    PER_CAN_TSR_ABRQ0 = 0x00000080, ///< Abort request for mailbox0
    PER_CAN_TSR_RQCP1 = 0x00000100, ///< Request completed mailbox1
    PER_CAN_TSR_TXOK1 = 0x00000200, ///< Transmission OK of mailbox1
    PER_CAN_TSR_ALST1 = 0x00000400, ///< Arbitration lost for mailbox1
    PER_CAN_TSR_TERR1 = 0x00000800, ///< Transmission error of mailbox1
    PER_CAN_TSR_ABRQ1 = 0x00008000, ///< Abort request for mailbox 1
    PER_CAN_TSR_RQCP2 = 0x00010000, ///< Request completed mailbox2
    PER_CAN_TSR_TXOK2 = 0x00020000, ///< Transmission OK of mailbox 2
    PER_CAN_TSR_ALST2 = 0x00040000, ///< Arbitration lost for mailbox 2
    PER_CAN_TSR_TERR2 = 0x00080000, ///< Transmission error of mailbox 2
    PER_CAN_TSR_ABRQ2 = 0x00800000, ///< Abort request for mailbox 2
    PER_CAN_TSR_CODE0 = 0x01000000, ///< Mailbox code 0
    PER_CAN_TSR_CODE1 = 0x02000000, ///< Mailbox code 1
    PER_CAN_TSR_TME0  = 0x04000000, ///< Transmit mailbox 0 empty
    PER_CAN_TSR_TME1  = 0x08000000, ///< Transmit mailbox 1 empty
    PER_CAN_TSR_TME2  = 0x10000000, ///< Transmit mailbox 2 empty
    PER_CAN_TSR_LOW0  = 0x20000000, ///< Lowest priority flag for mailbox 0
    PER_CAN_TSR_LOW1  = 0x40000000, ///< Lowest priority flag for mailbox 1
    PER_CAN_TSR_LOW2  = 0x80000000, ///< Lowest priority flag for mailbox 2
    PER_CAN_TSR_MASK  = PER_CAN_TSR_RQCP0 | ///< All interrupt flag
                        PER_CAN_TSR_TXOK0 |
                        PER_CAN_TSR_ALST0 |
                        PER_CAN_TSR_TERR0 |
                        PER_CAN_TSR_RQCP1 |
                        PER_CAN_TSR_TXOK1 |
                        PER_CAN_TSR_ALST1 |
                        PER_CAN_TSR_TERR1 |
                        PER_CAN_TSR_RQCP2 |
                        PER_CAN_TSR_TXOK2 |
                        PER_CAN_TSR_ALST2 |
                        PER_CAN_TSR_TERR2,
} per_can_tsr_e;

typedef struct
{
    // CAN master control register (CAN_MCR)
    per_bit_rw1_t Inrq; ///< Initialization request
    per_bit_rw1_t Sleep; ///< Sleep mode request
    per_bit_rw1_t Txfp; ///< Transmit FIFO priority
    per_bit_rw1_t Rflm; ///< Receive FIFO locked mode
    per_bit_rw1_t Nart; ///< No automatic retransmission
    per_bit_rw1_t Awum; ///< Automatic wakeup mode
    per_bit_rw1_t Abom; ///< Automatic bus-off management
    per_bit_rw1_t Ttcm; ///< Time triggered communication mode
    per_bit_n7_t McrBit8; ///< Reserved
    per_bit_rw1_t Reset; ///< bxCAN software master reset
    per_bit_rw1_t Dbf; ///< Debug freeze
    per_bit_n15_t McrBit17; ///< Reserved

    // CAN master status register (CAN_MSR)
    union
    {
        struct
        {
            per_bit_r1_t Inak; ///< Initialization acknowledge
            per_bit_r1_t Slak; ///< Sleep acknowledge
            per_bit_rc1_w1_t Erri; ///< Error interrupt
            per_bit_rc1_w1_t Wkui; ///< Wakeup interrupt
            per_bit_rc1_w1_t Slaki; ///< Sleep acknowledge interrupt
            per_bit_n3_t MsrBit5; ///< Reserved
            per_bit_r1_t Txm; ///< Transmit mode
            per_bit_r1_t Rxm; ///< Receive mode
            per_bit_r1_t Samp; ///< Last sample point
            per_bit_r1_t Rx; ///< CAN Rx signal
            per_bit_n20_t MsrBit12; ///< Reserved
        };
        per_bit_rw32_reg_t Msr; ///< CAN master status register (CAN_MSR)
    };

    // CAN transmit status register (CAN_TSR)
    union
    {
        struct
        {
            per_bit_rc1_w1_t Rqcp0; ///< Request completed mailbox0
            per_bit_rc1_w1_t Txok0; ///< Transmission OK of mailbox0
            per_bit_rc1_w1_t Alst0; ///< Arbitration lost for mailbox0
            per_bit_rc1_w1_t Terr0; ///< Transmission error of mailbox0
            per_bit_n3_t TsrBit; ///< Reserved
            per_bit_rs1_t Abrq0; ///< Abort request for mailbox0
            per_bit_rc1_w1_t Rqcp1; ///< Request completed mailbox1
            per_bit_rc1_w1_t Txok1; ///< Transmission OK of mailbox1
            per_bit_rc1_w1_t Alst1; ///< Arbitration lost for mailbox1
            per_bit_rc1_w1_t Terr1; ///< Transmission error of mailbox1
            per_bit_n3_t TsrBit; ///< Reserved
            per_bit_rs1_t Abrq1; ///< Abort request for mailbox 1
            per_bit_rc1_w1_t Rqcp2; ///< Request completed mailbox2
            per_bit_rc1_w1_t Txok2; ///< Transmission OK of mailbox 2
            per_bit_rc1_w1_t Alst2; ///< Arbitration lost for mailbox 2
            per_bit_rc1_w1_t Terr2; ///< Transmission error of mailbox 2
            per_bit_n3_t TsrBit; ///< Reserved
            per_bit_rs1_t Abrq2; ///< Abort request for mailbox 2
            per_bit_r2_t Code; ///< Mailbox code
            per_bit_r1_t Tme0; ///< Transmit mailbox 0 empty
            per_bit_r1_t Tme1; ///< Transmit mailbox 1 empty
            per_bit_r1_t Tme2; ///< Transmit mailbox 2 empty
            per_bit_r1_t Low0; ///< Lowest priority flag for mailbox 0
            per_bit_r1_t Low1; ///< Lowest priority flag for mailbox 1
            per_bit_r1_t Low2; ///< Lowest priority flag for mailbox 2
        };
        per_bit_rw32_reg_t Tsr; ///< CAN transmit status register (CAN_TSR)
    };










            // per_bit_r1_t ; ///< 
            // per_bit_rc1_w1_t ; ///< 
            // per_bit_n3_t TsrBit; ///< Reserved




} per_can_per_t;

/// CAN descriptor
typedef struct
{
    per_can_per_t* const Per; ///< Interface
    const per_log_e Err;      ///< Peripheral error number
} per_can_t;

/// Initialization request
static per_inline bool per_can_inrq(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Inrq);
}

/// Initialization request
static per_inline void per_can_set_inrq(const per_can_t* const can, bool val)
{
    per_bit_rw1_set(&can->Per->Inrq, val);
}

/// Sleep mode request
static per_inline bool per_can_sleep(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Sleep);
}

/// Sleep mode request
static per_inline void per_can_set_sleep(const per_can_t* const can, bool val)
{
    per_bit_rw1_set(&can->Per->Sleep, val);
}

/// Transmit FIFO priority
static per_inline bool per_can_txfp(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Txfp);
}

/// Transmit FIFO priority
static per_inline void per_can_set_txfp(const per_can_t* const can, bool val)
{
    per_bit_rw1_set(&can->Per->Txfp, val);
}

/// Receive FIFO locked mode
static per_inline bool per_can_rflm(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Rflm);
}

/// Receive FIFO locked mode
static per_inline void per_can_set_rflm(const per_can_t* const can, bool val)
{
    per_bit_rw1_set(&can->Per->Rflm, val);
}

/// No automatic retransmission
static per_inline bool per_can_nart(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Nart);
}

/// No automatic retransmission
static per_inline void per_can_set_nart(const per_can_t* const can, bool val)
{
    per_bit_rw1_set(&can->Per->Nart, val);
}

/// Automatic wakeup mode
static per_inline bool per_can_awum(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Awum);
}

/// Automatic wakeup mode
static per_inline void per_can_set_awum(const per_can_t* const can, bool val)
{
    per_bit_rw1_set(&can->Per->Awum, val);
}

/// Automatic bus-off management
static per_inline bool per_can_abom(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Abom);
}

/// Automatic bus-off management
static per_inline void per_can_set_abom(const per_can_t* const can, bool val)
{
    per_bit_rw1_set(&can->Per->Abom, val);
}

/// Time triggered communication mode
static per_inline bool per_can_ttcm(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Ttcm);
}

/// Time triggered communication mode
static per_inline void per_can_set_ttcm(const per_can_t* const can, bool val)
{
    per_bit_rw1_set(&can->Per->Ttcm, val);
}

/// bxCAN software master reset
static per_inline bool per_can_reset(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Reset);
}

/// bxCAN software master reset
static per_inline void per_can_set_reset(const per_can_t* const can, bool val)
{
    per_bit_rw1_set(&can->Per->Reset, val);
}

/// Debug freeze
static per_inline bool per_can_dbf(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Dbf);
}

/// Debug freeze
static per_inline void per_can_set_dbf(const per_can_t* const can, bool val)
{
    per_bit_rw1_set(&can->Per->Dbf, val);
}

/// Master status register (CAN_MSR)
static per_inline uint_fast32_t per_can_msr(const per_can_t* const can)
{
    return per_bit_rw32_reg(&can->Per->Msr);
}

/// Master status register (CAN_MSR)
static per_inline void per_can_set_msr(const per_can_t* const can, uint32_t val)
{
    per_bit_rw32_reg_set(&can->Per->Msr, val);
}

/// Initialization acknowledge
static per_inline bool per_can_inak(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Inak);
}

/// Sleep acknowledge
static per_inline bool per_can_Slak(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Slak);
}

/// Error interrupt
static per_inline bool per_can_erri(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Erri);
}

/// Error interrupt
static per_inline bool per_can_clr_erri(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Erri);
}

/// Wakeup interrupt
static per_inline bool per_can_wkui(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Wkui);
}

/// Wakeup interrupt
static per_inline bool per_can_clr_wkui(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Wkui);
}

/// Sleep acknowledge interrupt
static per_inline bool per_can_slaki(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Slaki);
}

/// Sleep acknowledge interrupt
static per_inline bool per_can_clr_slaki(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Slaki);
}

/// Transmit mode
static per_inline bool per_can_txm(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Txm);
}

/// Receive mode
static per_inline bool per_can_rxm(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Rxm);
}

/// Last sample point
static per_inline bool per_can_samp(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Samp);
}

/// CAN Rx signal
static per_inline bool per_can_rx(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Rx);
}

/// Transmit status register (CAN_TSR)
static per_inline uint_fast32_t per_can_tsr(const per_can_t* const can)
{
    return per_bit_rw32_reg(&can->Per->Tsr);
}

/// Transmit status register (CAN_TSR)
static per_inline void per_can_set_tsr(const per_can_t* const can, uint32_t val)
{
    per_bit_rw32_reg_set(&can->Per->Tsr, val);
}

/// Request completed mailbox0
static per_inline bool per_can_rqcp0(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Rqcp0);
}

/// Request completed mailbox0
static per_inline bool per_can_clr_rqcp0(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Rqcp0);
}

/// Transmission OK of mailbox0
static per_inline bool per_can_txok0(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Txok0);
}

/// Transmission OK of mailbox0
static per_inline bool per_can_clr_txok0(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Txok0);
}

/// Arbitration lost for mailbox0
static per_inline bool per_can_alst0(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Alst0);
}

/// Arbitration lost for mailbox0
static per_inline bool per_can_clr_alst0(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Alst0);
}

/// Transmission error of mailbox0
static per_inline bool per_can_terr0(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Terr0);
}

/// Transmission error of mailbox0
static per_inline bool per_can_clr_terr0(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Terr0);
}

/// Abort request for mailbox0
static per_inline bool per_can_abrq0(const per_can_t* const can)
{
    return per_bit_rs1(&can->Per->Abrq0);
}

/// Abort request for mailbox0
static per_inline void per_can_set_abrq0(const per_can_t* const can)
{
    per_bit_rs1_set(&can->Per->Abrq0);
}

/// Request completed mailbox1
static per_inline bool per_can_rqcp1(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Rqcp1);
}

/// Request completed mailbox1
static per_inline bool per_can_clr_rqcp1(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Rqcp1);
}

/// Transmission OK of mailbox1
static per_inline bool per_can_txok1(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Txok1);
}

/// Transmission OK of mailbox1
static per_inline bool per_can_clr_txok1(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Txok1);
}

/// Arbitration lost for mailbox1
static per_inline bool per_can_alst1(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Alst1);
}

/// Arbitration lost for mailbox1
static per_inline bool per_can_clr_alst1(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Alst1);
}

/// Transmission error of mailbox1
static per_inline bool per_can_terr1(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Terr1);
}

/// Transmission error of mailbox1
static per_inline bool per_can_clr_terr1(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Terr1);
}

/// Abort request for mailbox 1
static per_inline bool per_can_abrq1(const per_can_t* const can)
{
    return per_bit_rs1(&can->Per->Abrq1);
}

/// Abort request for mailbox 1
static per_inline void per_can_set_abrq1(const per_can_t* const can)
{
    per_bit_rs1_set(&can->Per->Abrq1);
}

/// Request completed mailbox2
static per_inline bool per_can_rqcp2(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Rqcp2);
}

/// Request completed mailbox2
static per_inline bool per_can_clr_rqcp2(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Rqcp2);
}

/// Transmission OK of mailbox 2
static per_inline bool per_can_txok2(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Txok2);
}

/// Transmission OK of mailbox 2
static per_inline bool per_can_clr_txok2(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Txok2);
}

/// Arbitration lost for mailbox 2
static per_inline bool per_can_alst2(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Alst2);
}

/// Arbitration lost for mailbox 2
static per_inline bool per_can_clr_alst2(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Alst2);
}

/// Transmission error of mailbox 2
static per_inline bool per_can_terr2(const per_can_t* const can)
{
    return per_bit_rc1_w1(&can->Per->Terr2);
}

/// Transmission error of mailbox 2
static per_inline bool per_can_clr_terr2(const per_can_t* const can)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Terr2);
}

/// Abort request for mailbox 2
static per_inline bool per_can_abrq2(const per_can_t* const can)
{
    return per_bit_rs1(&can->Per->Abrq2);
}

/// Abort request for mailbox 2
static per_inline void per_can_set_abrq2(const per_can_t* const can)
{
    per_bit_rs1_set(&can->Per->Abrq2);
}

/// Mailbox code
static per_inline uint_fast16_t per_can_code(const per_can_t* const can)
{
    return per_bit_r2(&can->Per->Code);
}

/// Transmit mailbox 0 empty
static per_inline bool per_can_tme0(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Tme0);
}

/// Transmit mailbox 1 empty
static per_inline bool per_can_tme1(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Tme1);
}

/// Transmit mailbox 2 empty
static per_inline bool per_can_tme2(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Tme2);
}

/// Lowest priority flag for mailbox 0
static per_inline bool per_can_low0(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Low0);
}

/// Lowest priority flag for mailbox 1
static per_inline bool per_can_low1(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Low1);
}

/// Lowest priority flag for mailbox 2
static per_inline bool per_can_low2(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Low2);
}












/// CAN fetch and clear active master interrupts and return the active interrupts
static per_inline per_can_msr_e per_can_mirq(const per_can_t* const can)
{
    uint_fast32_t irq = (uint_fast32_t)PER_CAN_MSR_MASK & per_can_msr(can);

    per_can_set_msr(can, irq); // Clear

    return (per_can_msr_e)irq;
}

/// CAN fetch and clear active transport interrupts and return the active interrupts
static per_inline per_can_tsr_e per_can_tirq(const per_can_t* const can)
{
    uint_fast32_t irq = (uint_fast32_t)PER_CAN_TSR_MASK & per_can_tsr(can);

    per_can_set_tsr(can, irq); // Clear

    return (per_can_tsr_e)irq;
}





// /// 
// static per_inline bool per_can_(const per_can_t* const can)
// {
//     return per_bit_rw1(&can->Per->);
// }

// /// 
// static per_inline void per_can_set_(const per_can_t* const can, bool val)
// {
//     per_bit_rw1_set(&can->Per->, val);
// }

// /// 
// static per_inline bool per_can_(const per_can_t* const can)
// {
//     return per_bit_rc1_w1(&can->Per->);
// }

// /// 
// static per_inline bool per_can_clr_(const per_can_t* const can)
// {
//     return per_bit_rc1_w1_rdclr(&can->Per->);
// }


// /// 
// static per_inline bool per_can_(const per_can_t* const can)
// {
//     return per_bit_rs1(&can->Per->);
// }

// /// 
// static per_inline void per_can_set_(const per_can_t* const can)
// {
//     per_bit_rs1_set(&can->Per->);
// }




#ifdef __cplusplus
}
#endif

#endif // per_can_f4_h_