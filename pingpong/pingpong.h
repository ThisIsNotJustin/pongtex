#ifndef PINGPONG_H
#define PINGPONG_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "../mutex/mutex.h"

typedef struct {
    size_t rally_count;
    size_t ball_pos;
    bool game_over;
    mutex_t mutex;
} game_state_t;

typedef struct {
    bool is_ping;
    bool is_pong;
    size_t hit_count;
} player_t;

void *ping_player(void *arg);
void *pong_player(void *arg);

#endif // PINGPONG_H