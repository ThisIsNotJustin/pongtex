#include <sys/mman.h>

#include "pingpong/pingpong.h"
#include "threads/thread.h"
#include "mutex/mutex.h"

int main() {
    game_state_t *game = mmap(NULL, sizeof(game_state_t),
                             PROT_READ | PROT_WRITE,
                             MAP_SHARED | MAP_ANON, -1, 0);
    
    if (game == MAP_FAILED) {
        printf("Failed to allocate shared memory\n");
        return 1;
    }
    
    mutex_init(&game->mutex);
    game->ball_pos = 0;
    game->rally_count = 0;
    game->game_over = false;

    thread_t ping_thread = custom_thread_create(ping_player, game);
    thread_t pong_thread = custom_thread_create(pong_player, game);
    
    if (!ping_thread || !pong_thread) {
        printf("Failed to create threads\n");
        return 1;
    }
    
    // run pong game for 10 seconds
    printf("Game starting!\n");
    sleep(10);
    
    game->game_over = true;
    sleep(1);
    printf("\nGame Over!\n");
    printf("Total rallies: %zu\n", game->rally_count);
    
    munmap(game, sizeof(game_state_t));
    
    return 0;
}