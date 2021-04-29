#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace RottEngine{
    class State{
    public:
        State() {}
        virtual ~State() {}
        virtual void processEvent(const sf::Event& event) = 0;
        virtual void update(const sf::Time& dt) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
    };
}