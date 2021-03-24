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

/// Initialize RCC
void bsp_rcc_init(void)
{
    const per_rcc_t* const rcc = per_rcc();

    /// PLLCFGR
    per_rcc_set_pllm(rcc, 4);      // 8M / 4 = 2M
    per_rcc_set_plln(rcc, 168);    // 2M * 168 = 336M
    per_rcc_set_pllp(rcc, 2);      // 336M / 2 = 168M
    per_rcc_set_pllsrc(rcc, true); // HSE
    per_rcc_set_pllq(rcc, 7);      // 336M / 7 = 48M

    /// CFGR
    per_rcc_set_hpre(rcc, 1);
    per_rcc_set_ppre1(rcc, 4);
    per_rcc_set_ppre2(rcc, 4);
    per_rcc_set_sw(rcc, PER_RCC_SW_PLL);

    /// CR
    per_rcc_setwait_hsi(rcc, true);
    per_rcc_set_hsebyp(rcc, true);
    per_rcc_setwait_hse(rcc, true);
    per_rcc_setwait_pll(rcc, true);

    per_rcc_set_gpioaen(rcc, true);
    per_rcc_set_gpioben(rcc, true);
    per_rcc_set_gpiocen(rcc, true);
    per_rcc_set_gpioden(rcc, true);
    per_rcc_set_gpiogen(rcc, true);
    per_rcc_set_gpiohen(rcc, true);

    per_rcc_set_dma1en(rcc, true);
    per_rcc_set_dma2en(rcc, true);

    per_rcc_set_usart3en(rcc, true);
    per_rcc_set_uart4en(rcc, true);

    per_rcc_set_tim1en(rcc, true);
    per_rcc_set_tim2en(rcc, true);
    per_rcc_set_tim3en(rcc, true);
}
