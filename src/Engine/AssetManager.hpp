#pragma once

#include <iostream>
#include <unordered_map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace RottEngine{
    class AssetManager{
    public:
        static void cleanup();

        static void addTexture(const std::string& path);
        static void delTexture(const std::string& path);
        static sf::Texture* getTexture(const std::string& path);

        static void addFont(const std::string& path);
        static void delFont(const std::string& path);
        static sf::Font* getFont(const std::string& path);

    private:
        static std::unordered_map<std::string, sf::Texture*> textures;
        static std::unordered_map<std::string, sf::Font*> fonts;
        AssetManager();
    };
}
