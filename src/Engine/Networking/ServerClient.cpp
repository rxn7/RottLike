#include "ServerClient.hpp"

ServerClient::ServerClient(){ }
ServerClient::ServerClient(sf::TcpSocket* p_socket) : m_socket(p_socket) { }

ServerClient::~ServerClient(){
    m_socket->disconnect();
    delete m_socket;
}