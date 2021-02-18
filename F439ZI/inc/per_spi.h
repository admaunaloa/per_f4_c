/**
 * @file per_spi.h
 *
 * This file contains the serial peripheral interface (SPI)
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

#ifndef per_spi_h_
#define per_spi_h_

#ifdef __cplusplus
extern "C"
{
#endif

#include "per_spi_f4.h"

/// SPI1 base address
#define PER_SPI_1 (PER_ADDR_APB2 + (uintptr_t)0x3000)

/// SPI2 base address
#define PER_SPI_2 (PER_ADDR_APB1 + (uintptr_t)0x3800)

/// SPI3 base address
#define PER_SPI_3 (PER_ADDR_APB1 + (uintptr_t)0x3C00)

/// SPI4 base address
#define PER_SPI_4 (PER_ADDR_APB2 + (uintptr_t)0x3400)

/// SPI5 base address
#define PER_SPI_5 (PER_ADDR_APB2 + (uintptr_t)0x5000)

/// SPI6 base address
#define PER_SPI_6 (PER_ADDR_APB2 + (uintptr_t)0x5400)

/// SPI pointer to spi 1
static per_inline const per_spi_t* const per_spi_1(void)
{
    static const per_spi_t spi =
    {
        .Per = (per_spi_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_SPI_1),
        .Err = PER_LOG_SPI_1,
    };
    return &spi;
}

/// SPI pointer to spi 2
static per_inline const per_spi_t* const per_spi_2(void)
{
    static const per_spi_t spi =
    {
        .Per = (per_spi_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_SPI_2),
        .Err = PER_LOG_SPI_2,
    };
    return &spi;
}

/// SPI pointer to spi 3
static per_inline const per_spi_t* const per_spi_3(void)
{
    static const per_spi_t spi =
    {
        .Per = (per_spi_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_SPI_3),
        .Err = PER_LOG_SPI_3,
    };
    return &spi;
}

/// SPI pointer to spi 4
static per_inline const per_spi_t* const per_spi_4(void)
{
    static const per_spi_t spi =
    {
        .Per = (per_spi_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_SPI_4),
        .Err = PER_LOG_SPI_4,
    };
    return &spi;
}

/// SPI pointer to spi 5
static per_inline const per_spi_t* const per_spi_5(void)
{
    static const per_spi_t spi =
    {
        .Per = (per_spi_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_SPI_5),
        .Err = PER_LOG_SPI_5,
    };
    return &spi;
}

/// SPI pointer to spi 6
static per_inline const per_spi_t* const per_spi_6(void)
{
    static const per_spi_t spi =
    {
        .Per = (per_spi_per_t* const)PER_BIT_REG_TO_BIT_BAND(PER_SPI_6),
        .Err = PER_LOG_SPI_6,
    };
    return &spi;
}

#ifdef __cplusplus
}
#endif

#endif // per_spi_h_