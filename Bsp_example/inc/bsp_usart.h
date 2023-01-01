/**
 * @file bsp_usart.h
 *
 * This file contains the Board Support Package (BSP) USART and UART
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

#ifndef bsp_usart_h_
#define bsp_usart_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp_dep.h"
#include "per_dma.h"
#include "per_usart.h"

/// Descriptor Read-write bit
typedef struct
{
    bool (*Setup)(uint8_t*, uint32_t, uint32_t, per_usart_ps_e, per_usart_m_e, per_usart_stop_e); //!< Configure parameters
    void (*Enable)(bool); //!< Enable operation
    uint16_t (*Lock)(void); //!< Mutex aquire
    void (*Unlock)(uint16_t); //!< Mutex release
    bool (*Transmit)(uint8_t*, uint32_t); //!< Send message
    uint8_t (*Receive)(void); //!< Receive message
    bool (*RxIdle)(void); //!< Is the line is idle
    uint16_t (*TxRest)(void); //!< Number of bytes to send left on DMA
    bool (*TxDone)(void); //!< Last byte is out on USART
} bsp_usart_desc_t;

/// Device data
typedef struct
{
    uint16_t Key; //!< Access key
    uint16_t Ndt; //!< Previous data counter
    uint16_t Cap; //!< Receive buffer capacity
    uint8_t* Buf; //!< Receive buffer pointer
    uint8_t* BufEnd; //!< Receive buffer end pointer
} bsp_usart_data_t;

extern bsp_usart_data_t usart_3_inst;

/// USART3 lock
static per_inline uint16_t usart_3_lock(void)
{
    uint16_t val = 0;

    if (usart_3_inst.Key == 0) // not locked yet
    {
        val = bsp_dep_mut16_lock(&usart_3_inst.Key); // create key
    }

    return val;
}

/// USART3 unlock
static per_inline void usart_3_unlock(uint16_t key)
{
    bsp_dep_mut16_unlock(&usart_3_inst.Key, key); // free mutex
}

bool usart_3_setup(uint8_t* buffer, uint32_t capacity, uint32_t baudrate, per_usart_ps_e parity, per_usart_m_e word_length, per_usart_stop_e stop_bit);

/// USART3 enable/disable
static per_inline void usart_3_enable(bool en)
{
    per_usart_set_ue(per_usart_3(), en);
}

bool usart_3_transmit(uint8_t* data, uint32_t size);

uint8_t usart_3_receive(void);

/// USART3 RX line is idle for at least one char
static per_inline bool usart_3_rx_idle(void)
{
    return per_usart_idle(per_usart_3());
}

/// USART3 left over to transfer
static per_inline uint16_t usart_3_tx_rest(void)
{
    return per_dma_ndt(per_dma_1_stream_3());
}

/// USART3 transfer completed
static per_inline bool usart_3_tx_done(void)
{
    return per_dma_tcif(per_dma_1_stream_3());
}

// Dummy functions to prevent null pointers

/// Dummy lock
static per_inline uint16_t dummy_lock(void)
{
    return 0;
}

/// Dummy unlock
static per_inline void dummy_unlock(uint16_t key)
{
}

/// Dummy configure
static per_inline bool dummy_setup(uint8_t* buffer, uint32_t capacity, uint32_t baudrate, per_usart_ps_e parity, per_usart_m_e word_length, per_usart_stop_e stop_bit)
{
    return false;
}

/// Dummy enable/disable
static per_inline void dummy_enable(bool en)
{
}

/// Dummy send string
static per_inline bool dummy_transmit(uint8_t* data, uint32_t size)
{
    return false;
}

/// Dummy receive byte
static per_inline uint8_t dummy_receive(void)
{
    return (uint8_t)0;
}

/// Dummy receive line idle
static per_inline bool dummy_rx_idle(void)
{
    return true;
}

/// Dummy left over to transfer
static per_inline uint16_t dummy_tx_rest(void)
{
    return (uint16_t)0;
}

/// Dummy transfer completed
static per_inline bool dummy_tx_done(void)
{
    return true;
}

/// USART3 get pointer to the descriptor.
static per_inline const bsp_usart_desc_t* bsp_usart_3(uint16_t key)
{
    static const bsp_usart_desc_t usart_desc =
    {
        .Lock = usart_3_lock,
        .Unlock = usart_3_unlock,
        .Setup = usart_3_setup,
        .Enable = usart_3_enable,
        .Transmit = usart_3_transmit,
        .Receive = usart_3_receive,
        .RxIdle = usart_3_rx_idle,
        .TxRest = usart_3_tx_rest,
        .TxDone = usart_3_tx_done,
    };
    /// Dummy descriptor. Prevents that all the caller functions require to check for null pointers.
    static const bsp_usart_desc_t dummy_desc =
    {
        .Setup = dummy_setup,
        .Enable = dummy_enable,
        .Lock = dummy_lock,
        .Unlock = dummy_unlock,
        .Transmit = dummy_transmit,
        .Receive = dummy_receive,
        .RxIdle = dummy_rx_idle,
        .TxRest = dummy_tx_rest,
        .TxDone = dummy_tx_done,
    };
    const bsp_usart_desc_t* desc;

    if (usart_3_inst.Key == key) // fit
    {
        desc = &usart_desc;
    }
    else // locked
    {
        desc = &dummy_desc;
        per_log_err(PER_LOG_USART_3, PER_USART_LOCK_ERR, key);
    }

    return desc;
}

#ifdef __cplusplus
}
#endif

#endif // bsp_usart_h_
