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
 */

#ifndef per_eth_f4_h_
#define per_eth_f4_h_

#ifdef __cplusplus
extern "C"
{
#endif

#include "per_bit_f4.h"
#include "per_log_f4.h"


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
    per_bit_n19_t MacffrBit11; ///< Reserved
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
    uint_fast16_t Md; ///< MII data

    // Ethernet MAC flow control register (ETH_MACFCR)


} __attribute__((packed)) per_eth_per_t;

/// ETH descriptor
typedef struct
{
    per_eth_per_t* const Per; ///< Peripheral
    const per_log_e Err;      ///< Peripheral error number
} per_eth_t;

/// ETH Receiver enable
static per_inline bool per_eth_re(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Re);
}

/// ETH Receiver enable
static per_inline void per_eth_set_re(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Re, val);
}

/// ETH Transmitter enable
static per_inline bool per_eth_te(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Te);
}

/// ETH Transmitter enable
static per_inline void per_eth_set_te(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Te, val);
}

/// ETH Deferral check
static per_inline bool per_eth_dc(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Dc);
}

/// ETH Deferral check
static per_inline void per_eth_set_dc(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Dc, val);
}

/// ETH Back-off limit
static per_inline per_eth_bl_e per_eth_bl(const per_eth_t* const eth)
{
    return (per_eth_bl_e)per_bit_rw2(&eth->Per->Bl);
}

/// ETH Back-off limit
static per_inline void per_eth_set_bl(const per_eth_t* const eth, per_eth_bl_e val)
{
    per_bit_rw2_set(&eth->Per->Bl, (uint_fast8_t)val);
}

/// ETH Automatic pad/CRC stripping
static per_inline bool per_eth_acps(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Acps);
}

/// ETH Automatic pad/CRC stripping
static per_inline void per_eth_set_acps(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Acps, val);
}

/// ETH Retry disable
static per_inline bool per_eth_rd(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Rd);
}

/// ETH Retry disable
static per_inline void per_eth_set_rd(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Rd, val);
}

/// ETH IPv4 checksum offload
static per_inline bool per_eth_ipco(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Ipco);
}

/// ETH IPv4 checksum offload
static per_inline void per_eth_set_ipco(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Ipco, val);
}

/// ETH Duplex mode
static per_inline bool per_eth_dm(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Dm);
}

/// ETH Duplex mode
static per_inline void per_eth_set_dm(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Dm, val);
}

/// ETH Loopback mode
static per_inline bool per_eth_lm(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Lm);
}

/// ETH Loopback mode
static per_inline void per_eth_set_lm(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Lm, val);
}

/// ETH Receive own disable
static per_inline bool per_eth_rod(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Rod);
}

/// ETH Receive own disable
static per_inline void per_eth_set_rod(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Rod, val);
}

/// ETH Fast Ethernet speed
static per_inline bool per_eth_fes(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Fes);
}

/// ETH Fast Ethernet speed
static per_inline void per_eth_set_fes(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Fes, val);
}

/// ETH Carrier sense disable
static per_inline bool per_eth_csd(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Csd);
}

/// ETH Carrier sense disable
static per_inline void per_eth_set_csd(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Csd, val);
}

/// ETH Interframe gap
static per_inline per_eth_ifg_e per_eth_ifg(const per_eth_t* const eth)
{
    return (per_eth_ifg_e)per_bit_rw3(&eth->Per->Ifg);
}

/// ETH Interframe gap
static per_inline void per_eth_set_ifg(const per_eth_t* const eth, per_eth_ifg_e val)
{
    per_bit_rw3_set(&eth->Per->Ifg, (uint_fast16_t)val);
}

/// ETH Jabber disable
static per_inline bool per_eth_jd(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Jd);
}

/// ETH Jabber disable
static per_inline void per_eth_set_jd(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Jd, val);
}

/// ETH Watchdog disable
static per_inline bool per_eth_wd(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Wd);
}

/// ETH Watchdog disable
static per_inline void per_eth_set_wd(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Wd, val);
}

/// ETH CRC stripping for Type frames
static per_inline bool per_eth_cstf(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Cstf);
}

/// ETH CRC stripping for Type frames
static per_inline void per_eth_set_cstf(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Cstf, val);
}

/// ETH Promiscuous mode
static per_inline bool per_eth_pm(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Pm);
}

/// ETH Promiscuous mode
static per_inline void per_eth_set_pm(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Pm, val);
}

/// ETH Hash unicast
static per_inline bool per_eth_hu(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Hu);
}

/// ETH Hash unicast
static per_inline void per_eth_set_hu(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Hu, val);
}

/// ETH Hash multicast
static per_inline bool per_eth_hm(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Hm);
}

/// ETH Hash multicast
static per_inline void per_eth_set_hm(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Hm, val);
}

/// ETH Destination address inverse filtering
static per_inline bool per_eth_daif(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Daif);
}

/// ETH Destination address inverse filtering
static per_inline void per_eth_set_daif(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Daif, val);
}

/// ETH Pass all multicast
static per_inline bool per_eth_pam(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Pam);
}

/// ETH Pass all multicast
static per_inline void per_eth_set_pam(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Pam, val);
}

/// ETH Broadcast frames disable
static per_inline bool per_eth_bfd(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Bfd);
}

/// ETH Broadcast frames disable
static per_inline void per_eth_set_bfd(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Bfd, val);
}

/// ETH Pass control frames
static per_inline per_eth_pcf_e per_eth_pcf(const per_eth_t* const eth)
{
    return (per_eth_pcf_e)per_bit_rw2(&eth->Per->Pcf);
}

/// ETH Pass control frames
static per_inline void per_eth_set_pcf(const per_eth_t* const eth, per_eth_pcf_e val)
{
    per_bit_rw2_set(&eth->Per->Pcf, (uint_fast16_t)val);
}

/// ETH< Source address inverse filtering
static per_inline bool per_eth_saif(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Saif);
}

/// ETH< Source address inverse filtering
static per_inline void per_eth_set_saif(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Saif, val);
}

/// ETH Source address filter
static per_inline bool per_eth_saf(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Saf);
}

/// ETH Source address filter
static per_inline void per_eth_set_saf(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Saf, val);
}

/// ETH Hash or perfect filter
static per_inline bool per_eth_hpf(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Hpf);
}

/// ETH Hash or perfect filter
static per_inline void per_eth_set_hpf(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Hpf, val);
}

/// ETH Receive all
static per_inline bool per_eth_ra(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Ra);
}

/// ETH Receive all
static per_inline void per_eth_set_ra(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Ra, val);
}

/// ETH Hash table high
static per_inline uint_fast32_t per_eth_hth(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->Per->Hth);
}

/// ETH Hash table high
static per_inline void per_eth_set_hth(const per_eth_t* const eth, uint_fast32_t val)
{
    per_bit_rw32_reg_set(&eth->Per->Hth, val);
}

/// ETH Hash table low
static per_inline uint_fast32_t per_eth_htl(const per_eth_t* const eth)
{
    return per_bit_rw32_reg(&eth->Per->Htl);
}

/// ETH Hash table low
static per_inline void per_eth_set_htl(const per_eth_t* const eth, uint_fast32_t val)
{
    per_bit_rw32_reg_set(&eth->Per->Htl, val);
}

/// ETH MII busy
static per_inline bool per_eth_mb(const per_eth_t* const eth)
{
    return per_bit_rs1(&eth->Per->Mb);
}

/// ETH MII busy
static per_inline void per_eth_set_mb(const per_eth_t* const eth)
{
    per_bit_rs1(&eth->Per->Mb);
}

/// ETH MII write
static per_inline bool per_eth_mw(const per_eth_t* const eth)
{
    return per_bit_rw1(&eth->Per->Mw);
}

/// ETH MII write
static per_inline void per_eth_set_mw(const per_eth_t* const eth, bool val)
{
    per_bit_rw1_set(&eth->Per->Mw, val);
}

/// ETH Clock range
static per_inline per_eth_cr_e per_eth_cr(const per_eth_t* const eth)
{
    return (per_eth_cr_e)per_bit_rw3(&eth->Per->Cr);
}

/// ETH Clock range
static per_inline void per_eth_set_cr(const per_eth_t* const eth, per_eth_cr_e val)
{
    per_bit_rw3_set(&eth->Per->Cr, (uint_fast16_t)val);
}

/// ETH MII register
static per_inline uint_fast16_t per_eth_mr(const per_eth_t* const eth)
{
    return per_bit_rw5(&eth->Per->Mr);
}

/// ETH MII register
static per_inline void per_eth_set_mr(const per_eth_t* const eth, uint_fast16_t val)
{
    per_bit_rw5_set(&eth->Per->Mr, val);
}

/// ETH PHY address
static per_inline uint_fast16_t per_eth_pa(const per_eth_t* const eth)
{
    return per_bit_rw5(&eth->Per->Pa);
}

/// ETH PHY address
static per_inline void per_eth_set_pa(const per_eth_t* const eth, uint_fast16_t val)
{
    per_bit_rw5_set(&eth->Per->Pa, val);
}

/// ETH MII address register
static per_inline uint_fast16_t per_eth_macmiiar(const per_eth_t* const eth)
{
    return per_bit_rw16_reg(&eth->Per->Macmiiar);
}

/// ETH MII address register
static per_inline void per_eth_set_macmiiar(const per_eth_t* const eth, uint16_t val)
{
    per_bit_rw16_reg_set(&eth->Per->Macmiiar, val);
}










/// ETH MII write address register
static per_inline void per_eth_macmiiar_write(const per_eth_t* const eth, uint_fast16_t reg, uint_fast16_t addr)
{
    uint16_t val = per_eth_macmiiar(eth) & per_bit_rw3_mask(&eth->Per->Cr); // Save the clock range

    val |= per_bit_rw1_mask(&eth->Per->Mw);
    val |= per_bit_rw5_mask(&eth->Per->Mr) & (reg << per_bit_rw5_shift(&eth->Per->Mr));
    val |= per_bit_rw5_mask(&eth->Per->Pa) & (addr << per_bit_rw5_shift(&eth->Per->Pa));

    per_bit_rw16_reg_set(&eth->Per->Macmiiar, val);
}




///// ETH
//static per_inline uint32_t per_eth_(const per_eth_t* const eth)
//{
//    return per_bit_rw32_reg(&eth->Per->);
//}
//
///// ETH
//static per_inline void per_eth_set_(const per_eth_t* const eth, uint32_t val)
//{
//    per_bit_rw32_reg_set(&eth->Per->, val);
//}

///// ETH
//static per_inline bool per_eth_(const per_eth_t* const eth)
//{
//    return per_bit_rw1(&eth->Per->);
//}
//
///// ETH
//static per_inline void per_eth_set_(const per_eth_t* const eth, bool val)
//{
//    per_bit_rw1_set(&eth->Per->, val);
//}


#ifdef __cplusplus
}
#endif

#endif // per_eth_f4_h_
