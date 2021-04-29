#pragma once

#include "Engine/Entity.hpp"
#include "Engine/AssetManager.hpp"
#include "Engine/Networking/Client.hpp"
#include <SFML/Network.hpp>
#include "Engine/AssetManager.hpp"
 
class OnlinePlayer : public RottEngine::Entity {
public:
    OnlinePlayer();
    virtual ~OnlinePlayer();
    void setNickname(const std::string& nickname);
    void setPosition(float x, float y);
    void update(const sf::Time& dt) override;
    void draw(sf::RenderWindow& window) override;
    std::string getNickname() const;

private:
    sf::Text m_nickname_text;
};