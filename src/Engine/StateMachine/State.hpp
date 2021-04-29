#pragma once

#include <SFML/System.hpp>

namespace RottEngine{
    class State{
    public:
        State() {}
        virtual ~State() {}
        virtual void init() = 0;
        virtual void processInput() = 0;
        virtual void update(const sf::Time& dt) = 0;
        virtual void draw() = 0;

        virtual void pause() = 0;
        virtual void start() = 0;
    };
}