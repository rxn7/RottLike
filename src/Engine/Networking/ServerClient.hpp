#pragma once

#include <SFML/Network.hpp>

class ServerClient {
public:
    ServerClient();
    ServerClient(sf::TcpSocket* p_socket);
    ~ServerClient();

public:
    sf::TcpSocket* m_socket;
    std::string m_nickname;
    sf::Vector2f m_pos;
    float m_melee_ang;
};
