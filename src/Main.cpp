#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <sstream>

#include "AssetManager.hpp"
#include "FpsTimer.hpp"
#include "LocalPlayer.hpp"

#define WIDTH 640
#define HEIGHT 480

#define START_AMOUNT_ASTEROIDS 7

int main(int argc, const char** argv){
    srand(time(0));

    AssetManager::addFont("res/font.ttf");
    AssetManager::addTexture("res/sprites/player.png");

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Rott Like");
    sf::Clock deltaClock;

    FpsTimer fpsTimer;
    LocalPlayer localPlayer;

    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){ window.close(); }
        }

        window.clear();
        
        localPlayer.update(dt, window);
        localPlayer.draw(window);

        fpsTimer.update(dt.asSeconds());
        fpsTimer.draw(window);

        window.display();
    }

    AssetManager::cleanup();

    return 0;
}