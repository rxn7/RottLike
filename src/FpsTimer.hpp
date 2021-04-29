#pragma once

#include <string>
#include <iomanip>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Engine/AssetManager.hpp"

class FpsTimer{
public:
    FpsTimer();
    void draw(sf::RenderWindow& window);
    void update(float dt);

private:
    sf::Text m_text;
    sf::Clock m_clock;
};