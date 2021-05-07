#include "Sword.hpp"
#include "PlayerBase.hpp"
#include "Game.hpp"

Sword::~Sword(){

}

Sword::Sword(){
    init();
}

Sword::Sword(PlayerBase* p_holder) : MeleeWeapon(p_holder) {
    init();
}

void Sword::init(){
    RottEngine::AssetManager::addTexture("res/sprites/sword.png");
    m_sprite.setTexture(*RottEngine::AssetManager::getTexture("res/sprites/sword.png"));
    
    sf::FloatRect sprite_rect = m_sprite.getLocalBounds();
    m_sprite.setOrigin(sprite_rect.width/2, sprite_rect.height+10);
}

void Sword::update(const sf::Time& dt){
    updatePosAndRot();
}

void Sword::draw(sf::RenderWindow& window){
    window.draw(m_sprite);
}