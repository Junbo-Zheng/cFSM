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

#include <stddef.h>

#include "fsm.h"

void fsm_init(fsm_t* fsm, const state_t* init)
{
    if (fsm == NULL) {
        return;
    }

    /* clang-format off */
    fsm->init = init;
    fsm->cur  = NULL;
    fsm->prev = NULL;
    /* clang-format on */

    fsm_turn_to(fsm, fsm->init);
}

void fsm_deinit(fsm_t* fsm)
{
    // TODO: add deinit code here if needed
    (void)fsm;
}

void fsm_turn_to(fsm_t* fsm, const state_t* state)
{
    if (fsm->cur != NULL) {
        if (fsm->cur->exit != NULL) {
            fsm->cur->exit(fsm);
        }
        fsm->prev = fsm->cur;
    }

    fsm->cur = state;

    if (fsm->cur->entry != NULL) {
        fsm->cur->entry(fsm);
    }
}

const state_t* fsm_get_cur(fsm_t* fsm)
{
    if (fsm == NULL) {
        return NULL;
    }

    return fsm->cur;
}

const state_t* fsm_get_prev(fsm_t* fsm)
{
    if (fsm == NULL) {
        return NULL;
    }

    return fsm->prev;
}

const char* fsm_get_cur_name(fsm_t* fsm)
{
    if (fsm == NULL) {
        return NULL;
    }

    return fsm->cur->name;
}

const char* fsm_get_state_name(const state_t* state)
{
    if (state == NULL) {
        return NULL;
    }

    return state->name;
}

bool fsm_trigger_event(fsm_t* fsm, event_t event, void* data)
{
    if (fsm->cur == NULL) {
        return false;
    }

    return fsm->cur->callback(fsm, event, data);
}
