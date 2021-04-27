#pragma once

#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual ~Entity();
    virtual void update(sf::Time dt, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

protected:
    sf::Texture* m_texture;
    sf::Sprite m_sprite;
};