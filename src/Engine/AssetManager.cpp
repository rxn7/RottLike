#include "AssetManager.hpp"

namespace RottEngine{
    std::unordered_map<std::string, sf::Texture*> AssetManager::textures;
    std::unordered_map<std::string, sf::Font*> AssetManager::fonts;

    void AssetManager::addTexture(const std::string& path){
        if(textures.count(path)){
            return;
        }

        sf::Texture* texture = new sf::Texture();
        if(!texture->loadFromFile(path)){
            std::cerr << "Cannot find resource " << path << " !" << std::endl;
            delete texture;
            return;
        }

        textures.emplace(path, texture);
    }

    sf::Texture* AssetManager::getTexture(const std::string& path){
        if(textures.count(path)){
            return textures.at(path);
        }

        std::cerr << "Error getting resource " << path << " !" << std::endl;
        return nullptr;
    }

    void AssetManager::delTexture(const std::string& path){
        if(textures.count(path)){
            delete textures[path];
            textures.erase(path);
            return;
        }

        std::cerr << "Error deleting resource " << path << " !" << std::endl;
    }

    void AssetManager::addFont(const std::string& path){
        if(fonts.count(path)){
            return;
        }

        sf::Font* font = new sf::Font();
        if(!font->loadFromFile(path)){
            std::cerr << "Cannot find resource " << path << " !" << std::endl;
            delete font;
            return;
        }

        fonts.emplace(path, font);
    }

    sf::Font* AssetManager::getFont(const std::string& path){
        if(fonts.count(path)){
            return fonts.at(path);
        }

        std::cerr << "Error getting resource " << path << " !" << std::endl;
        return nullptr;
    }

    void AssetManager::delFont(const std::string& path){
        if(fonts.count(path)){
            delete fonts[path];
            fonts.erase(path);
            return;
        }

        std::cerr << "Error deleting resource " << path << " !" << std::endl;
    }

    void AssetManager::cleanup(){
        for(auto& texture : textures){
            delete texture.second;
        }

        for(auto& font : fonts){
            delete font.second;
        }
    }
}