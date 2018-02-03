//
//  EventManager.hpp
//  SFML_test2
//
//  Created by Daniel Biehle on 12/26/17.
//  Copyright © 2017 Daniel Biehle. All rights reserved.
//

#ifndef EventManager_hpp
#define EventManager_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>

enum class EventType {
    KeyDown = sf::Event::KeyPressed,
    KeyUp = sf::Event::KeyReleased,
    MButtonDown = sf::Event::MouseButtonPressed,
    MButtonUp = sf::Event::MouseButtonReleased,
    MouseWheel = sf::Event::MouseWheelMoved,
    WindowResized = sf::Event::Resized,
    GainedFocus = sf::Event::GainedFocus,
    LostFocus = sf::Event::LostFocus,
    MouseEntered = sf::Event::MouseEntered,
    MouseLeft = sf::Event::MouseLeft,
    Closed = sf::Event::Closed,
    TextEntered = sf::Event::TextEntered,
    Keyboard = sf::Event::Count + 1, 
    Mouse,
    Joystick
};

struct EventInfo {
    EventInfo() { keyCode = 0; }
    EventInfo(int event) : keyCode(event) {};
    union {
        int keyCode;
    };
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails {
    EventDetails(const std::string& bindName) : name(bindName) {
        Clear(); 
    }
    std::string name;
    sf::Vector2i size;
    sf::Uint32 textEntered;
    sf::Vector2i mouse;
    int mouseWheelDelta;
    int keyCode; // Single key code.

    void Clear(){
        size = sf::Vector2i(0, 0);
        textEntered = 0;
        mouse = sf::Vector2i(0, 0);
        mouseWheelDelta = 0;
        keyCode = -1;
    }

};

struct Binding {
    Binding(const std::string& lname) : name(lname), details(lname), count(0) { }

    Events events;
    EventDetails details;
    std::string name;
    int count;                    // Count of events that are "happening".

    void BindEvent(EventType type, EventInfo info = EventInfo()) {
        events.emplace_back(type, info);
    }
};

using Bindings = std::unordered_map<std::string, Binding*>;

#endif