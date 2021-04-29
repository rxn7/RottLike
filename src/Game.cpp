#include "Game.hpp"

#define TICK_RATE 0.0416 // 24 tickrate

Game::~Game(){
    delete m_state;
}

// TODO: Main Menu with proper GUI

Game::Game(){
    RottEngine::AssetManager::addFont("res/font.ttf");
    RottEngine::AssetManager::addTexture("res/sprites/player.png");
    RottEngine::AssetManager::addTexture("res/sprites/online_player.png");
    
    m_state = new GameState();

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Rott Like"); window.setFramerateLimit(144);
    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){ 
                window.close(); 
                return;
            }
            
            m_state->processEvent(event);
        }

        window.clear();
        
        m_state->update(dt);
        m_state->draw(window);

        window.display();
    }
    
    RottEngine::AssetManager::cleanup();
}