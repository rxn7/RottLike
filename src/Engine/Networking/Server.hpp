#pragma once

#include "ServerClient.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

namespace RottEngine{
    class Server{
    public:
        ~Server();
        Server();
        void update();
        void handleConnections();
        void receivePackets();
        void disconnectClient(ServerClient* p_client, sf::Uint8 slot);
        void sendPacket(ServerClient* p_client, sf::Packet& packet);
        void sendPacketToAll(sf::Packet& packet, ServerClient* p_exclude = nullptr);

    private:
        sf::Uint8 getSlot(ServerClient* p_client);

    private:
        sf::TcpListener m_listener;
        sf::SocketSelector m_selector;

        std::vector<ServerClient*> m_clients;
    };
}