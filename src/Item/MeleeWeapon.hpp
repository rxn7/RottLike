#pragma once

#include "Item.hpp"
#include "Engine/Input.hpp"

class MeleeWeapon : public Item {
public:
    MeleeWeapon();
    MeleeWeapon(ITEM_CTOR_PARAMS);
    
    virtual ~MeleeWeapon();
    virtual void update(const sf::Time& dt) override {} 
    virtual void draw(sf::RenderWindow& window) override {} 
    void updateMelee(float ang_deg) override;
    sf::Sprite* getSprite() override;
    
protected:
    void updatePosAndRot();

protected:
    sf::Sprite m_sprite;

private:
    float prev_rot;
};