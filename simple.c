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

#include <stdio.h>
#include <unistd.h>

#include <fsm.h>

static fsm_t fsm = { 0 };

#define UNUSED(x) (void)(x)

typedef enum {
    EVENT_1 = 1,
    EVENT_2,
    EVENT_3,
} simple_event_t;

static void low_entry(fsm_t* sm)
{
    UNUSED(sm);
    printf("turn to %s\n", __func__);
}

static void low_exit(fsm_t* sm)
{
    UNUSED(sm);
    printf("exiting from %s\n", __func__);
}

static bool low_callback(fsm_t* sm, event_t event, void* data)
{
    UNUSED(sm);
    UNUSED(event);
    UNUSED(data);

    printf("%s with event: %u\n", __func__, event);
    return true;
}

static void mid_entry(fsm_t* sm)
{
    UNUSED(sm);
    printf("turn to %s\n", __func__);
}

static void mid_exit(fsm_t* sm)
{
    UNUSED(sm);
    printf("exiting from %s\n", __func__);
}

static bool mid_callback(fsm_t* sm, event_t event, void* data)
{
    UNUSED(sm);
    UNUSED(event);
    UNUSED(data);

    printf("%s with event: %u\n", __func__, event);
    return true;
}

static void high_entry(fsm_t* sm)
{
    UNUSED(sm);
    printf("turn to %s\n", __func__);
}

static void high_exit(fsm_t* sm)
{
    UNUSED(sm);
    printf("exiting from %s\n", __func__);
}

static bool high_callback(fsm_t* sm, event_t event, void* data)
{
    UNUSED(sm);
    UNUSED(event);
    UNUSED(data);

    printf("%s with event: %u\n", __func__, event);
    return true;
}

static const state_t low_state = {
    /* clang-format off */
    .name     = "low",
    .entry    = low_entry,
    .exit     = low_exit,
    .callback = low_callback,
    /* clang-format on */
};

static const state_t mid_state = {
    /* clang-format off */
    .name     = "mid",
    .entry    = mid_entry,
    .exit     = mid_exit,
    .callback = mid_callback,
    /* clang-format on */
};

static const state_t high_state = {
    /* clang-format off */
    .name     = "high",
    .entry    = high_entry,
    .exit     = high_exit,
    .callback = high_callback,
    /* clang-format on */
};

typedef enum {
    STATE_LOW,
    STATE_MID,
    STATE_HIGH,
} simple_state_t;

typedef struct {
    simple_state_t state;
    const state_t* entry;
} simple_state_entry_t;

static simple_state_entry_t state_entry[] = {
    {  STATE_LOW,  &low_state },
    {  STATE_MID,  &mid_state },
    { STATE_HIGH, &high_state },
};

int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    simple_state_t state = STATE_LOW;
    event_t event = (event_t)EVENT_1;

    fsm_init(&fsm, (const state_t*)state_entry[STATE_LOW].entry);
    printf("initial state: %s\n", fsm_get_cur_name(&fsm));
    printf("--------------------------------------------------\n");

    while (1) {
        printf("processing state: %u, event: %u, state name: %s\n", state,
               event, fsm_get_cur_name(&fsm));

        fsm_trigger_event(&fsm, event, NULL);

        /* update new state and event */
        state++;
        event++;

        if (state < sizeof(state_entry) / sizeof(state_entry[0])) {
            fsm_turn_to(&fsm, state_entry[state].entry);
        } else {
            printf("state out of bounds, resetting to low state and exit\n");
            state = STATE_LOW;
            event = (event_t)EVENT_1;
            break;
        }

        printf("--------------------------------------------------\n");
        sleep(2);
    }
    return 0;
}
