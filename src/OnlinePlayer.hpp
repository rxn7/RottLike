#pragma once

#include "Engine/Entity.hpp"
#include "Engine/AssetManager.hpp"
#include "Engine/Networking/Client.hpp"
#include <SFML/Network.hpp>
 
class OnlinePlayer : public RottEngine::Entity {
public:
    OnlinePlayer();
    virtual ~OnlinePlayer();
    void setPosition(float x, float y);
    void update(sf::Time dt, sf::RenderWindow& window) override;
};