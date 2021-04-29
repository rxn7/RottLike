#include "GameState.hpp"

#define TICK_RATE 0.0416 // 24 tick rate

GameState::GameState() {
    std::string server_ip, nickname;
    std::cout << "Enter the server's ip: ";
    std::cin >> server_ip;

    std::cout << "Enter your nickname: ";
    std::cin >> nickname;

    if(!mp_client.connect(server_ip.c_str(), 26950, nickname)){
        return;
    }

    mp_player = new LocalPlayer(&mp_client, nickname);
}

GameState::~GameState(){
    delete mp_player;
}

void GameState::processEvent(const sf::Event& event){
    
}

void GameState::update(const sf::Time& dt){
    if(m_tick_rate_clock.getElapsedTime().asSeconds() >= TICK_RATE){
        m_tick_rate_clock.restart();

        mp_player->update_network();
    }

    mp_player->update(dt);
    m_fps_timer.update(dt.asSeconds());
}

void GameState::draw(sf::RenderWindow& window){
    for(auto& player : mp_client.getOnlinePlayers()){
        player.second->draw(window);
    }

    mp_player->draw(window);
    m_fps_timer.draw(window);
}