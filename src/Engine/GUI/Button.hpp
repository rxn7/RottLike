#pragma once

#include <SFML/Graphics.hpp>
#include "../Utils.hpp"
#include "../Input.hpp"
#include <iostream>
#include <functional>

namespace RottEngine{
    namespace GUI{
        enum class ButtonState{
            IDLE = 0,
            HOVERED,
            ACTIVE
        };

        class Button{
        public:
            Button() {}
            Button(float x, float y, float width, float height, sf::Font* font, const std::string& text, std::function<void()> on_click_func, const sf::Color& idle_color = sf::Color(188, 190, 194, 150), const sf::Color& hover_color=sf::Color(202, 202, 204, 255), const sf::Color& active_color=sf::Color(136, 136, 143, 200));
            ~Button();

            void update();
            void draw(sf::RenderWindow& window);

            void setCharSize(sf::Uint8 size);
           
            void setIdleColor(const sf::Color& color);
            void setHoveredColor(const sf::Color& color);
            void setActiveColor(const sf::Color& color);
            void setOutlineColor(const sf::Color& color);
           
            void setTextColor(const sf::Color& color);
            void setTextOutlineColor(const sf::Color& color);
            void setTextOutlineThickness(sf::Uint8 thickness);

            const bool isPressed() const;
            const bool isHovered() const;
            const ButtonState getState() const;

        private:
            void updateColor();

        private:
            ButtonState m_state;

            sf::RectangleShape m_shape;
            sf::Text m_text;

            sf::Color m_idle_color;
            sf::Color m_hovered_color;
            sf::Color m_active_color;

            bool m_pressed;
            bool m_hovered;

            std::function<void()> m_on_click_func;
        };
    }
}
