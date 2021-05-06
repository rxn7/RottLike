#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

namespace RottEngine{
    class State{
    public:
        State() {}
        virtual ~State() {}
        virtual void processEvent(const sf::Event& event) = 0;
        virtual void processPacket(sf::Packet& packet, sf::Uint8 type) = 0;
        virtual void update(const sf::Time& dt) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
        
        bool isReady() { return m_ready; }

    protected:
        bool m_ready=false;
    };
}