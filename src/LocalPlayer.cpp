#include "LocalPlayer.hpp"

LocalPlayer::LocalPlayer(){
    m_sprite.setTexture(*AssetManager::getTexture("res/sprites/player.png"));
    m_sprite.setScale(5,5);
}

LocalPlayer::~LocalPlayer(){ }

void LocalPlayer::update(sf::Time dt, sf::RenderWindow& window){
    sf::Vector2f moveDir;

    float speed = PLAYER_MOVE_SPEED * dt.asMilliseconds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ moveDir.y -= speed; }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){ moveDir.y += speed; }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){ moveDir.x -= speed; }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){ moveDir.x += speed; }

    m_sprite.move(moveDir);
}