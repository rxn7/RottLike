#include "Chat.hpp"

Chat* Chat::instance;

Chat::Chat(RottEngine::Client* p_client) : mp_client(p_client) {
    instance = this;

    m_chat_input = RottEngine::GUI::Textbox(RottEngine::AssetManager::getFont("res/font.ttf"), 640-230, 480-30, 200, 30, 30);
    m_chat_send_btn = RottEngine::GUI::Button(640-75, 480-30, 75, 30, RottEngine::AssetManager::getFont("res/font.ttf"), "Send", std::bind(&sendMessage, this));
    
    m_chat_text.setFont(*RottEngine::AssetManager::getFont("res/font.ttf"));
    m_chat_text.setFillColor(sf::Color(255, 255, 255, 220)); // Make the text a bit transparent
    
    sf::FloatRect text_rect = m_chat_text.getLocalBounds();
    m_chat_text.setOrigin(0, text_rect.height);
    m_chat_text.setPosition(640-230, 480-45);
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
}

void Chat::addMessage(OnlinePlayer* p_player, const std::string& msg){
    if(instance == nullptr){
        std::cerr << "Chat error: instance is null!" << std::endl;
        return;
    }

    std::string str = instance->m_chat_text.getString();
    str.append("\n").append(p_player->getNickname()).append(": ").append(msg);
    instance->m_chat_text.setString(str);
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

void Chat::update(){
    m_chat_input.update();
    m_chat_send_btn.update();
}

void Chat::draw(sf::RenderWindow& window){
    m_chat_input.draw(window);
    m_chat_send_btn.draw(window);
    window.draw(m_chat_text);
}