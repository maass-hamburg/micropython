/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
 * Copyright (c) 2016 Linaro Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/clock.h>

#include "shared/timeutils/timeutils.h"

#include "py/obj.h"

static void mp_time_localtime_get(timeutils_struct_time_t *tm) {
    struct timespec tspec;

	sys_clock_gettime(SYS_CLOCK_REALTIME, &tspec);

    timeutils_seconds_since_epoch_to_struct_time(tspec.tv_sec, tm);
}

static mp_obj_t mp_time_time_get(void) {
    /* The absence of FP support is deliberate. The Zephyr port uses
     * single precision floats so the fraction component will start to
     * lose precision on devices with a long uptime.
     */
    struct timespec tspec;

	sys_clock_gettime(SYS_CLOCK_REALTIME, &tspec);

    return timeutils_obj_from_timestamp(tspec.tv_sec);
}

uint64_t mp_hal_time_ns(void) {
    struct timespec tspec;

	sys_clock_gettime(SYS_CLOCK_REALTIME, &tspec);

	return ((uint64_t)tspec.tv_sec * NSEC_PER_SEC) + tspec.tv_nsec;
}
