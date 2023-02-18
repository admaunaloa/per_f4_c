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
 * per_can_msr_fc()       clears active master interrupts and returns bitmask of the cleared ones
 * per_can_tsr_fc()       clears active transport interrupts and returns bitmask of the cleared ones
 * per_can_rfr_fc()       clears active fifo 0 bits and returns bitmask of the cleared ones
 * per_can_set_tir()      start transmision
 * per_can_set_tir_rm()   start transmision of remote message
 * per_can_set_tir_ttc()  start transmision of time triggered communication message
 * per_can_rir()          get identifier information received message
 * per_can_read()         read one message
 * per_can_read_time()    read one message time triggered communication
 * per_can_set_fir_16()   set 16 bit filters
 * per_can_set_fir_32()   set 32 bit filters
 * per_can_set_baudrate() set the transmission speed
 * 
 */

#ifndef per_can_f4_h_
#define per_can_f4_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_bit_f4.h"
#include "per_log_f4.h"
#include "per_rcc.h"

/// CAN1 base address
#define PER_CAN_1 ((per_can_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB1 + (uintptr_t)0x6400))

/// CAN2 base address
#define PER_CAN_2 ((per_can_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB1 + (uintptr_t)0x6800))

/// CAN3 base address
#define PER_CAN_3 ((per_can_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_APB1 + (uintptr_t)0x6C00))

/// CAN DATA SIZE MAX
#define PER_CAN_DATA_MAX (8)

/// CAN FILTER MAX
#define PER_CAN_FILTER_MAX (28)

/// CAN BAUD RATE DIVIDER
#define PER_CAN_BAUD_RATE_DIVIDER (1 + 12 + 5)

/// CAN error enumeration
typedef enum
{
    PER_CAN_ERR_OK = PER_LOG_CAN * PER_LOG_MULT, ///< No error
    PER_CAN_MBX_TX_ERR, ///< MBX_TX full
    PER_CAN_MBX_TX_RM_ERR, ///< MBX_TX full for remote message
    PER_CAN_MBX_TX_TTC_ERR, ///< MBX_TX full for time triggered communication
    PER_CAN_MBX_RX_OVR_ERR, ///< MBX_RX FIFO overrun
    PER_CAN_FBM_BANK_MAX_ERR, ///< Filter bank number too high on fbm get
    PER_CAN_SET_FBM_BANK_MAX_ERR, ///< Filter bank number too high on fbm set
    PER_CAN_FSC_BANK_MAX_ERR, ///< Filter bank number too high on fsc get
    PER_CAN_SET_FSC_BANK_MAX_ERR, ///< Filter bank number too high on fsc set
    PER_CAN_FFA_BANK_MAX_ERR, ///< Filter bank number too high on ffa get
    PER_CAN_SET_FFA_BANK_MAX_ERR, ///< Filter bank number too high on ffa set
    PER_CAN_FACT_BANK_MAX_ERR, ///< Filter bank number too high on fact get
    PER_CAN_SET_FACT_BANK_MAX_ERR, ///< Filter bank number too high on fact set
    PER_CAN_FIR_BANK_MAX_ERR, ///< Filter bank number too high on fir get
    PER_CAN_SET_FIR_BANK_MAX_ERR, ///< Filter bank number too high on fir set
    PER_CAN_SET_FIR_SINGLE_BANK_MAX_ERR, ///< Filter bank single number too high on fir set
    PER_CAN_SET_FIR_DUAL_BANK_MAX_ERR, ///< Filter bank dual number too high on fir set
    PER_CAN_BAUDRATE_ERR, ///< Baudrate invalid value
} per_can_error_e;

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

/// CAN receive FIFO x register (CAN_RFxR)
typedef enum
{
    PER_CAN_RFR_FMP  = 0b00000011, ///< FIFO x message pending
    PER_CAN_RFR_FULL = 0b00001000, ///< FIFO x full
    PER_CAN_RFR_FOVR = 0b00010000, ///< FIFO x overrun
    PER_CAN_RFR_RFOM = 0b00100000, ///< Release FIFO 1 output mailbox
    PER_CAN_RFR_MASK  = PER_CAN_RFR_FULL | ///< All interrupt flag
                        PER_CAN_RFR_FOVR,
} per_can_rfr_e;

/// CAN mailbox message transmit data
typedef struct
{
    union
    {
        uint8_t Data[PER_CAN_DATA_MAX];
        struct
        {
            uint32_t Low; ///< Low part
            uint32_t High; ///< High part
        };
    };
    uint32_t Id;
    uint_fast16_t Length;
} per_can_mess_t;

/// CAN mailbox message receive data for Time Triggered Communication
typedef struct
{
    union
    {
        uint8_t Data[PER_CAN_DATA_MAX];
        struct
        {
            uint32_t Low; ///< Low part
            uint32_t High; ///< High part
        };
    };
    uint32_t Id;
    uint_fast16_t Length;
    uint_fast16_t Time;
} per_can_mess_time_t;

/// CAN TX mailbox identifier register (CAN_TIxR) (x=0..2)
typedef enum
{
    PER_CAN_MBX_TX_0 = 0, ///< First
    PER_CAN_MBX_TX_1 = 1, ///< Second
    PER_CAN_MBX_TX_2 = 2, ///< Third
    PER_CAN_MBX_TX_LAST = PER_CAN_MBX_TX_2,  ///< Last
} per_can_mbx_tx_e;

/// CAN TX mailbox identifier register (CAN_TIxR) ()
typedef enum
{
    PER_CAN_TIR_TXRQ = 0b00000001, ///< Transmit mailbox request
    PER_CAN_TIR_RTR  = 0b00000010, ///< Remote transmission request
    PER_CAN_TIR_IDE  = 0b00000100, ///< Identifier extension
    PER_CAN_TIR_EXID_MASK  = 0x1fffffff,  ///< Extended identifier
    PER_CAN_TIR_EXID_SHIFT = 3,  ///< Extended identifier
    PER_CAN_TIR_STID_MASK  = 0x000007ff,  ///< Extended identifier
    PER_CAN_TIR_STID_SHIFT = 21,  ///< Extended identifier
} per_can_tir_e;

typedef enum
{
    PER_CAN_TDTR_DLC_MASK = 0x000f, ///< Data length code
    PER_CAN_TDTR_TGT = 0x0010, ///< Transmit global time
    PER_CAN_TDTR_TIME_SHIFT = 16, ///< Message time stamp
} per_can_tdtr_e;

/// CAN receive FIFO mailbox identifier register (CAN_RIxR) (x=0..1)
typedef enum
{
    PER_CAN_MBX_RX_0 = 0, ///< First
    PER_CAN_MBX_RX_1 = 1, ///< Second
    PER_CAN_MBX_RX_LAST = PER_CAN_MBX_RX_1,  ///< Last
} per_can_mbx_rx_e;

/// CAN receive FIFO mailbox identifier register (CAN_RIxR) (x=0..1)
typedef enum
{
    PER_CAN_RIR_RTR  = 0b00000010, ///< Remote transmission request
    PER_CAN_RIR_IDE  = 0b00000100, ///< Identifier extension
    PER_CAN_RIR_EXID_MASK  = 0x1fffffff,  ///< Extended identifier
    PER_CAN_RIR_EXID_SHIFT = 3,  ///< Extended identifier
    PER_CAN_RIR_STID_MASK  = 0x000007ff,  ///< Extended identifier
    PER_CAN_RIR_STID_SHIFT = 21,  ///< Extended identifier
} per_can_rir_e;

typedef enum
{
    PER_CAN_RDTR_DLC_MASK = 0x000f, ///< Data length code
    PER_CAN_RDTR_FMI_MASK = 0x00ff, ///< Filter match index
    PER_CAN_RDTR_FMI_SHIFT = 8, ///< Filter match index
    PER_CAN_RDTR_TIME_SHIFT = 16, ///< Message time stamp
} per_can_rdtr_e;

/// Filter bank scale configuration - register organization 32 bit
typedef enum
{
    PER_CAN_FIR_32_RTR  = 0b00000010, ///< Remote transmission request
    PER_CAN_FIR_32_IDE  = 0b00000100, ///< Identifier extension
    PER_CAN_FIR_32_EXID_MASK  = 0x1fffffff,  ///< Extended identifier
    PER_CAN_FIR_32_EXID_SHIFT = 3,  ///< Extended identifier
    PER_CAN_FIR_32_STID_MASK  = 0x000007ff,  ///< Extended identifier
    PER_CAN_FIR_32_STID_SHIFT = 21,  ///< Extended identifier
} per_can_fir_32_e;

/// Filter bank scale configuration - register organization 16 bit
typedef enum
{
    PER_CAN_FIR_16_IDE  = 0b00001000, ///< Identifier extension
    PER_CAN_FIR_16_RTR  = 0b00010000, ///< Remote transmission request
    PER_CAN_FIR_16_STID_MASK  = 0x000007ff,  ///< Extended identifier
    PER_CAN_FIR_16_STID_SHIFT = 5,  ///< Extended identifier
} per_can_fir_16_e;

/// CAN receive FIFO x register (CAN_RFxR)
typedef union
{
    struct
    {
        per_bit_r2_t Fmp; ///< FIFO message pending
        per_bit_n1_t RfrBit2; ///< Reserved
        per_bit_rc1_w1_t Full; ///< FIFO full
        per_bit_rc1_w1_t Fovr; ///< FIFO overrun
        per_bit_rs1_t Rfom; ///< Release FIFO output mailbox
        per_bit_n26_t RfrBit6; ///< Reserved
    };
    per_bit_rw32_reg_t Rfr; ///< CAN receive FIFO register (CAN_RFxR)
} per_can_rfr_t;

/// CAN transmit mailbox registers
typedef struct
{
    // CAN TX mailbox identifier register (CAN_TIxR) (x=0..2)
    union
    {
        struct
        {
            per_bit_rw1_t Txrq; ///< Transmit mailbox request
            per_bit_r1_t Rtr; ///< Remote transmission request
            per_bit_r1_t Ide; ///< Identifier extension
            per_bit_n18_t Exid; ///< Extended identifier
            per_bit_r11_t Stid; ///< Standard identifier or extended identifier
        };
        per_bit_rw32_reg_t Tir; ///< CAN TX mailbox identifier register (CAN_TIxR)
    };

    // CAN mailbox data length control and time stamp register (CAN_TDTxR)(x=0..2)
    union
    {
        struct
        {
            per_bit_rw4_t Dlc; ///< Data length code
            per_bit_n4_t TdtrBit4; ///< Reserved
            per_bit_rw1_t Tgt; ///< Transmit global time
            per_bit_n7_t TdtrBit9; ///< Reserved
            per_bit_rw16_t Time; ///< Message time stamp
        };
        per_bit_rw32_reg_t Tdtr; ///< CAN mailbox data length control and time stamp register
    };

    // CAN mailbox data low register (CAN_TDLxR) (x=0..2)
    per_bit_rw32_reg_t Tdlr; ///< CAN mailbox data low register

    // CAN mailbox data high register (CAN_TDHxR) (x=0..2)
    per_bit_rw32_reg_t Tdhr; ///< CAN mailbox data high register
} per_can_mbx_tx_t;

/// CAN receive mailbox registers
typedef struct
{
    // CAN receive FIFO mailbox identifier register (CAN_RIxR) (x=0..1)
    union
    {
        struct
        {
            per_bit_n1_t RirBit0; ///< Reserved
            per_bit_r1_t Rtr; ///< Remote transmission request
            per_bit_r1_t Ide; ///< Identifier extension
            per_bit_n18_t Exid; ///< Extended identifier
            per_bit_r11_t Stid; ///< Standard identifier or extended identifier
        };
        per_bit_r32_reg_t Rir; ///< CAN receive FIFO mailbox identifier register (CAN_RIxR) (x=0..1)
    };

    //CAN receive FIFO mailbox data length control and time stamp register (CAN_RDTxR) (x=0..1)
    union
    {
        struct
        {
            per_bit_r4_t Dlc; ///< Data length code
            per_bit_n4_t RdtrBit4; ///< Reserved
            per_bit_r8_t Fmi; ///< Filter match index
            per_bit_r16_t Time; ///< Message time stamp
        };
        per_bit_r32_reg_t Rdtr; ///< CAN mailbox data length control and time stamp register
    };
    
    // CAN receive FIFO mailbox data low register (CAN_RDLxR) (x=0..1)
    per_bit_r32_reg_t Rdlr; ///< CAN mailbox data low register

    // CAN receive FIFO mailbox data high register (CAN_RDHxR) (x=0..1)
    per_bit_r32_reg_t Rdhr; ///< CAN mailbox data high register
} per_can_mbx_rx_t;

/// CAN filter bank register
typedef union
{
    struct
    {
        per_bit_rw32_reg_t R1; ///< Filter bank i register 1
        per_bit_rw32_reg_t R2; ///< Filter bank i register 2
    } Fir32;
    struct
    {
        per_bit_rw16_reg_t R1; ///< Filter bank i register 1
        per_bit_rw16_reg_t R2; ///< Filter bank i register 2
        per_bit_rw16_reg_t R3; ///< Filter bank i register 3
        per_bit_rw16_reg_t R4; ///< Filter bank i register 4
    } Fir16;
} per_can_fir_t;

/// CAN control and status registers
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
            per_bit_n3_t TsrBit4; ///< Reserved
            per_bit_rs1_t Abrq0; ///< Abort request for mailbox0
            per_bit_rc1_w1_t Rqcp1; ///< Request completed mailbox1
            per_bit_rc1_w1_t Txok1; ///< Transmission OK of mailbox1
            per_bit_rc1_w1_t Alst1; ///< Arbitration lost for mailbox1
            per_bit_rc1_w1_t Terr1; ///< Transmission error of mailbox1
            per_bit_n3_t TsrBit12; ///< Reserved
            per_bit_rs1_t Abrq1; ///< Abort request for mailbox 1
            per_bit_rc1_w1_t Rqcp2; ///< Request completed mailbox2
            per_bit_rc1_w1_t Txok2; ///< Transmission OK of mailbox 2
            per_bit_rc1_w1_t Alst2; ///< Arbitration lost for mailbox 2
            per_bit_rc1_w1_t Terr2; ///< Transmission error of mailbox 2
            per_bit_n3_t TsrBit20; ///< Reserved
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

    // CAN receive FIFO x register (CAN_RFxR)
    per_can_rfr_t Rfr[PER_CAN_MBX_RX_LAST];

    // CAN interrupt enable register (CAN_IER)
    per_bit_rw1_t Tmeie; ///< Transmit mailbox empty interrupt enable
    per_bit_rw1_t Fmpie0; ///< FIFO message pending interrupt enable
    per_bit_rw1_t Ffie0; ///< FIFO full interrupt enable
    per_bit_rw1_t Fovie0; ///< FIFO overrun interrupt enable
    per_bit_rw1_t Fmpie1; ///< FIFO message pending interrupt enable
    per_bit_rw1_t Ffie1; ///< FIFO full interrupt enable
    per_bit_rw1_t Fovie1; ///< FIFO overrun interrupt enable
    per_bit_n1_t IerBit7; ///< Reserved
    per_bit_rw1_t Ewgie; ///< Error warning interrupt enable
    per_bit_rw1_t Epvie; ///< Error passive interrupt enable
    per_bit_rw1_t Bofie; ///< Bus-off interrupt enable
    per_bit_rw1_t Lecie; ///< Last error code interrupt enable
    per_bit_n3_t IerBit12; ///< Reserved
    per_bit_rw1_t Errie; ///< Error interrupt enable
    per_bit_rw1_t Wkuie; ///< Wakeup interrupt enable
    per_bit_rw1_t Slkie; ///< Sleep interrupt enable
    per_bit_n14_t IerBit18; ///< Reserved

    // CAN error status register (CAN_ESR)
    per_bit_r1_t Ewgf; ///< Error warning flag
    per_bit_r1_t Epvf; ///< Error passive flag
    per_bit_r1_t Boff; ///< Bus-off flag
    per_bit_n1_t EsrBit3; ///< Reserved
    per_bit_rw3_t Lec; ///< Last error code
    per_bit_n9_t EsrBit7; ///< Reserved
    per_bit_r8_t Tec; ///< Least significant byte of the 9-bit transmit error counter
    per_bit_r8_t Rec; ///< Receive error counter

    // CAN bit timing register (CAN_BTR)
    per_bit_rw10_t Brp; ///< Baud rate prescaler
    per_bit_n6_t BtrBit10; ///< Reserved
    per_bit_rw4_t Ts1; ///< Time segment 1
    per_bit_rw3_t Ts2; ///< Time segment 2
    per_bit_n1_t BtrBit23; ///< Reserved
    per_bit_rw2_t Sjw; ///< Resynchronization jump width
    per_bit_n4_t BtrBit26; ///< Reserved
    per_bit_rw1_t Lbkm; ///< Loop back mode (debug)
    per_bit_rw1_t Silm; ///< Silent mode (debug)

    // CAN Reserved
    per_bit_n32_t Reserved_0x20[22]; ///< Reserved 0x020 - 0x17f  
 
    // CAN transmit mailbox registers
    per_can_mbx_tx_t Mbxtx[PER_CAN_MBX_TX_LAST + 1]; 

    // CAN receive mailbox registers
    per_can_mbx_rx_t Mbxrx[PER_CAN_MBX_RX_LAST + 1]; 

    // CAN Reserved
    per_bit_n32_t Reserved_0x1d0[12]; ///< Reserved 0x1d0 - 0x200  

    // CAN filter master register (CAN_FMR)
    per_bit_rw1_t Finit; ///< Filter init mode
    per_bit_n7_t FmrBit1; ///< Reserved
    per_bit_rw6_t Can2sb; ///< CAN2 start bank
    per_bit_n18_t FmrBit14; ///< Reserved

    // CAN filter mode register (CAN_FM1R)
    per_bit_rw1_t Fbm[PER_CAN_FILTER_MAX]; ///< Filter mode
    per_bit_n4_t FbmBit28; ///< Reserved

    // CAN filter scale register (CAN_FS1R)
    per_bit_rw1_t Fsc[PER_CAN_FILTER_MAX]; ///< Filter scale configuration
    per_bit_n4_t FscBit28; ///< Reserved

    // CAN filter FIFO assignment register (CAN_FFA1R)
    per_bit_rw1_t Ffa[PER_CAN_FILTER_MAX]; ///< Filter FIFO assignment for filter 
    per_bit_n4_t FfaBit28; ///< Reserved

    // CAN filter activation register (CAN_FA1R)
    per_bit_rw1_t Fact[PER_CAN_FILTER_MAX]; ///< Filter active
    per_bit_n4_t FactBit28; ///< Reserved

    // CAN Reserved
    per_bit_n32_t Reserved_0x220[8]; ///< Reserved 0x220 - 0x240  

    // Filter bank i register x (CAN_FiRx) (i=0..27, x=1, 2)
    per_can_fir_t Fir[PER_CAN_FILTER_MAX]; ///< Filter bank register 
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
static per_inline void per_can_set_inrq(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Inrq, val);
}

/// Sleep mode request
static per_inline bool per_can_sleep(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Sleep);
}

/// Sleep mode request
static per_inline void per_can_set_sleep(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Sleep, val);
}

/// Transmit FIFO priority
static per_inline bool per_can_txfp(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Txfp);
}

/// Transmit FIFO priority
static per_inline void per_can_set_txfp(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Txfp, val);
}

/// Receive FIFO locked mode
static per_inline bool per_can_rflm(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Rflm);
}

/// Receive FIFO locked mode
static per_inline void per_can_set_rflm(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Rflm, val);
}

/// No automatic retransmission
static per_inline bool per_can_nart(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Nart);
}

/// No automatic retransmission
static per_inline void per_can_set_nart(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Nart, val);
}

/// Automatic wakeup mode
static per_inline bool per_can_awum(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Awum);
}

/// Automatic wakeup mode
static per_inline void per_can_set_awum(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Awum, val);
}

/// Automatic bus-off management
static per_inline bool per_can_abom(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Abom);
}

/// Automatic bus-off management
static per_inline void per_can_set_abom(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Abom, val);
}

/// Time triggered communication mode
static per_inline bool per_can_ttcm(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Ttcm);
}

/// Time triggered communication mode
static per_inline void per_can_set_ttcm(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Ttcm, val);
}

/// bxCAN software master reset
static per_inline bool per_can_reset(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Reset);
}

/// bxCAN software master reset
static per_inline void per_can_set_reset(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Reset, val);
}

/// Debug freeze
static per_inline bool per_can_dbf(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Dbf);
}

/// Debug freeze
static per_inline void per_can_set_dbf(const per_can_t* const can, const bool val)
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

/// CAN receive FIFO x register (CAN_RFxR)
static per_inline uint_fast32_t per_can_rfr(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_rw32_reg(&can->Per->Rfr[mbx].Rfr);
}

/// CAN receive FIFO x register (CAN_RFxR)
static per_inline void per_can_set_rfr(const per_can_t* const can, const per_can_mbx_rx_e mbx, uint32_t val)
{
    per_bit_rw32_reg_set(&can->Per->Rfr[mbx].Rfr, val);
}

/// FIFO x message pending
static per_inline uint_fast16_t per_can_fmp(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_r2(&can->Per->Rfr[mbx].Fmp);
}

/// FIFO x full
static per_inline bool per_can_full(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_rc1_w1(&can->Per->Rfr[mbx].Full);
}

/// FIFO x full
static per_inline bool per_can_clr_full(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Rfr[mbx].Full);
}

/// FIFO x overrun
static per_inline bool per_can_fovr(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_rc1_w1(&can->Per->Rfr[mbx].Fovr);
}

/// FIFO x overrun
static per_inline bool per_can_clr_fovr(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_rc1_w1_rdclr(&can->Per->Rfr[mbx].Fovr);
}

/// Release FIFO x output mailbox
static per_inline bool per_can_rfom(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_rs1(&can->Per->Rfr[mbx].Rfom);
}

/// Release FIFO x output mailbox
static per_inline void per_can_set_rfom(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    per_bit_rs1_set(&can->Per->Rfr[mbx].Rfom);
}

/// Transmit mailbox empty interrupt enable
static per_inline bool per_can_tmeie(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Tmeie);
}

/// Transmit mailbox empty interrupt enable
static per_inline void per_can_set_tmeie(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Tmeie, val);
}

/// FIFO message pending interrupt enable
static per_inline bool per_can_fmpie0(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Fmpie0);
}

/// FIFO message pending interrupt enable
static per_inline void per_can_set_fmpie0(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Fmpie0, val);
}

/// FIFO full interrupt enable
static per_inline bool per_can_ffie0(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Ffie0);
}

/// FIFO full interrupt enable
static per_inline void per_can_set_ffie0(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Ffie0, val);
}

/// FIFO overrun interrupt enable
static per_inline bool per_can_fovie0(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Fovie0);
}

/// FIFO overrun interrupt enable
static per_inline void per_can_set_fovie0(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Fovie0, val);
}

/// FIFO message pending interrupt enable
static per_inline bool per_can_fmpie1(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Fmpie1);
}

/// FIFO message pending interrupt enable
static per_inline void per_can_set_fmpie1(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Fmpie1, val);
}

/// FIFO full interrupt enable
static per_inline bool per_can_ffie1(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Ffie1);
}

/// FIFO full interrupt enable
static per_inline void per_can_set_ffie1(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Ffie1, val);
}

/// FIFO overrun interrupt enable
static per_inline bool per_can_fovie1(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Fovie1);
}

/// FIFO overrun interrupt enable
static per_inline void per_can_set_fovie1(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Fovie1, val);
}

/// Error warning interrupt enable
static per_inline bool per_can_ewgie(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Ewgie);
}

/// Error warning interrupt enable
static per_inline void per_can_set_ewgie(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Ewgie, val);
}

/// Error passive interrupt enable
static per_inline bool per_can_epvie(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Epvie);
}

/// Error passive interrupt enable
static per_inline void per_can_set_epvie(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Epvie, val);
}

/// Bus-off interrupt enable
static per_inline bool per_can_bofie(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Bofie);
}

/// Bus-off interrupt enable
static per_inline void per_can_set_bofie(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Bofie, val);
}

/// Last error code interrupt enable
static per_inline bool per_can_lecie(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Lecie);
}

/// Last error code interrupt enable
static per_inline void per_can_set_lecie(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Lecie, val);
}

/// Error interrupt enable
static per_inline bool per_can_errie(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Errie);
}

/// Error interrupt enable
static per_inline void per_can_set_errie(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Errie, val);
}

/// Wakeup interrupt enable
static per_inline bool per_can_wkuie(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Wkuie);
}

/// Wakeup interrupt enable
static per_inline void per_can_set_wkuie(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Wkuie, val);
}

/// Sleep interrupt enable
static per_inline bool per_can_slkie(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Slkie);
}

/// Sleep interrupt enable
static per_inline void per_can_set_slkie(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Slkie, val);
}

/// Error warning flag
static per_inline bool per_can_ewgf(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Ewgf);
}

/// Error passive flag
static per_inline bool per_can_epvf(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Epvf);
}

/// Bus-off flag
static per_inline bool per_can_boff(const per_can_t* const can)
{
    return per_bit_r1(&can->Per->Boff);
}

/// Last error code
static per_inline uint_fast16_t per_can_lec(const per_can_t* const can)
{
    return per_bit_rw3(&can->Per->Lec);
}

/// Last error code
static per_inline void per_can_set_lec(const per_can_t* const can, const uint_fast16_t val)
{
    per_bit_rw3_set(&can->Per->Lec, val);
}

/// Least significant byte of the 9-bit transmit error counter
static per_inline uint_fast16_t per_can_tec(const per_can_t* const can)
{
    return per_bit_r8(&can->Per->Tec);
}

/// Receive error counter
static per_inline uint_fast16_t per_can_rec(const per_can_t* const can)
{
    return per_bit_r8(&can->Per->Rec);
}

/// Baud rate prescaler
static per_inline uint_fast16_t per_can_brp(const per_can_t* const can)
{
    return per_bit_rw10(&can->Per->Brp);
}

/// Baud rate prescaler
static per_inline void per_can_set_brp(const per_can_t* const can, const uint_fast16_t val)
{
    per_bit_rw10_set(&can->Per->Brp, val);
}

/// Time segment 1
static per_inline uint_fast16_t per_can_ts1(const per_can_t* const can)
{
    return per_bit_rw4(&can->Per->Ts1);
}

/// Time segment 1
static per_inline void per_can_set_ts1(const per_can_t* const can, const uint_fast16_t val)
{
    per_bit_rw4_set(&can->Per->Ts1, val);
}

/// Time segment 2
static per_inline uint_fast16_t per_can_ts2(const per_can_t* const can)
{
    return per_bit_rw3(&can->Per->Ts2);
}

/// Time segment 2
static per_inline void per_can_set_ts2(const per_can_t* const can, const uint_fast16_t val)
{
    per_bit_rw3_set(&can->Per->Ts2, val);
}

/// Resynchronization jump width
static per_inline uint_fast16_t per_can_sjw(const per_can_t* const can)
{
    return per_bit_rw2(&can->Per->Sjw);
}

/// Resynchronization jump width
static per_inline void per_can_set_sjw(const per_can_t* const can, const uint_fast16_t val)
{
    per_bit_rw2_set(&can->Per->Sjw, val);
}

/// Loop back mode (debug)
static per_inline bool per_can_lbkm(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Lbkm);
}

/// Loop back mode (debug)
static per_inline void per_can_set_lbkm(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Lbkm, val);
}

/// Silent mode (debug)
static per_inline bool per_can_silm(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Silm);
}

/// Silent mode (debug)
static per_inline void per_can_set_silm(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Silm, val);
}

/// Transmit mailbox request
static per_inline bool per_can_txrq_tx(const per_can_t* const can, const per_can_mbx_tx_e mbx)
{
    return per_bit_rw1(&can->Per->Mbxtx[mbx].Txrq);
}

/// Transmit mailbox request
static per_inline void per_can_set_txrq_tx(const per_can_t* const can, const per_can_mbx_tx_e mbx, const bool val)
{
    per_bit_rw1_set(&can->Per->Mbxtx[mbx].Txrq, val);
}

/// Remote transmission request
static per_inline bool per_can_rtr_tx(const per_can_t* const can, const per_can_mbx_tx_e mbx)
{
    return per_bit_r1(&can->Per->Mbxtx[mbx].Rtr);
}

/// Identifier extension
static per_inline bool per_can_ide_tx(const per_can_t* const can, const per_can_mbx_tx_e mbx)
{
    return per_bit_r1(&can->Per->Mbxtx[mbx].Ide);
}

/// Standard identifier or extended identifier
static per_inline bool per_can_stid_tx(const per_can_t* const can, const per_can_mbx_tx_e mbx)
{
    return per_bit_r11(&can->Per->Mbxtx[mbx].Stid);
}

/// TX mailbox identifier register (CAN_TIxR)
static per_inline uint_fast32_t per_can_tir(const per_can_t* const can, const per_can_mbx_tx_e mbx)
{
    return per_bit_rw32_reg(&can->Per->Mbxtx[mbx].Tir);
}

/// TX mailbox identifier register (CAN_TIxR) set data
static per_inline void per_can_set_data(per_can_mbx_tx_t* const mbx, const per_can_mess_t* const data)
{
    per_bit_rw32_reg_set(&mbx->Tdhr, data->High);
    per_bit_rw32_reg_set(&mbx->Tdlr, data->Low);
}

/// TX mailbox identifier register (CAN_TIxR) set header
static per_inline void per_can_set_head(per_can_mbx_tx_t* const mbx, const uint32_t tdtr, const uint32_t tir)
{
    per_bit_rw32_reg_set(&mbx->Tdtr, tdtr);
    per_bit_rw32_reg_set(&mbx->Tir, tir); // Lastly set transmit request
}

/// TX mailbox identifier register (CAN_TIxR) set id
static per_inline uint32_t per_can_tir_id(const uint32_t id)
{
    if ((id & ~PER_CAN_TIR_STID_MASK) == 0) // Standard identifier
    {    
        return ((id & PER_CAN_TIR_STID_MASK) << PER_CAN_TIR_STID_SHIFT) | PER_CAN_TIR_TXRQ; // Add standard id
    }
    else
    {
        return ((id & PER_CAN_TIR_EXID_MASK) << PER_CAN_TIR_EXID_SHIFT) | (PER_CAN_TIR_IDE | PER_CAN_TIR_TXRQ); // Add extended id
    }
}

/// TX mailbox identifier register (CAN_TIxR) Normal data frame
static per_inline bool per_can_set_tir(const per_can_t* const can, const per_can_mess_t* const data)
{
    const uint32_t tdtr = data->Length & PER_CAN_TDTR_DLC_MASK;
    const uint32_t tir = per_can_tir_id(data->Id);

    // Note the if else below is deliberatly written out for performance
    if (!per_can_rtr_tx(can, PER_CAN_MBX_TX_0))
    {
        per_can_mbx_tx_t* const mbx = &can->Per->Mbxtx[PER_CAN_MBX_TX_0];
        per_can_set_data(mbx, data);
        per_can_set_head(mbx, tdtr, tir);
    }
    else if(!per_can_rtr_tx(can, PER_CAN_MBX_TX_1))
    {
        per_can_mbx_tx_t* const mbx = &can->Per->Mbxtx[PER_CAN_MBX_TX_1];
        per_can_set_data(mbx, data);
        per_can_set_head(mbx, tdtr, tir);
    }
    else if(!per_can_rtr_tx(can, PER_CAN_MBX_TX_2))
    {
        per_can_mbx_tx_t* const mbx = &can->Per->Mbxtx[PER_CAN_MBX_TX_2];
        per_can_set_data(mbx, data);
        per_can_set_head(mbx, tdtr, tir);
    }
    else
    {
        per_log_err(can->Err, PER_CAN_MBX_TX_ERR, data->Id);
        return false;
    }

    return true;
}

/// TX mailbox identifier register (CAN_TIxR) remote request
static per_inline bool per_can_set_tir_rm(const per_can_t* const can, const uint32_t id, const uint_fast16_t dlc)
{
    const uint32_t tdtr = dlc & PER_CAN_TDTR_DLC_MASK;
    const uint32_t tir = per_can_tir_id(id) | PER_CAN_TIR_RTR; // Transmit request

    // Note the if else below is deliberatly written out for performance
    if (!per_can_rtr_tx(can, PER_CAN_MBX_TX_0))
    {
        per_can_mbx_tx_t* const mbx = &can->Per->Mbxtx[PER_CAN_MBX_TX_0];
        per_can_set_head(mbx, tdtr, tir);
    }
    else if(!per_can_rtr_tx(can, PER_CAN_MBX_TX_1))
    {
        per_can_mbx_tx_t* const mbx = &can->Per->Mbxtx[PER_CAN_MBX_TX_1];
        per_can_set_head(mbx, tdtr, tir);
    }
    else if(!per_can_rtr_tx(can, PER_CAN_MBX_TX_2))
    {
        per_can_mbx_tx_t* const mbx = &can->Per->Mbxtx[PER_CAN_MBX_TX_2];
        per_can_set_head(mbx, tdtr, tir);
    }
    else
    {
        per_log_err(can->Err, PER_CAN_MBX_TX_RM_ERR, id);
        return false;
    }

    return true;
}

/// TX mailbox identifier register (CAN_TIxR) time triggered communication
static per_inline bool per_can_set_tir_ttc(const per_can_t* const can, const per_can_mess_t* const data, const uint16_t time)
{
    const uint32_t tdtr = ((PER_CAN_DATA_MAX & PER_CAN_TDTR_DLC_MASK) | PER_CAN_TDTR_TGT) | (time << PER_CAN_TDTR_TIME_SHIFT);
    const uint32_t tir = per_can_tir_id(data->Id) | PER_CAN_TIR_RTR; // Transmit request

    // Note the if else below is deliberatly written out for performance
    if (!per_can_rtr_tx(can, PER_CAN_MBX_TX_0))
    {
        per_can_mbx_tx_t* const mbx = &can->Per->Mbxtx[PER_CAN_MBX_TX_0];
        per_can_set_data(mbx, data);
        per_can_set_head(mbx, tdtr, tir);
    }
    else if(!per_can_rtr_tx(can, PER_CAN_MBX_TX_1))
    {
        per_can_mbx_tx_t* const mbx = &can->Per->Mbxtx[PER_CAN_MBX_TX_1];
        per_can_set_data(mbx, data);
        per_can_set_head(mbx, tdtr, tir);
    }
    else if(!per_can_rtr_tx(can, PER_CAN_MBX_TX_2))
    {
        per_can_mbx_tx_t* const mbx = &can->Per->Mbxtx[PER_CAN_MBX_TX_2];
        per_can_set_data(mbx, data);
        per_can_set_head(mbx, tdtr, tir);
    }
    else
    {
        per_log_err(can->Err, PER_CAN_MBX_TX_TTC_ERR, data->Id);
        return false;
    }

    return true;
}

/// Data length code
static per_inline uint_fast16_t per_can_dlc_tx(const per_can_t* const can, const per_can_mbx_tx_e mbx)
{
    return per_bit_rw4(&can->Per->Mbxtx[mbx].Dlc);
}

/// Data length code
static per_inline void per_can_set_dlc(const per_can_t* const can, const per_can_mbx_tx_e mbx, const uint16_t val)
{
    per_bit_rw4_set(&can->Per->Mbxtx[mbx].Dlc, val);
}

/// Transmit global time
static per_inline bool per_can_tgt(const per_can_t* const can, const per_can_mbx_tx_e mbx)
{
    return per_bit_rw1(&can->Per->Mbxtx[mbx].Tgt);
}

/// Transmit global time
static per_inline void per_can_set_tgt(const per_can_t* const can, const per_can_mbx_tx_e mbx, const bool val)
{
    per_bit_rw1_set(&can->Per->Mbxtx[mbx].Tgt, val);
}

/// Message time stamp
static per_inline uint_fast16_t per_can_time_tx(const per_can_t* const can, const per_can_mbx_tx_e mbx)
{
    return per_bit_rw16(&can->Per->Mbxtx[mbx].Time);
}

/// Message time stamp
static per_inline void per_can_set_time(const per_can_t* const can, const per_can_mbx_tx_e mbx, const uint16_t val)
{
    per_bit_rw16_set(&can->Per->Mbxtx[mbx].Time, val);
}

/// CAN mailbox data length control and time stamp register
static per_inline uint_fast32_t per_can_tdtr(const per_can_t* const can, const per_can_mbx_tx_e mbx)
{
    return per_bit_rw32_reg(&can->Per->Mbxtx[mbx].Tdtr);
}

/// CAN mailbox data length control and time stamp register
static per_inline void per_can_set_tdtr(const per_can_t* const can, const per_can_mbx_tx_e mbx, const uint32_t val)
{
    per_bit_rw32_reg_set(&can->Per->Mbxtx[mbx].Tdtr, val);
}

/// CAN mailbox data low register
static per_inline uint_fast32_t per_can_tdlr(const per_can_t* const can, const per_can_mbx_tx_e mbx)
{
    return per_bit_rw32_reg(&can->Per->Mbxtx[mbx].Tdlr);
}

/// CAN mailbox data low register
static per_inline void per_can_set_tdlr(const per_can_t* const can, const per_can_mbx_tx_e mbx, const uint32_t val)
{
    per_bit_rw32_reg_set(&can->Per->Mbxtx[mbx].Tdlr, val);
}

/// CAN mailbox data high register
static per_inline uint_fast32_t per_can_tdhr(const per_can_t* const can, const per_can_mbx_tx_e mbx)
{
    return per_bit_rw32_reg(&can->Per->Mbxtx[mbx].Tdhr);
}

/// CAN mailbox data high register
static per_inline void per_can_set_tdhr(const per_can_t* const can, const per_can_mbx_tx_e mbx, const uint32_t val)
{
    per_bit_rw32_reg_set(&can->Per->Mbxtx[mbx].Tdhr, val);
}

/// Remote transmission request
static per_inline bool per_can_rtr_rx(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_r1(&can->Per->Mbxrx[mbx].Rtr);
}

/// Identifier extension
static per_inline bool per_can_ide_rx(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_r1(&can->Per->Mbxrx[mbx].Ide);
}

/// Standard identifier or extended identifier
static per_inline uint_fast16_t per_can_stid_rx(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_r11(&can->Per->Mbxrx[mbx].Stid);
}

/// CAN receive FIFO mailbox identifier register (CAN_RIxR) (x=0..1)
static per_inline bool per_can_rir(const per_can_t* const can, const per_can_mbx_rx_e mbx, per_can_mess_t* data)
{
    uint_fast32_t rir = per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rir);

    if ((rir & PER_CAN_RIR_RTR) == 0) // non remote
    {
        data->Low = per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rdhr);
        data->High = per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rdlr);
    }

    if ((rir & PER_CAN_RIR_IDE) == 0) // Standard
    {
        data->Id = (rir >> PER_CAN_RIR_STID_SHIFT) & PER_CAN_RIR_STID_MASK;
    }
    else
    {
        data->Id = (rir >> PER_CAN_RIR_EXID_SHIFT) & PER_CAN_RIR_EXID_MASK;
    }

    return (rir & PER_CAN_RIR_RTR) != 0;
}

/// Data length code
static per_inline uint_fast16_t per_can_dlc(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_r4(&can->Per->Mbxrx[mbx].Dlc);
}

/// Filter match index
static per_inline uint_fast16_t per_can_fmi(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_r8(&can->Per->Mbxrx[mbx].Fmi);
}

/// Message time stamp
static per_inline uint_fast16_t per_can_time(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_r16(&can->Per->Mbxrx[mbx].Time);
}

/// CAN mailbox data length control and time stamp register
static per_inline uint_fast32_t per_can_rdtr(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rdtr);
}

/// CAN mailbox data low register
static per_inline uint_fast32_t per_can_rdlr(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rdlr);
}

/// CAN mailbox data high register
static per_inline uint_fast32_t per_can_rdhr(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    return per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rdhr);
}

/// Filter init mode
static per_inline bool per_can_finit(const per_can_t* const can)
{
    return per_bit_rw1(&can->Per->Finit);
}

/// Filter init mode
static per_inline void per_can_set_finit(const per_can_t* const can, const bool val)
{
    per_bit_rw1_set(&can->Per->Finit, val);
}

/// CAN2 start bank
static per_inline uint_fast16_t per_can_can2sb(const per_can_t* const can)
{
    return per_bit_rw6(&can->Per->Can2sb);
}

/// CAN2 start bank
static per_inline void per_can_set_can2sb(const per_can_t* const can, const uint_fast16_t val)
{
    per_bit_rw6_set(&can->Per->Can2sb, val);
}

/// Filter mode
static per_inline bool per_can_fbm(const per_can_t* const can, const uint_fast16_t bank)
{
    if (bank >= PER_CAN_FILTER_MAX)
    {
        per_log_err(can->Err, PER_CAN_FBM_BANK_MAX_ERR, bank);
        return false;
    }
    return per_bit_rw1(&can->Per->Fbm[bank]);
}

/// Filter mode
static per_inline bool per_can_set_fbm(const per_can_t* const can, const uint_fast16_t bank, const bool val)
{
    if (bank >= PER_CAN_FILTER_MAX)
    {
        per_log_err(can->Err, PER_CAN_SET_FBM_BANK_MAX_ERR, bank);
        return false;
    }

    per_bit_rw1_set(&can->Per->Fbm[bank], val);
    return true;
}

/// Filter scale configuration
static per_inline bool per_can_fsc(const per_can_t* const can, const uint_fast16_t bank)
{
    if (bank >= PER_CAN_FILTER_MAX)
    {
        per_log_err(can->Err, PER_CAN_FSC_BANK_MAX_ERR, bank);
        return false;
    }
    return per_bit_rw1(&can->Per->Fsc[bank]);
}

/// Filter scale configuration
static per_inline bool per_can_set_fsc(const per_can_t* const can, const uint_fast16_t bank, const bool val)
{
    if (bank >= PER_CAN_FILTER_MAX)
    {
        per_log_err(can->Err, PER_CAN_SET_FSC_BANK_MAX_ERR, bank);
        return false;
    }

    per_bit_rw1_set(&can->Per->Fsc[bank], val);
    return true;
}

/// Filter FIFO assignment for filter 
static per_inline bool per_can_ffa(const per_can_t* const can, const uint_fast16_t bank)
{
    if (bank >= PER_CAN_FILTER_MAX)
    {
        per_log_err(can->Err, PER_CAN_FFA_BANK_MAX_ERR, bank);
        return false;
    }
    return per_bit_rw1(&can->Per->Ffa[bank]);
}

/// Filter FIFO assignment for filter 
static per_inline bool per_can_set_ffa(const per_can_t* const can, const uint_fast16_t bank, const bool val)
{
    if (bank >= PER_CAN_FILTER_MAX)
    {
        per_log_err(can->Err, PER_CAN_SET_FFA_BANK_MAX_ERR, bank);
        return false;
    }

    per_bit_rw1_set(&can->Per->Ffa[bank], val);
    return true;
}

/// Filter active
static per_inline bool per_can_fact(const per_can_t* const can, const uint_fast16_t bank)
{
    if (bank >= PER_CAN_FILTER_MAX)
    {
        per_log_err(can->Err, PER_CAN_FACT_BANK_MAX_ERR, bank);
        return false;
    }
    return per_bit_rw1(&can->Per->Fact[bank]);
}

/// Filter active
static per_inline bool per_can_set_fact(const per_can_t* const can, const uint_fast16_t bank, const bool val)
{
    if (bank >= PER_CAN_FILTER_MAX)
    {
        per_log_err(can->Err, PER_CAN_SET_FACT_BANK_MAX_ERR, bank);
        return false;
    }

    per_bit_rw1_set(&can->Per->Fact[bank], val);
    return true;
}

/// Filter bank i register x
static per_inline bool per_can_fir(const per_can_t* const can, const uint_fast16_t bank, uint32_t* fir1, uint32_t* fir2)
{
    if (bank >= PER_CAN_FILTER_MAX)
    {
        per_log_err(can->Err, PER_CAN_FIR_BANK_MAX_ERR, bank);
        return false;
    }

    *fir1 = per_bit_rw32_reg(&can->Per->Fir[bank].Fir32.R1);
    *fir2 = per_bit_rw32_reg(&can->Per->Fir[bank].Fir32.R2);

    return true;
}

/// Filter bank i register x
static per_inline bool per_can_set_fir(const per_can_t* const can, const uint_fast16_t bank, const uint32_t fir1, const uint32_t fir2)
{
    if (bank >= PER_CAN_FILTER_MAX)
    {
        per_log_err(can->Err, PER_CAN_SET_FIR_BANK_MAX_ERR, bank);
        return false;
    }

    per_bit_rw32_reg_set(&can->Per->Fir[bank].Fir32.R1, fir1);
    per_bit_rw32_reg_set(&can->Per->Fir[bank].Fir32.R2, fir2);

    return true;
}

/// Compose fir 32 bit
static per_inline uint32_t per_can_fir_32(const uint32_t id, const bool rtr, const bool ide)
{
    uint32_t fir;

    if (ide) // Extended
    {    
        fir = ((id & PER_CAN_FIR_32_EXID_MASK) << PER_CAN_FIR_32_EXID_SHIFT) | PER_CAN_FIR_32_IDE; // Extended id
    }
    else
    {
        fir = (id & PER_CAN_FIR_32_STID_MASK) << PER_CAN_FIR_32_STID_SHIFT; // Standard id
    }

    if (rtr)
    {
        fir |= PER_CAN_FIR_32_RTR;
    }

    return fir;
}

/// Filter bank i register x
static per_inline bool per_can_set_fir_32(const per_can_t* const can, const uint_fast16_t bank, const uint32_t id1, const bool rtr1, const bool ide1, const uint32_t id2, const bool rtr2, const bool ide2, const bool list, const bool fifo)
{
    if (bank >= PER_CAN_FILTER_MAX)
    {
        per_log_err(can->Err, PER_CAN_SET_FIR_SINGLE_BANK_MAX_ERR, bank);
        return false;
    }

    per_can_set_fact(can, bank, false); // De-activate bank
    per_can_set_fbm(can, bank, list); // Filter bank mode mask (false) or list (true)
    per_can_set_fsc(can, bank, true); // Filter bank scale single 32 bit
    per_can_set_ffa(can, bank, fifo); // Fifo assignement FIFO 0 (false) FIFO 1 (true)

    uint32_t fir = per_can_fir_32(id1, rtr1, ide1);
    per_bit_rw32_reg_set(&can->Per->Fir[bank].Fir32.R1, fir);

    fir = per_can_fir_32(id2, rtr2, ide2);
    per_bit_rw32_reg_set(&can->Per->Fir[bank].Fir32.R2, fir);

    per_can_set_fact(can, bank, true); // Activate bank again

    return true;
}

/// Compose fir 16 bit
static per_inline uint16_t per_can_fir_16(const uint_fast16_t id, const bool rtr)
{
    uint16_t fir = (id & PER_CAN_FIR_16_STID_MASK) << PER_CAN_FIR_16_STID_SHIFT; // Standard id

    if (rtr) // Remote
    {
        fir |= PER_CAN_FIR_16_RTR;
    }

    return fir;
}

/// Filter bank i register x
static per_inline bool per_can_set_fir_16(const per_can_t* const can, const uint_fast16_t bank, const uint16_t id1, const bool rtr1, const uint16_t id2, const bool rtr2, const uint16_t id3, const bool rtr3, const uint16_t id4, const bool rtr4, const bool list, const bool fifo)
{
    if (bank >= PER_CAN_FILTER_MAX)
    {
        per_log_err(can->Err, PER_CAN_SET_FIR_SINGLE_BANK_MAX_ERR, bank);
        return false;
    }

    per_can_set_fact(can, bank, false); // De-activate bank
    per_can_set_fbm(can, bank, list); // Filter bank mode mask (false) or list (true)
    per_can_set_fsc(can, bank, false); // Filter bank scale dual 16 bit
    per_can_set_ffa(can, bank, fifo); // Fifo assignement FIFO 0 (false) FIFO 1 (true)

    uint16_t fir = per_can_fir_16(id1, rtr1);
    per_bit_rw16_reg_set(&can->Per->Fir[bank].Fir16.R1, fir);

    fir = per_can_fir_16(id2, rtr2);
    per_bit_rw16_reg_set(&can->Per->Fir[bank].Fir16.R2, fir);

    fir = per_can_fir_16(id3, rtr3);
    per_bit_rw16_reg_set(&can->Per->Fir[bank].Fir16.R3, fir);

    fir = per_can_fir_16(id4, rtr4);
    per_bit_rw16_reg_set(&can->Per->Fir[bank].Fir16.R4, fir);

    per_can_set_fact(can, bank, true); // Activate bank again

    return true;
}

/// CAN fetch and clear active master interrupts and return the active interrupts
static per_inline per_can_msr_e per_can_msr_fc(const per_can_t* const can)
{
    uint_fast32_t irq = (uint_fast32_t)PER_CAN_MSR_MASK & per_can_msr(can);

    per_can_set_msr(can, irq); // Clear

    return (per_can_msr_e)irq;
}

/// CAN fetch and clear active transport interrupts and return the active interrupts
static per_inline per_can_tsr_e per_can_tsr_fc(const per_can_t* const can)
{
    uint_fast32_t irq = (uint_fast32_t)PER_CAN_TSR_MASK & per_can_tsr(can);

    per_can_set_tsr(can, irq); // Clear

    return (per_can_tsr_e)irq;
}

/// CAN fetch and clear active FIFO x bits
static per_inline per_can_rfr_e per_can_rfr_fc(const per_can_t* const can, const per_can_mbx_rx_e mbx)
{
    uint_fast32_t fif = (uint_fast32_t)PER_CAN_RFR_MASK & per_can_rfr(can, mbx);

    per_can_set_rfr(can, mbx, fif); // Clear

    return (per_can_rfr_e)fif;
}

/// CAN fetch receive one message
static per_inline uint_fast16_t per_can_read(const per_can_t* const can, const per_can_mbx_rx_e mbx, per_can_mess_t* data)
{
    uint_fast32_t fif = per_can_rfr(can, mbx);
    uint_fast16_t fmp = fif & (uint_fast32_t)PER_CAN_RFR_FMP;

    if (fmp == 0)
    {
        return 0; // Noting to read
    }

    uint_fast32_t rir = per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rir);

    if ((rir & PER_CAN_RIR_RTR) == 0) // non remote
    {
        data->Low = per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rdhr);
        data->High = per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rdlr);
        data->Length = per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rdtr) & PER_CAN_RDTR_DLC_MASK;
    }
    else
    {
        data->Length = 0;
    }

    if ((rir & PER_CAN_RIR_IDE) == 0) // Standard
    {
        data->Id = (rir >> PER_CAN_RIR_STID_SHIFT) & PER_CAN_RIR_STID_MASK;
    }
    else
    {
        data->Id = (rir >> PER_CAN_RIR_EXID_SHIFT) & PER_CAN_RIR_EXID_MASK;
    }

    fif = PER_CAN_RFR_RFOM; // Release mailbox

    if ((fif & PER_CAN_RFR_FOVR) != 0) // Check for overrun errors
    {
        per_log_err(can->Err, PER_CAN_MBX_RX_OVR_ERR, mbx);
        fif |= PER_CAN_RFR_FOVR;
    }

    per_can_set_rfr(can, mbx, fif); // Release and clear

    return fmp;
}

/// CAN fetch receive one message Time Triggered Communication
static per_inline uint_fast16_t per_can_read_time(const per_can_t* const can, const per_can_mbx_rx_e mbx, per_can_mess_time_t* data)
{
    uint_fast32_t fif = per_can_rfr(can, mbx);
    uint_fast16_t fmp = fif & (uint_fast32_t)PER_CAN_RFR_FMP;

    if (fmp == 0)
    {
        return 0; // Noting to read
    }

    uint_fast32_t rir = per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rir);
    uint_fast32_t rdtr = per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rdtr);

    if ((rir & PER_CAN_RIR_RTR) == 0) // non remote
    {
        data->Low = per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rdhr);
        data->High = per_bit_r32_reg(&can->Per->Mbxrx[mbx].Rdlr);
        data->Length = rdtr & PER_CAN_RDTR_DLC_MASK;
        data->Time = rdtr >> PER_CAN_RDTR_TIME_SHIFT;
    }
    else
    {
        data->Length = 0;
    }

    if ((rir & PER_CAN_RIR_IDE) == 0) // Standard
    {
        data->Id = (rir >> PER_CAN_RIR_STID_SHIFT) & PER_CAN_RIR_STID_MASK;
    }
    else
    {
        data->Id = (rir >> PER_CAN_RIR_EXID_SHIFT) & PER_CAN_RIR_EXID_MASK;
    }

    fif = PER_CAN_RFR_RFOM; // Release mailbox

    if ((fif & PER_CAN_RFR_FOVR) != 0) // Check for overrun errors
    {
        per_log_err(can->Err, PER_CAN_MBX_RX_OVR_ERR, mbx);
        fif |= PER_CAN_RFR_FOVR;
    }

    per_can_set_rfr(can, mbx, fif); // Release and clear

    return fmp;
}

/// CAN Set baudrate value
static per_inline bool per_can_set_baudrate(const per_can_t* const can, uint_fast32_t rate)
{
    uint_fast32_t pre = (per_rcc_apb1_per_freq() / rate) / PER_CAN_BAUD_RATE_DIVIDER;

    if ((pre == 0) || (pre > UINT16_MAX ))
    {
        per_log_err(can->Err, PER_CAN_BAUDRATE_ERR, rate);
        return false;
    }

    per_can_set_brp(can, (uint16_t)(pre - 1));
    return true;
}

#ifdef __cplusplus
}
#endif

#endif // per_can_f4_h_
