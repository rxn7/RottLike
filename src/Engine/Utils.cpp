#include "Utils.hpp"

namespace RottEngine{
    void Utils::center(sf::Text* object){
        sf::FloatRect rect = object->getLocalBounds();
        object->setOrigin((int)(rect.left + rect.width/2.0f), (int)(rect.top  + rect.height/2.0f));
    }

    void Utils::center(sf::Sprite* object){
        sf::FloatRect rect = object->getLocalBounds();
        object->setOrigin(rect.left + rect.width/2.0f, rect.top  + rect.height/2.0f);
    }

    void Utils::center(sf::RectangleShape* object){
        sf::FloatRect rect = object->getLocalBounds();
        object->setOrigin(rect.left + rect.width/2.0f, rect.top  + rect.height/2.0f);
    }

    void Utils::centerVer(sf::Text* object){
        sf::FloatRect rect = object->getLocalBounds();
        object->setOrigin((int)(rect.left + rect.width/2.0f), (int)(rect.top  + rect.height/2.0f));
    }
}
