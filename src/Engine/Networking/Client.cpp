#include "Client.hpp"

namespace RottEngine{
    Client::~Client(){
        m_update_thread.join();

        for(auto& player : m_online_players){
            delete player.second;
        }
    }

    bool Client::connect(const char* address, unsigned short port){
        if(m_socket.connect(address, port) != sf::Socket::Done){
            std::cerr << "Could not connect to the server!" << std::endl;
            return false;    
        }
        
        std::cout << "Connected to the server!" << std::endl;
        m_update_thread = std::thread(&receivePackets, this);

        return true;    
    }

    void Client::receivePackets(){
        while(true){
            sf::Packet received_packet;
            if(m_socket.receive(received_packet) == sf::Socket::Done){            
                sf::Uint8 packet_type;
                received_packet >> packet_type;

                if(!received_packet){
                    std::cerr << "Failed to receive packet!" << std::endl;
                    return;
                }
                switch(packet_type){
                    case SERVER_PLAYER_CONNECTED:{
                        sf::Uint8 client_slot;
                        received_packet >> client_slot;

                        if(!m_online_players.count(client_slot)){
                            m_online_players.insert({client_slot, new OnlinePlayer()});
                            std::cout << "Player with slot " << (int)client_slot << " has connected." << std::endl;
                        }

                        break;
                    }

                    case SERVER_PLAYER_DISCONNECTED:{
                        sf::Uint8 client_slot;
                        received_packet >> client_slot;

                        if(m_online_players.count(client_slot)){
                            delete m_online_players[client_slot];
                            m_online_players.erase(client_slot);
                            std::cout << "Player with slot " << (int)client_slot << " has disconnected." << std::endl;
                        }

                        break;
                    }

                    case SERVER_PLAYER_MOVED:{
                        sf::Uint8 client_slot;
                        float px, py;
                        received_packet >> client_slot >> px >> py;

                        if(m_online_players.count(client_slot)){
                            m_online_players[client_slot]->setPosition(px,py);
                        }

                        break;
                    }
                }
                received_packet.clear();
            }
        }
    }

    void Client::sendPacket(sf::Packet& packet){
        if(packet.getDataSize() <= 0 || (m_socket.send(packet) != sf::Socket::Done)){
            std::cerr << "Couldn't send packet!" << std::endl;
        }
    }

    const std::unordered_map<sf::Uint8, OnlinePlayer*>& Client::getOnlinePlayers(){
        return m_online_players;
    }
}