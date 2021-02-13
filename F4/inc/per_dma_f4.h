/**
 * @file per_dma_f4.h
 *
 * This file contains the peripheral Direct Memory Access (DMA)
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

#ifndef per_dma_f4_h_
#define per_dma_f4_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_bit_f4.h"
#include "per_log_f4.h"

/// Maximum number of streams
#define PER_DMA_STREAM_MAX (8)

/// DMA error enumeration
typedef enum
{
    PER_DMA_ERR_OKK = PER_LOG_DMA * PER_LOG_MULT, ///< No error
    PER_DMA_ERR_LOCK, ///< Peripheral was locked, invalid key
    PER_DMA_ERR_BUSY, ///< There was still an other action active
    PER_DMA_ERR_TRANSFER, ///< Transfer error
    PER_DMA_ERR_DIRECTMODE, ///< Direct mode error
    PER_DMA_ERR_FIFO, ///< FIFO error
} per_dma_error_e;

/// DMA stream enumeration
typedef enum
{
    PER_DMA_STREAM_0 = 0, ///< Stream 0
    PER_DMA_STREAM_1, ///< Stream 1
    PER_DMA_STREAM_2, ///< Stream 2
    PER_DMA_STREAM_3, ///< Stream 3
    PER_DMA_STREAM_4, ///< Stream 4
    PER_DMA_STREAM_5, ///< Stream 5
    PER_DMA_STREAM_6, ///< Stream 6
    PER_DMA_STREAM_7, ///< Stream 7
} per_dma_stream_e;

/// DMA channel enumeration
typedef enum
{
    PER_DMA_CHANNEL_0 = 0b000, ///< Channel 0
    PER_DMA_CHANNEL_1 = 0b001, ///< Channel 1
    PER_DMA_CHANNEL_2 = 0b010, ///< Channel 2
    PER_DMA_CHANNEL_3 = 0b011, ///< Channel 3
    PER_DMA_CHANNEL_4 = 0b100, ///< Channel 4
    PER_DMA_CHANNEL_5 = 0b101, ///< Channel 5
    PER_DMA_CHANNEL_6 = 0b110, ///< Channel 6
    PER_DMA_CHANNEL_7 = 0b111, ///< Channel 7
} per_dma_channel_e;

/// DMA direction enumeration
typedef enum
{
    PER_DMA_DIR_PER_TO_MEM = 0b00, ///< Peripheral-to-memory
    PER_DMA_DIR_MEM_TO_PER = 0b01, ///< Memory-to-peripheral
    PER_DMA_DIR_MEM_TO_MEM = 0b10, ///< Memory-to-memory
} per_dma_dir_e;

/// DMA burst enumeration
typedef enum
{
    PER_DMA_BURST_SINGlE  = 0b00, ///< Single transfer
    PER_DMA_BURST_INCR_4  = 0b01, ///< Incremental burst of 4 beats
    PER_DMA_BURST_INCR_8  = 0b10, ///< Incremental burst of 8 beats
    PER_DMA_BURST_INCR_16 = 0b11, ///< Incremental burst of 16 beats
} per_dma_burst_e;

/// DMA priority level enumeration
typedef enum
{
    PER_DMA_PL_LOW       = 0b00, ///< Low
    PER_DMA_PL_MEDIUM    = 0b01, ///< Medium
    PER_DMA_PL_HIGH      = 0b10, ///< High
    PER_DMA_PL_VERY_HIGH = 0b11, ///< Very high
} per_dma_pl_e;

/// DMA size enumeration
typedef enum
{
    PER_DMA_SIZE_BYTE      = 0b00, ///< Byte (8-bit)
    PER_DMA_SIZE_HALF_WORD = 0b01, ///< Half-word (16-bit)
    PER_DMA_SIZE_WORD      = 0b10, ///< Word (32-bit)
} per_dma_size_e;

/// DMA FIFO status enumeration
typedef enum
{
    PER_DMA_FS_EMPTY_TO_ONE_QUARTER  = 0b000, ///< 0 < fifo_level < 1/4
    PER_DMA_FS_ONE_QUARTER_TO_HALF   = 0b001, ///< 1/4 < fifo_level < 1/2
    PER_DMA_FS_HALF_TO_THREE_QUARTER = 0b010, ///< 1/2 < fifo_level < 3/4
    PER_DMA_FS_THREE_QUARTER_TO_FULL = 0b011, ///< 3/4 < fifo_level < full
    PER_DMA_FS_EMPTY                 = 0b100, ///< FIFO is empty
    PER_DMA_FS_FULL                  = 0b101, ///< FIFO is full
} per_dma_fs_e;

/// DMA FIFO threshold selection enumeration
typedef enum
{
    PER_DMA_FTH_ONE_QUARTER   = 0b00, ///< 1/4 full FIFO
    PER_DMA_FTH_HALF          = 0b01, ///< 1/2 full FIFO
    PER_DMA_FTH_THREE_QUARTER = 0b10, ///< 3/4 full FIFO
    PER_DMA_FTH_FULL          = 0b11, ///< full FIFO
} per_dma_fth_e;

/// DMA Stream-channel options for DMA1
typedef struct
{
    per_dma_stream_e str; ///< Stream
    per_dma_channel_e chan; ///< Channel
} per_dma1_selection_t;

/// DMA Stream-channel options for DMA2
typedef struct
{
    per_dma_stream_e str; ///< Stream
    per_dma_channel_e chan; ///< Channel
} per_dma2_selection_t;

/// DMA interrupt status register
typedef struct
{
    per_bit_r1_t Feif; ///< Stream x FIFO error interrupt flag
    per_bit_n1_t IsrBit1; ///< Reserved
    per_bit_r1_t Dmeif; ///< Stream x direct mode error interrupt flag
    per_bit_r1_t Teif; ///< Stream x transfer error interrupt flag
    per_bit_r1_t Htif; ///< Stream x half transfer interrupt flag
    per_bit_r1_t Tcif; ///< Stream transfer complete interrupt flag
} __attribute__((packed)) per_dma_isr_t;

/// DMA interrupt flag clear register
typedef struct
{
    per_bit_w1_t Cfeif; ///< Stream x FIFO error interrupt flag
    per_bit_n1_t IfcrBit1; ///< Reserved
    per_bit_w1_t Cdmeif; ///< Stream x direct mode error interrupt flag
    per_bit_w1_t Cteif; ///< Stream x transfer error interrupt flag
    per_bit_w1_t Chtif; ///< Stream x half transfer interrupt flag
    per_bit_w1_t Ctcif; ///< Stream transfer complete interrupt flag
} __attribute__((packed)) per_dma_ifcr_t;

/// DMA configuration registers
typedef struct
{
    // DMA stream x configuration register (DMA_SxCR)
    per_bit_rw1_t En; ///< Stream enable / flag stream ready when read low
    per_bit_rw1_t Dmeie; ///< Direct mode error interrupt enable
    per_bit_rw1_t Teie; ///< Transfer error interrupt enable
    per_bit_rw1_t Htie; ///< Half transfer interrupt enable
    per_bit_rw1_t Tcie; ///< Transfer complete interrupt enable
    per_bit_rw1_t Pfctrl; ///< Peripheral flow controller
    per_bit_rw2_t Dir; ///< Data transfer direction
    per_bit_rw1_t Circ; ///< Circular mode
    per_bit_rw1_t Pinc; ///< Peripheral increment mode
    per_bit_rw1_t Minc; ///< Memory increment mode
    per_bit_rw2_t Psize; ///< Peripheral data size
    per_bit_rw2_t Msize; ///< Memory data size
    per_bit_rw1_t Pincos; ///< Peripheral increment offset size
    per_bit_rw2_t Pl; ///< Priority level
    per_bit_rw1_t Dbm; ///< Double buffer mode
    per_bit_rw1_t Ct; ///< Current target (only in double buffer mode)
    per_bit_n1_t SxcrBit20; ///< Reserved
    per_bit_rw2_t Pburst; ///< Peripheral burst transfer configuration
    per_bit_rw2_t Mburst; ///< Memory burst transfer configuration
    per_bit_rw3_t Chsel; ///< Channel selection
    per_bit_n4_t SxcrBit28; ///< Reserved

    // DMA stream x number of data register (DMA_SxNDTR)
    per_bit_rw16_reg_t Ndt; ///< Number of data items to transfer

    // DMA stream x peripheral address register (DMA_SxPAR)
    per_bit_rw32_reg_t Par; ///< Peripheral address

    // DMA stream x memory 0 address register (DMA_SxM0AR)
    per_bit_rw32_reg_t M0a; ///< Memory 0 address

    // DMA stream x memory 1 address register (DMA_SxM1AR)
    per_bit_rw32_reg_t M1a; ///< Memory 1 address (used in case of Double buffer mode)

    // DMA stream x FIFO control register (DMA_SxFCR)
    per_bit_rw2_t Fth; ///< FIFO threshold selection
    per_bit_rw1_t Dmdis; ///< Direct mode disable
    per_bit_r3_t Fs; ///< FIFO status
    per_bit_n1_t SxfcrBit6; ///< Reserved
    per_bit_rw1_t Feie; ///< FIFO error interrupt enable
    per_bit_n24_t SxfcrBit8; ///< Reserved
} __attribute__((packed)) per_dma_conf_t;

/// DMA Stream 0...7 configuration
typedef struct
{
    // DMA low interrupt status register (DMA_LISR)
    per_dma_isr_t Isr0; ///< Stream 0 IRQ flags
    per_dma_isr_t Isr1; ///< Stream 1 IRQ flags
    per_bit_n4_t LisrBit12; ///< Reserved
    per_dma_isr_t Isr2; ///< Stream 2 IRQ flags
    per_dma_isr_t Isr3; ///< Stream 3 IRQ flags
    per_bit_n4_t LisrBit28; ///< Reserved

    // DMA high interrupt status register (DMA_HISR)
    per_dma_isr_t Isr4; ///< Stream 4 IRQ flags
    per_dma_isr_t Isr5; ///< Stream 5 IRQ flags
    per_bit_n4_t HisrBit12; ///< Reserved
    per_dma_isr_t Isr6; ///< Stream 6 IRQ flags
    per_dma_isr_t Isr7; ///< Stream 7 IRQ flags
    per_bit_n4_t HisrBit28; ///< Reserved

    // DMA low interrupt flag clear register (DMA_LIFCR)
    per_dma_ifcr_t Ifcr0; ///< Stream 0 IRQ flags
    per_dma_ifcr_t Ifcr1; ///< Stream 1 IRQ flags
    per_bit_n4_t LifcrBit12; ///< Reserved
    per_dma_ifcr_t Ifcr2; ///< Stream 2 IRQ flags
    per_dma_ifcr_t Ifcr3; ///< Stream 3 IRQ flags
    per_bit_n4_t LifcrBit28; ///< Reserved

    // DMA high interrupt flag clear register (DMA_HIFCR)
    per_dma_ifcr_t Ifcr4; ///< Stream 4 IRQ flags
    per_dma_ifcr_t Ifcr5; ///< Stream 5 IRQ flags
    per_bit_n4_t HifcrBit12; ///< Reserved
    per_dma_ifcr_t Ifcr6; ///< Stream 6 IRQ flags
    per_dma_ifcr_t Ifcr7; ///< Stream 7 IRQ flags
    per_bit_n4_t HifcrBit28; ///< Reserved

    per_dma_conf_t Stream[PER_DMA_STREAM_MAX];
} __attribute__((packed)) per_dma_t;

/// DMA Stream descriptor
typedef struct
{
    per_dma_conf_t* const Conf; ///< Configuration structure pointer
    per_dma_isr_t* const Isr; ///< Interrupt status structure pointer
    per_dma_ifcr_t* const Ifcr; ///< Interrupt flag clear structure pointer
    const per_log_e Err; ///< Error peripheral number
} __attribute__((packed)) per_dma_stream_t;

/// DMA Stream-channel selection options
typedef struct
{
    per_dma_conf_t* const Conf; ///< Configuration
    const per_dma_channel_e Chan; ///< Channel
} per_dma_selection_t;

/// DMA Stream enable / flag stream ready when read low
static per_inline bool per_dma_en(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->En);
}

/// DMA Stream enable / flag stream ready when read low
static per_inline void per_dma_set_en(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->En, val);
}

/// DMA Direct mode error interrupt enable
static per_inline bool per_dma_dmeie(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->Dmeie);
}

/// DMA Direct mode error interrupt enable
static per_inline void per_dma_set_dmeie(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->Dmeie, val);
}

/// DMA Transfer error interrupt enable
static per_inline bool per_dma_teie(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->Teie);
}

/// DMA Transfer error interrupt enable
static per_inline void per_dma_set_teie(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->Teie, val);
}

/// DMA Half transfer interrupt enable
static per_inline bool per_dma_htie(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->Htie);
}

/// DMA Half transfer interrupt enable
static per_inline void per_dma_set_htie(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->Htie, val);
}

/// DMA Transfer complete interrupt enable
static per_inline bool per_dma_tcie(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->Tcie);
}

/// DMA Transfer complete interrupt enable
static per_inline void per_dma_set_tcie(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->Tcie, val);
}

/// DMA Peripheral flow controller
static per_inline bool per_dma_pfctrl(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->Pfctrl);
}

/// DMA Peripheral flow controller
static per_inline void per_dma_set_pfctrl(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->Pfctrl, val);
}

/// DMA Data transfer direction
static per_inline per_dma_dir_e per_dma_dir(const per_dma_stream_t* const dma)
{
    return (per_dma_dir_e)per_bit_rw2(&dma->Conf->Dir);
}

/// DMA Data transfer direction
static per_inline bool per_dma_set_dir(const per_dma_stream_t* const dma, per_dma_dir_e dir)
{
    return per_bit_rw2_set(&dma->Conf->Dir, (uint_fast16_t)dir);
}

/// DMA Circular mode
static per_inline bool per_dma_circ(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->Circ);
}

/// DMA Circular mode
static per_inline void per_dma_set_circ(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->Circ, val);
}

/// DMA Peripheral increment mode
static per_inline bool per_dma_pinc(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->Pinc);
}

/// DMA Peripheral increment mode
static per_inline void per_dma_set_pinc(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->Pinc, val);
}

/// DMA Memory increment mode
static per_inline bool per_dma_minc(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->Minc);
}

/// DMA Memory increment mode
static per_inline void per_dma_set_minc(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->Minc, val);
}

/// DMA peripheral data size get
static per_inline per_dma_size_e per_dma_psize(const per_dma_stream_t* const dma)
{
    return (per_dma_size_e)per_bit_rw2(&dma->Conf->Psize);
}

/// DMA peripheral data size set
static per_inline bool per_dma_set_psize(const per_dma_stream_t* const dma, per_dma_size_e size)
{
    return per_bit_rw2_set(&dma->Conf->Psize, (uint_fast16_t)size);
}

/// DMA memory data size get
static per_inline per_dma_size_e per_dma_msize(const per_dma_stream_t* const dma)
{
    return (per_dma_size_e)per_bit_rw2(&dma->Conf->Msize);
}

/// DMA memory data size set
static per_inline bool per_dma_set_msize(const per_dma_stream_t* const dma, per_dma_size_e size)
{
    return per_bit_rw2_set(&dma->Conf->Msize, (uint_fast16_t)size);
}

/// DMA Peripheral increment offset size
static per_inline bool per_dma_pincos(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->Pincos);
}

/// DMA Peripheral increment offset size
static per_inline void per_dma_set_pincos(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->Pincos, val);
}

/// DMA priority get
static per_inline per_dma_pl_e per_dma_pl(const per_dma_stream_t* const dma)
{
    return (per_dma_pl_e)per_bit_rw2(&dma->Conf->Pl);
}

/// DMA priority set
static per_inline bool per_dma_set_pl(const per_dma_stream_t* const dma, per_dma_pl_e prio)
{
    return per_bit_rw2_set(&dma->Conf->Pl, (uint_fast16_t)prio);
}

/// DMA Double buffer mode
static per_inline bool per_dma_dbm(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->Dbm);
}

/// DMA Double buffer mode
static per_inline void per_dma_set_dbm(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->Dbm, val);
}

/// DMA Current target (only in double buffer mode)
static per_inline bool per_dma_ct(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->Ct);
}

/// DMA Current target (only in double buffer mode)
static per_inline void per_dma_set_ct(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->Ct, val);
}

/// DMA peripheral burst size get
static per_inline per_dma_burst_e per_dma_pburst(const per_dma_stream_t* const dma)
{
    return (per_dma_burst_e)per_bit_rw2(&dma->Conf->Pburst);
}

/// DMA peripheral burst size set
static per_inline bool per_dma_set_pburst(const per_dma_stream_t* const dma, per_dma_burst_e burst)
{
    return per_bit_rw2_set(&dma->Conf->Pburst, (uint_fast16_t)burst);
}

/// DMA memory burst size get
static per_inline per_dma_burst_e per_dma_mburst(const per_dma_stream_t* const dma)
{
    return (per_dma_burst_e)per_bit_rw2(&dma->Conf->Mburst);
}

/// DMA memory burst size set
static per_inline bool per_dma_set_mburst(const per_dma_stream_t* const dma, per_dma_burst_e burst)
{
    return per_bit_rw2_set(&dma->Conf->Mburst, (uint_fast16_t)burst);
}

/// DMA Channel selection
static per_inline per_dma_channel_e per_dma_chsel(const per_dma_stream_t* const dma)
{
    return (per_dma_channel_e)per_bit_rw3(&dma->Conf->Chsel);
}

/// DMA Channel selection
static per_inline bool per_dma_set_chsel(const per_dma_stream_t* const dma, const per_dma_selection_t* selection)
{
    if (dma->Conf != selection->Conf)
    {
        per_log_err_function_not_supported();
    }

    return per_bit_rw3_set(&dma->Conf->Chsel, (uint_fast16_t)selection->Chan);
}

/// DMA number of data
static per_inline uint_fast16_t per_dma_ndt(const per_dma_stream_t* const dma)
{
    return per_bit_rw16_reg(&dma->Conf->Ndt);
}

/// DMA number of data
static per_inline void per_dma_set_ndt(const per_dma_stream_t* const dma, uint16_t val)
{
    per_bit_rw16_reg_set(&dma->Conf->Ndt, val);
}


/// DMA peripheral address
static per_inline uint_fast32_t per_dma_par(const per_dma_stream_t* const dma)
{
    return per_bit_rw32_reg(&dma->Conf->Par);
}

/// DMA peripheral address
static per_inline void per_dma_set_par(const per_dma_stream_t* const dma, uint_fast32_t val)
{
    per_bit_rw32_reg_set(&dma->Conf->Par, val);
}

/// DMA memory 0 address
static per_inline uint_fast32_t per_dma_m0a(const per_dma_stream_t* const dma)
{
    return per_bit_rw32_reg(&dma->Conf->M0a);
}

/// DMA memory 0 address
static per_inline void per_dma_set_m0a(const per_dma_stream_t* const dma, uint_fast32_t val)
{
    per_bit_rw32_reg_set(&dma->Conf->M0a, val);
}

/// DMA memory 1 address
static per_inline uint_fast32_t per_dma_m1a(const per_dma_stream_t* const dma)
{
    return per_bit_rw32_reg(&dma->Conf->M1a);
}

/// DMA memory 1 address
static per_inline void per_dma_set_m1a(const per_dma_stream_t* const dma, uint_fast32_t val)
{
    per_bit_rw32_reg_set(&dma->Conf->M1a, val);
}

/// DMA FIFO threshold level
static per_inline per_dma_fth_e per_dma_fth(const per_dma_stream_t* const dma)
{
    return (per_dma_fth_e)per_bit_rw2(&dma->Conf->Fth);
}

/// DMA FIFO threshold level
static per_inline bool per_dma_set_fth(const per_dma_stream_t* const dma, per_dma_fth_e lev)
{
    return per_bit_rw2_set(&dma->Conf->Fth, (uint_fast16_t)lev);
}

/// DMA Direct mode disable
static per_inline bool per_dma_dmdis(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->Dmdis);
}

/// DMA Direct mode disable
static per_inline void per_dma_set_dmdis(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->Dmdis, val);
}

/// DMA FIFO status
static per_inline per_dma_fs_e per_dma_fs(const per_dma_stream_t* const dma)
{
    return (per_dma_fs_e)per_bit_r3(&dma->Conf->Fs);
}

/// DMA FIFO error interrupt enable
static per_inline bool per_dma_feie(const per_dma_stream_t* const dma)
{
    return per_bit_rw1(&dma->Conf->Feie);
}

/// DMA FIFO error interrupt enable
static per_inline void per_dma_set_feie(const per_dma_stream_t* const dma, bool val)
{
    per_bit_rw1_set(&dma->Conf->Feie, val);
}

/// DMA Stream FIFO error interrupt flag
static per_inline bool per_dma_feif(const per_dma_stream_t* const dma)
{
    return per_bit_r1(&dma->Isr->Feif);
}

/// DMA Stream direct mode error interrupt flag
static per_inline bool per_dma_dmeif(const per_dma_stream_t* const dma)
{
    return per_bit_r1(&dma->Isr->Dmeif);
}

/// DMA Stream transfer error interrupt flag
static per_inline bool per_dma_teif(const per_dma_stream_t* const dma)
{
    return per_bit_r1(&dma->Isr->Teif);
}

/// DMA Stream half transfer interrupt flag
static per_inline bool per_dma_htif(const per_dma_stream_t* const dma)
{
    return per_bit_r1(&dma->Isr->Htif);
}

/// DMA Stream transfer complete interrupt flag
static per_inline bool per_dma_tcif(const per_dma_stream_t* const dma)
{
    return per_bit_r1(&dma->Isr->Tcif);
}

/// DMA Stream direct mode error interrupt flag
static per_inline void per_dma_clr_cdmeif(const per_dma_stream_t* const dma)
{
    per_bit_w1_set(&dma->Ifcr->Cdmeif, true);
}

/// DMA Stream FIFO error interrupt flag
static per_inline void per_dma_clr_cfeif(const per_dma_stream_t* const dma)
{
    per_bit_w1_set(&dma->Ifcr->Cfeif, true);
}

/// DMA  Stream transfer error interrupt flag
static per_inline void per_dma_clr_cteif(const per_dma_stream_t* const dma)
{
    per_bit_w1_set(&dma->Ifcr->Cteif, true);
}

/// DMA Stream half transfer interrupt flag
static per_inline void per_dma_clr_chtif(const per_dma_stream_t* const dma)
{
    per_bit_w1_set(&dma->Ifcr->Chtif, true);
}

/// DMA Stream transfer complete interrupt flag
static per_inline void per_dma_clr_ctcif(const per_dma_stream_t* const dma)
{
    per_bit_w1_set(&dma->Ifcr->Ctcif, true);
}

/// DMA Check stream for direct mode error and log and clear it
static per_inline void per_dma_clr_dmeif(const per_dma_stream_t* const dma)
{
    if (per_dma_dmeif(dma))
    {
        per_dma_clr_cdmeif(dma);
        per_log_err(dma->Err, PER_DMA_ERR_DIRECTMODE, 0);
    }
}

/// DMA Check stream for FIFO error and log and clear it
static per_inline void per_dma_clr_feif(const per_dma_stream_t* const dma)
{
    if (per_dma_feif(dma))
    {
        per_dma_clr_cfeif(dma);
        per_log_err(dma->Err, PER_DMA_ERR_FIFO, 0);
    }
}

/// DMA Check stream for transfer error and log and clear it
static per_inline void per_dma_clr_teif(const per_dma_stream_t* const dma)
{
    if (per_dma_teif(dma))
    {
        per_dma_clr_cteif(dma);
        per_log_err(dma->Err, PER_DMA_ERR_TRANSFER, 0);
    }
}

#ifdef __cplusplus
}
#endif

#endif // per_dma_f4_h_
