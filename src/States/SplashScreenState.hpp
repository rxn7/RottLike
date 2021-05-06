#pragma once

#include "Engine/StateMachine/State.hpp"
#include "Engine/AssetManager.hpp"
#include "States/MainMenuState.hpp"
#include "Engine/Utils.hpp"

class SplashScreenState : public RottEngine::State{
public:
    SplashScreenState();
    ~SplashScreenState();

    void processEvent(const sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
    void processPacket(sf::Packet& packet, sf::Uint8 type) override {}

private:
    void skip();
    sf::Clock m_intro_clock;
    sf::Sprite m_logo;
    sf::Text m_skip_text;
    bool m_skipped;
};