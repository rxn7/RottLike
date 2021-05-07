#pragma once

#include <cmath>
#include "Engine/Networking/Client.hpp"
#include "Engine/Entity.hpp"
#include "Engine/AssetManager.hpp"
#include <SFML/Network.hpp>
#include "Nametag.hpp"
#include "PlayerBase.hpp"

#define PLAYER_MOVE_SPEED 150.0f
 
class LocalPlayer : public PlayerBase {
public:
    LocalPlayer(RottEngine::Client* p_client);
    virtual ~LocalPlayer();

    void update(const sf::Time& dt) override;
    void tick();
    void draw(sf::RenderWindow& window) override;
    void setCanMove(bool value);

    RottEngine::Client* getClient() const;
    
private:
    bool m_can_move=true;
    sf::Vector2f m_previous_pos;
    RottEngine::Client* mp_client;
};