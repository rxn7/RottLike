#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <sstream>

#include "Engine/StateMachine/State.hpp"
#include "Engine/Networking/Client.hpp"
#include "Engine/AssetManager.hpp"
#include "FpsTimer.hpp"
#include "OnlinePlayer.hpp"
#include "LocalPlayer.hpp"
#include "States/GameState.hpp"

#define WIDTH 640
#define HEIGHT 480

class OnlinePlayer;

class Game{
public:
    Game();
    ~Game();

private:
    RottEngine::State* m_state;
};