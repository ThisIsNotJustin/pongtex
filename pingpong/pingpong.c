#include "pingpong.h"

void *ping_player(void *arg) {
    game_state_t *game = (game_state_t *) arg;
    if (game == NULL) {
        printf("Ping Player Game State is NULL\n");
        return NULL;
    }

    printf("Ping player started\n");
    while (!game->game_over) {
        mutex_lock(&game->mutex);

        if (game->ball_pos == 0) {
            printf("Ping Hit (X) ----> (Y)\n");
            game->ball_pos = 1;
            game->rally_count++;
            usleep(500000);
        }

        mutex_unlock(&game->mutex);
        usleep(100000);
    }

    return NULL;
}

void *pong_player(void *arg) {
    game_state_t *game = (game_state_t *) arg;
    if (game == NULL) {
        printf("Pong Player Game State is NULL\n");
        return NULL;
    }

    printf("Pong player started\n");
    while (!game->game_over) {
        mutex_lock(&game->mutex);

        if (game->ball_pos == 1) {
            printf("Pong Hit (Y) ----> (X)\n");
            game->ball_pos = 0;
            game->rally_count++;
            usleep(500000);
        }

        mutex_unlock(&game->mutex);
        usleep(100000);
    }

    return NULL;
}