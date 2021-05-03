#pragma once

#include "Engine/StateMachine/State.hpp"
#include "Engine/GUI/Button.hpp"
#include "Engine/AssetManager.hpp"
#include "Engine/Networking/Server.hpp"
#include "Game.hpp"

class MainMenuState : public RottEngine::State {
public:
    MainMenuState();
    ~MainMenuState();

    void processEvent(const sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
    
private:
    void hostGame();
    void joinGame();

private:
    RottEngine::GUI::Button m_host_game_button;
    RottEngine::GUI::Button m_join_game_button;
};
