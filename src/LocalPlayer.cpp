#include "LocalPlayer.hpp"
#include "Engine/Networking/Packets.hpp"

LocalPlayer::LocalPlayer(RottEngine::Client* p_client, const std::string& nickname) : mp_client(p_client), m_nickname(nickname){
    m_sprite.setTexture(*RottEngine::AssetManager::getTexture("res/sprites/player.png"));
    m_sprite.setScale(3,3);

    m_nickname_text.setFont(*RottEngine::AssetManager::getFont("res/font.ttf"));
    m_nickname_text.setScale(0.6, 0.6);
    m_nickname_text.setString(m_nickname);
    m_nickname_text.setOrigin(m_nickname_text.getGlobalBounds().width/2, 0);
}

LocalPlayer::~LocalPlayer(){ }

void LocalPlayer::update(const sf::Time& dt){
    sf::Vector2f move_dir;

    float speed = PLAYER_MOVE_SPEED * dt.asSeconds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ move_dir.y -= speed; }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){ move_dir.y += speed; }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){ move_dir.x -= speed; }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){ move_dir.x += speed; }

    m_sprite.move(move_dir);

    sf::Vector2f pos = m_sprite.getPosition();
    m_nickname_text.setPosition(pos.x, pos.y-8);
}

void LocalPlayer::update_network(){
    // If the position has changed, send the player moved packet to the server
    sf::Vector2f curr_pos = m_sprite.getPosition();

    if(m_previous_pos != curr_pos){
        sf::Packet player_moved_packed;
        player_moved_packed << sf::Uint8(CLIENT_PLAYER_MOVED) << curr_pos.x << curr_pos.y;
        
        mp_client->sendPacket(player_moved_packed);
    }

    m_previous_pos = curr_pos;
}

void LocalPlayer::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
    window.draw(m_nickname_text);
}