#include "Button.hpp"

namespace RottEngine{
    namespace GUI{
        Button::Button(float x, float y, float width, float height, sf::Font* font, const std::string& text, std::function<void()> on_click_func, const sf::Color& idle_color, const sf::Color& hovered_color, const sf::Color& active_color)
            : m_idle_color(idle_color), m_hovered_color(hovered_color), m_active_color(active_color), m_state(ButtonState::IDLE), m_on_click_func(on_click_func)
        {
            m_shape.setPosition(x, y);
            m_shape.setSize({width, height});
            m_shape.setOutlineThickness(3);
            RottEngine::Utils::center(&m_shape);

            m_text.setFont(*font);
            m_text.setString(text);
            m_text.setFillColor(sf::Color::White);
            m_text.setCharacterSize(12);
            m_text.setPosition(m_shape.getPosition());
            m_text.setOutlineThickness(3);
            RottEngine::Utils::center(&m_text);

            m_shape.setFillColor(m_idle_color);
        }

        Button::~Button(){

        }

        void Button::update(){
            m_state = ButtonState::IDLE;

            sf::Vector2i mouse_pos = Input::getMousePos();

            // Hover
            if(m_shape.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)){
                m_state = ButtonState::HOVERED;

                // Pressed
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    // If the button is JUST pressed
                    if(!m_pressed && m_on_click_func != nullptr){
                        m_on_click_func();
                    }
                    
                    m_pressed = true;
                    m_state = ButtonState::ACTIVE;
                }else{
                    m_pressed = false;
                }
            }

            updateColor();
        }

        void Button::draw(sf::RenderWindow& window){
            window.draw(m_shape);
            window.draw(m_text);
        }

        void Button::updateColor(){
              switch(m_state){
                case ButtonState::IDLE:{
                    m_shape.setFillColor(m_idle_color);
                    break;
                }

                case ButtonState::ACTIVE:{
                    m_shape.setFillColor(m_active_color);
                    break;
                }

                case ButtonState::HOVERED:{
                    m_shape.setFillColor(m_hovered_color);
                    break;
                }

                // ERROR
                default:{
                    m_shape.setFillColor(sf::Color::Red);
                    std::cerr << "Error: Wrong button state!" << std::endl;
                    break;
                }
            }
        }

        void Button::setActiveColor(const sf::Color& color){
            m_active_color = color;
        }

        void Button::setHoveredColor(const sf::Color& color){
            m_hovered_color = color;
        }

        void Button::setIdleColor(const sf::Color& color){
            m_idle_color = color;
        }

        void Button::setCharSize(sf::Uint8 size){
            m_text.setCharacterSize(size);
            RottEngine::Utils::center(&m_text);
        }

        void Button::setTextColor(const sf::Color& color){
            m_text.setFillColor(color);
        }

        void Button::setOutlineColor(const sf::Color& color){
            m_text.setOutlineColor(color);
        }

        void Button::setTextOutlineThickness(sf::Uint8 thickness){
            m_text.setOutlineThickness(thickness);
        }

        const bool Button::isHovered() const {
            return m_state == ButtonState::HOVERED;
        }

        const bool Button::isPressed() const {
            return m_state == ButtonState::ACTIVE;
        }
    }
}