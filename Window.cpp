//
//  Window.cpp
//  SFML_test2
//
//  Created by Daniel Biehle on 12/14/17.
//  Copyright © 2017 Daniel Biehle. All rights reserved.
//

#include "Window.hpp"

void Window::setup(const std::string &title, const sf::Vector2u &size) {
    _title = title;
    _size = size;
    _isFullScreen = false;
    _isDone = false;
    _window.setFramerateLimit(60);
    create();
}

Window::Window(const std::string& title, const sf::Vector2u& size) {
    setup(title, size);
}

Window::Window() {
    setup("Window", sf::Vector2u(640, 480));
}

Window::~Window() {
    destroy();
}

void Window::create() {
    auto style =  _isFullScreen ? sf::Style::Fullscreen : sf::Style::Default;
    _window.create({_size.x, _size.y, 32}, _title, style);
}

void Window::destroy() {
    _window.close();
}

void Window::toggleFullScreen() {
    _isFullScreen = !_isFullScreen;
    destroy();
    create();
}

void Window::handleInput(){
    sf::Event event;
    
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _isDone = true;
        }
        
        if (event.type == sf::Event::KeyPressed and
            event.key.code == sf::Keyboard::F5) {
            toggleFullScreen();
        }
        if (event.type == sf::Event::KeyPressed and
            event.key.code == sf::Keyboard::Escape) {
            exit(1);
        }
    }
}

void Window::update() { }

bool Window::isDone() {
    return _isDone;
}

sf::Vector2u Window::getSize() {
    return _size;
}

sf::RenderWindow& Window::getRenderWindow() {
    return _window;
}

void Window::draw(sf::Drawable &drawable) {
    _window.draw(drawable);
}

void Window::beginDraw() {
    _window.clear(sf::Color::Black);
}

void Window::endDraw() {
    _window.display();
}
