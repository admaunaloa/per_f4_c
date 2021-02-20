/**
 * @file bsp_dep.c
 *
 * This file contains the Board Support Package (BSP) dependencies
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

#include "bsp_dep.h"

#include "cmsis_gcc.h" // for the LDREX and STREX
#include "per_des.h"

/// LOG event information structure
typedef struct
{
    uint_fast32_t Per; ///< Peripheral
    uint_fast32_t Ev; ///< Event
    uint_fast32_t Val; ///< Value
    struct
    {
        int_fast16_t Era; ///< Overflow on seconds
        int_fast32_t Seconds; ///< Seconds since 1970
        int_fast32_t Nanoseconds; ///< Nanoseconds
    } Timestamp; ///< IEEE1588 time format
} bsp_dep_log_ev_t;

/// LOG list structure
typedef struct
{
    volatile bsp_dep_log_ev_t Ev; ///< Event
    volatile uint_fast32_t Tot; ///< Counter
} bsp_dep_log_lev_t;

static bsp_dep_log_lev_t err; ///< error details

/// Get random key number
uint32_t bsp_dep_key_gen(void)
{
    static uint32_t key;
    key += per_des_uid()->Uid0;

    if (0 == key)
    {
        key += 1;
    }

    return key;
}

/// Lock a mutex
uint16_t bsp_dep_mut16_lock(uint16_t* mut)
{
    uint16_t res = 0; // no lock

    if (0 == __LDREXH(mut)) // Load with exclusive access, zero is free
    {
        uint16_t key = (uint16_t)bsp_dep_key_gen();

        if (0 == __STREXH(key, mut)) // Store with exclusive access
        {
            __DMB(); // Success, synchronize with data memory barrier
            res = key;
        }
    }

    return res;
}

/// Unlock a mutex
void bsp_dep_mut16_unlock(uint16_t* mut, uint16_t key)
{
    if (key == *mut)
    {
        *mut = 0; // Clear it
    }
}

/* Howto use this logging;
 * This logging is designed to be extensible and has a default implementation that provides
 * usable error information with a minimal performance and footprint overhead.
 *
 * In case of an error the library does a callback on the "per_log() -> bsp_log()" function in this file.
 * By default this function logs the peripheral number and error code and it increments
 * the total number of errors. During debugging a breakpoint in this function is helpfull to
 * get the call-stack during the error.
 *
 * The total number of errors that can be get with the function "per_log_err_tot()" is a fast quality indicator.
 * It should return zero :-) if it is changed more detailed error information can be fetched with "per_log_err_last()"
 * This simple information is already very usable. An application can check if there where any errors
 * and on what peripheral and error code it was.
 *
 * The implementation of the per_log() function is in the per_dep.c so that it can be tailored to
 * the application. a First extension could be to add a time-stamp to the last error logged.
 * If more error information is required this function can be extended with printf style messages that send
 * details to the appropriate debug channel.
 * To keep the function call structure flat a separate thread can monitor the per_log_err_tot() number and
 * printf the last error information if it changes.
 *
 * The default "per_log()" function makes the debug logging extensible and flexible and it minimizes
 * the external dependencies of the library.
 */

/// Logging
void bsp_dep_log_err(uint_fast32_t per, uint_fast32_t ev, uint_fast32_t val)
{
    err.Ev.Per = per;
    err.Ev.Ev = ev;
    err.Ev.Val = val;
    ++(err.Tot);
    // Solve this in the application!
    /* list->Timestamp.Era = ;
       list->Timestamp.Seconds = ;
       list->Timestamp.Nanoseconds = ;
     */
}

/// Logging get total event count, fast
uint32_t bsp_dep_log_err_tot(void)
{
    return err.Tot;
}
