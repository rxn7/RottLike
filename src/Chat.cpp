#include "Chat.hpp"
#include "States/GameState.hpp"


#define CHAT_MAX_MESSAGES 5

Chat* Chat::instance;

Chat::Chat(RottEngine::Client* p_client, GameState* p_state) : mp_client(p_client), mp_state(p_state) {
    instance = this;

    m_chat_input = RottEngine::GUI::Textbox(RottEngine::AssetManager::getFont("res/font.ttf"), 640-130, 480-30, 200, 30, 30);
    
    m_chat_text.setFont(*RottEngine::AssetManager::getFont("res/font.ttf"));
    m_chat_text.setFillColor(sf::Color(255, 255, 255, 220)); // Make the text a bit transparent
    m_chat_text.setPosition(640-230, 480-75);
    m_chat_text.setCharacterSize(13);
    m_chat_text.setOutlineThickness(1);
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

    addLocalMessage(msg);
}

void Chat::addMessage(OnlinePlayer* p_player, const std::string& msg){
    if(instance == nullptr){
        std::cerr << "Chat error: instance is null!" << std::endl;
        return;
    }

    instance->addMessage({p_player->getNickname(), msg});
}

void Chat::addLocalMessage(const std::string& msg){
    addMessage({mp_client->getNickname(), msg});
}

void Chat::addMessage(const Message& msg){
    m_messages.push_back({msg});

    while(m_messages.size() > CHAT_MAX_MESSAGES){
        m_messages.erase(m_messages.begin());
    }

    updateMessages();
    updateTextOrigin();
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
    std::string str;

    for(Message& m : m_messages){
        str.append("\n").append(m.nickname).append(": ").append(m.msg);
    }

    m_chat_text.setString(str);
}

void Chat::updateTextOrigin(){
    sf::FloatRect text_rect = m_chat_text.getLocalBounds();
    m_chat_text.setOrigin(0, text_rect.height);
}

void Chat::update(){
    m_chat_input.update();
    mp_state->getPlayer()->setCanMove(!m_chat_input.isFocused());
}

void Chat::draw(sf::RenderWindow& window){
    m_chat_input.draw(window);
    window.draw(m_chat_text);
}