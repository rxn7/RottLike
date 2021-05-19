#include "Server.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

#define TICK_RATE 0.0416 // 24 tickrate
#define PORT 26950
namespace RottEngine{
    Server::~Server(){
        for(ServerClient* c : m_clients){
            delete c;
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
        // Tick loop
        while(true){
            if(tickRateClock.getElapsedTime().asSeconds() >= TICK_RATE){
                tickRateClock.restart();
                update();
            }
        }

        #ifdef _WIN32
            ShowWindow(GetConsoleWindow(), SW_SHOW);
        #endif

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

        // If listener accepted a new connection correctly
        if(m_listener.accept(*new_client) == sf::Socket::Done){
            std::cout << "Player with ip: " << new_client->getRemoteAddress() << " is trying to connect..." << std::endl;
            m_clients.push_back(new ServerClient(new_client));
            m_selector.add(*new_client);
        }

        // If listener didn't accept a new connection correctly
        else{
            std::cerr << "Eror listening to new clients conection. Restart the server!" << std::endl;
            delete new_client;
            return;
        }
    }

    void Server::receivePackets(){
        for(ServerClient* client : m_clients){
            sf::Uint8 slot = getSlot(client);

            // If client is ready
            if(m_selector.isReady(*client->m_socket)){
                sf::Packet packet;
                sf::Socket::Status status = client->m_socket->receive(packet);

                // If packet has received
                if(status == sf::Socket::Done){
                    // Check if the packet isnt empty
                    if(packet.getDataSize() > 0){
                        // Read the packet type
                        sf::Uint8 packet_type;
                        packet >> packet_type;

                        // Check if packet isnt corrupted
                        if(!packet){
                            std::cerr << "Failed to receive packet!" << std::endl;
                            continue;
                        }

                        // Packet types
                        switch(packet_type){
                            case CLIENT_PLAYER_MOVED:{
                                float px,py;
                                packet >> px >> py;

                                sf::Packet server_player_moved;
                                server_player_moved << sf::Uint8(SERVER_PLAYER_MOVED) << slot << px << py;

                                client->m_pos = {px, py};

                                for(ServerClient* c : m_clients){
                                    if(c != client){
                                        c->m_socket->send(server_player_moved);
                                    }
                                }
                                break;
                            }

                            case CLIENT_CONNECTED:{
                                std::string nickname;
                                packet >> nickname;

                                m_clients[slot]->m_nickname = nickname;

                                // Get the new client slot
                                std::cout << "Client with ip: " << client->m_socket->getRemoteAddress() << " and nick " << nickname << " has connected. Their slot will be: " << (int)slot << std::endl;

                                // Notify the new player about all the connected players
                                for(ServerClient* c : m_clients){
                                    if(c != client){
                                        sf::Packet player_connected_packet;
                                        player_connected_packet << sf::Uint8(SERVER_PLAYER_CONNECTED) << getSlot(c) << c->m_nickname << c->m_pos.x << c->m_pos.y << c->m_melee_ang;

                                        client->m_socket->send(player_connected_packet);
                                        player_connected_packet.clear();
                                    }
                                }

                                // Notify all the clients about the new client
                                sf::Packet player_connected_packet;
                                player_connected_packet << sf::Uint8(SERVER_PLAYER_CONNECTED) << slot << nickname;
                                sendPacketToAll(player_connected_packet, client);

                                break;
                            }

                            case CLIENT_CHAT:{
                                std::string msg;
                                packet >> msg;

                                std::cout << "[CHAT] " << client->m_nickname << ": " << msg << std::endl;

                                sf::Packet server_chat_packet;
                                server_chat_packet << sf::Uint8(SERVER_CHAT) << getSlot(client) << msg;
                                sendPacketToAll(server_chat_packet, client);

                                break;
                            }

                            case CLIENT_MELEE_UPDATE: {
                                float ang_deg;
                                packet >> ang_deg;

                                client->m_melee_ang = ang_deg;

                                sf::Packet server_melee_update_packet;
                                server_melee_update_packet << sf::Uint8(SERVER_MELEE_UPDATE) << slot << ang_deg;
                                sendPacketToAll(server_melee_update_packet, client);

                                break;
                            }
                        }
                    }
                }
                // If player has disconnected
                else if(status == sf::Socket::Disconnected){
                    disconnectClient(client, slot);
                    continue;
                }
            }
        }
    }

    void Server::disconnectClient(ServerClient* p_client, sf::Uint8 slot){
        std::cout << "Client with ip: " << p_client->m_socket->getRemoteAddress() << " and nick: " << p_client->m_nickname << " has disconnected." << std::endl;

        // Remove the client from the server
        m_clients.erase(m_clients.begin() + getSlot(p_client));
        m_selector.remove(*p_client->m_socket);
        p_client->m_socket->disconnect();
        delete p_client;

        // Notify every player that the client has disconnected
        sf::Packet player_disconnected_packet;
        player_disconnected_packet << sf::Uint8(SERVER_PLAYER_DISCONNECTED) << slot;
        sendPacketToAll(player_disconnected_packet);
    }

    void Server::sendPacket(ServerClient* p_client, sf::Packet& packet){
        if(p_client->m_socket->send(packet) != sf::Socket::Done){
            std::cerr << "Couldn't send packet!" << std::endl;

            disconnectClient(p_client, getSlot(p_client));
        }
    }

    sf::Uint8 Server::getSlot(ServerClient* p_client){
        std::vector<ServerClient*>::iterator itr = std::find(m_clients.begin(), m_clients.end(), p_client);
        return std::distance(m_clients.begin(), itr);
    }

    void Server::sendPacketToAll(sf::Packet& packet, ServerClient* p_exlcude){
        for(ServerClient* c : m_clients){
            if(c != p_exlcude){
                c->m_socket->send(packet);
            }
        }
    }
}
