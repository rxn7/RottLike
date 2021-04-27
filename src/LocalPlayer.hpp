#pragma once

#include "Entity.hpp"
#include "AssetManager.hpp"
#include <cmath>
 
#define PLAYER_MOVE_SPEED 400.0f

class LocalPlayer : public Entity {
public:
    LocalPlayer();
    virtual ~LocalPlayer();
    void update(sf::Time dt, sf::RenderWindow& window) override;
};