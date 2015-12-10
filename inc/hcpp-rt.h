/* Copyright (c) 2015, Rice University

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1.  Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
2.  Redistributions in binary form must reproduce the above
     copyright notice, this list of conditions and the following
     disclaimer in the documentation and/or other materials provided
     with the distribution.
3.  Neither the name of Rice University
     nor the names of its contributors may be used to endorse or
     promote products derived from this software without specific
     prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

/*
 * hcpp-rt.h
 *
 *      Author: Vivek Kumar (vivekk@rice.edu)
 *      Acknowledgments: https://wiki.rice.edu/confluence/display/HABANERO/People
 */

#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include "litectx.h"

#ifndef HCPP_RT_H_
#define HCPP_RT_H_

#ifdef __cplusplus
extern "C" {
#endif

// forward declaration
extern pthread_key_t ws_key;
struct hc_context;
struct hclib_options;
struct hc_workerState;
struct place_t;
struct deque_t;
struct hc_deque_t;
struct finish_t;

typedef struct hc_workerState {
        pthread_t t; /* the pthread associated */
        struct finish_t* current_finish;
        struct place_t * pl; /* the directly attached place */
        struct place_t ** hpt_path; /* Path from root to worker's leaf place. Array of places. */
        struct hc_context * context;
        struct hc_workerState * next_worker; /* the link of other ws in the same place */
        struct hc_deque_t * current; /* the current deque/place worker is on */
        struct hc_deque_t * deques;
        int id; /* The id, identify a worker */
        int did; /* the mapping device id */
        LiteCtx *curr_ctx;
} hc_workerState;

#ifdef HC_ASSERTION_CHECK
#define HASSERT(cond) if(!(cond)){ printf("W%d: assertion failure\n", get_hc_wid()); assert(cond); }
#else
#define HASSERT(cond)       // Do Nothing
#endif

#define CURRENT_WS_INTERNAL ((hc_workerState *) pthread_getspecific(ws_key))

int get_hc_wid();
hc_workerState* current_ws();

#define HC_MALLOC(msize)	malloc(msize)
#define HC_FREE(p)			free(p)
typedef void (*generic_framePtr)(void*);

#include "hcpp-timer.h"
#include "hcpp-ddf.h"
#include "hcpp-place.h"

int  hclib_numWorkers();
void hclib_init(int * argc, char ** argv);
void hclib_finalize();
void hclib_start_finish();
void hclib_end_finish();
void hclib_user_harness_timer(double dur);

#ifdef __cplusplus
}
#endif

#endif
