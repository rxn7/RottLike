#include "Input.hpp"

namespace RottEngine{
    sf::Vector2i Input::mouse_pos;

    void Input::update(sf::RenderWindow& window){
        mouse_pos = sf::Mouse::getPosition(window);
    }

    sf::Vector2i Input::getMousePos(){
        return mouse_pos;
    }
}   
