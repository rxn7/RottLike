#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <sstream>

#include "Engine/Networking/Client.hpp"
#include "Engine/AssetManager.hpp"
#include "FpsTimer.hpp"
#include "OnlinePlayer.hpp"
#include "LocalPlayer.hpp"

#define WIDTH 640
#define HEIGHT 480

class OnlinePlayer;

class Game{
public:
    Game();
    ~Game();
};