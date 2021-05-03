#include "Textbox.hpp"

namespace RottEngine {
    namespace GUI {
        Textbox* Textbox::mp_active;

        Textbox::Textbox(sf::Font* font, float x, float y, float width, float height, sf::Uint16 limit, const sf::Color& idle_color, const sf::Color& active_color) : m_active_color(active_color), m_idle_color(idle_color), m_limit(limit) {
            m_shape.setSize({width, height});
            RottEngine::Utils::center(&m_shape);
            m_shape.setPosition(x, y);            
            m_shape.setOutlineThickness(3);
            m_shape.setOutlineColor(m_idle_color);
            m_shape.setFillColor(sf::Color(0,0,0,150));

            m_text.setCharacterSize(10);
            m_text.setPosition(x - (m_shape.getLocalBounds().width/2) + 10, y - height/4);
            m_text.setFont(*font);
        }

        void Textbox::processEvent(const sf::Event& event){
            // Dont do anything if this textbox isnt active
            if(mp_active != this){
                return;
            }

            switch(event.type){
                case sf::Event::KeyPressed:{
                    switch(event.key.code){
                        case sf::Keyboard::Escape:{
                            mp_active = nullptr;
                            return;
                        }
                    }

                    break;
                }

                case sf::Event::TextEntered:{
                    if(event.text.unicode == '\b'){
                        delLastChar();
                        return;
                    }

                    // Check if the text size is in limit
                    if(m_limit && m_text.getString().getSize() >= m_limit){
                        return;
                    }

                    // Check if the char is in ASCII range (0-127)
                    if(event.text.unicode > 127){
                        return;
                    }

                    char typed_char = static_cast<char>(event.text.unicode);
                    m_text.setString(m_text.getString() + typed_char);

                    break;
                }
            }
        }

        void Textbox::update(){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::Vector2f mouse_pos(RottEngine::Input::getMousePos());
                if(m_shape.getGlobalBounds().contains(mouse_pos)){
                    mp_active = this;
                }
            }
            

            // Update the shape outline color
            m_shape.setOutlineColor(mp_active == this ? m_active_color : m_idle_color);
        }

        void Textbox::clear(){
            m_text.setString("");
        }

        void Textbox::draw(sf::RenderWindow& window){
            window.draw(m_shape);
            window.draw(m_text);
        }

        void Textbox::delLastChar(){
            std::string str = m_text.getString();
            
            // Check if there's any charachter to delete
            if(str.length() > 0){
                m_text.setString(str.substr(0, str.size()-1));
            }
        }

        std::string Textbox::getText() const {
            return m_text.getString();
        }

        void Textbox::focus(){
            mp_active = this;
        }

        void Textbox::unfocus(){
            mp_active = nullptr;
        }

        bool Textbox::isFocused() const {
            return mp_active == this;
        }
    }
}