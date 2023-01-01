/**
 * @file per_i2c.h
 *
 * This file contains the Inter-integrated circuit interface (I2C)
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

#ifndef per_i2c_h_
#define per_i2c_h_

#ifdef __cplusplus
extern "C"
{
#endif

#include "per_i2c_f4.h"

/// I2C pointer to spi 1
static per_inline const per_i2c_t* const per_i2c_1(void)
{
    static const per_i2c_t spi =
    {
        .Per = PER_I2C_1,
        .Err = PER_LOG_I2C_1,
    };
    return &spi;
}

/// I2C pointer to spi 2
static per_inline const per_i2c_t* const per_i2c_2(void)
{
    static const per_i2c_t spi =
    {
        .Per = PER_I2C_2,
        .Err = PER_LOG_I2C_2,
    };
    return &spi;
}

/// I2C pointer to spi 3
static per_inline const per_i2c_t* const per_i2c_3(void)
{
    static const per_i2c_t spi =
    {
        .Per = PER_I2C_3,
        .Err = PER_LOG_I2C_3,
    };
    return &spi;
}

#ifdef __cplusplus
}
#endif

#endif // per_i2c_h_
