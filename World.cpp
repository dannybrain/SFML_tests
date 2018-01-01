//
//  World.cpp
//  SFML_test2
//
//  Created by Daniel Biehle on 12/26/17.
//  Copyright © 2017 Daniel Biehle. All rights reserved.
//

#include "World.hpp"

World::World(sf::Vector2i wsize) {
	_block_size = 32;

	_window_size = wsize;
	respawn_apple();
	_appleShape.setFillColor(sf::Color::Red);
	_appleShape.setRadius(_block_size / 2);

	for(int i = 0; i < 4; i++) {
       _bounds[i].setFillColor(sf::Color(150,0,0));
       if(((i + 1) % 2)) {
        	_bounds[i].setSize(sf::Vector2f(_window_size.x, _block_size)); 
        } else {
	        _bounds[i].setSize(sf::Vector2f(_block_size, _window_size.y));
		}

		if (i < 2) {
			_bounds[i].setPosition(0, 0);
		} else {
			_bounds[i].setOrigin(_bounds[i].getSize());
			_bounds[i].setPosition(sf::Vector2f(_window_size));
		}

	}

}

World::~World() {}
int World::getBlockSize() { return _block_size; }

void World::respawn_apple() {
	int max_x = (_window_size.x / _block_size) - 2;
	int max_y = (_window_size.y / _block_size) - 2;
	_items = sf::Vector2i( rand() % max_x + 1, rand() % max_y + 1);
	_appleShape.setPosition(_items.x * _block_size, _items.y * _block_size);
}

void World::update(Snake &player) {
	if (player.getPosition() == _items) {
		player.extend();
		player.increaseScore();
		respawn_apple();
	}

	// check borders
	int grid_x = _window_size.x / _block_size;
	int grid_y = _window_size.y / _block_size;

	if (player.getPosition().x <= 0 || player.getPosition().y <= 0 ||
		player.getPosition().x >= grid_x - 1 || player.getPosition().y >= grid_y - 1) {
		player.lose();
	}
}

void World::render(sf::RenderWindow &window) {
	for (int i=0; i < 4; i++) {
		window.draw(_bounds[i]);
	}
	window.draw(_appleShape);
}



