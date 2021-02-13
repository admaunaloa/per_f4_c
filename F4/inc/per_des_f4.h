/**
 * @file per_des_f4.h
 *
 * This file contains the Device Electronic Signature (DES)
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

#ifndef per_des_f4_h_
#define per_des_f4_h_

#ifdef __cplusplus
extern "C"
{
#endif

#include "per_dep.h"

/// Address of UID
#define PER_DES_UID ((uintptr_t)0x1FFF7A10)

/// Address of programmed flash size value
#define PER_DES_FLASH_SIZE ((uintptr_t)0x1FFF7A22)

typedef struct
{
    uint32_t Uid0; ///< UID bit 0-31
    uint32_t Uid32; ///< UID bit 32-63
    uint32_t Uid64; ///< UID bit 64-95
} __attribute__((packed)) per_des_uid_t;

/// Device unique device identifier UID
static per_inline const per_des_uid_t* per_des_uid(void)
{
    return (const per_des_uid_t*)PER_DES_UID;
}

/// Device flash size in Kbytes
static per_inline uint16_t per_des_flash_size(void)
{
    return *(uint16_t*)PER_DES_FLASH_SIZE;
}

#ifdef __cplusplus
}
#endif

#endif // per_des_f4_h_
