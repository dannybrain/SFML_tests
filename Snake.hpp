//
//  Snake.hpp
//  SFML_test2
//
//  Created by Daniel Biehle on 12/26/17.
//  Copyright © 2017 Daniel Biehle. All rights reserved.
//

#ifndef Snake_hpp
#define Snake_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

struct snakeSegment {
    snakeSegment(int x, int y) : position(x, y) {};
    sf::Vector2i position;
};

using snakeContainer = std::vector<snakeSegment>;

enum class snakeDirection {
    None,
    Up,
    Down,
    Left,
    Right
};

class Snake {
private:
    snakeContainer _body;
    sf::RectangleShape _bodyShape;
    snakeDirection _direction;
    int _size;
    int _speed;
    int _speed_increment;
    int _lives;
    int _score;
    bool _lost;
    void _checkCollisions();
    
public:
    Snake(int size);
    ~Snake();
    
    int getSize();
    int getSpeed();
    sf::Vector2i getPosition();
    snakeDirection getDirection();
    void setDirection(snakeDirection dir);
    int getScore();
    int getLives();
    bool hasLost();
    void increaseScore();
    
    void lose(); //handle lose rules
    void toggleLost();
    void extend();
    void reset();
    void move();
    void tick(); // fixed time step move
    void cut(int segment);
    void render(sf::RenderWindow& window);

};

#endif /* Snake_hpp */
