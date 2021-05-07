#pragma once

#include "Engine/Entity.hpp"

#define ITEM_CTOR_PARAMS RottEngine::Entity* p_holder, bool is_local

class Item {
public:
    Item();
    Item(RottEngine::Entity* p_holder, bool is_local=true);
    virtual ~Item();

    void setHolder(RottEngine::Entity* p_holder, bool is_local=true);

    RottEngine::Entity* getHolder();
    bool isHeldByLocalPlayer() const;

    virtual void draw(sf::RenderWindow& window) {}
    virtual void update(const sf::Time& dt) {}

private:
    bool m_is_local; // Is the item held by local player
    RottEngine::Entity* mp_holder;
};