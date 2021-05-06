#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <queue>

#include "Engine/StateMachine/State.hpp"
#include "Engine/AssetManager.hpp"
#include "Engine/Input.hpp"
#include "States/SplashScreenState.hpp"

#define WINDOW_WIDTH 860
#define WINDOW_HEIGHT 640

class OnlinePlayer;

class Game{
public:
    Game();
    ~Game();
    static void addPacket(sf::Packet& packet);
    static void changeState(RottEngine::State* new_state);
    static void processPacket(sf::Packet& packet, sf::Uint8 type);
    static sf::RenderWindow* getWindow();

private:
    void processPackets();

private:
    static Game* instance; 
    
    sf::RenderWindow* mp_window;

    std::queue<sf::Packet> m_packets;
    RottEngine::State* m_state;
    RottEngine::State* m_new_state;
    bool m_change_state=false;
};