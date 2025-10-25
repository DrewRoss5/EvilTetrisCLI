#include <iostream>
#include "../inc/game.hpp"
#include <thread> 
#include <chrono>

int main(){
    GameState game;
    game.add_random_block();
    while (true){
        game.display();
        if (!game.update()){
            game.add_random_block();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        system("clear");
    }
}