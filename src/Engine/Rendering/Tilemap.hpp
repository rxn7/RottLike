#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Tile.hpp"

namespace RottEngine{
    class Tilemap {
    public:
        Tilemap() {} 
        Tilemap(sf::Texture* texture, int width, int height, float tile_txt_dimension, float tile_world_dimension);

        void draw(sf::RenderWindow& window, sf::RenderStates states);

    private:
        void addTileVerts(const Tile& tile, sf::Vector2f pos);

    private:
        sf::Texture* mp_texture;
        sf::VertexArray m_vertex_array;

        unsigned int width, height;
        float m_tile_txt_dimension, m_tile_world_dimension;
    };
}