#include <iostream>
#include "EventManager.hpp"


int main(int argc, char **argv) {

    Events events;

    using Bindings = std::unordered_map<std::string, Binding*>;

    std::cout << "KeyDown = " <<  static_cast<int>(EventType::KeyDown)
              << "TextEntered = " << static_cast<int>(EventType::TextEntered)
              << "Keyboard = " << static_cast<int>(EventType::Keyboard)
              << "Joystick = " << static_cast<int>(EventType::Joystick)
              << std::endl;

}