/**
 * @file per_eth_f4.h
 *
 * This file contains the Ethernet peripheral interface (ETH)
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
 * per_eth_mac_miiar_write()     writes the MII register in one command
 * per_eth_dma_irq()            clears active interrupts and returns bitmask of the cleared ones
 *
 */

#ifndef per_eth_f4_h_
#define per_eth_f4_h_

#ifdef __cplusplus
extern "C"
{
#endif

#include "per_bit_f4.h"
#include "per_log_f4.h"

/// ETH MAC base address
#define PER_ETH_MAC ((per_eth_mac_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_AHB1 + (uintptr_t)0x8000))

/// ETH MMC base address
#define PER_ETH_MMC ((per_eth_mmc_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_AHB1 + (uintptr_t)0x8100))

/// ETH PTP base address
#define PER_ETH_PTP ((per_eth_ptp_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_AHB1 + (uintptr_t)0x8700))

/// ETH DMA base address
#define PER_ETH_DMA ((per_eth_dma_t* const)PER_BIT_REG_TO_BIT_BAND(PER_ADDR_AHB1 + (uintptr_t)0x9000))

/// PPS frequency maximum value
#define PER_ETH_PTP_PPSFREQ_MAX (32768)

/// DMA Rx DMA PBL
#define PER_ETH_DMA_RDP_MAX (32)

/// DMA Rx Tx priority ratio
#define PER_ETH_DMA_PM_MAX (4)

/// DMA Rx Tx priority ratio
#define PER_ETH_DMA_PBL_MAX (32)

/// DMA Descriptor skip length
#define PER_ETH_DMA_DSL_MAX PER_BIT_MAX(5)

/// DMA Transmit threshold control Most significant bit
#define DMA_TTS_MSB (0b0100)

/// ETH error enumeration
typedef enum
{
    PER_ETH_ERR_OK = PER_LOG_ETH * PER_LOG_MULT, ///< No error
    PER_ETH_PTP_PPSFREQ_ERR, ///< PPS frequency invalid
    PER_ETH_DMA_RDP_ERR, ///< Rx DMA PBL
    PER_ETH_DMA_PM_ERR, ///< DMA Rx Tx priority ratio invalid
    PER_ETH_DMA_PBL_ERR, ///< DMA Programmable burst length invalid
    PER_ETH_DMA_DSL_ERR, ///< DMA Descriptor skip length invalid
} per_eth_error_e;

/// ETH Interframe gap
typedef enum
{
    PER_ETH_IFG_96 = 0b000, ///< 96
    PER_ETH_IFG_88 = 0b001, ///< 88
    PER_ETH_IFG_80 = 0b010, ///< 80
    PER_ETH_IFG_72 = 0b011, ///< 72
    PER_ETH_IFG_64 = 0b100, ///< 64
    PER_ETH_IFG_56 = 0b101, ///< 56
    PER_ETH_IFG_48 = 0b110, ///< 48
    PER_ETH_IFG_40 = 0b111, ///< 40
} per_eth_ifg_e;

/// ETH Back-off limit
typedef enum
{
    PER_ETH_BL_10 = 0b00, ///< 10
    PER_ETH_BL_8  = 0b01, ///< 8
    PER_ETH_BL_4  = 0b10, ///< 4
    PER_ETH_BL_1  = 0b11, ///< 1
} per_eth_bl_e;

/// ETH Pass control frames
typedef enum
{
    PER_ETH_PCF_NONE     = 0b00, ///< Prevent all control frames
    PER_ETH_PCF_NO_PAUSE = 0b01, ///< Prevent pause frames
    PER_ETH_PCF_ALL      = 0b10, ///< Forward all
    PER_ETH_PCF_ADDRESS  = 0b11, ///< Prevent frames that do not pass the address filter
} per_eth_pcf_e;

/// ETH Clock range
typedef enum
{
    PER_ETH_CR_60_100  = 0b000, ///< 60-100 MHz HCLK/42
    PER_ETH_CR_100_150 = 0b001, ///< 100-150 MHzHCLK/62
    PER_ETH_CR_20_35   = 0b010, ///< 20-35 MHz HCLK/16
    PER_ETH_CR_35_60   = 0b011, ///< 35-60 MHz HCLK/26
    PER_ETH_CR_150_168 = 0b100, ///< 150-168 MHz HCLK/102
} per_eth_cr_e;

/// ETH PMT control and status register flags
typedef enum
{
     PER_ETH_PMTCSR_PD  = 0x0001, ///< Power down
     PER_ETH_PMTCSR_WFE = 0x0002, ///< Wakeup frame enable
     PER_ETH_PMTCSR_MPE = 0x0004, ///< Magic Packet enable
     PER_ETH_PMTCSR_MPR = 0x0020, ///< Magic packet received
     PER_ETH_PMTCSR_WFR = 0x0040, ///< Wakeup frame received
     PER_ETH_PMTCSR_GU  = 0x0200, ///< Global unicast
     PER_ETH_PMTCSR_WFFRPR = 0x8000, ///< Wakeup frame filter register pointer reset
     PER_ETH_PMTCSR_RC_R_MASK  = PER_ETH_PMTCSR_MPR | ///< Receive flags
                                 PER_ETH_PMTCSR_WFR,
} per_eth_pmtcsr_e;

/// MAC small FIFO read / write controllers status
typedef enum
{
    PER_ETH_MSFRWCS_IDLE = 0b00, ///< Idle
    PER_ETH_MSFRWCS_READ  = 0b01, ///< Read active
    PER_ETH_MSFRWCS_WRITE = 0b10, ///< Write active
    PER_ETH_MSFRWCS_READ_WRITE = 0b11, ///< Read and write active
} per_eth_msfrwcs_e;

/// ETH Rx FIFO read controller status
typedef enum
{
    PER_ETH_RFRCS_IDLE   = 0b00, ///< IDLE state
    PER_ETH_RFRCS_DATA   = 0b01, ///< Reading frame data
    PER_ETH_RFRCS_STATUS = 0b10, ///< Reading frame status (or time-stamp)
    PER_ETH_RFRCS_FLUSH  = 0b11, ///< Flushing the frame data and status
} per_eth_rfrcs_e;

/// ETH Rx FIFO fill level
typedef enum
{
    PER_ETH_RFFL_EMPTY  = 0b00, ///< Empty
    PER_ETH_RFFL_BELOW  = 0b01, ///< Fill-level below flow-control de-activate threshold
    PER_ETH_RFFL_ABOVE  = 0b10, ///< Fill-level above flow-control activate threshold
    PER_ETH_RFFL_FULL   = 0b11, ///< Full
} per_eth_rffl_e;

/// ETH MAC transmit frame controller status
typedef enum
{
    PER_ETH_MTFCS_IDLE     = 0b00, ///< Idle
    PER_ETH_MTFCS_WAIT     = 0b01, ///< Waiting for Status of previous frame or IFG/backoff period to be over
    PER_ETH_MTFCS_PAUSE    = 0b10, ///< Generating and transmitting a Pause control frame (in full duplex mode)
    PER_ETH_MTFCS_TRANSFER = 0b11, ///< Transferring input frame for transmission
} per_eth_mtfcs_e;

/// ETH Tx FIFO read status
typedef enum
{
    PER_ETH_TFRS_IDLE  = 0b00, ///< Idle state
    PER_ETH_TFRS_READ  = 0b01, ///< Read state (transferring data to the MAC transmitter)
    PER_ETH_TFRS_WAIT  = 0b10, ///< Waiting for TxStatus from MAC transmitter
    PER_ETH_TFRS_WRITE = 0b11, ///< Writing the received TxStatus or flushing the TxFIFO
} per_eth_tfrs_e;

/// ETH Time stamp clock node type
typedef enum
{
    PER_ETH_TSCNT_ORDINARY = 0b00, ///< Ordinary clock
    PER_ETH_TSCNT_BOUND = 0b01, ///< Boundary clock
    PER_ETH_TSCNT_END   = 0b10, ///< End-to-end transparent clock
    PER_ETH_TSCNT_PEER  = 0b11, ///< Peer-to-peer transparent clock
} per_eth_tscnt_e;

/// ETH DMA Status register flags
typedef enum
{
    PER_ETH_DMA_SR_TS   = 0x000001, ///< Transmit status
    PER_ETH_DMA_SR_TPSS = 0x000002, ///< Transmit process stopped status
    PER_ETH_DMA_SR_TBUS = 0x000004, ///< Transmit buffer unavailable status
    PER_ETH_DMA_SR_TJTS = 0x000008, ///< Transmit jabber timeout status
    PER_ETH_DMA_SR_ROS  = 0x000010, ///< Receive overflow status
    PER_ETH_DMA_SR_TUS  = 0x000020, ///< Transmit underflow status
    PER_ETH_DMA_SR_RS   = 0x000040, ///< Receive status
    PER_ETH_DMA_SR_RBUS = 0x000080, ///< Receive buffer unavailable status
    PER_ETH_DMA_SR_RPSS = 0x000100, ///< Receive process stopped status
    PER_ETH_DMA_SR_RWTS = 0x000200, ///< Receive watchdog timeout status
    PER_ETH_DMA_SR_ETS  = 0x000400, ///< Early transmit status
    PER_ETH_DMA_SR_FBES = 0x002000, ///< Fatal bus error status
    PER_ETH_DMA_SR_ERS  = 0x004000, ///< Early receive status
    PER_ETH_DMA_SR_AIS  = 0x008000, ///< Abnormal interrupt summary
    PER_ETH_DMA_SR_NIS  = 0x010000, ///< Normal interrupt summary
    PER_ETH_DMA_SR_MASK = PER_ETH_DMA_SR_TS | ///< All interrupt flag
                          PER_ETH_DMA_SR_TPSS |
                          PER_ETH_DMA_SR_TBUS |
                          PER_ETH_DMA_SR_TJTS |
                          PER_ETH_DMA_SR_ROS |
                          PER_ETH_DMA_SR_TUS |
                          PER_ETH_DMA_SR_RS |
                          PER_ETH_DMA_SR_RBUS |
                          PER_ETH_DMA_SR_RPSS |
                          PER_ETH_DMA_SR_RWTS |
                          PER_ETH_DMA_SR_ETS |
                          PER_ETH_DMA_SR_FBES |
                          PER_ETH_DMA_SR_ERS |
                          PER_ETH_DMA_SR_AIS |
                          PER_ETH_DMA_SR_NIS,
} per_eth_dma_sr_e;

/// ETH DMA Transmit process state
typedef enum
{
    PER_ETH_DMA_TPS_STOPPED = 0b000, ///< Stopped; Reset or Stop Transmit Command issued
    PER_ETH_DMA_TPS_FETCHING = 0b001, ///< Running; Fetching transmit transfer descriptor
    PER_ETH_DMA_TPS_WAITING = 0b010, ///< Running; Waiting for status
    PER_ETH_DMA_TPS_READING = 0b011, ///< Running; Reading Data from host memory
    PER_ETH_DMA_TPS_SUSPENDED = 0b110, ///< Suspended
    PER_ETH_DMA_TPS_CLOSING = 0b111, ///< Running; Closing transmit descriptor
} per_eth_dma_tps_e;

/// ETH DMA Receive process state
typedef enum
{
    PER_ETH_DMA_RPS_STOPPED = 0b000, ///< Stopped: Reset or Stop Receive Command issued
    PER_ETH_DMA_RPS_FETCHING = 0b001, ///< Running: Fetching receive transfer descriptor
    PER_ETH_DMA_RPS_WAITING = 0b011, ///< Running: Waiting for receive packet
    PER_ETH_DMA_RPS_SUSPENDED = 0b100, ///< Suspended: Receive descriptor unavailable
    PER_ETH_DMA_RPS_CLOSING = 0b101, ///< Running: Closing receive descriptor
    PER_ETH_DMA_RPS_TRANSFERRING = 0b111, ///< Running: Transferring the receive packet data
} per_eth_dma_rps_e;

/// ETH DMA Transmit threshold control
typedef enum
{
    PER_ETH_DMA_TTC_64  = 0b000, ///< 64
    PER_ETH_DMA_TTC_128 = 0b001, ///< 128
    PER_ETH_DMA_TTC_192 = 0b010, ///< 192
    PER_ETH_DMA_TTC_256 = 0b011, ///< 256
    PER_ETH_DMA_TTC_40  = 0b100, ///< 40
    PER_ETH_DMA_TTC_32  = 0b101, ///< 32
    PER_ETH_DMA_TTC_24  = 0b110, ///< 24
    PER_ETH_DMA_TTC_16  = 0b111, ///< 16
} per_eth_dma_ttc_e;

/// ETH DMA Receive threshold control
typedef enum
{
    PER_ETH_DMA_RTC_64  = 0b00, ///< 64
    PER_ETH_DMA_RTC_32  = 0b01, ///< 32
    PER_ETH_DMA_RTC_96  = 0b10, ///< 96
    PER_ETH_DMA_RTC_128 = 0b11, ///< 128
} per_eth_dma_rtc_e;

/// ETH DMA missed frame and buffer overflow counter register (ETH_DMAMFBOCR)
typedef enum
{
    PER_ETH_DMA_MFBOCR_MFC_MASK  = 0xffff, ///< Missed frames by the controller
    PER_ETH_DMA_MFBOCR_OMFC_MASK = 0x01 << 16, ///< Overflow bit for missed frame counter
    PER_ETH_DMA_MFBOCR_MFA_SHIFT = 17, ///< Missed frames by the application
    PER_ETH_DMA_MFBOCR_MFA_MASK  = 0x07ff, ///< Missed frames by the application
    PER_ETH_DMA_MFBOCR_OFOC_MASK = 0x01 << 28, ///< Overflow bit for FIFO overflow counter
} per_eth_dma_mfbocr_e;

typedef struct
{
    // MAC configuration register (ETH_MACCR)
    per_bit_n2_t CrBit0; ///< Reserved
    per_bit_rw1_t Re; ///< Receiver enable
    per_bit_rw1_t Te; ///< Transmitter enable
    per_bit_rw1_t Dc; ///< Deferral check
    per_bit_rw2_t Bl; ///< Back-off limit
    per_bit_rw1_t Acps; ///< Automatic pad/CRC stripping
    per_bit_n1_t CrBit8; ///< Reserved
    per_bit_rw1_t Rd; ///< Retry disable
    per_bit_rw1_t Ipco; ///< IPv4 checksum offload
    per_bit_rw1_t Dm; ///< Duplex mode
    per_bit_rw1_t Lm; ///< Loopback mode
    per_bit_rw1_t Rod; ///< Receive own disable
    per_bit_rw1_t Fes; ///< Fast Ethernet speed
    per_bit_n1_t CrBit15; ///< Reserved
    per_bit_rw1_t Csd; ///< Carrier sense disable
    per_bit_rw3_t Ifg; ///< Interframe gap
    per_bit_n2_t CrBit20; ///< Reserved
    per_bit_rw1_t Jd; ///< Jabber disable
    per_bit_rw1_t Wd; ///< Watchdog disable
    per_bit_n1_t CrBit24; ///< Reserved
    per_bit_rw1_t Cstf; ///< CRC stripping for Type frames
    per_bit_n6_t CrBit26; ///< Reserved

    // MAC frame filter register (ETH_MACFFR)
    per_bit_rw1_t Pm; ///< Promiscuous mode
    per_bit_rw1_t Hu; ///< Hash unicast
    per_bit_rw1_t Hm; ///< Hash multicast
    per_bit_rw1_t Daif; ///< Destination address inverse filtering
    per_bit_rw1_t Pam; ///< Pass all multicast
    per_bit_rw1_t Bfd; ///< Broadcast frames disable
    per_bit_rw2_t Pcf; ///< Pass control frames
    per_bit_rw1_t Saif; ///< Source address inverse filtering
    per_bit_rw1_t Saf; ///< Source address filter
    per_bit_rw1_t Hpf; ///< Hash or perfect filter
    per_bit_n20_t FfrBit11; ///< Reserved
    per_bit_rw1_t Ra; ///< Receive all

    // MAC hash table high register (ETH_MACHTHR)
    per_bit_rw32_reg_t Hth; ///< Hash table high

    // MAC hash table low register (ETH_MACHTLR)
    per_bit_rw32_reg_t Htl; ///< Hash table low

    // MAC MII address register (ETH_MACMIIAR)
    union
    {
        struct
        {
            per_bit_rs1_t Mb; ///< MII busy
            per_bit_rw1_t Mw; ///< MII write
            per_bit_rw3_t Cr; ///< Clock range
            per_bit_n1_t MiiarBit5; ///< Reserved
            per_bit_rw5_t Mr; ///< MII register
            per_bit_rw5_t Pa; ///< PHY address
            per_bit_rw16_t MiiarBit16; ///< Reserved
        };
        per_bit_rw16_reg_t Miiar; ///< Register access
    };

    // MAC MII data register (ETH_MACMIIDR)
    per_bit_rw16_reg_t Md; ///< MII data

    // MAC flow control register (ETH_MACFCR)
    per_bit_rs1_t Fcb; ///< Flow control busy/back pressure activate
    per_bit_rw1_t Tfce; ///< Transmit flow control enable
    per_bit_rw1_t Rfce; ///< Receive flow control enable
    per_bit_rw1_t Upfd; ///< Unicast pause frame detect
    per_bit_rw2_t Plt; ///< Pause low threshold
    per_bit_n1_t FcrBit6; ///< Reserved
    per_bit_rw1_t Zqpd; ///< Zero-quanta pause disable
    per_bit_n8_t FcrBit8; ///< Reserved
    per_bit_rw16_t Pt; ///< Pause time

    // MAC VLAN tag register (ETH_MACVLANTR)
    per_bit_rw16_t Vlanti; ///< VLAN tag identifier (for receive frames)
    per_bit_rw1_t Vlantc; ///< 12-bit VLAN tag comparison
    per_bit_n15_t VlantrBit17; ///< Reserved

    per_bit_n32_t MacReg20[2]; ///< Reserved

    // MAC remote wakeup frame filter register (ETH_MACRWUFFR)
    per_bit_rw32_reg_t Rwuffr; ///< remote wakeup frame filter register

    // MAC PMT control and status register (ETH_MACPMTCSR)
    per_bit_rw32_reg_t Macpmtcsr; ///< Register access

    per_bit_n32_t MacReg30; ///< Reserved

    // MAC debug register (ETH_MACDBGR)
    per_bit_r1_t Mmrpea; ///< MAC MII receive protocol engine active
    per_bit_r2_t Msfrwcs; ///< MAC small FIFO read / write controllers status
    per_bit_n1_t DbgrBit3; ///< Reserved
    per_bit_r1_t Rfwra; ///< Rx FIFO write controller active
    per_bit_r2_t Rfrcs; ///< Rx FIFO read controller status
    per_bit_n1_t DbgrBit7; ///< Reserved
    per_bit_r2_t Rffl; ///< Rx FIFO fill level
    per_bit_n6_t DbgrBit10; ///< Reserved
    per_bit_r1_t Mmtea; ///< MAC MII transmit engine active
    per_bit_r2_t Mtfcs; ///< MAC transmit frame controller status
    per_bit_r1_t Mtp; ///< MAC transmitter in pause
    per_bit_r2_t Tfrs; ///< Tx FIFO read status
    per_bit_r1_t Tfwa; ///< Tx FIFO write active
    per_bit_n1_t DbgrBit23; ///< Reserved
    per_bit_r1_t Tfne; ///< Tx FIFO not empty
    per_bit_r1_t Tff; ///< Tx FIFO full
    per_bit_n6_t DbgrBit26; ///< Reserved

    // MAC interrupt status register (ETH_MACSR)
    per_bit_n3_t CsrBit0; ///< Reserved
    per_bit_r1_t Pmts; ///< PMT status
    per_bit_r1_t Mmcs; ///< MMC status
    per_bit_r1_t Mmcrs; ///< MMC receive status
    per_bit_r1_t Mmcts; ///< MMC transmit status
    per_bit_n2_t CsrBit7; ///< Reserved
    per_bit_r1_t Tsts; ///< Time stamp trigger status
    per_bit_n22_t CsrBit10; ///< Reserved

    // MAC interrupt mask register (ETH_MACIMR)
    per_bit_n3_t ImrBit0; ///< Reserved
    per_bit_rw1_t Pmtim; ///< PMT interrupt mask
    per_bit_n5_t ImrBit4; ///< Reserved
    per_bit_rw1_t Tstim; ///< Time stamp trigger interrupt mask
    per_bit_n22_t ImrBit10; ///< Reserved

    // MAC address 0 high register (ETH_MACA0HR)
    per_bit_rw16_t Maca0h; ///< MAC address0 high [47:32]
    per_bit_n15_t A0hrBit16; ///< Reserved
    per_bit_n1_t Mo; ///< Always 1

    // MAC address 0 low register (ETH_MACA0LR)
    per_bit_rw32_reg_t Maca0l; ///< MAC address0 low [31:0]

    // MAC address 1 high register (ETH_MACA1HR)
    per_bit_rw16_t Maca1h; ///< MAC address1 high [47:32]
    per_bit_n8_t A1hrBit16; ///< Reserved
    per_bit_rw6_t Mbc1; ///< Mask byte control
    per_bit_rw1_t Sa1; ///< Source address
    per_bit_rw1_t Ae1; ///< Address enable

    // MAC address 1 low register (ETH_MACA1LR)
    per_bit_rw32_reg_t Maca1l; ///< MAC address1 low [31:0]

    // MAC address 2 high register (ETH_MACA2HR)
    per_bit_rw16_t Maca2h; ///< MAC address2 high [47:32]
    per_bit_n8_t A2hrBit16; ///< Reserved
    per_bit_rw6_t Mbc2; ///< Mask byte control
    per_bit_rw1_t Sa2; ///< Source address
    per_bit_rw1_t Ae2; ///< Address enable

    // MAC address 2 low register (ETH_MACA2LR)
    per_bit_rw32_reg_t Maca2l; ///< MAC address2 low [31:0]

    // MAC address 3 high register (ETH_MACA3HR)
    per_bit_rw16_t Maca3h; ///< MAC address3 high [47:32]
    per_bit_n8_t A3hrBit16; ///< Reserved
    per_bit_rw6_t Mbc3; ///< Mask byte control
    per_bit_rw1_t Sa3; ///< Source address
    per_bit_rw1_t Ae3; ///< Address enable

    // MAC address 3 low register (ETH_MACA3LR)
    per_bit_rw32_reg_t Maca3l; ///< MAC address3 low [31:0]
} per_eth_mac_t;

typedef struct
{
    // MMC control register (ETH_MMCCR)
    per_bit_rw1_t Cr; ///< Counter reset
    per_bit_rw1_t Csr; ///< Counter stop rollover
    per_bit_rw1_t Ror; ///< Reset on read
    per_bit_rw1_t Mcf; ///< MMC counter freeze
    per_bit_rw1_t Mcp; ///< MMC counter preset
    per_bit_rw1_t Mcfhp; ///< MMC counter Full-Half preset
    per_bit_n26_t CrBit6; ///< Reserved

    // MMC receive interrupt register (ETH_MMCRIR)
    per_bit_n5_t RirBit0; ///< Reserved
    per_bit_r1_t Rfces; ///< Received frames CRC error status
    per_bit_r1_t Rfaes; ///< Received frames alignment error status
    per_bit_n10_t RirBit7; ///< Reserved
    per_bit_r1_t Rgufs; ///< Received Good Unicast Frames Status
    per_bit_n14_t RirBit18; ///< Reserved

    // MMC transmit interrupt register (ETH_MMCTIR)
    per_bit_n14_t TirBit0; ///< Reserved
    per_bit_r1_t Tgfscs; ///< Transmitted good frames single collision status
    per_bit_r1_t Tgmscs; ///< Transmitted good frames more single collision status
    per_bit_n5_t TirBit16; ///< Reserved
    per_bit_r1_t Tgfs; ///< Transmitted good frames status
    per_bit_n10_t TirBit22; ///< Reserved

    // MMC receive interrupt mask register (ETH_MMCRIMR)
    per_bit_n5_t ImrBit0; ///< Reserved
    per_bit_rw1_t Rfcem; ///< Received frame CRC error mask
    per_bit_rw1_t Rfaem; ///< Received frames alignment error mask
    per_bit_n10_t ImrBit7; ///< Reserved
    per_bit_rw1_t Rgufm; ///< Received good unicast frames mask
    per_bit_n14_t ImrBit18; ///< Reserved

    // MMC transmit interrupt mask register (ETH_MMCTIMR)
    per_bit_n14_t TimrBit0; ///< Reserved
    per_bit_rw1_t Tgfscm; ///< Transmitted good frames single collision mask
    per_bit_rw1_t Tgfmscm; ///< Transmitted good frames more single collision mask
    per_bit_n5_t TimrBit16; ///< Reserved
    per_bit_rw1_t Tgfm; ///< Transmitted good frames mask
    per_bit_n10_t TimrBit22; ///< Reserved

    per_bit_n32_t MmcReg14[14]; ///< Reserved

    // MMC transmitted good frames after a single collision counter register (ETH_MMCTGFSCCR)
    per_bit_r32_reg_t Tgfscc; ///< Transmitted good frames single collision counter

    // MMC transmitted good frames after more than a single collision counter register (ETH_MMCTGFMSCCR)
    per_bit_r32_reg_t Tgfmscc; ///< Transmitted good frames more single collision counter

    per_bit_n32_t MmcReg54[5]; ///< Reserved

    // MMC transmitted good frames counter register (ETH_MMCTGFCR)
    per_bit_r32_reg_t Tgfc; ///< Transmitted good frames counter

    per_bit_n32_t MmcReg6c[10]; ///< Reserved

    // MMC received frames with CRC error counter register (ETH_MMCRFCECR)
    per_bit_r32_reg_t Rfcec; ///< Received frames CRC error counter

    // MMC received frames with alignment error counter register (ETH_MMCRFAECR)
    per_bit_r32_reg_t Rfaec; ///< Received frames alignment error counter

    per_bit_n32_t MmcReg9c[10]; ///< Reserved

    // MMC received good unicast frames counter register (ETH_MMCRGUFCR)
    per_bit_r32_reg_t Rgufc; ///< Received good unicast frames counter
} per_eth_mmc_t;

typedef struct
{
    // PTP time stamp control register (ETH_PTPTSCR)
    per_bit_rw1_t Tse; ///< Time stamp enable
    per_bit_rw1_t Tsfcu; ///< Time stamp fine or coarse update
    per_bit_rw1_t Tssti; ///< Time stamp system time initialize
    per_bit_rw1_t Tsstu; ///< Time stamp system time update
    per_bit_rw1_t Tsite; ///< Time stamp interrupt trigger enable
    per_bit_rw1_t Ttsaru; ///< Time stamp addend register update
    per_bit_n2_t TscrBit6; ///< Reserved
    per_bit_rw1_t Tssarfe; ///< Time stamp snapshot for all received frames enable
    per_bit_rw1_t Tsssr; ///< Time stamp subsecond rollover: digital or binary rollover control
    per_bit_rw1_t Tsptppsv2e; ///< Time stamp PTP packet snooping for version2 format enable
    per_bit_rw1_t Tssptpoefe; ///< Time stamp snapshot for PTP over ethernet frames enable
    per_bit_rw1_t Tssipv6fe; ///< Time stamp snapshot for IPv6 frames enable
    per_bit_rw1_t Tssipv4fe; ///< Time stamp snapshot for IPv4 frames enable
    per_bit_rw1_t Tsseme; ///< Time stamp snapshot for event message enable
    per_bit_rw1_t Tssmrme; ///< Time stamp snapshot for message relevant to master enable
    per_bit_rw2_t Tscnt; ///< Time stamp clock node type
    per_bit_rw1_t Tspffmae; ///< Time stamp PTP frame filtering MAC address enable
    per_bit_n13_t TscrBit19; ///< Reserved

    // PTP subsecond increment register (ETH_PTPSSIR)
    per_bit_rw8_reg_t Stssi; ///< System time subsecond increment

    // PTP time stamp high register (ETH_PTPTSHR)
    per_bit_r32_reg_t Sts; ///< System time second

    // PTP time stamp low register (ETH_PTPTSLR)
    per_bit_r32_reg_t Stss; ///< System time subseconds. Note used as signed int32

    // PTP time stamp high update register (ETH_PTPTSHUR)
    per_bit_rw32_reg_t Tsus; ///< Time stamp update second

    // PTP time stamp low update register (ETH_PTPTSLUR)
    per_bit_rw32_reg_t Tsuss; ///< Time stamp update subseconds. Note used as signed int32

    // PTP time stamp addend register (ETH_PTPTSAR)
    per_bit_rw32_reg_t Tsa; ///< Time stamp addend

    // PTP target time high register (ETH_PTPTTHR)
    per_bit_rw32_reg_t Ttsh; ///< Target time stamp high

    // PTP target time low register (ETH_PTPTTLR)
    per_bit_rw32_reg_t Ttsl; ///< Target time stamp low

    per_bit_n32_t PtpReg24; ///< Reserved

    // PTP time stamp status register (ETH_PTPTSSR)
    per_bit_r1_t Tsso; ///< Time stamp second overflow
    per_bit_r1_t Tsttr; ///< Time stamp target time reached
    per_bit_n30_t TsrBit2; ///< Reserved

    // PTP PPS control register (ETH_PTPPPSCR)
    per_bit_rw4_t Ppsfreq; ///< PPS frequency selection
    per_bit_n28_t PpscrBit4; ///< Reserved

} per_eth_ptp_t;

typedef struct
{
    // DMA bus mode register (ETH_DMABMR)
    per_bit_rs1_t Sftr; ///< (Sr) Software reset. Note duplicate abbreviation
    per_bit_rw1_t Da; ///< DMA Arbitration
    per_bit_rw5_t Dsl; ///< Descriptor skip length
    per_bit_rw1_t Edfe; ///< Enhanced descriptor format enable
    per_bit_rw6_t Pbl; ///< Programmable burst length
    per_bit_rw2_t Pm; ///< Rx Tx priority ratio
    per_bit_rw1_t Fb; ///< Fixed burst
    per_bit_rw6_t Rdp; ///< Rx DMA PBL
    per_bit_rw1_t Usp; ///< Use separate PBL
    per_bit_rw1_t Fpm; ///< 4xPBL mode
    per_bit_rw1_t Aab; ///< Address-aligned beats
    per_bit_rw1_t Mb; ///< Mixed burst
    per_bit_n5_t BmrBit27; ///< Reserved

    // DMA transmit poll demand register (ETH_DMATPDR)
    per_bit_w32_reg_t Tpd; ///< Transmit poll demand

    // DMA receive poll demand register (ETH_DMARPDR)
    per_bit_w32_reg_t Rpd; ///< Receive poll demand

    // DMA receive descriptor list address register (ETH_DMARDLAR)
    per_bit_rw32_reg_t Srl; ///< Start of receive list

    // DMA transmit descriptor list address register (ETH_DMATDLAR)
    per_bit_rw32_reg_t Stl; ///< Start of transmit list

    // DMA status register (ETH_DMASR)
    union
    {
        struct
        {
            per_bit_rc1_w1_t Ts; ///< Transmit status
            per_bit_rc1_w1_t Tpss; ///< Transmit process stopped status
            per_bit_rc1_w1_t Tbus; ///< Transmit buffer unavailable status
            per_bit_rc1_w1_t Tjts; ///< Transmit jabber timeout status
            per_bit_rc1_w1_t Ros; ///< Receive overflow status
            per_bit_rc1_w1_t Tus; ///< Transmit underflow status
            per_bit_rc1_w1_t Rs; ///< Receive status
            per_bit_rc1_w1_t Rbus; ///< Receive buffer unavailable status
            per_bit_rc1_w1_t Rpss; ///< Receive process stopped status
            per_bit_rc1_w1_t Rwts; ///< Receive watchdog timeout status
            per_bit_rc1_w1_t Ets; ///< Early transmit status
            per_bit_n2_t SrBit11; ///< Reserved
            per_bit_rc1_w1_t Fbes; ///< Fatal bus error status
            per_bit_rc1_w1_t Ers; ///< Early receive status
            per_bit_rc1_w1_t Ais; ///< Abnormal interrupt summary
            per_bit_rc1_w1_t Nis; ///< Normal interrupt summary
            per_bit_r3_t Rps; ///< Receive process state
            per_bit_r3_t Tps; ///< Transmit process state
            per_bit_r3_t Ebs; ///< Error bits status
            per_bit_n1_t SrBit26; ///< Reserved
            per_bit_r1_t Mmcs; ///< MMC status
            per_bit_r1_t Pmts; ///< PMT status
            per_bit_r1_t Tsts; ///< Time stamp trigger status
            per_bit_n2_t SrBit30; ///< Reserved
        };
        per_bit_rw32_reg_t Sr; ///< DMA status register (ETH_DMASR)
    };

    // DMA operation mode register (ETH_DMAOMR)
    per_bit_n1_t OmrBit0; ///< Reserved
    per_bit_rw1_t Ssr; ///< (Sr) Start/stop receive. Note duplicate abbreviation
    per_bit_rw1_t Osf; ///< Operate on second frame
    per_bit_rw2_t Rtc; ///< Receive threshold control
    per_bit_n1_t OmrBit5; ///< Reserved
    per_bit_rw1_t Fugf; ///< Forward undersized good frames
    per_bit_rw1_t Fef; ///< Forward error frames
    per_bit_n5_t OmrBit8; ///< Reserved
    per_bit_rw1_t St; ///< Start/stop transmission
    per_bit_rw3_t Ttc; ///< Transmit threshold control
    per_bit_n3_t OmrBit17; ///< Reserved
    per_bit_rw1_t Ftf; ///< Flush transmit FIFO
    per_bit_rs1_t Tsf; ///< Transmit store and forward
    per_bit_n2_t OmrBit22; ///< Reserved
    per_bit_rw1_t Dfrf; ///< Disable flushing of received frames
    per_bit_rw1_t Rsf; ///< Receive store and forward
    per_bit_rw1_t Dtcefd; ///< Dropping of TCP/IP checksum error frames disable
    per_bit_n5_t OmrBit27; ///< Reserved

    // DMA interrupt enable register (ETH_DMAIER)
    union
    {
        struct
        {
            per_bit_rw1_t Tie; ///< Transmit interrupt enable
            per_bit_rw1_t Tpsie; ///< Transmit process stopped interrupt enable
            per_bit_rw1_t Tbuie; ///< Transmit buffer unavailable interrupt enable
            per_bit_rw1_t Tjtie; ///< Transmit jabber timeout interrupt enable
            per_bit_rw1_t Roie; ///< Overflow interrupt enable
            per_bit_rw1_t Tuie; ///< Underflow interrupt enable
            per_bit_rw1_t Rie; ///< Receive interrupt enable
            per_bit_rw1_t Rbuie; ///< Receive buffer unavailable interrupt enable
            per_bit_rw1_t Rpsie; ///< Receive process stopped interrupt enable
            per_bit_rw1_t Rwtie; ///< Receive watchdog timeout interrupt enable
            per_bit_rw1_t Etie; ///< Early transmit interrupt enable
            per_bit_n2_t DierBit11; ///< Reserved
            per_bit_rw1_t Fbeie; ///< Fatal bus error interrupt enable
            per_bit_rw1_t Erie; ///< Early receive interrupt enable
            per_bit_rw1_t Aise; ///< Abnormal interrupt summary enable
            per_bit_rw1_t Nise; ///< Normal interrupt summary enable
            per_bit_n15_t DierBit17; ///< Reserved
        };
        per_bit_rw32_reg_t Dier; ///< DMA interrupt enable register (ETH_DMAIER)
    };

    // DMA missed frame and buffer overflow counter register (ETH_DMAMFBOCR)
    union
    {
        struct
        {
            per_bit_r16_t Mfc; ///< Missed frames by the controller
            per_bit_r1_t Omfc; ///< Overflow bit for missed frame counter
            per_bit_r11_t Mfa; ///< Missed frames by the application
            per_bit_r1_t Omfa; ///< Overflow bit for FIFO overflow counter
            per_bit_n3_t MfbocrBit29; ///< Reserved
        };
        per_bit_r32_reg_t Mfbocr; ///< DMA missed frame and buffer overflow counter register (ETH_DMAMFBOCR)
    };

    // DMA receive status watchdog timer register (ETH_DMARSWTR)
    per_bit_rw8_t Rswtc; ///< Receive status (RS) watchdog timer count
    per_bit_n24_t RswtrBit8; ///< Reserved

    // DMA current host transmit descriptor register (ETH_DMACHTDR)
    per_bit_r32_reg_t Htdap; ///< Host transmit descriptor address pointer

    // DMA current host receive descriptor register (ETH_DMACHRDR)
    per_bit_r32_reg_t Hrdap; ///< Host receive descriptor address pointer

    // DMA current host transmit buffer address register (ETH_DMACHTBAR)
    per_bit_r32_reg_t Htbap; ///< Host transmit buffer address pointer

    // DMA current host receive buffer address register (ETH_DMACHRBAR)
    per_bit_r32_reg_t Hrbap; ///< Host receive buffer address pointer

} per_eth_dma_t;

/// ETH descriptor
typedef struct
{
    per_eth_mac_t* const PerMac; ///< Peripheral MAC
    per_eth_mmc_t* const PerMmc; ///< Peripheral MMC
    per_eth_ptp_t* const PerPtp; ///< Peripheral PTP
    per_eth_dma_t* const PerDma; ///< Peripheral DMA
    const per_log_e Err;         ///< Peripheral error number
} per_eth_t;

/// ETH Receiver enable
static per_inline bool per_eth_mac_re(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Re);
}

/// ETH Receiver enable
static per_inline void per_eth_mac_set_re(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Re, val);
}

/// ETH Transmitter enable
static per_inline bool per_eth_mac_te(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Te);
}

/// ETH Transmitter enable
static per_inline void per_eth_mac_set_te(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Te, val);
}

/// ETH Deferral check
static per_inline bool per_eth_mac_dc(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Dc);
}

/// ETH Deferral check
static per_inline void per_eth_mac_set_dc(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Dc, val);
}

/// ETH Back-off limit
static per_inline per_eth_bl_e per_eth_mac_bl(const per_eth_t* const eth)
{
    return (per_eth_bl_e)per_bit_rw2(&eth->PerMac->Bl);
}

/// ETH Back-off limit
static per_inline void per_eth_mac_set_bl(const per_eth_t* const eth, per_eth_bl_e val)
{
    per_bit_rw2_set(&eth->PerMac->Bl, (uint_fast8_t)val);
}

/// ETH Automatic pad/CRC stripping
static per_inline bool per_eth_mac_acps(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Acps);
}

/// ETH Automatic pad/CRC stripping
static per_inline void per_eth_mac_set_acps(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Acps, val);
}

/// ETH Retry disable
static per_inline bool per_eth_mac_rd(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Rd);
}

/// ETH Retry disable
static per_inline void per_eth_mac_set_rd(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Rd, val);
}

/// ETH IPv4 checksum offload
static per_inline bool per_eth_mac_ipco(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Ipco);
}

/// ETH IPv4 checksum offload
static per_inline void per_eth_mac_set_ipco(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Ipco, val);
}

/// ETH Duplex mode
static per_inline bool per_eth_mac_dm(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Dm);
}

/// ETH Duplex mode
static per_inline void per_eth_mac_set_dm(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Dm, val);
}

/// ETH Loopback mode
static per_inline bool per_eth_mac_lm(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Lm);
}

/// ETH Loopback mode
static per_inline void per_eth_mac_set_lm(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Lm, val);
}

/// ETH Receive own disable
static per_inline bool per_eth_mac_rod(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Rod);
}

/// ETH Receive own disable
static per_inline void per_eth_mac_set_rod(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Rod, val);
}

/// ETH Fast Ethernet speed
static per_inline bool per_eth_mac_fes(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Fes);
}

/// ETH Fast Ethernet speed
static per_inline void per_eth_mac_set_fes(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Fes, val);
}

/// ETH Carrier sense disable
static per_inline bool per_eth_mac_csd(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Csd);
}

/// ETH Carrier sense disable
static per_inline void per_eth_mac_set_csd(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Csd, val);
}

/// ETH Interframe gap
static per_inline per_eth_ifg_e per_eth_mac_ifg(const per_eth_t* const eth)
{
    return (per_eth_ifg_e)per_bit_rw3(&eth->PerMac->Ifg);
}

/// ETH Interframe gap
static per_inline void per_eth_mac_set_ifg(const per_eth_t* const eth, per_eth_ifg_e val)
{
    per_bit_rw3_set(&eth->PerMac->Ifg, (uint_fast16_t)val);
}

/// ETH Jabber disable
static per_inline bool per_eth_mac_jd(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Jd);
}

/// ETH Jabber disable
static per_inline void per_eth_mac_set_jd(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Jd, val);
}

/// ETH Watchdog disable
static per_inline bool per_eth_mac_wd(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Wd);
}

/// ETH Watchdog disable
static per_inline void per_eth_mac_set_wd(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Wd, val);
}

/// ETH CRC stripping for Type frames
static per_inline bool per_eth_mac_cstf(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Cstf);
}

/// ETH CRC stripping for Type frames
static per_inline void per_eth_mac_set_cstf(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Cstf, val);
}

/// ETH Promiscuous mode
static per_inline bool per_eth_mac_pm(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Pm);
}

/// ETH Promiscuous mode
static per_inline void per_eth_mac_set_pm(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Pm, val);
}

/// ETH Hash unicast
static per_inline bool per_eth_mac_hu(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Hu);
}

/// ETH Hash unicast
static per_inline void per_eth_mac_set_hu(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Hu, val);
}

/// ETH Hash multicast
static per_inline bool per_eth_mac_hm(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Hm);
}

/// ETH Hash multicast
static per_inline void per_eth_mac_set_hm(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Hm, val);
}

/// ETH Destination address inverse filtering
static per_inline bool per_eth_mac_daif(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Daif);
}

/// ETH Destination address inverse filtering
static per_inline void per_eth_mac_set_daif(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Daif, val);
}

/// ETH Pass all multicast
static per_inline bool per_eth_mac_pam(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Pam);
}

/// ETH Pass all multicast
static per_inline void per_eth_mac_set_pam(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Pam, val);
}

/// ETH Broadcast frames disable
static per_inline bool per_eth_mac_bfd(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Bfd);
}

/// ETH Broadcast frames disable
static per_inline void per_eth_mac_set_bfd(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Bfd, val);
}

/// ETH Pass control frames
static per_inline per_eth_pcf_e per_eth_mac_pcf(const per_eth_t* const eth)
{
    return (per_eth_pcf_e)per_bit_rw2(&eth->PerMac->Pcf);
}

/// ETH Pass control frames
static per_inline void per_eth_mac_set_pcf(const per_eth_t* const eth, per_eth_pcf_e val)
{
    per_bit_rw2_set(&eth->PerMac->Pcf, (uint_fast16_t)val);
}

/// ETH< Source address inverse filtering
static per_inline bool per_eth_mac_saif(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Saif);
}

/// ETH< Source address inverse filtering
static per_inline void per_eth_mac_set_saif(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Saif, val);
}

/// ETH Source address filter
static per_inline bool per_eth_mac_saf(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Saf);
}

/// ETH Source address filter
static per_inline void per_eth_mac_set_saf(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Saf, val);
}

/// ETH Hash or perfect filter
static per_inline bool per_eth_mac_hpf(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Hpf);
}

/// ETH Hash or perfect filter
static per_inline void per_eth_mac_set_hpf(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Hpf, val);
}

/// ETH Receive all
static per_inline bool per_eth_mac_ra(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Ra);
}

/// ETH Receive all
static per_inline void per_eth_mac_set_ra(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Ra, val);
}

/// ETH Hash table high
static per_inline uint_fast32_t per_eth_mac_hth(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->PerMac->Hth);
}

/// ETH Hash table high
static per_inline void per_eth_mac_set_hth(const per_eth_t* const eth, uint32_t val)
{
    per_bit_rw32_reg_set(&eth->PerMac->Hth, val);
}

/// ETH Hash table low
static per_inline uint_fast32_t per_eth_mac_htl(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->PerMac->Htl);
}

/// ETH Hash table low
static per_inline void per_eth_mac_set_htl(const per_eth_t* const eth, uint32_t val)
{
    per_bit_rw32_reg_set(&eth->PerMac->Htl, val);
}

/// ETH MII busy
static per_inline bool per_eth_mac_mb(const per_eth_t* const eth)
{
    return per_bit_rs1(&eth->PerMac->Mb);
}

/// ETH MII busy
static per_inline void per_eth_mac_clr_mb(const per_eth_t* const eth)
{
    per_bit_rs1_set(&eth->PerMac->Mb);
}

/// ETH MII write
static per_inline bool per_eth_mac_mw(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerMac->Mw);
}

/// ETH MII write
static per_inline void per_eth_mac_set_mw(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerMac->Mw, val);
}

/// ETH Clock range
static per_inline per_eth_cr_e per_eth_mac_cr(const per_eth_t* const eth)
{
    return (per_eth_cr_e)per_bit_rw3(&eth->PerMac->Cr);
}

/// ETH Clock range
static per_inline void per_eth_mac_set_cr(const per_eth_t* const eth, per_eth_cr_e val)
{
    per_bit_rw3_set(&eth->PerMac->Cr, (uint_fast16_t)val);
}

/// ETH MII register
static per_inline uint_fast16_t per_eth_mac_mr(const per_eth_t* const eth)
{
    return per_bit_rw5(&eth->PerMac->Mr);
}

/// ETH MII register
static per_inline void per_eth_mac_set_mr(const per_eth_t* const eth, uint_fast16_t val)
{
    per_bit_rw5_set(&eth->PerMac->Mr, val);
}

/// ETH PHY address
static per_inline uint_fast16_t per_eth_mac_pa(const per_eth_t* const eth)
{
    return per_bit_rw5(&eth->PerMac->Pa);
}

/// ETH PHY address
static per_inline void per_eth_mac_set_pa(const per_eth_t* const eth, uint_fast16_t val)
{
    per_bit_rw5_set(&eth->PerMac->Pa, val);
}

/// ETH MII address register
static per_inline uint_fast16_t per_eth_mac_miiar(const per_eth_t* const eth)
{
    return per_bit_rw16_reg(&eth->PerMac->Miiar);
}

/// ETH MII address register
static per_inline void per_eth_mac_set_miiar(const per_eth_t* const eth, uint16_t val)
{
    per_bit_rw16_reg_set(&eth->PerMac->Miiar, val);
}

/// ETH MII write address register
static per_inline void per_eth_mac_miiar_write(const per_eth_t* const eth, uint_fast16_t reg, uint_fast16_t addr)
{
    per_eth_mac_t* const per = eth->PerMac;
    uint16_t val = per_bit_rw5_mask(&per->Mr) & (reg << per_bit_rw5_shift(&per->Mr));

    val |= per_bit_rw5_mask(&per->Pa) & (addr << per_bit_rw5_shift(&per->Pa));
    val |= per_bit_rw1_mask(&per->Mw); // set write bit
    val |= per_bit_rw16_reg(&eth->PerMac->Miiar) & per_bit_rw3_mask(&per->Cr); // Save the clock range

    per_bit_rw16_reg_set(&per->Miiar, val);
}

/// ETH MII data register
static per_inline uint_fast16_t per_eth_mac_md(const per_eth_t* const eth)
{
    return per_bit_rw16_reg(&eth->PerMac->Md);
}

/// ETH MII data register
static per_inline void per_eth_mac_set_md(const per_eth_t* const eth, uint16_t val)
{
    per_bit_rw16_reg_set(&eth->PerMac->Md, val);
}

/// ETH Flow control busy/back pressure activate
static per_inline bool per_eth_mac_fcb(const per_eth_t* const eth)
{
   return per_bit_rs1(&eth->PerMac->Fcb);
}

/// ETH Flow control busy/back pressure activate
static per_inline void per_eth_mac_clr_fcb(const per_eth_t* const eth)
{
   per_bit_rs1_set(&eth->PerMac->Fcb);
}

/// ETH Transmit flow control enable
static per_inline bool per_eth_mac_tfce(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMac->Tfce);
}

/// ETH Transmit flow control enable
static per_inline void per_eth_mac_set_tfce(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMac->Tfce, val);
}

/// ETH Receive flow control enable
static per_inline bool per_eth_mac_rfce(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMac->Rfce);
}

/// ETH Receive flow control enable
static per_inline void per_eth_mac_set_rfce(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMac->Rfce, val);
}

/// ETH Unicast pause frame detect
static per_inline bool per_eth_mac_upfd(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMac->Upfd);
}

/// ETH Unicast pause frame detect
static per_inline void per_eth_mac_set_upfd(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMac->Upfd, val);
}

/// ETH Pause low threshold
static per_inline uint_fast16_t per_eth_mac_plt(const per_eth_t* const eth)
{
    return per_bit_rw2(&eth->PerMac->Plt);
}

/// ETH Pause low threshold
static per_inline void per_eth_mac_set_plt(const per_eth_t* const eth, uint16_t val)
{
    per_bit_rw2_set(&eth->PerMac->Plt, val);
}

/// ETH Zero-quanta pause disable
static per_inline bool per_eth_mac_zqpd(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMac->Zqpd);
}

/// ETH Zero-quanta pause disable
static per_inline void per_eth_mac_set_zqpd(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMac->Zqpd, val);
}

/// ETH Pause time
static per_inline uint_fast16_t per_eth_mac_pt(const per_eth_t* const eth)
{
    return per_bit_rw16(&eth->PerMac->Pt);
}

/// ETH Pause time
static per_inline void per_eth_mac_set_pt(const per_eth_t* const eth, uint16_t val)
{
    per_bit_rw16_set(&eth->PerMac->Pt, val);
}

/// ETH VLAN tag identifier (for receive frames)
static per_inline uint_fast16_t per_eth_mac_vlanti(const per_eth_t* const eth)
{
    return per_bit_rw16(&eth->PerMac->Vlanti);
}

/// ETH VLAN tag identifier (for receive frames)
static per_inline void per_eth_mac_set_vlanti(const per_eth_t* const eth, uint16_t val)
{
    per_bit_rw16_set(&eth->PerMac->Vlanti, val);
}

/// ETH 12-bit VLAN tag comparison
static per_inline bool per_eth_mac_vlantc(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMac->Vlantc);
}

/// ETH 12-bit VLAN tag comparison
static per_inline void per_eth_mac_set_vlantc(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMac->Vlantc, val);
}

/// remote wakeup frame filter register
static per_inline uint_fast16_t per_eth_mac_rwuffr(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->PerMac->Rwuffr);
}

/// remote wakeup frame filter register
static per_inline void per_eth_mac_set_rwuffr(const per_eth_t* const eth, uint16_t val)
{
    per_bit_rw32_reg_set(&eth->PerMac->Rwuffr, val);
}

/// ETH Macpmtcsr update
uint32_t per_eth_mac_macpmtcsr(const per_eth_t* const eth);

/// ETH Macpmtcsr set bit. Note not-atomic.
static per_inline void per_eth_mac_set_macpmtcsr(const per_eth_t* const eth,
                                             per_eth_pmtcsr_e bit,
                                             bool val)
{
    uint32_t macpmtcsr = per_eth_mac_macpmtcsr(eth);

    if (val)
    {
        macpmtcsr |= bit;
    }
    else
    {
        macpmtcsr &= ~bit;
    }

    per_bit_rw32_reg_set(&eth->PerMac->Macpmtcsr, macpmtcsr);
}

/// ETH Power down
static per_inline bool per_eth_mac_pd(const per_eth_t* const eth)
{
   return (per_eth_mac_macpmtcsr(eth) & PER_ETH_PMTCSR_PD) != 0;
}

/// ETH Power down. Note not-atomic.
static per_inline void per_eth_mac_set_pd(const per_eth_t* const eth)
{
    per_eth_mac_set_macpmtcsr(eth, PER_ETH_PMTCSR_PD, true);
}

/// ETH Wakeup frame enable
static per_inline bool per_eth_mac_wfe(const per_eth_t* const eth)
{
   return (per_eth_mac_macpmtcsr(eth) & PER_ETH_PMTCSR_WFE) != 0;
}

/// ETH Wakeup frame enable. Note not-atomic.
static per_inline void per_eth_mac_set_wfe(const per_eth_t* const eth, bool val)
{
    per_eth_mac_set_macpmtcsr(eth, PER_ETH_PMTCSR_WFE, val);
}

/// ETH Magic Packet enable
static per_inline bool per_eth_mac_mpe(const per_eth_t* const eth)
{
   return (per_eth_mac_macpmtcsr(eth) & PER_ETH_PMTCSR_MPE) != 0;
}

/// ETH Magic Packet enable. Note not-atomic.
static per_inline void per_eth_mac_set_mpe(const per_eth_t* const eth, bool val)
{
    per_eth_mac_set_macpmtcsr(eth, PER_ETH_PMTCSR_MPE, val);
}

/// ETH Magic packet received
bool per_eth_mac_wfr(const per_eth_t* const eth);

/// ETH Magic Packet received
bool per_eth_mac_mpr(const per_eth_t* const eth);

/// ETH Global unicast
static per_inline bool per_eth_mac_gu(const per_eth_t* const eth)
{
   return (per_eth_mac_macpmtcsr(eth) & PER_ETH_PMTCSR_GU) != 0;
}

/// ETH Global unicast. Note not-atomic.
static per_inline void per_eth_mac_set_gu(const per_eth_t* const eth, bool val)
{
    per_eth_mac_set_macpmtcsr(eth, PER_ETH_PMTCSR_GU, val);
}

/// ETH Wakeup frame filter register pointer reset. Note not-atomic.
static per_inline void per_eth_mac_set_wfrpr(const per_eth_t* const eth)
{
    per_eth_mac_set_macpmtcsr(eth, PER_ETH_PMTCSR_WFFRPR, true);
}

/// ETH MAC MII receive protocol engine active
static per_inline bool per_eth_mac_mmrpea(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMac->Mmrpea);
}

/// ETH MAC small FIFO read / write controllers status
static per_inline per_eth_msfrwcs_e per_eth_mac_msfrwcs(const per_eth_t* const eth)
{
    return (per_eth_msfrwcs_e)per_bit_r2(&eth->PerMac->Msfrwcs);
}

/// ETH Rx FIFO write controller active
static per_inline bool per_eth_mac_rfwra(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMac->Rfwra);
}

/// ETH Rx FIFO read controller status
static per_inline per_eth_rfrcs_e per_eth_mac_rfrcs(const per_eth_t* const eth)
{
    return (per_eth_rfrcs_e)per_bit_r2(&eth->PerMac->Rfrcs);
}

/// ETH Rx FIFO fill level
static per_inline per_eth_rffl_e per_eth_mac_rffl(const per_eth_t* const eth)
{
    return (per_eth_rffl_e)per_bit_r2(&eth->PerMac->Rffl);
}

/// ETH MAC MII transmit engine active
static per_inline bool per_eth_mac_mmtea(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMac->Mmtea);
}

/// ETH MAC transmit frame controller status
static per_inline per_eth_mtfcs_e per_eth_mac_mtfcs(const per_eth_t* const eth)
{
    return (per_eth_mtfcs_e)per_bit_r2(&eth->PerMac->Mtfcs);
}

/// ETH MAC transmitter in pause
static per_inline bool per_eth_mac_mtp(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMac->Mtp);
}

/// ETH Tx FIFO read status
static per_inline per_eth_tfrs_e per_eth_mac_tfrs(const per_eth_t* const eth)
{
    return (per_eth_tfrs_e)per_bit_r2(&eth->PerMac->Tfrs);
}

/// ETH Tx FIFO write active
static per_inline bool per_eth_mac_tfwa(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMac->Tfwa);
}

/// ETH Tx FIFO not empty
static per_inline bool per_eth_mac_tfne(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMac->Tfne);
}

/// ETH Tx FIFO full
static per_inline bool per_eth_mac_tff(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMac->Tff);
}

/// ETH PMT status
static per_inline bool per_eth_mac_pmts(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMac->Pmts);
}

/// ETH MMC status
static per_inline bool per_eth_mac_mmcs(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMac->Mmcs);
}

/// ETH MMC receive status
static per_inline bool per_eth_mac_mmcrs(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMac->Mmcrs);
}

/// ETH MMC transmit status
static per_inline bool per_eth_mac_mmcts(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMac->Mmcts);
}

/// ETH Time stamp trigger status
static per_inline bool per_eth_mac_tsts(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMac->Tsts);
}

/// ETH PMT interrupt mask
static per_inline bool per_eth_mac_pmtim(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMac->Pmtim);
}

/// ETH PMT interrupt mask
static per_inline void per_eth_mac_set_pmtim(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMac->Pmtim, val);
}

/// ETH Time stamp trigger interrupt mask
static per_inline bool per_eth_mac_tstim(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMac->Tstim);
}

/// ETH Time stamp trigger interrupt mask
static per_inline void per_eth_mac_set_tstim(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMac->Tstim, val);
}

/// ETH MAC address0 high [47:32]
static per_inline uint_fast16_t per_eth_mac_maca0h(const per_eth_t* const eth)
{
    return per_bit_rw16(&eth->PerMac->Maca0h);
}

/// ETH MAC address0 high [47:32]
static per_inline void per_eth_mac_set_maca0h(const per_eth_t* const eth, uint16_t val)
{
    per_bit_rw16_set(&eth->PerMac->Maca0h, val);
}

/// ETH MAC address0 low [31:0]
static per_inline uint32_t per_eth_mac_maca0l(const per_eth_t* const eth)
{
   return per_bit_rw32_reg(&eth->PerMac->Maca0l);
}

/// ETH MAC address0 low [31:0]
static per_inline void per_eth_mac_set_maca0l(const per_eth_t* const eth, uint32_t val)
{
   per_bit_rw32_reg_set(&eth->PerMac->Maca0l, val);
}

/// ETH MAC address1 high [47:32]
static per_inline uint_fast16_t per_eth_mac_maca1h(const per_eth_t* const eth)
{
    return per_bit_rw16(&eth->PerMac->Maca1h);
}

/// ETH MAC address1 high [47:32]
static per_inline void per_eth_mac_set_maca1h(const per_eth_t* const eth, uint16_t val)
{
    per_bit_rw16_set(&eth->PerMac->Maca1h, val);
}

/// ETH Mask byte control
static per_inline bool per_eth_mac_mbc1(const per_eth_t* const eth)
{
   return per_bit_rw6(&eth->PerMac->Mbc1);
}

/// ETH Mask byte control
static per_inline void per_eth_mac_set_mbc1(const per_eth_t* const eth, bool val)
{
   per_bit_rw6_set(&eth->PerMac->Mbc1, val);
}

/// ETH Source address
static per_inline bool per_eth_mac_sa1(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMac->Sa1);
}

/// ETH Source address
static per_inline void per_eth_mac_set_sa1(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMac->Sa1, val);
}

/// ETH Address enable
static per_inline bool per_eth_mac_ae1(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMac->Ae1);
}

/// ETH Address enable
static per_inline void per_eth_mac_set_ae1(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMac->Ae1, val);
}

/// ETH MAC address1 low [31:0]
static per_inline uint32_t per_eth_mac_maca1l(const per_eth_t* const eth)
{
   return per_bit_rw32_reg(&eth->PerMac->Maca1l);
}

/// ETH MAC address1 low [31:0]
static per_inline void per_eth_mac_set_maca1l(const per_eth_t* const eth, uint32_t val)
{
   per_bit_rw32_reg_set(&eth->PerMac->Maca1l, val);
}

/// ETH MAC address2 high [47:32]
static per_inline uint_fast16_t per_eth_mac_maca2h(const per_eth_t* const eth)
{
    return per_bit_rw16(&eth->PerMac->Maca2h);
}

/// ETH MAC address2 high [47:32]
static per_inline void per_eth_mac_set_maca2h(const per_eth_t* const eth, uint16_t val)
{
    per_bit_rw16_set(&eth->PerMac->Maca2h, val);
}

/// ETH Mask byte control
static per_inline bool per_eth_mac_mbc2(const per_eth_t* const eth)
{
   return per_bit_rw6(&eth->PerMac->Mbc2);
}

/// ETH Mask byte control
static per_inline void per_eth_mac_set_mbc2(const per_eth_t* const eth, bool val)
{
   per_bit_rw6_set(&eth->PerMac->Mbc2, val);
}

/// ETH Source address
static per_inline bool per_eth_mac_sa2(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMac->Sa2);
}

/// ETH Source address
static per_inline void per_eth_mac_set_sa2(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMac->Sa2, val);
}

/// ETH Address enable
static per_inline bool per_eth_mac_ae2(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMac->Ae2);
}

/// ETH Address enable
static per_inline void per_eth_mac_set_ae2(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMac->Ae2, val);
}

/// ETH MAC address2 low [31:0]
static per_inline uint32_t per_eth_mac_maca2l(const per_eth_t* const eth)
{
   return per_bit_rw32_reg(&eth->PerMac->Maca2l);
}

/// ETH MAC address2 low [31:0]
static per_inline void per_eth_mac_set_maca2l(const per_eth_t* const eth, uint32_t val)
{
   per_bit_rw32_reg_set(&eth->PerMac->Maca2l, val);
}

/// ETH MAC address3 high [47:32]
static per_inline uint_fast16_t per_eth_mac_maca3h(const per_eth_t* const eth)
{
    return per_bit_rw16(&eth->PerMac->Maca3h);
}

/// ETH MAC address3 high [47:32]
static per_inline void per_eth_mac_set_maca3h(const per_eth_t* const eth, uint16_t val)
{
    per_bit_rw16_set(&eth->PerMac->Maca3h, val);
}

/// ETH Mask byte control
static per_inline bool per_eth_mac_mbc3(const per_eth_t* const eth)
{
   return per_bit_rw6(&eth->PerMac->Mbc3);
}

/// ETH Mask byte control
static per_inline void per_eth_mac_set_mbc3(const per_eth_t* const eth, bool val)
{
   per_bit_rw6_set(&eth->PerMac->Mbc3, val);
}

/// ETH Source address
static per_inline bool per_eth_mac_sa3(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMac->Sa3);
}

/// ETH Source address
static per_inline void per_eth_mac_set_sa3(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMac->Sa3, val);
}

/// ETH Address enable
static per_inline bool per_eth_mac_ae3(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMac->Ae3);
}

/// ETH Address enable
static per_inline void per_eth_mac_set_ae3(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMac->Ae3, val);
}

/// ETH MAC address3 low [31:0]
static per_inline uint32_t per_eth_mac_maca3l(const per_eth_t* const eth)
{
   return per_bit_rw32_reg(&eth->PerMac->Maca3l);
}

/// ETH MAC address3 low [31:0]
static per_inline void per_eth_mac_set_maca3l(const per_eth_t* const eth, uint32_t val)
{
   per_bit_rw32_reg_set(&eth->PerMac->Maca3l, val);
}

/// Counter reset
static per_inline bool per_eth_mmc_cr(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMmc->Cr);
}

/// Counter reset
static per_inline void per_eth_mmc_set_cr(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMmc->Cr, val);
}

/// Counter stop rollover
static per_inline bool per_eth_mmc_csr(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMmc->Csr);
}

/// Counter stop rollover
static per_inline void per_eth_mmc_set_csr(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMmc->Csr, val);
}

/// Reset on read
static per_inline bool per_eth_mmc_ror(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMmc->Ror);
}

/// Reset on read
static per_inline void per_eth_mmc_set_ror(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMmc->Ror, val);
}

/// MMC counter freeze
static per_inline bool per_eth_mmc_mcf(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMmc->Mcf);
}

/// MMC counter freeze
static per_inline void per_eth_mmc_set_mcf(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMmc->Mcf, val);
}

/// MMC counter preset
static per_inline bool per_eth_mmc_mcp(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMmc->Mcp);
}

/// MMC counter preset
static per_inline void per_eth_mmc_set_mcp(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMmc->Mcp, val);
}

/// MMC counter Full-Half preset
static per_inline bool per_eth_mmc_mcfhp(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMmc->Mcfhp);
}

/// MMC counter Full-Half preset
static per_inline void per_eth_mmc_set_mcfhp(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMmc->Mcfhp, val);
}

/// Received frames CRC error status
static per_inline bool per_eth_mmc_rfces(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMmc->Rfces);
}

/// Received frames alignment error status
static per_inline bool per_eth_mmc_rfaes(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMmc->Rfaes);
}

/// Received Good Unicast Frames Status
static per_inline bool per_eth_mmc_rgufs(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMmc->Rgufs);
}

/// Transmitted good frames single collision status
static per_inline bool per_eth_mmc_tgfscs(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMmc->Tgfscs);
}

/// Transmitted good frames more single collision status
static per_inline bool per_eth_mmc_tgmscs(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMmc->Tgmscs);
}

/// Transmitted good frames status
static per_inline bool per_eth_mmc_tgfs(const per_eth_t* const eth)
{
   return per_bit_r1(&eth->PerMmc->Tgfs);
}

/// Received frame CRC error mask
static per_inline bool per_eth_mmc_rfcem(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMmc->Rfcem);
}

/// Received frame CRC error mask
static per_inline void per_eth_mmc_set_rfcem(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMmc->Rfcem, val);
}

/// Received frames alignment error mask
static per_inline bool per_eth_mmc_rfaem(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMmc->Rfaem);
}

/// Received frames alignment error mask
static per_inline void per_eth_mmc_set_rfaem(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMmc->Rfaem, val);
}

/// Received good unicast frames mask
static per_inline bool per_eth_mmc_rgufm(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMmc->Rgufm);
}

/// Received good unicast frames mask
static per_inline void per_eth_mmc_set_rgufm(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMmc->Rgufm, val);
}

///  Transmitted good frames single collision mask
static per_inline bool per_eth_mmc_tgfscm(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMmc->Tgfscm);
}

/// Transmitted good frames single collision mask
static per_inline void per_eth_mmc_set_tgfscm(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMmc->Tgfscm, val);
}

/// Transmitted good frames more single collision mask
static per_inline bool per_eth_mmc_tgfmscm(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMmc->Tgfmscm);
}

/// Transmitted good frames more single collision mask
static per_inline void per_eth_mmc_set_tgfmscm(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMmc->Tgfmscm, val);
}

/// Transmitted good frames mask
static per_inline bool per_eth_mmc_tgfm(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerMmc->Tgfm);
}

/// Transmitted good frames mask
static per_inline void per_eth_mmc_set_tgfm(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerMmc->Tgfm, val);
}

/// Transmitted good frames single collision counter
static per_inline uint_fast32_t per_eth_tgfscc(const per_eth_t* const eth)
{
   return per_bit_r32_reg(&eth->PerMmc->Tgfscc);
}

/// Transmitted good frames more single collision counter
static per_inline uint_fast32_t per_eth_tgfmscc(const per_eth_t* const eth)
{
   return per_bit_r32_reg(&eth->PerMmc->Tgfmscc);
}

/// Transmitted good frames counter
static per_inline uint_fast32_t per_eth_tgfc(const per_eth_t* const eth)
{
   return per_bit_r32_reg(&eth->PerMmc->Tgfc);
}

/// Received frames CRC error counter
static per_inline uint_fast32_t per_eth_rfcec(const per_eth_t* const eth)
{
   return per_bit_r32_reg(&eth->PerMmc->Rfcec);
}

/// Received frames alignment error counter
static per_inline uint_fast32_t per_eth_rfaec(const per_eth_t* const eth)
{
   return per_bit_r32_reg(&eth->PerMmc->Rfaec);
}

/// Received good unicast frames counter
static per_inline uint_fast32_t per_eth_rgufc(const per_eth_t* const eth)
{
   return per_bit_r32_reg(&eth->PerMmc->Rgufc);
}

/// Time stamp enable
static per_inline bool per_eth_ptp_tse(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerPtp->Tse);
}

/// Time stamp enable
static per_inline void per_eth_ptp_set_tse(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerPtp->Tse, val);
}

/// Time stamp fine or coarse update
static per_inline bool per_eth_ptp_tsfcu(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerPtp->Tsfcu);
}

/// Time stamp fine or coarse update
static per_inline void per_eth_ptp_set_tsfcu(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerPtp->Tsfcu, val);
}

/// Time stamp system time initialize
static per_inline bool per_eth_ptp_tssti(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerPtp->Tssti);
}

/// Time stamp system time initialize
static per_inline void per_eth_ptp_set_tssti(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerPtp->Tssti, val);
}

/// Time stamp system time update
static per_inline bool per_eth_ptp_tsstu(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerPtp->Tsstu);
}

/// Time stamp system time update
static per_inline void per_eth_ptp_set_tsstu(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerPtp->Tsstu, val);
}

/// Time stamp interrupt trigger enable
static per_inline bool per_eth_ptp_tsite(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerPtp->Tsite);
}

/// Time stamp interrupt trigger enable
static per_inline void per_eth_ptp_set_tsite(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerPtp->Tsite, val);
}

/// Time stamp addend register update
static per_inline bool per_eth_ptp_ttsaru(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerPtp->Ttsaru);
}

/// Time stamp addend register update
static per_inline void per_eth_ptp_set_ttsaru(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerPtp->Ttsaru, val);
}

/// Time stamp snapshot for all received frames enable
static per_inline bool per_eth_ptp_tssarfe(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerPtp->Tssarfe);
}

/// Time stamp snapshot for all received frames enable
static per_inline void per_eth_ptp_set_tssarfe(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerPtp->Tssarfe, val);
}

/// Time stamp subsecond rollover: digital or binary rollover control
static per_inline bool per_eth_ptp_tsssr(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerPtp->Tsssr);
}

/// Time stamp subsecond rollover: digital or binary rollover control
static per_inline void per_eth_ptp_set_tsssr(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerPtp->Tsssr, val);
}

/// Time stamp PTP packet snooping for version2 format enable
static per_inline bool per_eth_ptp_tsptppsv2e(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerPtp->Tsptppsv2e);
}

/// Time stamp PTP packet snooping for version2 format enable
static per_inline void per_eth_ptp_set_tsptppsv2e(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerPtp->Tsptppsv2e, val);
}

/// Time stamp snapshot for PTP over ethernet frames enable
static per_inline bool per_eth_ptp_tssptpoefe(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerPtp->Tssptpoefe);
}

/// Time stamp snapshot for PTP over ethernet frames enable
static per_inline void per_eth_ptp_set_tssptpoefe(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerPtp->Tssptpoefe, val);
}

/// Time stamp snapshot for IPv6 frames enable
static per_inline bool per_eth_ptp_tssipv6fe(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerPtp->Tssipv6fe);
}

/// Time stamp snapshot for IPv6 frames enable
static per_inline void per_eth_ptp_set_tssipv6fe(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerPtp->Tssipv6fe, val);
}

/// Time stamp snapshot for IPv4 frames enable
static per_inline bool per_eth_ptp_tssipv4fe(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerPtp->Tssipv4fe);
}

/// Time stamp snapshot for IPv4 frames enable
static per_inline void per_eth_ptp_set_tssipv4fe(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerPtp->Tssipv4fe, val);
}

/// Time stamp snapshot for event message enable
static per_inline bool per_eth_ptp_tsseme(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerPtp->Tsseme);
}

/// Time stamp snapshot for event message enable
static per_inline void per_eth_ptp_set_tsseme(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerPtp->Tsseme, val);
}

/// Time stamp snapshot for message relevant to master enable
static per_inline bool per_eth_ptp_tssmrme(const per_eth_t* const eth)
{
   return per_bit_rw1(&eth->PerPtp->Tssmrme);
}

/// Time stamp snapshot for message relevant to master enable
static per_inline void per_eth_ptp_set_tssmrme(const per_eth_t* const eth, bool val)
{
   per_bit_rw1_set(&eth->PerPtp->Tssmrme, val);
}

/// Time stamp clock node type
static per_inline per_eth_tscnt_e per_eth_ptp_tscnt(const per_eth_t* const eth)
{
    return (per_eth_tscnt_e)per_bit_rw2(&eth->PerPtp->Tscnt);
}

/// Time stamp clock node type
static per_inline void per_eth_ptp_set_tscnt(const per_eth_t* const eth, per_eth_tscnt_e val)
{
    per_bit_rw2_set(&eth->PerPtp->Tscnt, (uint_fast16_t)val);
}

/// Time stamp PTP frame filtering MAC address enable
static per_inline bool per_eth_ptp_tspffmae(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerPtp->Tspffmae);
}

/// Time stamp PTP frame filtering MAC address enable
static per_inline void per_eth_ptp_set_tspffmae(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerPtp->Tspffmae, val);
}

/// System time subsecond increment
static per_inline uint8_t per_eth_ptp_stssi(const per_eth_t* const eth)
{
    return per_bit_rw8_reg(&eth->PerPtp->Stssi);
}

/// System time subsecond increment
static per_inline void per_eth_ptp_set_stssi(const per_eth_t* const eth, uint8_t val)
{
    per_bit_rw8_reg_set(&eth->PerPtp->Stssi, val);
}

/// System time second
static per_inline uint32_t per_eth_ptp_sts(const per_eth_t* const eth)
{
    return per_bit_r32_reg(&eth->PerPtp->Sts);
}

/// System time subseconds
static per_inline int32_t per_eth_ptp_stss(const per_eth_t* const eth)
{
    return (int32_t)per_bit_r32_reg(&eth->PerPtp->Stss);
}

///Time stamp update second
static per_inline uint32_t per_eth_ptp_tsus(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->PerPtp->Tsus);
}

///Time stamp update second
static per_inline void per_eth_ptp_set_tsus(const per_eth_t* const eth, uint32_t val)
{
    per_bit_rw32_reg_set(&eth->PerPtp->Tsus, val);
}

/// Time stamp update subseconds
static per_inline int32_t per_eth_ptp_tsuss(const per_eth_t* const eth)
{
    return (int32_t)per_bit_rw32_reg(&eth->PerPtp->Tsuss);
}

/// Time stamp update subseconds
static per_inline void per_eth_ptp_set_tsuss(const per_eth_t* const eth, int32_t val)
{
    per_bit_rw32_reg_set(&eth->PerPtp->Tsuss, (uint32_t)val);
}

/// Time stamp addend
static per_inline uint32_t per_eth_ptp_tsa(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->PerPtp->Tsa);
}

/// Time stamp addend
static per_inline void per_eth_ptp_set_tsa(const per_eth_t* const eth, uint32_t val)
{
    per_bit_rw32_reg_set(&eth->PerPtp->Tsa, val);
}

/// Target time stamp high
static per_inline uint32_t per_eth_ptp_ttsh(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->PerPtp->Ttsh);
}

/// Target time stamp high
static per_inline void per_eth_ptp_set_ttsh(const per_eth_t* const eth, uint32_t val)
{
    per_bit_rw32_reg_set(&eth->PerPtp->Ttsh, val);
}

/// Target time stamp low
static per_inline uint32_t per_eth_ptp_ttsl(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->PerPtp->Ttsl);
}

/// Target time stamp low
static per_inline void per_eth_ptp_set_ttsl(const per_eth_t* const eth, uint32_t val)
{
    per_bit_rw32_reg_set(&eth->PerPtp->Ttsl, val);
}

/// Time stamp second overflow
static per_inline bool per_eth_ptp_tsso(const per_eth_t* const eth)
{
    return per_bit_r1(&eth->PerPtp->Tsso);
}

/// Time stamp target time reached
static per_inline bool per_eth_ptp_tsttr(const per_eth_t* const eth)
{
    return per_bit_r1(&eth->PerPtp->Tsttr);
}

/// PPS frequency selection
static per_inline uint_fast16_t per_eth_ptp_ppsfreq(const per_eth_t* const eth)
{
    return per_bit_inv_log2(per_bit_rw4(&eth->PerPtp->Ppsfreq));
}

/// PPS frequency selection
static per_inline bool per_eth_ptp_set_ppsfreq(const per_eth_t* const eth, uint_fast16_t val)
{
    if ((val > PER_ETH_PTP_PPSFREQ_MAX) ||
        !per_bit_is_log2(val))
    {
        per_log_err(eth->Err, PER_ETH_PTP_PPSFREQ_ERR, val);
        return false;
    }

    return per_bit_rw4_set(&eth->PerPtp->Ppsfreq, per_bit_log2(val));
}

/// Software reset
static per_inline bool per_eth_dma_sr1(const per_eth_t* const eth)
{
    return per_bit_rs1(&eth->PerDma->Sftr);
}

/// Software reset
static per_inline void per_eth_dma_set_sr1(const per_eth_t* const eth)
{
    per_bit_rs1_set(&eth->PerDma->Sftr);
}

/// DMA Arbitration
static per_inline bool per_eth_dma_da(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Da);
}

/// DMA Arbitration
static per_inline void per_eth_dma_set_da(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Da, val);
}

/// Descriptor skip length
static per_inline uint_fast16_t per_eth_dma_dsl(const per_eth_t* const eth)
{
    return per_bit_rw5(&eth->PerDma->Dsl);
}

/// Descriptor skip length
static per_inline bool per_eth_dma_set_dsl(const per_eth_t* const eth, uint16_t val)
{
    if (val > PER_ETH_DMA_DSL_MAX)
    {
        per_log_err(eth->Err, PER_ETH_DMA_DSL_ERR, val);
        return false;
    }

    return per_bit_rw5_set(&eth->PerDma->Dsl, val);
}

/// Enhanced descriptor format enable
static per_inline bool per_eth_dma_edfe(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Edfe);
}

/// Enhanced descriptor format enable
static per_inline void per_eth_dma_set_edfe(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Edfe, val);
}

/// Programmable burst length
static per_inline uint_fast16_t per_eth_dma_pbl(const per_eth_t* const eth)
{
    return per_bit_rw6(&eth->PerDma->Pbl);
}

/// Programmable burst length
static per_inline bool per_eth_dma_set_pbl(const per_eth_t* const eth, uint16_t val)
{
    if ((val > PER_ETH_DMA_PBL_MAX) ||
        !per_bit_is_log2(val))
    {
        per_log_err(eth->Err, PER_ETH_DMA_PBL_ERR, val);
        return false;
    }

    return per_bit_rw6_set(&eth->PerDma->Pbl, val);
}

/// Rx Tx priority ratio
static per_inline uint_fast16_t per_eth_dma_pm(const per_eth_t* const eth)
{
    return per_bit_rw2(&eth->PerDma->Pm) + 1;
}

/// Rx Tx priority ratio
static per_inline bool  per_eth_dma_set_pm(const per_eth_t* const eth, uint16_t val)
{
    if ((val > PER_ETH_DMA_PM_MAX) ||
        (val == 0))
    {
        per_log_err(eth->Err, PER_ETH_DMA_PM_ERR, val);
        return false;
    }

    return per_bit_rw2_set(&eth->PerDma->Pm, val - 1);
}

/// Fixed burst
static per_inline bool per_eth_dma_fb(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Fb);
}

/// Fixed burst
static per_inline void per_eth_dma_set_fb(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Fb, val);
}

/// Rx DMA PBL
static per_inline uint_fast16_t per_eth_dma_rdp(const per_eth_t* const eth)
{
    return per_bit_rw6(&eth->PerDma->Rdp);
}

/// Rx DMA PBL
static per_inline bool per_eth_dma_set_rdp(const per_eth_t* const eth, uint16_t val)
{
    if ((val > PER_ETH_DMA_RDP_MAX) ||
        !per_bit_is_log2(val))
    {
        per_log_err(eth->Err, PER_ETH_DMA_RDP_ERR, val);
        return false;
    }

    return per_bit_rw6_set(&eth->PerDma->Rdp, val);
}

/// Use separate PBL
static per_inline bool per_eth_dma_usp(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Usp);
}

/// Use separate PBL
static per_inline void per_eth_dma_set_usp(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Usp, val);
}

/// 4xPBL mode
static per_inline bool per_eth_dma_fpm(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Fpm);
}

/// 4xPBL mode
static per_inline void per_eth_dma_set_fpm(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Fpm, val);
}

/// Address-aligned beats
static per_inline bool per_eth_dma_aab(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Aab);
}

/// Address-aligned beats
static per_inline void per_eth_dma_set_aab(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Aab, val);
}

/// Mixed burst
static per_inline bool per_eth_dma_mb(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Mb);
}

/// Mixed burst
static per_inline void per_eth_dma_set_mb(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Mb, val);
}

/// Transmit poll demand
static per_inline void per_eth_dma_set_tpd(const per_eth_t* const eth)
{
    per_bit_w32_reg_set(&eth->PerDma->Tpd, 1);
}

/// Receive poll demand
static per_inline void per_eth_dma_set_rpd(const per_eth_t* const eth)
{
    per_bit_w32_reg_set(&eth->PerDma->Rpd, 1);
}

/// Start of receive list
static per_inline uint_fast32_t per_eth_dma_srl(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->PerDma->Srl);
}

/// Start of receive list
static per_inline void per_eth_dma_set_srl(const per_eth_t* const eth, uint32_t val)
{
    per_bit_rw32_reg_set(&eth->PerDma->Srl, val);
}

/// Start of transmit list
static per_inline uint_fast32_t per_eth_dma_stl(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->PerDma->Stl);
}

/// Start of transmit list
static per_inline void per_eth_dma_set_stl(const per_eth_t* const eth, uint32_t val)
{
    per_bit_rw32_reg_set(&eth->PerDma->Stl, val);
}

/// Status register (ETH_DMASR)
static per_inline uint_fast32_t per_eth_dma_sr(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->PerDma->Sr);
}

/// Status register (ETH_DMASR)
static per_inline void per_eth_dma_set_sr(const per_eth_t* const eth, uint32_t val)
{
    per_bit_rw32_reg_set(&eth->PerDma->Sr, val);
}

/// Transmit status
static per_inline bool per_eth_dma_ts(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Ts);
}

/// Transmit status
static per_inline bool per_eth_dma_clr_ts(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Ts);
}

/// Transmit process stopped status
static per_inline bool per_eth_dma_tpss(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Tpss);
}

/// Transmit process stopped status
static per_inline bool per_eth_dma_clr_tpss(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Tpss);
}

/// Transmit buffer unavailable status
static per_inline bool per_eth_dma_tbus(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Tbus);
}

/// Transmit buffer unavailable status
static per_inline bool per_eth_dma_clr_tbus(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Tbus);
}

/// Transmit jabber timeout status
static per_inline bool per_eth_dma_tjts(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Tjts);
}

/// Transmit jabber timeout status
static per_inline bool per_eth_dma_clr_tjts(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Tjts);
}

/// Receive overflow status
static per_inline bool per_eth_dma_ros(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Ros);
}

/// Receive overflow status
static per_inline bool per_eth_dma_clr_ros(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Ros);
}

/// Transmit underflow status
static per_inline bool per_eth_dma_tus(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Tus);
}

/// Transmit underflow status
static per_inline bool per_eth_dma_clr_tus(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Tus);
}

/// Receive status
static per_inline bool per_eth_dma_rs(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Rs);
}

/// Receive status
static per_inline bool per_eth_dma_clr_rs(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Rs);
}

/// Receive buffer unavailable status
static per_inline bool per_eth_dma_rbus(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Rbus);
}

/// Receive buffer unavailable status
static per_inline bool per_eth_dma_clr_rbus(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Rbus);
}

/// Receive process stopped status
static per_inline bool per_eth_dma_rpss(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Rpss);
}

/// Receive process stopped status
static per_inline bool per_eth_dma_clr_rpss(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Rpss);
}

/// Receive watchdog timeout status
static per_inline bool per_eth_dma_rwts(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Rwts);
}

/// Receive watchdog timeout status
static per_inline bool per_eth_dma_clr_rwts(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Rwts);
}

/// Early transmit status
static per_inline bool per_eth_dma_ets(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Ets);
}

/// Early transmit status
static per_inline bool per_eth_dma_clr_ets(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Ets);
}

/// Fatal bus error status
static per_inline bool per_eth_dma_fbes(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Fbes);
}

/// Fatal bus error status
static per_inline bool per_eth_dma_clr_fbes(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Fbes);
}

/// Early receive status
static per_inline bool per_eth_dma_ers(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Ers);
}

/// Early receive status
static per_inline bool per_eth_dma_clr_ers(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Ers);
}

/// Abnormal interrupt summary
static per_inline bool per_eth_dma_ais(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Ais);
}

/// Abnormal interrupt summary
static per_inline bool per_eth_dma_clr_ais(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Ais);
}

/// Normal interrupt summary
static per_inline bool per_eth_dma_nis(const per_eth_t* const eth)
{
    return per_bit_rc1_w1(&eth->PerDma->Nis);
}

/// Normal interrupt summary
static per_inline bool per_eth_dma_clr_nis(const per_eth_t* const eth)
{
    return per_bit_rc1_w1_rdclr(&eth->PerDma->Nis);
}

/// Receive process state
static per_inline per_eth_dma_rps_e per_eth_dma_rps(const per_eth_t* const eth)
{
    return (per_eth_dma_rps_e)per_bit_r3(&eth->PerDma->Rps);
}

/// Transmit process state
static per_inline per_eth_dma_tps_e per_eth_dma_tps(const per_eth_t* const eth)
{
    return (per_eth_dma_tps_e)per_bit_r3(&eth->PerDma->Tps);
}

/// Error bits status
static per_inline uint_fast16_t per_eth_dma_ebs(const per_eth_t* const eth)
{
    return per_bit_r3(&eth->PerDma->Ebs);
}

/// MMC status
static per_inline bool per_eth_dma_mmcs(const per_eth_t* const eth)
{
    return per_bit_r1(&eth->PerDma->Mmcs);
}

/// PMT status
static per_inline bool per_eth_dma_pmts(const per_eth_t* const eth)
{
    return per_bit_r1(&eth->PerDma->Pmts);
}

/// Time stamp trigger status
static per_inline bool per_eth_dma_tsts(const per_eth_t* const eth)
{
    return per_bit_r1(&eth->PerDma->Tsts);
}

/// (Sr) Start/stop receive. Note duplicate abbreviation
static per_inline bool per_eth_dma_ssr(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Ssr);
}

/// (Sr) Start/stop receive. Note duplicate abbreviation
static per_inline void per_eth_dma_set_ssr(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Ssr, val);
}

/// Operate on second frame
static per_inline bool per_eth_dma_osf(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Osf);
}

/// Operate on second frame
static per_inline void per_eth_dma_set_osf(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Osf, val);
}

/// Receive threshold control
static per_inline per_eth_dma_rtc_e per_eth_dma_rtc(const per_eth_t* const eth)
{
    return (per_eth_dma_rtc_e)per_bit_rw2(&eth->PerDma->Rtc);
}

/// Receive threshold control
static per_inline bool per_eth_dma_set_rtc(const per_eth_t* const eth, per_eth_dma_rtc_e val)
{
    return per_bit_rw2_set(&eth->PerDma->Rtc, (uint16_t)val);
}

/// Forward undersized good frames
static per_inline bool per_eth_dma_fugf(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Fugf);
}

/// Forward undersized good frames
static per_inline void per_eth_dma_set_fugf(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Fugf, val);
}

/// Forward error frames
static per_inline bool per_eth_dma_fef(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Fef);
}

/// Forward error frames
static per_inline void per_eth_dma_set_fef(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Fef, val);
}

/// Start/stop transmission
static per_inline bool per_eth_dma_st(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->St);
}

/// Start/stop transmission
static per_inline void per_eth_dma_set_st(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->St, val);
}

/// Transmit threshold control
static per_inline per_eth_dma_ttc_e per_eth_dma_ttc(const per_eth_t* const eth)
{
    return (per_eth_dma_ttc_e)per_bit_rw3(&eth->PerDma->Ttc);
}

/// Transmit threshold control
static per_inline bool per_eth_dma_set_ttc(const per_eth_t* const eth, per_eth_dma_ttc_e val)
{
    return per_bit_rw3_set(&eth->PerDma->Ttc, (uint16_t)val);
}

/// Flush transmit FIFO
static per_inline bool per_eth_dma_ftf(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Ftf);
}

/// Flush transmit FIFO
static per_inline void per_eth_dma_set_ftf(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Ftf, val);
}

/// Transmit store and forward
static per_inline bool per_eth_dma_tsf(const per_eth_t* const eth)
{
    return per_bit_rs1(&eth->PerDma->Tsf);
}

/// Transmit store and forward
static per_inline void per_eth_dma_set_tsf(const per_eth_t* const eth)
{
    per_bit_rs1_set(&eth->PerDma->Tsf);
}

/// Disable flushing of received frames
static per_inline bool per_eth_dma_dfrf(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Dfrf);
}

/// Disable flushing of received frames
static per_inline void per_eth_dma_set_dfrf(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Dfrf, val);
}

/// Receive store and forward
static per_inline bool per_eth_dma_rsf(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Rsf);
}

/// Receive store and forward
static per_inline void per_eth_dma_set_rsf(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Rsf, val);
}

/// Dropping of TCP/IP checksum error frames disable
static per_inline bool per_eth_dma_dtcefd(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Dtcefd);
}

/// Dropping of TCP/IP checksum error frames disable
static per_inline void per_eth_dma_set_dtcefd(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Dtcefd, val);
}

/// DMA interrupt enable register (ETH_DMAIER)
static per_inline uint_fast32_t per_eth_dma_dier(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->PerDma->Dier);
}

/// DMA interrupt enable register (ETH_DMAIER)
static per_inline void per_eth_dma_set_dier(const per_eth_t* const eth, uint32_t val)
{
    per_bit_rw32_reg_set(&eth->PerDma->Dier, val);
}

/// Transmit interrupt enable
static per_inline bool per_eth_dma_tie(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Tie);
}

/// Transmit interrupt enable
static per_inline void per_eth_dma_set_tie(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Tie, val);
}

/// Transmit process stopped interrupt enable
static per_inline bool per_eth_dma_tpsie(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Tpsie);
}

/// Transmit process stopped interrupt enable
static per_inline void per_eth_dma_set_tpsie(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Tpsie, val);
}

/// Transmit buffer unavailable interrupt enable
static per_inline bool per_eth_dma_tbuie(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Tbuie);
}

/// Transmit buffer unavailable interrupt enable
static per_inline void per_eth_dma_set_tbuie(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Tbuie, val);
}

/// Transmit jabber timeout interrupt enable
static per_inline bool per_eth_dma_tjtie(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Tjtie);
}

/// Transmit jabber timeout interrupt enable
static per_inline void per_eth_dma_set_tjtie(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Tjtie, val);
}

/// Overflow interrupt enable
static per_inline bool per_eth_dma_roie(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Roie);
}

/// Overflow interrupt enable
static per_inline void per_eth_dma_set_roie(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Roie, val);
}

/// Underflow interrupt enable
static per_inline bool per_eth_dma_tuie(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Tuie);
}

/// Underflow interrupt enable
static per_inline void per_eth_dma_set_tuie(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Tuie, val);
}

/// Receive interrupt enable
static per_inline bool per_eth_dma_rie(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Rie);
}

/// Receive interrupt enable
static per_inline void per_eth_dma_set_rie(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Rie, val);
}

/// Receive buffer unavailable interrupt enable
static per_inline bool per_eth_dma_rbuie(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Rbuie);
}

/// Receive buffer unavailable interrupt enable
static per_inline void per_eth_dma_set_rbuie(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Rbuie, val);
}

/// Receive process stopped interrupt enable
static per_inline bool per_eth_dma_rpsie(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Rpsie);
}

/// Receive process stopped interrupt enable
static per_inline void per_eth_dma_set_rpsie(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Rpsie, val);
}

/// Receive watchdog timeout interrupt enable
static per_inline bool per_eth_dma_rwtie(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Rwtie);
}

/// Receive watchdog timeout interrupt enable
static per_inline void per_eth_dma_set_rwtie(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Rwtie, val);
}

/// Early transmit interrupt enable
static per_inline bool per_eth_dma_etie(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Etie);
}

/// Early transmit interrupt enable
static per_inline void per_eth_dma_set_etie(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Etie, val);
}

/// Fatal bus error interrupt enable
static per_inline bool per_eth_dma_fbeie(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Fbeie);
}

/// Fatal bus error interrupt enable
static per_inline void per_eth_dma_set_fbeie(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Fbeie, val);
}

/// Early receive interrupt enable
static per_inline bool per_eth_dma_erie(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Erie);
}

/// Early receive interrupt enable
static per_inline void per_eth_dma_set_erie(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Erie, val);
}

/// Abnormal interrupt summary enable
static per_inline bool per_eth_dma_aise(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Aise);
}

/// Abnormal interrupt summary enable
static per_inline void per_eth_dma_set_aise(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Aise, val);
}

/// Normal interrupt summary enable
static per_inline bool per_eth_dma_nise(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->PerDma->Nise);
}

/// Normal interrupt summary enable
static per_inline void per_eth_dma_set_nise(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->PerDma->Nise, val);
}

/// DMA missed frame and buffer overflow counter register (ETH_DMAMFBOCR)
static per_inline uint_fast32_t per_eth_dma_mfbocr(const per_eth_t* const eth)
{
    return per_bit_r32_reg(&eth->PerDma->Mfbocr);
}

/// Missed frames by the controller
uint32_t per_eth_dma_mfc(const per_eth_t* const eth);

/// Overflow bit for missed frame counter
bool per_eth_dma_omfc(const per_eth_t* const eth);

/// Missed frames by the application
uint32_t per_eth_dma_mfa(const per_eth_t* const eth);

/// Overflow bit for FIFO overflow counter
bool per_eth_dma_omfa(const per_eth_t* const eth);

/// Receive status (RS) watchdog timer count
static per_inline uint_fast16_t per_eth_dma_rswtc(const per_eth_t* const eth)
{
    return per_bit_rw8(&eth->PerDma->Rswtc);
}

/// Receive status (RS) watchdog timer count
static per_inline bool per_eth_dma_set_rswtc(const per_eth_t* const eth, uint16_t val)
{
    return per_bit_rw8_set(&eth->PerDma->Rswtc, val);
}

/// Host transmit descriptor address pointer
static per_inline uint_fast32_t per_eth_dma_htdap(const per_eth_t* const eth)
{
    return per_bit_r32_reg(&eth->PerDma->Htdap);
}

/// Host receive descriptor address pointer
static per_inline uint_fast32_t per_eth_dma_hrdap(const per_eth_t* const eth)
{
    return per_bit_r32_reg(&eth->PerDma->Hrdap);
}

/// Host transmit buffer address pointer
static per_inline uint_fast32_t per_eth_dma_htbap(const per_eth_t* const eth)
{
    return per_bit_r32_reg(&eth->PerDma->Htbap);
}

/// Host receive buffer address pointer
static per_inline uint_fast32_t per_eth_dma_hrbap(const per_eth_t* const eth)
{
    return per_bit_r32_reg(&eth->PerDma->Hrbap);
}

/// ETH DNA fetch and clear active interrupts and return the active interrupts
static per_inline per_eth_dma_sr_e per_eth_dma_irq(const per_eth_t* const eth)
{
    uint_fast32_t irq = per_eth_dma_dier(eth) & (uint_fast16_t)PER_ETH_DMA_SR_MASK & per_eth_dma_sr(eth);

    per_eth_dma_set_sr(eth, irq); // Clear

    return (per_eth_dma_sr_e)irq;
}

#ifdef __cplusplus
}
#endif

#endif // per_eth_f4_h_
