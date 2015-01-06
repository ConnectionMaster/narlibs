/*
    Copyright (c) 2007-2013 Contributors as noted in the AUTHORS file

    This file is part of 0MQ.

    0MQ is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    0MQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __ZMQ_UTILS_H_INCLUDED__
#define __ZMQ_UTILS_H_INCLUDED__

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/*  Handle DSO symbol visibility                                             */
#if defined _WIN32
#   if defined ZMQ_STATIC
#       define ZMQ_EXPORT
#   elif defined DLL_EXPORT
#       define ZMQ_EXPORT __declspec(dllexport)
#   else
#       define ZMQ_EXPORT __declspec(dllimport)
#   endif
#else
#   if defined __SUNPRO_C  || defined __SUNPRO_CC
#       define ZMQ_EXPORT __global
#   elif (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER
#       define ZMQ_EXPORT __attribute__ ((visibility("default")))
#   else
#       define ZMQ_EXPORT
#   endif
#endif

typedef void (zmq_thread_fn) (void*);

/*  Helper functions are used by perf tests so that they don't have to care   */
/*  about minutiae of time-related functions on different OS platforms.       */

/*  Starts the stopwatch. Returns the handle to the watch.                    */
ZMQ_EXPORT void *zmq_stopwatch_start (void);

/*  Stops the stopwatch. Returns the number of microseconds elapsed since     */
/*  the stopwatch was started.                                                */
ZMQ_EXPORT unsigned long zmq_stopwatch_stop (void *watch_);

/*  Sleeps for specified number of seconds.                                   */
ZMQ_EXPORT void zmq_sleep (int seconds_);

/* Start a thread. Returns a handle to the thread.                            */
ZMQ_EXPORT void *zmq_threadstart (zmq_thread_fn* func, void* arg);

/* Wait for thread to complete then free up resources.                        */
ZMQ_EXPORT void zmq_threadclose (void* thread);

#undef ZMQ_EXPORT

#ifdef __cplusplus
}
#endif

#endif
