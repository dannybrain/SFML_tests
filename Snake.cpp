//
//  Snake.cpp
//  SFML_test2
//
//  Created by Daniel Biehle on 12/26/17.
//  Copyright © 2017 Daniel Biehle. All rights reserved.
//

#include <math.h> // logarithm functions
#include "Snake.hpp"

int Snake::_lives = 3;

Snake::Snake(int size) {
	_block_size = size;
	_bodyShape.setSize(sf::Vector2f(_block_size - 1, _block_size - 1));
	reset();
}

Snake::~Snake() {};

// move the snake to its original position
void Snake::reset() {
	_body.clear();
	
	_body.push_back(snakeSegment(5, 7));
	_body.push_back(snakeSegment(5, 6));
	_body.push_back(snakeSegment(5, 5));
	
	setDirection(snakeDirection::None);
	_score = 0;
	//_lives = 3;
	_lost = false;
	_speed_increment = 10;
	_speed = 10 + _speed_increment;
	
}

sf::Vector2i Snake::getPosition() {
	return (_body.empty() ? sf::Vector2i(1, 1) : _body.front().position);
}

void Snake::extend() {
	if (_body.empty()) { return; }

	snakeSegment& tail_head = _body[_body.size() - 1];
	if (_body.size() > 1) {
		snakeSegment& bone = _body[_body.size() - 2];
		if (tail_head.position.x == bone.position.x) {
			if (tail_head.position.y > bone.position.y) {
				_body.push_back(snakeSegment(tail_head.position.x, 
											 tail_head.position.y + 1));
			} else {
				_body.push_back(snakeSegment(tail_head.position.x,
											 tail_head.position.y - 1));
			}
		} else if (tail_head.position.y == bone.position.y) {
			if (tail_head.position.x > bone.position.y) {
				_body.push_back(snakeSegment(tail_head.position.x + 1,
											 tail_head.position.y));
			} else {
				_body.push_back(snakeSegment(tail_head.position.x - 1,
											 tail_head.position.y));
			}
		}
	} else {
		if (_direction == snakeDirection::Up) {
			_body.push_back(snakeSegment(tail_head.position.x, tail_head.position.y + 1));
		} else if (_direction == snakeDirection::Down) {
			_body.push_back(snakeSegment(tail_head.position.x, tail_head.position.y - 1));
		} else if (_direction == snakeDirection::Left) {
			_body.push_back(snakeSegment(tail_head.position.x + 1, tail_head.position.y));
		} else if (_direction == snakeDirection::Right) {
			_body.push_back(snakeSegment(tail_head.position.x - 1, tail_head.position.y));
		}
	}
}

void Snake::tick() {
	if (_body.empty() || _direction == snakeDirection::None) { return; }

	move();
	_checkCollisions();	
}

void Snake::move() {
	for (int i=_body.size() - 1; i > 0; i--) {
		_body[i].position = _body[i - 1].position;
	}

	// set head position
	if (_direction == snakeDirection::Left) {
		_body[0].position.x--;
	} else if (_direction == snakeDirection::Right) {
		_body[0].position.x++;
	} else if (_direction == snakeDirection::Up) {
		_body[0].position.y--;
	} else if (_direction == snakeDirection::Down) {
		_body[0].position.y++;
	}
}

void Snake::_checkCollisions() {
	if (_body.size() <= 4) { return; }
	auto &head = _body.front();

	for (auto itr = _body.begin() + 1; itr != _body.end(); itr++) {
		if (itr->position == head.position) {
			int segment = _body.end() - itr;
			cut(segment);
			break;
		}
	}
	return;	
}

void Snake::cut(int segment) {
	for (int i=0; i < segment; i++) {
		_body.pop_back();
	}
	Snake::_lives--;
	if (Snake::_lives <= 0) { lose(); }
}

void Snake::render(sf::RenderWindow &window) {
	if (_body.empty()) { return; }

	auto head = _body.begin();
	_bodyShape.setFillColor(sf::Color::Yellow);
	_bodyShape.setPosition(head->position.x * _block_size, head->position.y * _block_size);
	window.draw(_bodyShape);

	for (auto itr=_body.begin() + 1; itr < _body.end(); itr++) {
		_bodyShape.setFillColor(sf::Color::Green);
		_bodyShape.setPosition(itr->position.x * _block_size, itr->position.y * _block_size);
		window.draw(_bodyShape);
	}
}

// helper methods ===========================================================
void Snake::increaseScore() { _score++; _speed += 1 / (2 * log(_body.size())) * _speed_increment; }
void Snake::setDirection(snakeDirection dir) { _direction = dir; }
snakeDirection Snake::getDirection() { return _direction; }
int Snake::getSize() { return _body.size(); }
int Snake::getSpeed() { return _speed; }
void Snake::setSpeed(int speed) { _speed = speed; }
int Snake::getLives() { return Snake::_lives; }
int Snake::getScore() { return _score; }
bool Snake::hasLost() { return _lost; }
void Snake::lose() { _lost = true; }
void Snake::toggleLost() { _lost = !_lost; }
