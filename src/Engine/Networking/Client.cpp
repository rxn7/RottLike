#include "Client.hpp"
#include "Game.hpp"

class Game;

namespace RottEngine{
    Client::~Client(){
        m_socket.disconnect();
        m_update_thread.join();

        for(auto& player : m_online_players){
            delete player.second;
        }
    }

    bool Client::connect(const char* address, unsigned short port, const std::string& nickname){
        if(m_socket.connect(address, port) != sf::Socket::Done){
            std::cerr << "Couldn't connect to the server!" << std::endl;
            return false;
        }

        std::cout << "Connected to the server!" << std::endl;
        m_update_thread = std::thread(&Client::receivePackets, this);

        m_nickname = nickname;

        sf::Packet nickname_packet;
        nickname_packet << sf::Uint8(CLIENT_CONNECTED) << nickname;
        sendPacket(nickname_packet);

        return true;
    }

    void Client::receivePackets(){
        while(true){
            sf::Packet received_packet;
            if(m_socket.receive(received_packet) == sf::Socket::Done){
                if(!received_packet){
                    std::cerr << "Failed to receive packet!" << std::endl;
                    exit(-1);
                    return;
                }

                Game::addPacket(received_packet);
            }
        }
    }

    void Client::sendPacket(sf::Packet& packet) {
        if(packet.getDataSize() <= 0 || (m_socket.send(packet) != sf::Socket::Done)){
            std::cerr << "Couldn't send packet!" << std::endl;
            exit(-1);
        }
    }

    std::unordered_map<sf::Uint8, OnlinePlayer*>* Client::getOnlinePlayers() {
        return &m_online_players;
    }

    const std::string Client::getNickname() const {
        return m_nickname;
    }
}
