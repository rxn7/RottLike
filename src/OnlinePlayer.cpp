#include "OnlinePlayer.hpp"

OnlinePlayer::~OnlinePlayer(){
    
}

OnlinePlayer::OnlinePlayer() : m_nametag(this) {
    m_sprite.setTexture(*RottEngine::AssetManager::getTexture("res/sprites/online_player.png"));
    m_sprite.setScale(3,3);
    RottEngine::Utils::center(&m_sprite);
}

void OnlinePlayer::setPosition(float x, float y){
    m_sprite.setPosition(x, y);
    m_nametag.update();
}

void OnlinePlayer::setNickname(const std::string& nickname){
    m_nickname = nickname;
    m_nametag.setName(nickname.c_str(), sf::Color::White);
}

void OnlinePlayer::update(const sf::Time& dt) {
}

void OnlinePlayer::draw(sf::RenderWindow& window){
    window.draw(m_sprite);
    m_nametag.draw(window);
}

std::string OnlinePlayer::getNickname() const {
    return m_nickname;
}