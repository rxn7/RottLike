#pragma once

#include <mutex>
#include <deque>
#include "Engine/GUI/Textbox.hpp"
#include "Engine/GUI/Button.hpp"
#include "Engine/AssetManager.hpp"
#include <SFML/Graphics/RichText.hpp>

namespace RottEngine{
    class Client;
}

struct Message{
    enum MessageType{
        MESSAGE,
        DISCONNECTED,
        CONNECTED,
    };

    Message(const std::string& _nick, const std::string& _msg, MessageType _type = MessageType::MESSAGE){
        this->nickname = _nick;
        this->msg = _msg;
        type = _type;
    }

    MessageType type;
    std::string nickname;
    std::string msg;
};

class OnlinePlayer;
class GameState;

class Chat {
public:
    Chat() {}
    Chat(RottEngine::Client* p_client, GameState* p_state);
    ~Chat();

    void processEvent(const sf::Event& event);
    void update();
    void draw(sf::RenderWindow& window);

    void addPlayerConnectedMessage(const std::string& nick);
    void addPlayerDisconnectedMessage(const std::string& nick);
    void addMessage(const std::string& nick, const std::string& msg, Message::MessageType type=Message::MessageType::MESSAGE);
    static Chat* getInstance();

private:
    void updateTextOrigin();
    void sendMessage();
    void updateMessages();

private:
    static Chat* instance;

    std::vector<Message> m_messages;

    bool m_update=false;
    GameState* mp_state;
    RottEngine::Client* mp_client;
    RottEngine::GUI::Textbox m_chat_input;
    sfe::RichText m_chat_text;
};