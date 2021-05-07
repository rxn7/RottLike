#include "JoinGameState.hpp"
#include "Game.hpp"

JoinGameState::JoinGameState(){
    sf::Font* font = RottEngine::AssetManager::getFont("res/font.ttf");

    m_connect_btn = RottEngine::GUI::Button(860/2, 640-200, 200, 50, font, "Connect", std::bind(&tryConnect, this));
    m_connect_btn.setCharSize(24);

    m_ip_field = RottEngine::GUI::Textbox(font, 300, 100, 300, 50, 22);
    m_ip_field.setCharSize(20);

    m_nick_field = RottEngine::GUI::Textbox(font, 300, 200, 300, 50, 16);
    m_nick_field.setCharSize(20);

    m_ip_text.setFont(*font);
    m_ip_text.setPosition(50, 100);  
    m_ip_text.setString("IP:");    
    m_ip_text.setCharacterSize(20);  
    RottEngine::Utils::center(&m_ip_text);
    
    m_nick_text.setFont(*font);
    m_nick_text.setPosition(50, 200);
    m_nick_text.setString("Nick:");
    m_nick_text.setCharacterSize(20);
    RottEngine::Utils::center(&m_nick_text);

    m_ready = true;
}

JoinGameState::~JoinGameState(){
}

void JoinGameState::tryConnect(){
    mp_client = new RottEngine::Client();
    
    if(mp_client->connect(m_ip_field.getText().c_str(), 26950, m_nick_field.getText())){
        Game::changeState(new GameState(mp_client));
    }else{
        m_ip_field.clear();
        std::cerr << "Ip is not correct!" << std::endl;
        delete mp_client;
    }
}

void JoinGameState::update(const sf::Time& dt){
    m_ip_field.update();
    m_nick_field.update();
    m_connect_btn.update();
}

void JoinGameState::processEvent(const sf::Event& event){
    m_ip_field.processEvent(event);
    m_nick_field.processEvent(event);
}

void JoinGameState::draw(sf::RenderWindow& window){
    m_connect_btn.draw(window);
    m_ip_field.draw(window);
    m_nick_field.draw(window);
    window.draw(m_nick_text);
    window.draw(m_ip_text);
}
