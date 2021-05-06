#include "Game.hpp"

#define TICK_RATE 0.0416 // 24 tickrate

Game::~Game(){
    delete mp_window;
    delete m_state;
}

std::mutex packets_mutex;

Game* Game::instance;

Game::Game(){
    instance = this;

    RottEngine::AssetManager::addFont("res/font.ttf");

    m_state = new SplashScreenState();

    mp_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Rott Like", sf::Style::Titlebar | sf::Style::Close);
    sf::Clock deltaClock;

    while (mp_window->isOpen()) {
        // Dont do anything if the current state isn't ready
        if(!m_state->isReady()){
            continue;
        }
        
        if(m_change_state){
            m_state = m_new_state;
            m_change_state = false;
            continue;
        }

        sf::Time dt = deltaClock.restart();
        sf::Event event;
        while (mp_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed){ 
                mp_window->close(); 
                return;
            }
            
            m_state->processEvent(event);
        }

        processPackets();

        RottEngine::Input::update(*mp_window);

        mp_window->clear();
        
        m_state->update(dt);
        m_state->draw(*mp_window);

        mp_window->display();
    }

    RottEngine::AssetManager::cleanup();
}

void Game::processPackets(){
    if(m_state != nullptr && m_state->isReady()){
        packets_mutex.lock();
        while(m_packets.size() > 0){
            sf::Packet packet = m_packets.front();
            sf::Uint8 type;
            packet >> type;

            m_state->processPacket(packet, type);

            m_packets.pop();
        }
        packets_mutex.unlock();
    }
}

void Game::changeState(RottEngine::State* new_state){
    instance->m_change_state = true;
    instance->m_new_state = new_state;
}

void Game::addPacket(sf::Packet& packet){
    packets_mutex.lock();
    instance->m_packets.push(packet);
    packets_mutex.unlock();
}

sf::RenderWindow* Game::getWindow(){
    return instance->mp_window;
}