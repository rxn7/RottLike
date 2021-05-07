#include "OnlinePlayer.hpp"

OnlinePlayer::~OnlinePlayer(){
}

OnlinePlayer::OnlinePlayer() : PlayerBase(PlayerType::ONLINE) {
    m_sprite.setTexture(*RottEngine::AssetManager::getTexture("res/sprites/online_player.png"));
    m_sprite.setScale(3,3);
    RottEngine::Utils::center(&m_sprite);
    m_nametag = NameTag(this);
}

void OnlinePlayer::setPosition(float x, float y){
    m_sprite.setPosition(x, y);
    m_nametag.update();
}

void OnlinePlayer::update(const sf::Time& dt) {
}

void OnlinePlayer::draw(sf::RenderWindow& window){
    window.draw(m_sprite);
    m_nametag.draw(window);
}