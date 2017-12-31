//
//  Snake.cpp
//  SFML_test2
//
//  Created by Daniel Biehle on 12/26/17.
//  Copyright © 2017 Daniel Biehle. All rights reserved.
//

#include "Snake.hpp"

Snake::Snake(int size) {
	_size = size;
	_bodyShape.setSize(sf::Vector2f(_size - 1, _size - 1));
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
	_lives = 3;
	_lost = false;
	_speed = 500;
	
}

sf::Vector2i Snake::getPosition() {
	return (_body.empty() ? sf::Vector2i(1, 1) : _body.front().position);
}

void Snake::extend() {
	if (_body.empty()) { return; }

	snakeSegment& tail_head = _body[_size - 1];
	if (_body.size() > 1) {
		snakeSegment& bone = _body[_size - 2];
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
	if (--_lives <= 0) { lose(); }
}

void Snake::render(sf::RenderWindow &window) {
	if (_body.empty()) { return; }

	auto head = _body.begin();
	_bodyShape.setFillColor(sf::Color::Yellow);
	_bodyShape.setPosition(head->position.x * _size, head->position.y * _size);
	window.draw(_bodyShape);

	for (auto itr=_body.begin() + 1; itr < _body.end(); itr++) {
		_bodyShape.setFillColor(sf::Color::Green);
		_bodyShape.setPosition(itr->position.x * _size, itr->position.y * _size);
		window.draw(_bodyShape);
	}
}

// helper methods ===========================================================
void Snake::increaseScore() { _score++; }
void Snake::setDirection(snakeDirection dir) { _direction = dir; }
snakeDirection Snake::getDirection() { return _direction; }
int Snake::getSize() { return _size; }
int Snake::getSpeed() { return _speed; }
int Snake::getLives() { return _lives; }
int Snake::getScore() { return _score; }
bool Snake::hasLost() { return _lost; }
void Snake::lose() { _lost = true; }
void Snake::toggleLost() { _lost = !_lost; }
