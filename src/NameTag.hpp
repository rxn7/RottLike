#pragma once

#include <SFML/Graphics.hpp>
#include "Engine/Entity.hpp"
#include "Engine/AssetManager.hpp"
#include "Engine/Utils.hpp"

class NameTag {
public:
    NameTag(RottEngine::Entity* entity);
    void setName(const std::string& name, sf::Color color);
    void update();
    void draw(sf::RenderWindow& window);

private:
    RottEngine::Entity* mp_entity;
    sf::Text m_text;
};