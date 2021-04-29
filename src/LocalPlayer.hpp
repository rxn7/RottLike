#pragma once

#include "Engine/Networking/Client.hpp"
#include "Engine/Entity.hpp"
#include "Engine/AssetManager.hpp"
#include <SFML/Network.hpp>
#include <cmath>
 
#define PLAYER_MOVE_SPEED 150.0f

class LocalPlayer : public RottEngine::Entity {
public:
    LocalPlayer(RottEngine::Client* p_client, const std::string& nickname);
    virtual ~LocalPlayer();
    void update(const sf::Time& dt) override;
    void update_network();
    void draw(sf::RenderWindow& window) override;
    
private:
    sf::Vector2f m_previous_pos;
    RottEngine::Client* mp_client;
    NameTag m_nametag;
};