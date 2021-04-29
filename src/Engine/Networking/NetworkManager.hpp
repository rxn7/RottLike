#pragma once

#include <SFML/Network.hpp>
#include <iostream>

#define NETWORK_SERVER 0
#define NETWORK_CLIENT 1

#include "Server.hpp"

namespace RottEngine{
    class NetworkManager{
    public:
        static int init();
    };
}