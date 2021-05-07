#include "OnlinePlayer.hpp"

OnlinePlayer::~OnlinePlayer(){
}

OnlinePlayer::OnlinePlayer() : PlayerBase(PlayerType::ONLINE) {
    m_sprite.setTexture(*RottEngine::AssetManager::getTexture("res/sprites/online_player.png"));
    m_sprite.setScale(3,3);
    RottEngine::Utils::center(&m_sprite);
    m_nametag = NameTag(this);

    setItem(new Sword((PlayerBase*)this));
}

void OnlinePlayer::updateMelee(float ang_deg){
    if(mp_held_item != nullptr){
        mp_held_item->updateMelee(ang_deg);
    }
}

void OnlinePlayer::setPosition(float x, float y){
    m_sprite.setPosition(x, y);
    
    if(mp_held_item != nullptr){
        mp_held_item->getSprite()->setPosition(x, y+5);
    }
    
    m_nametag.update();
}

void OnlinePlayer::update(const sf::Time& dt) {
}

void OnlinePlayer::draw(sf::RenderWindow& window){
    window.draw(m_sprite);
    m_nametag.draw(window);

    if(mp_held_item != nullptr){
        mp_held_item->draw(window);
    }
}