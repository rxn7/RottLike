#pragma once

#include "Item.hpp"

class MeleeWeapon : public Item {
public:
    MeleeWeapon();
    MeleeWeapon(ITEM_CTOR_PARAMS);
    
    virtual ~MeleeWeapon();
    virtual void update(const sf::Time& dt) override {} 
    virtual void draw(sf::RenderWindow& window) override {} 
};