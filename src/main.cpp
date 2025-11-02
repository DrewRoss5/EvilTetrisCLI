#include <iostream>
#include "../inc/game.hpp"
#include <thread> 
#include <chrono>
#include <ncurses.h>

int main(){
    // initialize ncurses
    initscr();
    noecho();
    cbreak();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    // initialize the game
    GameState game;
    game.add_random_block();
    for (int i = 0; i < 4; i++){
        game.update();
    }
    while (true){
        game.check_move();
        bool updated = game.update();
        game.display();
        if (!updated)
            game.add_random_block();
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        // check if blocks have gone over the top
        if (game.check_game_over()){
            endwin();
            std::cout << "GAME OVER!" << std::endl;
            break;
        }
    }
}