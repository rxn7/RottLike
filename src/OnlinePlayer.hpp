#pragma once

#include "Engine/Entity.hpp"
#include "Engine/AssetManager.hpp"
#include "Engine/Networking/Client.hpp"
#include <SFML/Network.hpp>
#include "PlayerBase.hpp"
#include "Item/Sword.hpp"

class OnlinePlayer : public PlayerBase {
public:
    OnlinePlayer();
    virtual ~OnlinePlayer();

    void setPosition(float x, float y);
    void update(const sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;

    void updateMelee(float ang_deg);
};