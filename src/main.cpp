#include <iostream>
#include "../inc/game.hpp"
#include <thread> 
#include <chrono>

int main(){
    GameState game;
    game.add_random_block();
    while (true){
        game.display();
        // check if the last block is still falling 
        if (!game.update())
            game.add_random_block();
        // check if the blocks have gone over the top
        if (game.check_game_over()){
            std::cout << "GAME OVER!" << std::endl; 
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        system("clear");
    }
}