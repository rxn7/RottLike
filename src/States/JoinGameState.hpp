#pragma once

#include "Engine/StateMachine/State.hpp"
#include "Engine/GUI/Textbox.hpp"
#include "Engine/GUI/Button.hpp"
#include "Engine/Networking/Client.hpp"
#include "GameState.hpp"

class JoinGameState : public RottEngine::State{
public:
    JoinGameState();
    ~JoinGameState();

    void processEvent(const sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
    void processPacket(sf::Packet& packet, sf::Uint8 type) override {}

private:
    void tryConnect();

private:
    RottEngine::Client* mp_client;
    RottEngine::GUI::Button m_connect_btn;
    RottEngine::GUI::Textbox m_ip_field;
    RottEngine::GUI::Textbox m_nick_field;
    sf::Text m_ip_text;
    sf::Text m_nick_text;
};