#pragma once

#include "Engine/GUI/Textbox.hpp"
#include "Engine/GUI/Button.hpp"
#include "Engine/AssetManager.hpp"
#include "OnlinePlayer.hpp"

namespace RottEngine{
    class Client;
}

class OnlinePlayer;
struct Message;
class GameState;

class Chat {
public:
    Chat() {}
    Chat(RottEngine::Client* p_client, GameState* p_state);
    ~Chat() {}
    
    void processEvent(const sf::Event& event);
    void update();
    void draw(sf::RenderWindow& window);
    static void addMessage(OnlinePlayer* p_player, const std::string& msg);

private:
    void updateTextOrigin();
    void sendMessage();
    void addLocalMessage(const std::string& msg);
    void addMessage(const Message& msg);
    void updateMessages();

private:
    static Chat* instance;

    GameState* mp_state;
    RottEngine::Client* mp_client;

    std::vector<Message> m_messages;
    RottEngine::GUI::Textbox m_chat_input;
    sf::Text m_chat_text;
};

struct Message{
    Message(const std::string& _nick, const std::string& _msg){
        this->nickname = _nick;
        this->msg = _msg;
    }

    std::string nickname;
    std::string msg;
};