/**
 * @file per_eth_f4.h
 *
 * This file contains the Ethernet peripheral interface (ETH)
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
 * per_eth_macmiiar_write()     writes the MII register in one command
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

/// ETH error enumeration
typedef enum
{
    PER_ETH_ERR_OK = PER_LOG_ETH * PER_LOG_MULT, ///< No error
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
    PER_ETH_CR_60_100   = 0b000, ///< 60-100 MHz HCLK/42
    PER_ETH_CR_100_150  = 0b001, ///< 100-150 MHzHCLK/62
    PER_ETH_CR_20_35    = 0b010, ///< 20-35 MHz HCLK/16
    PER_ETH_CR_35_60    = 0b011, ///< 35-60 MHz HCLK/26
    PER_ETH_CR_150_168  = 0b100, ///< 150-168 MHz HCLK/102
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
    PER_ETH_MSFRWCS_WRITE  = 0b10, ///< Write active
    PER_ETH_MSFRWCS_READ_WRITE = 0b11, ///< Read and write active
} per_eth_msfrwcs_e;

/// ETH Rx FIFO read controller status
typedef enum
{
    PER_ETH_RFRCS_IDLE = 0b00, ///< IDLE state
    PER_ETH_RFRCS_DATA  = 0b01, ///< Reading frame data
    PER_ETH_RFRCS_STATUS  = 0b10, ///< Reading frame status (or time-stamp)
    PER_ETH_RFRCS_FLUSH = 0b11, ///< Flushing the frame data and status
} per_eth_rfrcs_e;

/// ETH Rx FIFO fill level
typedef enum
{
    PER_ETH_RFFL_EMPTY = 0b00, ///< Empty
    PER_ETH_RFFL_BELOW  = 0b01, ///< Fill-level below flow-control de-activate threshold
    PER_ETH_RFFL_ABOVE  = 0b10, ///< Fill-level above flow-control activate threshold
    PER_ETH_RFFL_FULL  = 0b11, ///< Full
} per_eth_rffl_e;

/// ETH MAC transmit frame controller status
typedef enum
{
    PER_ETH_MTFCS_IDLE = 0b00, ///< Idle
    PER_ETH_MTFCS_WAIT  = 0b01, ///< Waiting for Status of previous frame or IFG/backoff period to be over
    PER_ETH_MTFCS_PAUSE  = 0b10, ///< Generating and transmitting a Pause control frame (in full duplex mode)
    PER_ETH_MTFCS_TRANSFER  = 0b11, ///< Transferring input frame for transmission
} per_eth_mtfcs_e;

/// ETH Tx FIFO read status
typedef enum
{
    PER_ETH_TFRS_IDLE = 0b00, ///< Idle state
    PER_ETH_TFRS_READ  = 0b01, ///< Read state (transferring data to the MAC transmitter)
    PER_ETH_TFRS_WAIT  = 0b10, ///< Waiting for TxStatus from MAC transmitter
    PER_ETH_TFRS_WRITE  = 0b11, ///< Writing the received TxStatus or flushing the TxFIFO
} per_eth_tfrs_e;

typedef struct
{
    // Ethernet MAC configuration register (ETH_MACCR)
    per_bit_n2_t MaccrBit0; ///< Reserved
    per_bit_rw1_t Re; ///< Receiver enable
    per_bit_rw1_t Te; ///< Transmitter enable
    per_bit_rw1_t Dc; ///< Deferral check
    per_bit_rw2_t Bl; ///< Back-off limit
    per_bit_rw1_t Acps; ///< Automatic pad/CRC stripping
    per_bit_n1_t MaccrBit8; ///< Reserved
    per_bit_rw1_t Rd; ///< Retry disable
    per_bit_rw1_t Ipco; ///< IPv4 checksum offload
    per_bit_rw1_t Dm; ///< Duplex mode
    per_bit_rw1_t Lm; ///< Loopback mode
    per_bit_rw1_t Rod; ///< Receive own disable
    per_bit_rw1_t Fes; ///< Fast Ethernet speed
    per_bit_n1_t MaccrBit15; ///< Reserved
    per_bit_rw1_t Csd; ///< Carrier sense disable
    per_bit_rw3_t Ifg; ///< Interframe gap
    per_bit_n2_t MaccrBit20; ///< Reserved
    per_bit_rw1_t Jd; ///< Jabber disable
    per_bit_rw1_t Wd; ///< Watchdog disable
    per_bit_n1_t MaccrBit24; ///< Reserved
    per_bit_rw1_t Cstf; ///< CRC stripping for Type frames
    per_bit_n6_t MaccrBit26; ///< Reserved

    // Ethernet MAC frame filter register (ETH_MACFFR)
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
    per_bit_n20_t MacffrBit11; ///< Reserved
    per_bit_rw1_t Ra; ///< Receive all

    // Ethernet MAC hash table high register (ETH_MACHTHR)
    per_bit_rw32_reg_t Hth; ///< Hash table high

    // Ethernet MAC hash table low register (ETH_MACHTLR)
    per_bit_rw32_reg_t Htl; ///< Hash table low

    // Ethernet MAC MII address register (ETH_MACMIIAR)
    union
    {
        struct
        {
            per_bit_rs1_t Mb; ///< MII busy
            per_bit_rw1_t Mw; ///< MII write
            per_bit_rw3_t Cr; ///< Clock range
            per_bit_n1_t MacmiiarBit5; ///< Reserved
            per_bit_rw5_t Mr; ///< MII register
            per_bit_rw5_t Pa; ///< PHY address
            per_bit_rw16_t MacmiiarBit16; ///< Reserved
        };
        per_bit_rw16_reg_t Macmiiar; ///< Register access
    };

    // Ethernet MAC MII data register (ETH_MACMIIDR)
    per_bit_rw16_reg_t Md; ///< MII data

    // Ethernet MAC flow control register (ETH_MACFCR)
    per_bit_rs1_t Fcb; ///< Flow control busy/back pressure activate
    per_bit_rw1_t Tfce; ///< Transmit flow control enable
    per_bit_rw1_t Rfce; ///< Receive flow control enable
    per_bit_rw1_t Upfd; ///< Unicast pause frame detect
    per_bit_rw2_t Plt; ///< Pause low threshold
    per_bit_n1_t MacfcrBit6; ///< Reserved
    per_bit_rw1_t Zqpd; ///< Zero-quanta pause disable
    per_bit_n8_t MacfcrBit8; ///< Reserved
    per_bit_rw16_t Pt; ///< Pause time

    // Ethernet MAC VLAN tag register (ETH_MACVLANTR)
    per_bit_rw16_t Vlanti; ///< VLAN tag identifier (for receive frames)
    per_bit_rw1_t Vlantc; ///< 12-bit VLAN tag comparison
    per_bit_n15_t MacvlantrBit17; ///< Reserved

    per_bit_n32_t MacReg20[2]; ///< Reserved

    // Ethernet MAC remote wakeup frame filter register (ETH_MACRWUFFR)
    per_bit_rw32_reg_t Rwuffr; ///< remote wakeup frame filter register

    // Ethernet MAC PMT control and status register (ETH_MACPMTCSR)
    per_bit_rw32_reg_t Macpmtcsr; ///< Register access

    per_bit_n32_t MacReg30; ///< Reserved

    // Ethernet MAC debug register (ETH_MACDBGR)
    per_bit_r1_t Mmrpea; ///< MAC MII receive protocol engine active
    per_bit_r2_t Msfrwcs; ///< MAC small FIFO read / write controllers status
    per_bit_n1_t MacdbgrBit3; ///< Reserved
    per_bit_r1_t Rfwra; ///< Rx FIFO write controller active
    per_bit_r2_t Rfrcs; ///< Rx FIFO read controller status
    per_bit_n1_t MacdbgrBit7; ///< Reserved
    per_bit_r2_t Rffl; ///< Rx FIFO fill level
    per_bit_n6_t MacdbgrBit10; ///< Reserved
    per_bit_r1_t Mmtea; ///< MAC MII transmit engine active
    per_bit_r2_t Mtfcs; ///< MAC transmit frame controller status
    per_bit_r1_t Mtp; ///< MAC transmitter in pause
    per_bit_r2_t Tfrs; ///< Tx FIFO read status
    per_bit_r1_t Tfwa; ///< Tx FIFO write active
    per_bit_n1_t MacdbgrBit23; ///< Reserved
    per_bit_r1_t Tfne; ///< Tx FIFO not empty
    per_bit_r1_t Tff; ///< Tx FIFO full
    per_bit_n6_t MacdbgrBit26; ///< Reserved

    // Ethernet MAC interrupt status register (ETH_MACSR)
    per_bit_n3_t MaccsrBit0; ///< Reserved
    per_bit_r1_t Pmts; ///< PMT status
    per_bit_r1_t Mmcs; ///< MMC status
    per_bit_r1_t Mmcrs; ///< MMC receive status
    per_bit_r1_t Mmcts; ///< MMC transmit status
    per_bit_n2_t MaccsrBit7; ///< Reserved
    per_bit_r1_t Tsts; ///< Time stamp trigger status
    per_bit_n22_t MaccsrBit10; ///< Reserved

    // Ethernet MAC interrupt mask register (ETH_MACIMR)
    per_bit_n3_t MacimrBit0; ///< Reserved
    per_bit_rw1_t Pmtim; ///< PMT interrupt mask
    per_bit_n5_t MacimrBit4; ///< Reserved
    per_bit_rw1_t Tstim; ///< Time stamp trigger interrupt mask
    per_bit_n22_t MacimrBit10; ///< Reserved

    // Ethernet MAC address 0 high register (ETH_MACA0HR)
    per_bit_rw16_t Maca0h; ///< MAC address0 high [47:32]
    per_bit_n15_t Maca0hrBit16; ///< Reserved
    per_bit_n1_t Mo; ///< Always 1

    // Ethernet MAC address 0 low register (ETH_MACA0LR)
    per_bit_rw32_reg_t Maca0l; ///< MAC address0 low [31:0]

    // Ethernet MAC address 1 high register (ETH_MACA1HR)
    per_bit_rw16_t Maca1h; ///< MAC address1 high [47:32]
    per_bit_n8_t Maca1hrBit16; ///< Reserved
    per_bit_rw6_t Mbc1; ///< Mask byte control
    per_bit_rw1_t Sa1; ///< Source address
    per_bit_rw1_t Ae1; ///< Address enable

    // Ethernet MAC address 1 low register (ETH_MACA1LR)
    per_bit_rw32_reg_t Maca1l; ///< MAC address1 low [31:0]

    // Ethernet MAC address 2 high register (ETH_MACA2HR)
    per_bit_rw16_t Maca2h; ///< MAC address2 high [47:32]
    per_bit_n8_t Maca2hrBit16; ///< Reserved
    per_bit_rw6_t Mbc2; ///< Mask byte control
    per_bit_rw1_t Sa2; ///< Source address
    per_bit_rw1_t Ae2; ///< Address enable

    // Ethernet MAC address 2 low register (ETH_MACA2LR)
    per_bit_rw32_reg_t Maca2l; ///< MAC address2 low [31:0]

    // Ethernet MAC address 3 high register (ETH_MACA3HR)
    per_bit_rw16_t Maca3h; ///< MAC address3 high [47:32]
    per_bit_n8_t Maca3hrBit16; ///< Reserved
    per_bit_rw6_t Mbc3; ///< Mask byte control
    per_bit_rw1_t Sa3; ///< Source address
    per_bit_rw1_t Ae3; ///< Address enable

    // Ethernet MAC address 3 low register (ETH_MACA3LR)
    per_bit_rw32_reg_t Maca3l; ///< MAC address3 low [31:0]
} __attribute__((packed)) per_eth_mac_t;

typedef struct
{
    // Ethernet MMC control register (ETH_MMCCR)
    per_bit_rw1_t Cr; ///< Counter reset
    per_bit_rw1_t Csr; ///< Counter stop rollover
    per_bit_rw1_t Ror; ///< Reset on read
    per_bit_rw1_t Mcf; ///< MMC counter freeze
    per_bit_rw1_t Mcp; ///< MMC counter preset
    per_bit_rw1_t Mcfhp; ///< MMC counter Full-Half preset
    per_bit_n26_t MmccrBit6; ///< Reserved

    // Ethernet MMC receive interrupt register (ETH_MMCRIR)
    per_bit_n5_t MmcrirBit0; ///< Reserved
    per_bit_r1_t Rfces; ///< Received frames CRC error status
    per_bit_r1_t Rfaes; ///< Received frames alignment error status
    per_bit_n10_t MmcrirBit7; ///< Reserved
    per_bit_r1_t Rgufs; ///< Received Good Unicast Frames Status
    per_bit_n14_t MmcrirBit18; ///< Reserved

    // Ethernet MMC transmit interrupt register (ETH_MMCTIR)
    per_bit_n14_t MmctirBit0; ///< Reserved
    per_bit_r1_t Tgfscs; ///< Transmitted good frames single collision status
    per_bit_r1_t Tgmscs; ///< Transmitted good frames more single collision status
    per_bit_n5_t MmctirBit16; ///< Reserved
    per_bit_r1_t Tgfs; ///< Transmitted good frames status
    per_bit_n10_t MmctirBit22; ///< Reserved

    // Ethernet MMC receive interrupt mask register (ETH_MMCRIMR)
    per_bit_n5_t MmcimrBit0; ///< Reserved
    per_bit_rw1_t Rfcem; ///< Received frame CRC error mask
    per_bit_rw1_t Rfaem; ///< Received frames alignment error mask
    per_bit_n10_t MmcimrBit7; ///< Reserved
    per_bit_rw1_t Rgufm; ///< Received good unicast frames mask
    per_bit_n14_t MmcimrBit18; ///< Reserved

    // Ethernet MMC transmit interrupt mask register (ETH_MMCTIMR)
    per_bit_n14_t MmctimrBit0; ///< Reserved
    per_bit_rw1_t Tgfscm; ///< Transmitted good frames single collision mask
    per_bit_rw1_t Tgfmscm; ///< Transmitted good frames more single collision mask
    per_bit_n5_t MmctimrBit16; ///< Reserved
    per_bit_rw1_t Tgfm; ///< Transmitted good frames mask
    per_bit_n10_t MmctimrBit22; ///< Reserved

    per_bit_n32_t MmcReg14[14]; ///< Reserved

    // Ethernet MMC transmitted good frames after a single collision counter register (ETH_MMCTGFSCCR)
    per_bit_r32_reg_t Tgfscc; ///< Transmitted good frames single collision counter

    // Ethernet MMC transmitted good frames after more than a single collision counter register (ETH_MMCTGFMSCCR)
    per_bit_r32_reg_t Tgfmscc; ///< Transmitted good frames more single collision counter

    per_bit_n32_t MmcReg54[5]; ///< Reserved

    // Ethernet MMC transmitted good frames counter register (ETH_MMCTGFCR)
    per_bit_r32_reg_t Tgfc; ///< Transmitted good frames counter

    per_bit_n32_t MmcReg6c[10]; ///< Reserved

    // Ethernet MMC received frames with CRC error counter register (ETH_MMCRFCECR)
    per_bit_r32_reg_t Rfcec; ///< Received frames CRC error counter

    // Ethernet MMC received frames with alignment error counter register (ETH_MMCRFAECR)
    per_bit_r32_reg_t Rfaec; ///< Received frames alignment error counter

    per_bit_n32_t MmcReg9c[10]; ///< Reserved

    // MMC received good unicast frames counter register (ETH_MMCRGUFCR)
    per_bit_r32_reg_t Rgufc; ///< Received good unicast frames counter
} __attribute__((packed)) per_eth_mmc_t;

typedef struct
{
} __attribute__((packed)) per_eth_ptp_t;

typedef struct
{
} __attribute__((packed)) per_eth_dma_t;

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
static per_inline void per_eth_mac_set_hth(const per_eth_t* const eth, uint_fast32_t val)
{
    per_bit_rw32_reg_set(&eth->PerMac->Hth, val);
}

/// ETH Hash table low
static per_inline uint_fast32_t per_eth_mac_htl(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->PerMac->Htl);
}

/// ETH Hash table low
static per_inline void per_eth_mac_set_htl(const per_eth_t* const eth, uint_fast32_t val)
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
static per_inline uint_fast16_t per_eth_mac_macmiiar(const per_eth_t* const eth)
{
    return per_bit_rw16_reg(&eth->PerMac->Macmiiar);
}

/// ETH MII address register
static per_inline void per_eth_mac_set_macmiiar(const per_eth_t* const eth, uint16_t val)
{
    per_bit_rw16_reg_set(&eth->PerMac->Macmiiar, val);
}

/// ETH MII write address register
static per_inline void per_eth_mac_macmiiar_write(const per_eth_t* const eth, uint_fast16_t reg, uint_fast16_t addr)
{
    per_eth_mac_t* const per = eth->PerMac;
    uint16_t val = per_bit_rw5_mask(&per->Mr) & (reg << per_bit_rw5_shift(&per->Mr));

    val |= per_bit_rw5_mask(&per->Pa) & (addr << per_bit_rw5_shift(&per->Pa));
    val |= per_bit_rw1_mask(&per->Mw); // set write bit
    val |= per_bit_rw16_reg(&eth->PerMac->Macmiiar) & per_bit_rw3_mask(&per->Cr); // Save the clock range

    per_bit_rw16_reg_set(&per->Macmiiar, val);
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

#ifdef __cplusplus
}
#endif

#endif // per_eth_f4_h_
