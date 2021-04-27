#include "AssetManager.hpp"

std::unordered_map<std::string, sf::Texture*> AssetManager::textures;
std::unordered_map<std::string, sf::Font*> AssetManager::fonts;

void AssetManager::addTexture(const std::string& path){
    sf::Texture* texture = new sf::Texture();
    if(!texture->loadFromFile(path)){
        std::cerr << "Cannot find resource " << path << " !" << std::endl;
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

void AssetManager::addFont(const std::string& path){
    sf::Font* font = new sf::Font();
    if(!font->loadFromFile(path)){
        std::cerr << "Cannot find resource " << path << " !" << std::endl;
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

void AssetManager::cleanup(){
    for(auto& texture : textures){
        delete texture.second;
    }

    for(auto& font : fonts){
        delete font.second;
    }
}