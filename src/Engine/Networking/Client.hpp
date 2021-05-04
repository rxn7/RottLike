#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <unordered_map>
#include "Packets.hpp"
#include "OnlinePlayer.hpp"
#include "Chat.hpp"

class OnlinePlayer;

namespace RottEngine{
    class Client{
    public:
        ~Client();

        bool connect(const char* address, unsigned short port, const std::string& nickname);
        void receivePackets();
        void sendPacket(sf::Packet& packet);
        const std::unordered_map<sf::Uint8, OnlinePlayer*>& getOnlinePlayers() const;
        const std::string getNickname() const;

    private:
        std::string m_nickname;
        sf::TcpSocket m_socket;
        std::thread m_update_thread;
        std::unordered_map<sf::Uint8, OnlinePlayer*> m_online_players;
    };
}