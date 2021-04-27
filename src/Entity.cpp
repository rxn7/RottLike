#include "Entity.hpp"

Entity::~Entity() { }

void Entity::draw(sf::RenderWindow& window){
    window.draw(m_sprite);
}

void Entity::update(sf::Time dt, sf::RenderWindow& window) { }