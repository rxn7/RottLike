#include "Game.hpp"
#include "Engine/Networking/NetworkManager.hpp"

#define WIDTH 640
#define HEIGHT 480

int main(int argc, const char** argv){
    if(RottEngine::NetworkManager::init() == NETWORK_CLIENT){
        Game game;
    }else{
        RottEngine::Server server;
    }

    std::cin.get();
    std::cin.get();
}