/**
 * @file per_sys_cfg.h
 *
 * This file contains the peripheral system configuration (SYSCFG)
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

#ifndef per_sys_cfg_h_
#define per_sys_cfg_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "per_sys_cfg_f4.h"

/// SYSCFG base address
#define PER_SYSCFG (PER_ADDR_APB2 + (uintptr_t)0x3800)

static per_inline per_sys_cfg_t* per_sys_cfg(void)
{
    return (per_sys_cfg_t*)PER_BIT_REG_TO_BIT_BAND(PER_SYSCFG);
}

#ifdef __cplusplus
}
#endif

#endif // per_sys_cfg_h_
