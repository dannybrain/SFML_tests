#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main(int, char const**)
{
    Game game;

    while (!game.getWindow()->isDone()) {
        game.handleInput();
        game.update();
        game.render();
        //std::cout << game.getDelta().asMicroseconds() << std::endl;
        game.restartClock();
    }
    
    return EXIT_SUCCESS;
}
