#include "Server.hpp"
#include <unordered_map>
#include "Packets.hpp"

#define TICK_RATE 0.0416 // 24 tickrate
#define PORT 26950
namespace RottEngine{
    Server::~Server(){
        for(sf::TcpSocket* client : m_clients){
            delete client;
        }
    }

    Server::Server(){
        std::cout << "Server is starting on port " << PORT << "..." << std::endl;

        if(m_listener.listen(26950) != sf::Socket::Done){
            std::cerr << "Couldn't listen on port: " << PORT << "!!" << std::endl;
            return;
        }else{
            std::cout << "Server has started!" << std::endl;
        }

        m_selector.add(m_listener);

        sf::Clock tickRateClock;
        while(true){
            if(tickRateClock.getElapsedTime().asSeconds() >= TICK_RATE){
                tickRateClock.restart();
                update();
            }
        }

        std::cout << "Server is closing..."; 
    }

    void Server::update(){
        while(true){
            if(m_selector.wait()){
                if(m_selector.isReady(m_listener)){
                    handleConnections();
                }else{
                    receivePackets();
                }
            }
        }
    }

    void Server::handleConnections(){
        sf::TcpSocket* new_client = new sf::TcpSocket();
        if(m_listener.accept(*new_client) == sf::Socket::Done){
            // Add the client 
            {
                m_clients.push_back(new_client);
                m_selector.add(*new_client);
                
                // Get the new client slot
                std::vector<sf::TcpSocket*>::iterator itr = std::find(m_clients.begin(), m_clients.end(), new_client);
                sf::Uint8 new_client_slot = std::distance(m_clients.begin(), itr);

                std::cout << "Client with ip: " << new_client->getRemoteAddress() << " has connected. Their slot will be: " << (int)new_client_slot << std::endl;
                
                // Notify all the clients about the new client
                {
                    sf::Packet player_connected_packet;
                    player_connected_packet << sf::Uint8(SERVER_PLAYER_CONNECTED) << new_client_slot;

                    for(sf::TcpSocket* client : m_clients){
                        if(client != new_client){
                            client->send(player_connected_packet);
                        }
                    }

                    player_connected_packet.clear();
                }
            }

            // Add all the clients to the new client
            {
                for(sf::TcpSocket* client : m_clients){
                    if(client != new_client){
                        std::vector<sf::TcpSocket*>::iterator itr = std::find(m_clients.begin(), m_clients.end(), client);
                        sf::Uint8 client_slot = std::distance(m_clients.begin(), itr);

                        sf::Packet player_connected_packet;
                        player_connected_packet << sf::Uint8(SERVER_PLAYER_CONNECTED) << client_slot;

                        new_client->send(player_connected_packet);

                        player_connected_packet.clear();
                    }
                }
            }
        }else{
            std::cerr << "Eror listening to new clients conection. Restart the server!" << std::endl;
            delete new_client;
            return;
        }
    }

    void Server::receivePackets(){
        for(std::vector<sf::TcpSocket*>::iterator it = m_clients.begin(); it != m_clients.end(); it++){
            sf::TcpSocket* client = *it;
            
            sf::Uint8 slot = std::distance(m_clients.begin(), it);

            if(m_selector.isReady(*client)){
                sf::Packet packet;
                sf::Socket::Status status = client->receive(packet);
                if(status == sf::Socket::Done){
                    // Check if the packet isnt empty
                    if(packet.getDataSize() > 0){
                        sf::Uint8 packet_type;
                        packet >> packet_type;

                        // Check if packet isnt corrupted
                        if(!packet){
                            std::cerr << "Failed to receive packet!" << std::endl;
                            continue;
                        }

                        switch(packet_type){
                            case CLIENT_PLAYER_MOVED:{
                                float px,py;
                                packet >> px >> py;

                                sf::Packet server_player_moved;
                                server_player_moved << sf::Uint8(SERVER_PLAYER_MOVED) << slot << px << py;

                                for(sf::TcpSocket* c : m_clients){
                                    if(c != client){
                                        c->send(server_player_moved);
                                    }
                                }
                                break;
                            }
                        }
                    }
                }else if(status == sf::Socket::Disconnected){
                    disconnectClient(client, slot);
                }
            }
        }
    }

    void Server::disconnectClient(sf::TcpSocket* p_client, sf::Uint8 slot){
        std::cout << "Client with ip: " << p_client->getRemoteAddress() << " has disconnected." << std::endl;
        p_client->disconnect();
        delete p_client;
        m_clients.erase(m_clients.begin() + slot);

        // Notify every player that the client has disconnected
        sf::Packet player_disconnected_packet;
        player_disconnected_packet << sf::Uint8(SERVER_PLAYER_DISCONNECTED) << slot;

        for(sf::TcpSocket* client : m_clients){
            client->send(player_disconnected_packet);
        }
    }
    void Server::sendPacket(sf::TcpSocket* p_client, sf::Packet& packet){
        if(p_client->send(packet) != sf::Socket::Done){
            std::cerr << "Couldn't send packet!" << std::endl;
        }
    }
}