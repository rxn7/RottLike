#pragma once

#include "Item/Item.hpp"
#include "NameTag.hpp"

enum PlayerType { LOCAL, ONLINE };
class PlayerBase : public RottEngine::Entity {

public:
    PlayerBase(PlayerType type);
    virtual ~PlayerBase();

    bool isLocal() const;
    void setItem(Item* p_item);
    void setNickname(const std::string& nickname);
    
    std::string getNickname() const;
    Item* getHeldItem() const;

protected:
    PlayerType m_type;
    NameTag m_nametag;
    std::string m_nickname;
    Item* mp_held_item;
};
