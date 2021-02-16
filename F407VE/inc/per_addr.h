/**
 * @file per_addr.h
 *
 * This file contains the peripheral addresses
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

#ifndef per_addr_h_
#define per_addr_h_

#ifdef __cplusplus
extern "C" {
#endif

#define PER_ADDR_FLASH            ((uintptr_t) 0x08000000) ///< FLASH (up to 2 MB) base address in the alias region
#define PER_ADDR_CCMDATARAM       ((uintptr_t) 0x10000000) ///< CCM (core coupled memory) data RAM (64 KB) base address in the alias region
#define PER_ADDR_SRAM1            ((uintptr_t) 0x20000000) ///< SRAM1(112 KB) base address in the alias region
#define PER_ADDR_SRAM2            ((uintptr_t) 0x2001C000) ///< SRAM2(16 KB) base address in the alias region
#define PER_ADDR_SRAM3            ((uintptr_t) 0x20020000) ///< SRAM3(64 KB) base address in the alias region
#define PER_ADDR_PERIPH           ((uintptr_t) 0x40000000) ///< Peripheral base address in the alias region
#define PER_ADDR_BKPSRAM          ((uintptr_t) 0x40024000) ///< Backup SRAM(4 KB) base address in the alias region
#define PER_ADDR_FMC_R            ((uintptr_t) 0xA0000000) ///< FMC registers base address
#define PER_ADDR_SRAM1_BB         ((uintptr_t) 0x22000000) ///< SRAM1 base address in the bit-band region
#define PER_ADDR_SRAM2_BB         ((uintptr_t) 0x22380000) ///< SRAM2 base address in the bit-band region
#define PER_ADDR_SRAM3_BB         ((uintptr_t) 0x22400000) ///< SRAM3 base address in the bit-band region
#define PER_ADDR_PERIPH_BB        ((uintptr_t) 0x42000000) ///< Peripheral base address in the bit-band region
#define PER_ADDR_BKPSRAM_BB       ((uintptr_t) 0x42480000) ///< Backup SRAM(4 KB) base address in the bit-band region
#define PER_ADDR_FLASH_OTP        ((uintptr_t) 0x1FFF7800) ///< Base address of : (up to 528 Bytes) embedded FLASH OTP Area

#define PER_ADDR_APB1       PER_ADDR_PERIPH ///< APB1 peripherals base
#define PER_ADDR_APB2       (PER_ADDR_PERIPH + (uintptr_t) 0x00010000) ///< APB2 peripherals base
#define PER_ADDR_AHB1       (PER_ADDR_PERIPH + (uintptr_t) 0x00020000) ///< AHB1 peripherals base
#define PER_ADDR_AHB2       (PER_ADDR_PERIPH + (uintptr_t) 0x10000000) ///< AHB2 peripherals base

#ifdef __cplusplus
}
#endif

#endif // per_addr_h_
