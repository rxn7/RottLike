#include "MeleeWeapon.hpp"
#include "PlayerBase.hpp"
#include "Game.hpp"

MeleeWeapon::MeleeWeapon() : Item() {
}

MeleeWeapon::MeleeWeapon(ITEM_CTOR_PARAMS) : Item(p_holder) {
}

MeleeWeapon::~MeleeWeapon() {

}

void MeleeWeapon::updateMelee(float ang_deg){
    m_sprite.setRotation(ang_deg);
}

void MeleeWeapon::updatePosAndRot(){
    // Update sprite pos
    sf::Vector2f pos = mp_holder->getSprite()->getPosition();
    pos.y += 5; // Move the sprite down a bit
    m_sprite.setPosition(pos);

    // Update sprite rot
    sf::Vector2f mouse_pos = Game::getWindow()->mapPixelToCoords(RottEngine::Input::getMousePos());

    float dx = mouse_pos.x - m_sprite.getPosition().x;
    float dy = mouse_pos.y - m_sprite.getPosition().y;

    const float PI = 3.14159265;
    float ang_deg = (atan2f(dy, dx) * 180 / PI) + 90;

    m_sprite.setRotation(ang_deg);

    if(prev_rot != ang_deg){
        if(isHeldByLocalPlayer()){
            RottEngine::Client* mp_client = ((LocalPlayer*)mp_holder)->getClient();
            
            sf::Packet melee_update_packet;
            melee_update_packet << sf::Uint8(CLIENT_MELEE_UPDATE) << ang_deg;

            mp_client->sendPacket(melee_update_packet);
        }
    }

    prev_rot = ang_deg;
}

sf::Sprite* MeleeWeapon::getSprite() {
    return &m_sprite;
}