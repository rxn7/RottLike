#include "SplashScreenState.hpp"

#define INTRO_DURATION 6
#define LOGO_MOVE_SPEED 150

SplashScreenState::SplashScreenState(){
    RottEngine::AssetManager::addTexture("res/sprites/splash_screen.png");
    m_logo.setTexture(*RottEngine::AssetManager::getTexture("res/sprites/splash_screen.png"));
    m_logo.setOrigin(m_logo.getLocalBounds().width/2, m_logo.getLocalBounds().height/2);
    m_logo.setPosition(WINDOW_WIDTH/2, 0-(m_logo.getLocalBounds().height/2));

    m_skip_text.setFont(*RottEngine::AssetManager::getFont("res/font.ttf"));
    m_skip_text.setString("Press any key to skip.");
    m_skip_text.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT - 50);
    m_skip_text.setOutlineThickness(3);
    RottEngine::Utils::center(&m_skip_text);

    m_ready = true;
}

SplashScreenState::~SplashScreenState(){
    RottEngine::AssetManager::delTexture("res/sprites/splash_screen.png");
}

void SplashScreenState::processEvent(const sf::Event& event){
    if(m_skipped){
        return;
    }

    if(event.type == sf::Event::KeyPressed){
        skip();
    }
}

void SplashScreenState::update(const sf::Time& dt){
    if(m_skipped){
        return;
    }

    if(m_intro_clock.getElapsedTime().asSeconds() >= INTRO_DURATION){
        m_intro_clock.restart();
        skip();
    }

    m_logo.move({0, LOGO_MOVE_SPEED*dt.asSeconds()});
}

void SplashScreenState::draw(sf::RenderWindow& window){
    window.draw(m_logo);
    window.draw(m_skip_text);
}

void SplashScreenState::skip(){
    m_skipped = true;
    Game::changeState(new MainMenuState());
}