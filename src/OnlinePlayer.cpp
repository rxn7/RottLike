#include "OnlinePlayer.hpp"

OnlinePlayer::~OnlinePlayer(){
    
}

OnlinePlayer::OnlinePlayer() {
    m_sprite.setTexture(*RottEngine::AssetManager::getTexture("res/sprites/online_player.png"));
    m_sprite.setScale(3,3);
}

void OnlinePlayer::setPosition(float x, float y){
    m_sprite.setPosition(x, y);
}

void OnlinePlayer::update(sf::Time dt, sf::RenderWindow& window) {

}