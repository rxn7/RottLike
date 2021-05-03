#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <sstream>

#include "Engine/Rendering/Tilemap.hpp"
#include "Engine/StateMachine/State.hpp"
#include "Engine/Networking/Client.hpp"
#include "Engine/AssetManager.hpp"
#include "Engine/Input.hpp"
#include "FpsTimer.hpp"
#include "OnlinePlayer.hpp"
#include "LocalPlayer.hpp"
#include "States/GameState.hpp"
#include "States/SplashScreenState.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class OnlinePlayer;

class Game{
public:
    Game();
    ~Game();
    static void changeState(RottEngine::State* new_state);
    static sf::RenderWindow* getWindow();

private:
    static Game* instance; 
    
    sf::RenderWindow* mp_window;

    RottEngine::State* m_state;
    RottEngine::State* m_new_state;
    bool m_change_state=false;
};