# EvilTetrisCLI
EvilTetris is a modified version of the classic Tetris game with two changes: Blocks pieces break off and obey gravity, and pieces can't be rotated, drastically chaning the game's dynamic.

# Running the Game:
To run the game, clone this repo, and ensure g++ is installed. Then:
```
g++ src/main.cpp src/game.cpp src/block.cpp -o test -lncurses
```
Use the arrow keys to move the falling blocks.
