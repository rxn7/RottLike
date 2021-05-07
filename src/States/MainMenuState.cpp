#include "MainMenuState.hpp"
#include "Engine/Networking/Server.hpp"

MainMenuState::MainMenuState(){
    m_host_game_button = RottEngine::GUI::Button(860/4, 640/2, 860/2, 640, RottEngine::AssetManager::getFont("res/font.ttf"), "Host New Game", std::bind(&hostGame, this));
    m_host_game_button.setCharSize(25);

    m_join_game_button = RottEngine::GUI::Button(860 - (860/4), 640/2, 860/2, 640, RottEngine::AssetManager::getFont("res/font.ttf"), "Join a Game", std::bind(&joinGame, this));
    m_join_game_button.setCharSize(25);
    
    m_ready = true;
}

MainMenuState::~MainMenuState(){}

void MainMenuState::hostGame(){
    Game::getWindow()->close();

    // Start new server
    RottEngine::Server server;
}

void MainMenuState::joinGame(){
    Game::changeState(new JoinGameState());
}

void MainMenuState::draw(sf::RenderWindow& window){
    m_host_game_button.draw(window);
    m_join_game_button.draw(window);
}

void MainMenuState::update(const sf::Time& dt){
    m_host_game_button.update();
    m_join_game_button.update();
}

void MainMenuState::processEvent(const sf::Event& event){}