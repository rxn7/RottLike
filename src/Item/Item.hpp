#pragma once

#include <SFML/Graphics.hpp>

#define ITEM_CTOR_PARAMS PlayerBase* p_holder

class PlayerBase;

class Item {
public:
    Item();
    Item(ITEM_CTOR_PARAMS);
    virtual ~Item();

    void setHolder(ITEM_CTOR_PARAMS);

    PlayerBase* getHolder();
    bool isHeldByLocalPlayer() const;

    virtual void draw(sf::RenderWindow& window) {}
    virtual void update(const sf::Time& dt) {}
    virtual void updateMelee(float ang_deg) {}
    virtual sf::Sprite* getSprite() { return nullptr; }

protected:
    PlayerBase* mp_holder;
};