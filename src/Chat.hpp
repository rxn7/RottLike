#pragma once

#include "Engine/GUI/Textbox.hpp"
#include "Engine/GUI/Button.hpp"
#include "Engine/AssetManager.hpp"
#include "OnlinePlayer.hpp"

namespace RottEngine{
    class Client;
}

class OnlinePlayer;

class Chat {
public:
    Chat() {}
    Chat(RottEngine::Client* p_client);
    ~Chat() {}
    
    void processEvent(const sf::Event& event);
    void update();
    void draw(sf::RenderWindow& window);
    static void addMessage(OnlinePlayer* p_player, const std::string& msg);

private:
    void sendMessage();

private:
    static Chat* instance;

    RottEngine::Client* mp_client;
    RottEngine::GUI::Textbox m_chat_input;
    RottEngine::GUI::Button m_chat_send_btn;
    sf::Text m_chat_text;
};