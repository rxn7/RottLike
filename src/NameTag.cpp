#include "NameTag.hpp"

NameTag::NameTag(RottEngine::Entity* entity) : mp_entity(entity){
    m_text.setScale(0.6, 0.6); 
    m_text.setFont(*RottEngine::AssetManager::getFont("res/font.ttf"));
}

void NameTag::setName(const char* name, sf::Color color){
    m_text.setString(name);
    m_text.setFillColor(color);
}

void NameTag::update(){
    sf::Vector2f pos = mp_entity->getSprite()->getPosition();    
    pos.y += 10;
    m_text.setPosition(pos);
}

void NameTag::draw(sf::RenderWindow& window){
    window.draw(m_text);
}