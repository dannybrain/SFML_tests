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

Game::Game() : _window("game", sf::Vector2u(1024, 768)), 
               _world(sf::Vector2i(1024, 768)), 
               _snake(_world.getBlockSize()) {
    _texture.loadFromFile(resourcePath() + "icon.png");
    _mushroom.setTexture(_texture);
}

void Game::debug() {
    sf::Font font;
    sf::Text text;
    sf::String dinfo;

    dinfo = "Speed " + std::to_string(_snake.getSpeed()) +
            "\nSize " + std::to_string(_snake.getSize()) +
            "\nLives " + std::to_string(_snake.getLives()) +
            "\nScore " + std::to_string(_snake.getScore()) +
            "\nDirection " + std::to_string(
                               static_cast<int>(_snake.getDirection())) +
            "\nDelta " + std::to_string(_cumul_delta.asSeconds());

    if (font.loadFromFile("sansation.ttf")) {
        text.setFont(font);
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Style::Bold);
        text.setCharacterSize(18);
        text.setPosition(_window.getSize().x - 180, 16);
        text.setString(dinfo);
        _window.draw(text);
    }

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
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _snake.setSpeed(10);
    }

}

void Game::render() {
    _window.beginDraw();
    //_window.draw(_mushroom);
    _snake.render(_window.getRenderWindow());
    _world.render(_window.getRenderWindow());
    debug();
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
