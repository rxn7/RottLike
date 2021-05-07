#pragma once

#include <SFML/Graphics.hpp>
#include "MeleeWeapon.hpp"
#include "Engine/AssetManager.hpp"
#include "Engine/Input.hpp"
#include <cmath>

class Sword : public MeleeWeapon {
public:
    Sword();
    Sword(PlayerBase* p_holder);
    virtual ~Sword();
    
    void draw(sf::RenderWindow& window) override;
    void update(const sf::Time& dt) override;

private:
    void init();
};