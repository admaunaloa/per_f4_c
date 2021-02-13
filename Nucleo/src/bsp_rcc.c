/**
 * @file bsp_rcc.c
 *
 * This file contains the Board Support Package (BSP)  RCC
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

#include "per_rcc.h"

/// Enable RCC clock
static void bsp_rcc_on(per_rcc_en1_t* pClockEn)
{
    per_rcc_enable(pClockEn, true);
}

/// Initialize RCC
void bsp_rcc_init(void)
{
    const per_rcc_t* const pHalRccp = per_rcc();
    bsp_rcc_on(&pHalRccp->Per->Gpioaen);
    bsp_rcc_on(&pHalRccp->Per->Gpioben);
    bsp_rcc_on(&pHalRccp->Per->Gpiocen);
    bsp_rcc_on(&pHalRccp->Per->Gpioden);
    bsp_rcc_on(&pHalRccp->Per->Gpioeen);
    //      bsp_rcc_on(&pHalRccp->Per->Crcen);
    //      bsp_rcc_on(&pHalRccp->Per->Ccmdataramen);
    bsp_rcc_on(&pHalRccp->Per->Dma1en);
    bsp_rcc_on(&pHalRccp->Per->Dma2en);
    //      bsp_rcc_on(&pHalRccp->Per->Ethmacen);
    //      bsp_rcc_on(&pHalRccp->Per->Ethmactxen);
    //      bsp_rcc_on(&pHalRccp->Per->Ethmacrxen);
    //      bsp_rcc_on(&pHalRccp->Per->Ethmacptpen);
    //      bsp_rcc_on(&pHalRccp->Per->Otghsen);
    //      bsp_rcc_on(&pHalRccp->Per->Otghsulpien);
    //    bsp_rcc_on(&pHalRccp->Per->Usart1en);
    //    bsp_rcc_on(&pHalRccp->Per->Usart2en);
    bsp_rcc_on(&pHalRccp->Per->Usart3en);
    bsp_rcc_on(&pHalRccp->Per->Uart4en);
    //    bsp_rcc_on(&pHalRccp->Per->Uart5en);
    //    bsp_rcc_on(&pHalRccp->Per->Usart6en);
    bsp_rcc_on(&pHalRccp->Per->Tim1en);
    bsp_rcc_on(&pHalRccp->Per->Tim2en);
    bsp_rcc_on(&pHalRccp->Per->Tim3en);
}
