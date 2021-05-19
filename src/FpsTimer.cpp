#include "FpsTimer.hpp"

FpsTimer::FpsTimer() {
    m_text.setFont(*RottEngine::AssetManager::getFont("res/font.TTF"));
    m_text.setScale(0.9f, 0.9f);
    m_text.setString("FPS: 0");
}

void FpsTimer::update(float dt){
    if(m_clock.getElapsedTime().asMilliseconds() >= 1000){
        m_clock.restart();

        std::stringstream ss;
        ss << "FPS: " << std::fixed << std::setprecision(0) << 1 / dt;

        m_text.setString(ss.str());
    }
}

void FpsTimer::draw(sf::RenderWindow& window){
    window.draw(m_text);
}
