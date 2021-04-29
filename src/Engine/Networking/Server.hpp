#pragma once

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
        void disconnectClient(sf::TcpSocket* p_client, sf::Uint8 slot);
        void sendPacket(sf::TcpSocket* p_client, sf::Packet& packet);

    private:
        sf::TcpListener m_listener;
        sf::SocketSelector m_selector;

        // Todo: move it to a single class
        std::vector<sf::TcpSocket*> m_clients;
        std::vector<std::string> m_client_nicknames;
    };
}