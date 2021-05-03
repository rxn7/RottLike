#include "GameState.hpp"

#define TICK_RATE 0.0416 // 24 tick rate

GameState::~GameState(){
    delete mp_player;
}

GameState::GameState() {
    RottEngine::AssetManager::addTexture("res/sprites/player.png");
    RottEngine::AssetManager::addTexture("res/sprites/online_player.png");
    RottEngine::AssetManager::addTexture("res/sprites/tileset.png");

    std::string server_ip, nickname;
    std::cout << "Enter the server's ip: ";
    std::cin >> server_ip;

    std::cout << "Enter your nickname: ";
    std::cin >> nickname;

    if(!m_client.connect(server_ip.c_str(), 26950, nickname)){
        std::cerr << "Couldn't connect to the server!" << std::endl;
        return;
    }

    mp_player = new LocalPlayer(&m_client, nickname);

    m_chat = Chat(&m_client);
    m_camera = sf::View(sf::Vector2f(0,0), sf::Vector2f(640, 480));
    m_gui_camera = sf::View(sf::Vector2f((float)640/2, (float)480/2), sf::Vector2f(640, 480));
    m_tilemap = RottEngine::Tilemap(RottEngine::AssetManager::getTexture("res/sprites/tileset.png"), 24, 24, 16, 64);

    m_pos_text.move(0, 30);
    m_pos_text.setString("x: ?\ny: ?");
    m_pos_text.setFont(*RottEngine::AssetManager::getFont("res/font.ttf"));

    m_ready = true;
}

void GameState::processEvent(const sf::Event& event){
    m_chat.processEvent(event);
}

void GameState::update(const sf::Time& dt){
    if(m_tick_rate_clock.getElapsedTime().asSeconds() >= TICK_RATE){
        m_tick_rate_clock.restart();
        mp_player->tick();

        sf::Vector2f player_pos = mp_player->getSprite()->getPosition();
        
        std::stringstream pos_text_stream;
        pos_text_stream << "x: " << (int)player_pos.x << "\n" << "y: " << (int)player_pos.y;
        m_pos_text.setString(pos_text_stream.str());
    }

    mp_player->update(dt);

    m_fps_timer.update(dt.asSeconds());
    m_chat.update();

    m_camera.setCenter(mp_player->getSprite()->getPosition());
}

void GameState::draw(sf::RenderWindow& window){
    // WORLD
    window.setView(m_camera);
    m_tilemap.draw(window, sf::RenderStates::Default);

    for(auto& player : m_client.getOnlinePlayers()){
        player.second->draw(window);
    }

    mp_player->draw(window);
    
    // GUI
    window.setView(m_gui_camera);
    window.draw(m_pos_text);
    m_fps_timer.draw(window);
    m_chat.draw(window);
}