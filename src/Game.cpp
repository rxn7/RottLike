#include "Game.hpp"

#define TICK_RATE 0.0416 // 24 tickrate

Game::~Game(){
    
}

Game::Game(){
    std::cout << "Enter the server's ip: ";
    std::string server_ip;
    std::cin >> server_ip;

    RottEngine::AssetManager::addFont("res/font.ttf");
    RottEngine::AssetManager::addTexture("res/sprites/player.png");
    RottEngine::AssetManager::addTexture("res/sprites/online_player.png");
    
    RottEngine::Client client;
    if(!client.connect(server_ip.c_str(), 26950)){
        return;
    }

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Rott Like"); window.setFramerateLimit(144);
    sf::Clock deltaClock, tickRateTimer;

    FpsTimer fpsTimer;
    LocalPlayer localPlayer(&client);

    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){ window.close(); }
        }

        window.clear();
        
        if(tickRateTimer.getElapsedTime().asSeconds() >= TICK_RATE){
            tickRateTimer.restart();

            localPlayer.update_network();
        }

        localPlayer.update(dt, window);
        fpsTimer.update(dt.asSeconds());
        
        for(auto& player : client.getOnlinePlayers()){
            player.second->draw(window);
        }

        localPlayer.draw(window);
        fpsTimer.draw(window);

        window.display();
    }
    
    RottEngine::AssetManager::cleanup();
}