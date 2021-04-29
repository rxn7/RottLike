#include "NetworkManager.hpp"

#define PORT 26950

namespace RottEngine{
    int NetworkManager::init(){
        char type;
        std::cout << "Do you want to host a new game? Y or N" << std::endl;
        std::cin >> type;

        return type == 'y' || type == 'Y' ? NETWORK_SERVER : NETWORK_CLIENT;
    }
}