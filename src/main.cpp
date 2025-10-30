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
    // initialize the game
    GameState game;
    game.add_random_block();
    for (int i = 0; i < 4; i++){
        game.update();
    }
    while (true){
        
        game.await_move();
        //game.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        
        /*
        game.display();
        // check if the last block is still falling 
        if (!game.update())
            game.add_random_block();
        // check if the blocks have gone over the top
        if (game.check_game_over()){
            endwin();
            std::cout << "GAME OVER!" << std::endl;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        */
    }
}