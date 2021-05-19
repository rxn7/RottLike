#include "NameTag.hpp"

NameTag::NameTag(RottEngine::Entity* entity) : mp_entity(entity){
    m_text.setScale(0.6, 0.6); 
    m_text.setFont(*RottEngine::AssetManager::getFont("res/font.TTF"));
    m_text.setOutlineThickness(3);
    m_text.setOutlineColor(sf::Color::Black);
    RottEngine::Utils::center(&m_text);
}

void NameTag::setName(const std::string& name, sf::Color color){
    std::cout << name << "." << std::endl;
    m_text.setString(name);
    m_text.setFillColor(color);
    RottEngine::Utils::center(&m_text);
}

void NameTag::update(){
    sf::Vector2f pos = mp_entity->getSprite()->getPosition();    
    pos.y -= 30;
    m_text.setPosition(pos);
}

void NameTag::draw(sf::RenderWindow& window){
    window.draw(m_text);
}
