//
//  Window.hpp
//  SFML_test2
//
//  Created by Daniel Biehle on 12/14/17.
//  Copyright © 2017 Daniel Biehle. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Window {
public:
    Window();
    Window(const std::string& title, const sf::Vector2u& size);
    ~Window();
    
    void beginDraw();
    void endDraw();
    void draw(sf::Drawable &drawable);
    void update();
    void handleInput();
    
    sf::Vector2u getSize();
    sf::RenderWindow& getRenderWindow();
    bool isDone();
    bool isFullScreen();
    void toggleFullScreen();

private:
    sf::RenderWindow _window;
    sf::Vector2u _size;
    std::string _title;
    
    void setup(const std::string& title, const sf::Vector2u& size);
    void create();
    void destroy();
    bool _isFullScreen;
    bool _isDone;
};

#endif /* Window_hpp */
