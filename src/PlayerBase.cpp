#include "PlayerBase.hpp"

PlayerBase::~PlayerBase(){
    delete mp_held_item;
}

PlayerBase::PlayerBase(PlayerType type) : m_type(type), m_nametag(this) {
}

std::string PlayerBase::getNickname() const {
    return m_nickname;
}

Item* PlayerBase::getHeldItem() const {
    return mp_held_item;
}

void PlayerBase::setNickname(const std::string& nick){
    m_nickname = nick;
    m_nametag.setName(nick.c_str(), isLocal() ? sf::Color::Yellow : sf::Color::White);
}

void PlayerBase::setItem(Item* p_item){
    mp_held_item = p_item;
}

bool PlayerBase::isLocal() const{
    return m_type == LOCAL;
}