#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Utils.hpp"
#include "../Input.hpp"

namespace RottEngine {
    namespace GUI {
        class Textbox{
        public:
            Textbox() {}
            Textbox(sf::Font* font, float x, float y, float width, float height, sf::Uint16 limit=0, const sf::Color& idle_color = sf::Color::White, const sf::Color& active_color = sf::Color::Green);
            void processEvent(const sf::Event& event);
            void draw(sf::RenderWindow& window);
            void setCharSize(sf::Uint8 size);
            void update();
            void clear();
            void focus();
            void unfocus();
            std::string getText() const;
            bool isFocused() const;

        private:
            void delLastChar();

        private:
            static Textbox* mp_active;

            sf::Uint16 m_limit;
            sf::Color m_active_color;
            sf::Color m_idle_color;
            sf::RectangleShape m_shape;
            sf::Text m_text;
        };  
    }
}
