/**
 * @file bsp_usart.c
 *
 * This file contains the Board Support Package (BSP) USART and UART
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

#include "bsp_usart.h"

#include "per_rcc.h"
#include "bsp_gpio.h"

bsp_usart_data_t usart_3_inst; ///< USART3 instance

/// Configure USART
static per_inline bool usart_setup(const per_usart_t* const usart, uint32_t rate, per_usart_ps_e par, per_usart_m_e len, per_usart_stop_e stop)
{
    bool result = per_usart_set_baudrate(usart, rate);

    if (result)
    {
        result = per_usart_set_stop(usart, stop);
    }

    if (result)
    {
        per_usart_set_ps(usart, par);
        per_usart_set_m(usart, len);
        per_usart_set_re(usart, true); // Receive enable
        per_usart_set_te(usart, true); // Transmit enable
    }

    return result;
}

/// Disable DMA interrupts
static void usart_dma_conf_irq_disable(const per_dma_stream_t* dma)
{
    per_dma_set_dmeie(dma, false);
    per_dma_set_teie(dma, false);
    per_dma_set_htie(dma, false);
    per_dma_set_tcie(dma, false);
}

/// Clear errors DMA1 STREAM 1 for USART 3 RX
static void usart_3_dma_1_stream_1_error_clear(void)
{
    const per_dma_stream_t* dma = per_dma_1_stream_1();
    per_dma_clr_dmeif(dma);
    per_dma_clr_feif(dma);
    per_dma_clr_teif(dma);
    per_dma_clr_chtif(dma);
    per_dma_clr_ctcif(dma);
}

/// Clear errors DMA1 STREAM 3 for USART 3 TX
static void usart_3_dma_1_stream_3_error_clear(void)
{
    const per_dma_stream_t* dma = per_dma_1_stream_3();
    per_dma_clr_dmeif(dma);
    per_dma_clr_cfeif(dma);
    per_dma_clr_teif(dma);
    per_dma_clr_chtif(dma);
    per_dma_clr_ctcif(dma);
}

/// Configure DMA1 STREAM 1 for USART 3 RX multiple size registers
static bool usart_3_dma_1_stream_1_setup_multi(const per_dma_stream_t* dma)
{
    return per_dma_set_dir(dma, PER_DMA_DIR_PER_TO_MEM) &&
           per_dma_set_psize(dma, PER_DMA_SIZE_BYTE) &&
           per_dma_set_msize(dma, PER_DMA_SIZE_BYTE) &&
           per_dma_set_pl(dma, PER_DMA_PL_LOW) &&
           per_dma_set_pburst(dma, PER_DMA_BURST_SINGlE) &&
           per_dma_set_mburst(dma, PER_DMA_BURST_SINGlE) &&
           per_dma_set_chsel(dma, &PER_DMA_1_STREAM_1_USART3_RX);
}

/// Configure DMA1 STREAM 1 for USART 3 RX
static bool usart_3_dma_1_stream_1_setup(uint8_t* buf, uint32_t cap)
{
    bsp_usart_data_t* inst = &usart_3_inst;
    const per_dma_stream_t* dma = per_dma_1_stream_1();
    bool result = !per_dma_en(dma);

    if (result)
    {
        usart_dma_conf_irq_disable(dma);
        result = usart_3_dma_1_stream_1_setup_multi(dma);

        if (result)
        {
            per_dma_set_pfctrl(dma, false);
            per_dma_set_circ(dma, true);
            per_dma_set_pinc(dma, false);
            per_dma_set_minc(dma, true);
            per_dma_set_pincos(dma, false);
            per_dma_set_dbm(dma, false);
            per_dma_set_par(dma, (uint32_t)per_usart_addr_dr(per_usart_3()));
            usart_3_dma_1_stream_1_error_clear();
            per_dma_set_m0a(dma, (uint32_t)buf);
            per_dma_set_ndt(dma, cap);
            inst->Buf = buf;
            inst->BufEnd = buf + cap;
            inst->Cap = cap;
            inst->Ndt = cap;
            per_dma_set_en(dma, true);
        }
    }
    else
    {
        per_log_err(PER_LOG_USART_3, PER_USART_BUSY_ERR, 0);
    }

    return result;
}

/// Configure DMA1 STREAM 3 for USART 3 TX multiple size registers
static bool usart_3_dma_1_stream_3_setup_multi(const per_dma_stream_t* dma)
{
    return per_dma_set_dir(dma, PER_DMA_DIR_MEM_TO_PER) &&
           per_dma_set_psize(dma, PER_DMA_SIZE_BYTE) &&
           per_dma_set_msize(dma, PER_DMA_SIZE_BYTE) &&
           per_dma_set_pl(dma, PER_DMA_PL_LOW) &&
           per_dma_set_pburst(dma, PER_DMA_BURST_SINGlE) &&
           per_dma_set_mburst(dma, PER_DMA_BURST_SINGlE) &&
           per_dma_set_fth(dma, PER_DMA_FTH_ONE_QUARTER) &&
           per_dma_set_chsel(dma, &PER_DMA_1_STREAM_3_USART3_TX);
}

/// Configure DMA1 STREAM 3 for USART 3 TX
bool usart_3_dma_1_stream_3_setup(void)
{
    const per_dma_stream_t* dma = per_dma_1_stream_3();
    bool result = !per_dma_en(dma);

    if (result)
    {
        usart_dma_conf_irq_disable(dma);
        result = usart_3_dma_1_stream_3_setup_multi(dma);

        if (result)
        {
            per_dma_set_pfctrl(dma, false);
            per_dma_set_circ(dma, false);
            per_dma_set_pinc(dma, false);
            per_dma_set_minc(dma, true);
            per_dma_set_pincos(dma, false);
            per_dma_set_dbm(dma, false);
            per_dma_set_par(dma, (uint32_t)per_usart_addr_dr(per_usart_3()));
            per_dma_set_feie(dma, false);
            per_dma_set_dmdis(dma, true);
        }
    }
    else
    {
        per_log_err(PER_LOG_USART_3, PER_USART_BUSY_ERR, 0);
    }

    return result;
}

/// USART3 initialize
void usart_3_init(void)
{
    bsp_gpio_usart_3_tx()->Init(); // GPIO
    bsp_gpio_usart_3_rx()->Init(); // GPIO
}

/// USART3 configure
bool usart_3_setup(uint8_t* buffer, uint32_t capacity, uint32_t rate, per_usart_ps_e par, per_usart_m_e len, per_usart_stop_e stop)
{
    per_usart_set_dmat(per_usart_3(), true);
    per_usart_set_dmar(per_usart_3(), true);
    return usart_3_dma_1_stream_1_setup(buffer, capacity) && // RX
           usart_3_dma_1_stream_3_setup() && // TX
           usart_setup(per_usart_3(), rate, par, len, stop);
}

/// USART3 send string
bool usart_3_transmit(uint8_t* data, uint32_t size)
{
    const per_dma_stream_t* dma = per_dma_1_stream_3();
    bool result = !per_dma_en(dma);

    if (result)
    {
        usart_3_dma_1_stream_3_error_clear();
        per_dma_set_m0a(dma, (uint32_t)data);
        per_dma_set_ndt(dma, size);
        per_dma_set_en(dma, true);
    }
    else
    {
        per_log_err(PER_LOG_USART_3, PER_USART_BUSY_ERR, 0);
    }

    return result;
}

/// USART3 receive byte
uint8_t usart_3_receive(void)
{
    const per_dma_stream_t* dma = per_dma_1_stream_1();
    uint16_t ndt = per_dma_ndt(dma);
    uint8_t result = 0;

    if (ndt != usart_3_inst.Ndt)
    {
        result = *(usart_3_inst.Buf + usart_3_inst.Cap - usart_3_inst.Ndt);

        if (usart_3_inst.Ndt > 0)
        {
            usart_3_inst.Ndt--;
        }
        else
        {
            usart_3_inst.Ndt = usart_3_inst.Cap;
        }
    }

    return result;
}

/// USART3 receive multiple bytes
uint16_t usart_3_receive2(uint8_t* dest, uint16_t cap)
{
    const per_dma_stream_t* dma = per_dma_1_stream_1();
    uint16_t ndt = per_dma_ndt(dma);
    int32_t dev = usart_3_inst.Ndt - ndt;
    uint16_t size = 0;

    if (dev != 0) // new data
    {
        uint16_t size1 = 0;

        if (dev < 0)
        {
            size1 = usart_3_inst.Ndt;

            if (size1 > cap)
            {
                size1 = cap; // clip
            }

            bsp_mem_copy(dest, usart_3_inst.BufEnd - usart_3_inst.Ndt, size1); // Copy first part
            usart_3_inst.Ndt -= size1;

            if (usart_3_inst.Ndt == 0) // Rest
            {
                cap -= size1;
                usart_3_inst.Ndt = usart_3_inst.Cap;
                dev = usart_3_inst.Ndt - ndt;
            }
        }

        if (dev > 0)
        {
            size = (uint16_t)dev;

            if (size > cap)
            {
                size = cap; // clip
            }

            bsp_mem_copy(dest, usart_3_inst.BufEnd - usart_3_inst.Ndt, size); // Copy all
            usart_3_inst.Ndt -= size;
        }

        size += size1; // Total
    }

    return size;
}
