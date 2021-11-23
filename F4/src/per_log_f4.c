/**
 * @file per_log_f4.c
 *
 * This file contains the peripheral logging functions
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

#include "per_log_f4.h"

static per_log_event_t last; //!< Last event
static volatile uint32_t count; //!< Number of errors
static void (*callback)(uint_fast32_t per, uint_fast32_t ev, uint_fast32_t val);

/// Logging peripheral error event with valuer
void per_log_err(per_log_e per, uint_fast32_t ev, uint_fast32_t val)
{
    last.peripheral = per;
    last.event = ev;
    last.value = val;
    count++;

    if (0 != callback)
    {
        callback(per, ev, val); // inform user
    }
}

/// Logging user callback function set
void per_log_set_callback(void (*fct)(uint_fast32_t per, uint_fast32_t ev, uint_fast32_t val))
{
    callback = fct;
}

/// Logging user callback function clear
void per_log_clr_callback(void)
{
    callback = 0;
}

/// Get last logging event
uint32_t per_log_get(per_log_event_t* ev)
{
    uint32_t cnt;

    do
    {
        cnt = count;
        per_mem_copy(ev, &last, sizeof(*ev));
    }
    while(cnt != count);

    return cnt;
}
