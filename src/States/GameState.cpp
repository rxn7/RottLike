#include "GameState.hpp"

#define TICK_RATE 0.0416 // 24 tick rate

GameState::~GameState(){
    delete mp_player;
}

GameState::GameState() {
    RottEngine::AssetManager::addTexture("res/sprites/player.png");
    RottEngine::AssetManager::addTexture("res/sprites/online_player.png");
    RottEngine::AssetManager::addTexture("res/sprites/tileset.png");

    std::string server_ip, nickname;
    std::cout << "Enter the server's ip: ";
    std::cin >> server_ip;

    std::cout << "Enter your nickname: ";
    std::cin >> nickname;

    if(!m_client.connect(server_ip.c_str(), 26950, nickname)){
        std::cerr << "Couldn't connect to the server!" << std::endl;
        return;
    }

    mp_player = new LocalPlayer(&m_client, nickname);

    m_chat = Chat(&m_client, this);
    m_camera = sf::View(sf::Vector2f(0,0), sf::Vector2f(640, 480));
    m_gui_camera = sf::View(sf::Vector2f((float)860/2, (float)640/2), sf::Vector2f(860, 640));
    m_tilemap = RottEngine::Tilemap(RottEngine::AssetManager::getTexture("res/sprites/tileset.png"), 24, 24, 16, 64);

    m_pos_text.move(0, 30);
    m_pos_text.setString("x: ?\ny: ?");
    m_pos_text.setFont(*RottEngine::AssetManager::getFont("res/font.ttf"));

    m_ready = true;
}

void GameState::processPacket(sf::Packet& packet, sf::Uint8 type){
    switch(type){
        case SERVER_PLAYER_CONNECTED:{
            sf::Uint8 client_slot;
            std::string client_nickname;
            packet >> client_slot >> client_nickname;

            OnlinePlayer* new_player = new OnlinePlayer();
            new_player->setNickname(client_nickname);

            m_client.getOnlinePlayers()->insert({client_slot, new_player});
            std::cout << "Player with slot " << (int)client_slot << " and nick " << client_nickname << " has connected." << std::endl;
            break;
        }

        case SERVER_PLAYER_DISCONNECTED:{
            sf::Uint8 client_slot;
            packet >> client_slot;

            if(m_client.getOnlinePlayers()->count(client_slot)){
                OnlinePlayer* player = m_client.getOnlinePlayers()->at(client_slot);
                
                m_chat.addPlayerDisconnectedMessage(player->getNickname());
                std::cout << "Player with slot " << (int)client_slot << " and nick: " << player->getNickname() << " has disconnected." << std::endl;
                
                delete m_client.getOnlinePlayers()->at(client_slot);
                m_client.getOnlinePlayers()->erase(client_slot);
            }
            break;
        }

        case SERVER_PLAYER_MOVED:{
            sf::Uint8 client_slot;

            float px, py;
            packet >> client_slot >> px >> py;

            if(m_client.getOnlinePlayers()->count(client_slot)){
                m_client.getOnlinePlayers()->at(client_slot)->setPosition(px,py);
            }
            break;
        }

        case SERVER_CHAT:{
            sf::Uint8 slot;
            std::string msg;

            packet >> slot >> msg;
            OnlinePlayer* player = m_client.getOnlinePlayers()->at(slot);

            if(player == nullptr){
                std::cout << "[CHAT] " << "Error receiving a message. Player pointer is null." << std::endl;
                return;
            }

            std::string nick = player->getNickname();

            std::cout << "[CHAT] " << nick << ": " << msg << std::endl;

            m_chat.addMessage(nick, msg);
            break;
        }
    }
}

void GameState::processEvent(const sf::Event& event){
    m_chat.processEvent(event);
}

void GameState::update(const sf::Time& dt){
    if(m_tick_rate_clock.getElapsedTime().asSeconds() >= TICK_RATE){
        m_tick_rate_clock.restart();
        mp_player->tick();

        sf::Vector2f player_pos = mp_player->getSprite()->getPosition();
        
        std::stringstream pos_text_stream;
        pos_text_stream << "x: " << (int)player_pos.x << "\n" << "y: " << (int)player_pos.y;
        m_pos_text.setString(pos_text_stream.str());
    }

    mp_player->update(dt);

    m_fps_timer.update(dt.asSeconds());
    m_chat.update();

    m_camera.setCenter(mp_player->getSprite()->getPosition());
    m_chat.update();
}

void GameState::draw(sf::RenderWindow& window){
    // WORLD
    window.setView(m_camera);
    m_tilemap.draw(window, sf::RenderStates::Default);

    for(auto& player : *m_client.getOnlinePlayers()){
        player.second->draw(window);
    }

    mp_player->draw(window);
    
    // GUI
    window.setView(m_gui_camera);
    window.draw(m_pos_text);
    m_fps_timer.draw(window);
    m_chat.draw(window);
}

LocalPlayer* GameState::getPlayer() const{
    return mp_player;
}