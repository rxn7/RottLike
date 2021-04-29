#include "Entity.hpp"

namespace RottEngine{
    void Entity::draw(sf::RenderWindow& window){
        window.draw(m_sprite);
    }
}