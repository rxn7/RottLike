#pragma once

#include <SFML/Graphics.hpp>

namespace RottEngine{
    namespace Utils{
        void center(sf::Text* object);
        void center(sf::Sprite* object);
        void center(sf::RectangleShape* object);

        void centerVer(sf::Text* object);
    }
}