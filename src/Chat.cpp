#include "Chat.hpp"
#include "States/GameState.hpp"

#define CHAT_MAX_MESSAGES 5

Chat* Chat::instance;

Chat::~Chat(){
}

Chat::Chat(RottEngine::Client* p_client, GameState* p_state) : mp_client(p_client), mp_state(p_state) {
    m_chat_input = RottEngine::GUI::Textbox(RottEngine::AssetManager::getFont("res/font.ttf"), 860-130, 640-30, 200, 30, 30);
    
    m_chat_text.setFont(*RottEngine::AssetManager::getFont("res/font.ttf"));
    m_chat_text.setPosition(860-300, 640-75);
    m_chat_text.setCharacterSize(17);

    updateTextOrigin();
}

void Chat::sendMessage(){
    std::string msg = m_chat_input.getText();
    
    if(msg.length() < 1){
        return;
    }

    m_chat_input.clear();
    m_chat_input.unfocus();

    sf::Packet message_packet;
    message_packet << sf::Uint8(CLIENT_CHAT) << msg;
    mp_client->sendPacket(message_packet);

    addMessage(mp_client->getNickname(), msg);
}

void Chat::addPlayerDisconnectedMessage(const std::string& nick){
    addMessage(nick, "", Message::MessageType::DISCONNECTED);
}

void Chat::addMessage(const std::string& nick, const std::string& msg, Message::MessageType type){
    m_messages.push_back(Message(nick, msg, type));
    m_update = true;
}

void Chat::processEvent(const sf::Event& event){
    if(event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::Enter){
            if(m_chat_input.isFocused()){
                sendMessage();
            }
        }
    }

    m_chat_input.processEvent(event);
}

void Chat::updateMessages(){
    while(m_messages.size() > CHAT_MAX_MESSAGES){
        m_messages.erase(m_messages.begin());
    }

    std::stringstream str;
    
    m_chat_text.clear();

    for(Message& m : m_messages){
        switch(m.type){
            case Message::MessageType::MESSAGE: {
                m_chat_text << "\n" << sf::Text::Italic 
                << sf::Color::Green << m.nickname 
                << sf::Text::Regular << sf::Color::White << ": " << m.msg;
                
                break;
            }

            case Message::MessageType::DISCONNECTED: {
                m_chat_text << "\n" << sf::Text::Italic 
                << sf::Color::Yellow << m.nickname 
                << sf::Text::Regular << sf::Color::Red << " has disconnected.";

                break;
            }
        }
    }
}

void Chat::updateTextOrigin(){
    sf::FloatRect text_rect = m_chat_text.getLocalBounds();
    m_chat_text.setOrigin(0, text_rect.height);
}

void Chat::update(){
    m_chat_input.update();
    mp_state->getPlayer()->setCanMove(!m_chat_input.isFocused());

    if(m_update){
        updateMessages();
        updateTextOrigin();
        m_update = false;
    }
}

void Chat::draw(sf::RenderWindow& window){
    m_chat_input.draw(window);
    window.draw(m_chat_text);
}

Chat* Chat::getInstance(){
    return instance;
}