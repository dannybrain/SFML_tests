//
//  Game.cpp
//  SFML_test2
//
//  Created by Daniel Biehle on 12/14/17.
//  Copyright © 2017 Daniel Biehle. All rights reserved.
//

#include "Game.hpp"
#include "ResourcePath.hpp"

Game::Game() : _window("game", sf::Vector2u(800, 600)) {
    _texture.loadFromFile(resourcePath() + "icon.png");
    _mushroom.setTexture(_texture);
    _vect = sf::Vector2f(400, 400);
}

void Game::move_mushroom() {
   /* _mushroom.setPosition(
        _mushroom.getPosition().x + (_vect.x * _delta.asSeconds()),
        _mushroom.getPosition().y + (_vect.y * _delta.asSeconds())
    );*/
    _mushroom.move(_vect * _delta.asSeconds());

    if (_mushroom.getPosition().x + _mushroom.getTexture()->getSize().x > _window.getSize().x or
        _mushroom.getPosition().x < 0)
        _vect.x *= -1;
    
    if (_mushroom.getPosition().y + _mushroom.getTexture()->getSize().y > _window.getSize().y or
        _mushroom.getPosition().y < 0)
        _vect.y *= -1;
}

void Game::update() {
    move_mushroom();
}

void Game::handleInput() {
    _window.handleInput();
}

void Game::render() {
    _window.beginDraw();
    _window.draw(_mushroom);
    _window.endDraw();
}

Window* Game::getWindow() {
    return &_window;
}

sf::Time Game::getDelta() {
    return _delta;
}
sf::Time Game::getCumulativeDelta() {
    return _cumul_delta;
}

void Game::restartClock() {
    _delta = _clock.restart();
    _cumul_delta += _delta;
}
