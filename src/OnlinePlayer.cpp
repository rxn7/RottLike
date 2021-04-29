#include "OnlinePlayer.hpp"

OnlinePlayer::~OnlinePlayer(){
    
}

OnlinePlayer::OnlinePlayer() {
    m_sprite.setTexture(*RottEngine::AssetManager::getTexture("res/sprites/online_player.png"));
    m_sprite.setScale(3,3);

    m_nickname_text.setFont(*RottEngine::AssetManager::getFont("res/font.ttf"));
    m_nickname_text.setScale(0.6, 0.6);
    m_nickname_text.setString("nickname_here");
}

void OnlinePlayer::setPosition(float x, float y){
    m_sprite.setPosition(x, y);
    m_nickname_text.setPosition(x, y-8);
}

void OnlinePlayer::setNickname(const std::string& nickname){
    m_nickname_text.setFillColor(sf::Color::Blue);
    m_nickname_text.setString(nickname);
    m_nickname_text.setOrigin(m_nickname_text.getGlobalBounds().width/2, 0);
    m_nickname_text.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y - 5);
}

void OnlinePlayer::update(const sf::Time& dt) {
}

void OnlinePlayer::draw(sf::RenderWindow& window){
    window.draw(m_sprite);
    window.draw(m_nickname_text);
}

std::string OnlinePlayer::getNickname() const {
    return m_nickname_text.getString();
}