# PongTex

## Ping Pong Terminal Game utilizing a Mutex
This is a simple ping pong game written in C that uses mutexes for mutual exclusion between two players (Ping and Pong) to ensure they are only able to hit the ping pong ball during their respective turn. The game runs for 10 seconds before concluding, counting the number of rallies.

## Introduction

The game simulates a two-player ping pong match. Player 1 (Ping) and Player 2 (Pong) take turns hitting the ball back and forth. The game is synchronized using a custom mutex implementation to ensure that only one player can hit the ball at a time, avoiding race conditions. The game will run for 10 seconds, and the rally count will be displayed at the end.

## Game Overview
- Duration: The game runs for 10 seconds before it automatically ends
- Objective: Players (Ping and Pong) take turns hitting the ball.
- Synchronization: A mutex is used to ensure that only one player can hit the ball at a time
- Game State: The game maintains a shared state that tracks the ball's position, rally count, and if the game is over

## How to Run
### Clone the Repository
```bash
git clone https://github.com/ThisIsNotJustin/pongtex.git
cd pongtex
```

### Compile the Code
```bash
gcc -c threads/thread.c -I./threads -I./mutex -o build/thread.o
gcc -c pingpong/pingpong.c -I./pingpong -I./mutex -I./threads -o build/pingpong.o
gcc -c mutex/mutex.c -o build/mutex.o -I$(xcrun --show-sdk-path)/usr/include  
gcc -g build/main.o build/pingpong.o build/thread.o build/mutex.o -o build/pingpong_game -lpthread
```

### Run the Game!
```bash
./build/pingpong_game
```