#pragma once
#include <SFML/Graphics.hpp>

namespace RottEngine{
    class Entity {
    public:
        virtual ~Entity() {}
        virtual void update(const sf::Time& dt) = 0;
        virtual void draw(sf::RenderWindow& window);

    protected:
        sf::Texture* m_texture;
        sf::Sprite m_sprite;
    };
}