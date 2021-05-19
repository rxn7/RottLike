#pragma once

#include "../Engine/StateMachine/State.hpp"
#include "../Engine/Rendering/Tilemap.hpp"
#include "../Engine/AssetManager.hpp"
#include "../FpsTimer.hpp"
#include "../LocalPlayer.hpp"
#include "../Chat.hpp"

class GameState : public RottEngine::State{
public:
    GameState(RottEngine::Client* p_client);
    ~GameState();

    void processEvent(const sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
    void processPacket(sf::Packet& packet, sf::Uint8 type) override;

    LocalPlayer* getPlayer();

private:
    Chat m_chat;

    RottEngine::Tilemap m_tilemap;

    sf::View m_camera, m_gui_camera;

    LocalPlayer* mp_player;
    RottEngine::Client* mp_client;

    FpsTimer m_fps_timer;
    sf::Text m_pos_text;
    sf::Clock m_tick_rate_clock;
};
