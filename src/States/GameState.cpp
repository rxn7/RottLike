#include "GameState.hpp"

#define TICK_RATE 0.0416 // 24 tick rate

GameState::~GameState(){
    delete mp_player;
}

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

    m_camera = sf::View(sf::Vector2f(0,0), sf::Vector2f(640, 480));
    m_gui_camera = sf::View(sf::Vector2f((float)640/2, (float)480/2), sf::Vector2f(640, 480));
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

    m_camera.setCenter(mp_player->getSprite()->getPosition());
}

void GameState::draw(sf::RenderWindow& window){
    // WORLD
    window.setView(m_camera);

    for(auto& player : mp_client.getOnlinePlayers()){
        player.second->draw(window);
    }

    mp_player->draw(window);
    
    // GUI
    window.setView(m_gui_camera);
    m_fps_timer.draw(window);
}