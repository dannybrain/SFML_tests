//
//  World.hpp
//  SFML_test2
//
//  Created by Daniel Biehle on 12/26/17.
//  Copyright © 2017 Daniel Biehle. All rights reserved.
//
#ifndef World_hpp
#define World_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Snake.hpp"

class World {
private:
	sf::Vector2i _window_size;
	sf::Vector2i _items;
	int _block_size;

	sf::CircleShape _appleShape;
	sf::RectangleShape _bounds[4];

public:
	World(sf::Vector2i wsize);
	~World(); 

	void respawn_apple();
	int getBlockSize();
	void render(sf::RenderWindow& window);
	void update(Snake& player);
};

#endif