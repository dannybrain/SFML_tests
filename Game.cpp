//
//  Game.cpp
//  SFML_test2
//
//  Created by Daniel Biehle on 12/14/17.
//  Copyright © 2017 Daniel Biehle. All rights reserved.
//
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "ResourcePath.hpp"

Game::Game() : _window("game", sf::Vector2u(800, 600)), 
               _world(sf::Vector2i(800, 600)), 
               _snake(_world.getBlockSize()) {
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
    //move_mushroom();
    float timestep = 1.0f / _snake.getSpeed();

    if (_cumul_delta.asSeconds() >= timestep) {
        _snake.tick();
        _world.update(_snake);
        if (_snake.hasLost()){
            _snake.reset();
        }
        _cumul_delta -= sf::seconds(timestep);
    } else {
        std::cout << "speed " << _snake.getSpeed()
                  << "cumul " << _cumul_delta.asSeconds() 
                  << " VS " << timestep << std::endl;
    }
}

void Game::handleInput() {
    // window exit/key press
    _window.handleInput();

    // snake specific keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and 
        _snake.getDirection() != snakeDirection::Down) {
        _snake.setDirection(snakeDirection::Up);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and
        _snake.getDirection() != snakeDirection::Right) {
        _snake.setDirection(snakeDirection::Left);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and
        _snake.getDirection() != snakeDirection::Left) {
        _snake.setDirection(snakeDirection::Right);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and
        _snake.getDirection() != snakeDirection::Up) {
        _snake.setDirection(snakeDirection::Down);
    }

}

void Game::render() {
    _window.beginDraw();
    //_window.draw(_mushroom);
    _snake.render(_window.getRenderWindow());
    _world.render(_window.getRenderWindow());
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
