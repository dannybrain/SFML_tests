//
//  Game.hpp
//  SFML_test2
//
//  Created by Daniel Biehle on 12/14/17.
//  Copyright © 2017 Daniel Biehle. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Window.hpp"

class Game {
private:
    Window _window;
    sf::Texture _texture;
    sf::Sprite _mushroom;   // our main sprite
    sf::Clock _clock;       // internal clock
    sf::Time _delta;        // time elapsed between 2 cycles
    sf::Time _cumul_delta;  // cumulative delta
    sf::Vector2f _vect;     // movement vector for our mushroom
    
    void move_mushroom();
    
public:
    Game();
    ~Game(){};
    Window* getWindow();
    void handleInput();
    void restartClock();
    sf::Time getDelta();
    sf::Time getCumulativeDelta();
    void update();
    void render();
    
};

#endif /* Game_hpp */
