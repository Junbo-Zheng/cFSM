/*
 * Copyright (C) 2025 Junbo Zheng. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __FSM_H__
#define __FSM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef struct _fsm fsm_t;

typedef uint32_t event_t;

typedef struct {
    const char* name;
    void (*entry)(fsm_t* fsm);
    void (*exit)(fsm_t* fsm);
    bool (*callback)(fsm_t* fsm, event_t event, void* data);
} state_t;

typedef struct _fsm {
    const state_t* init;
    const state_t* prev;
    const state_t* cur;
} fsm_t;

void fsm_init(fsm_t* fsm, const state_t* init);
void fsm_deinit(fsm_t* fsm);

void fsm_turn_to(fsm_t* fsm, const state_t* state);
bool fsm_trigger_event(fsm_t* fsm, event_t event, void* data);

const state_t* fsm_get_cur(fsm_t* fsm);
const state_t* fsm_get_prev(fsm_t* fsm);

const char* fsm_get_cur_name(fsm_t* fsm);
const char* fsm_get_state_name(const state_t* state);

#ifdef __cplusplus
}
#endif

#endif /* __FSM_H__ */
