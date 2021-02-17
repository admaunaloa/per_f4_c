/**
 * @file bsp_dep.h
 *
 * This file contains the peripheral dependency and portability macros
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

#ifndef bsp_dep_h_
#define bsp_dep_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "string.h"
#include "stdint.h"

/// memory copy abstraction
#define bsp_mem_copy(dest,src,n) memcpy(dest,src,n)

uint16_t bsp_dep_mut16_lock(uint16_t* mut);

void bsp_dep_mut16_unlock(uint16_t* mut, uint16_t key);

void bsp_dep_log_err(uint_fast32_t per, uint_fast32_t ev, uint_fast32_t val);

uint32_t bsp_dep_log_err_tot(void);

#ifdef __cplusplus
}
#endif

#endif // bsp_dep_h_
