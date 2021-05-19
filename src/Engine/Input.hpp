#pragma once

#include <SFML/Graphics.hpp>

namespace RottEngine{
    class Input {
    public:
        static void update(sf::RenderWindow& window);
        static sf::Vector2i getMousePos();
    private:
        Input() {}

    private: 
        static sf::Vector2i mouse_pos;
    };
}
