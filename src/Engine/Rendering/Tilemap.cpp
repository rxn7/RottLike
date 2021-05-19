#include "Tilemap.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace RottEngine{
    Tilemap::Tilemap(sf::Texture* p_texture, int width, int height, float tile_txt_dimension, float tile_world_dimension)
        : width(width), height(height), m_tile_txt_dimension(tile_txt_dimension), m_tile_world_dimension(tile_world_dimension), mp_texture(p_texture)
	{
        //                                                      4 vertices per tile
        m_vertex_array = sf::VertexArray(sf::PrimitiveType::Quads, width*height*4);

        Tile tile(0,0);

        int half_width = width/2;
        int half_height = height/2; 

        for(int x= -half_width; x<width-half_width; x++){
            for(int y= -half_height; y<height-half_height; y++){
               addTileVerts(tile, sf::Vector2f(x, y));
            }
        }
    }

    void Tilemap::addTileVerts(const Tile& tile, sf::Vector2f pos){
        m_vertex_array.append(sf::Vertex((sf::Vector2f(0,0) + pos) * m_tile_world_dimension,
            sf::Vector2f(m_tile_txt_dimension * tile.x, m_tile_txt_dimension * tile.y)));

        m_vertex_array.append(sf::Vertex((sf::Vector2f(1,0) + pos) * m_tile_world_dimension,
            sf::Vector2f(m_tile_txt_dimension * tile.x + m_tile_txt_dimension, m_tile_txt_dimension * tile.y)));

        m_vertex_array.append(sf::Vertex((sf::Vector2f(1,1) + pos) * m_tile_world_dimension,
            sf::Vector2f(m_tile_txt_dimension * tile.x + m_tile_txt_dimension, m_tile_txt_dimension * tile.y + m_tile_txt_dimension)));

        m_vertex_array.append(sf::Vertex((sf::Vector2f(0,1) + pos) * m_tile_world_dimension,
            sf::Vector2f(m_tile_txt_dimension * tile.x, m_tile_txt_dimension * tile.y + m_tile_txt_dimension)));
    }

    void Tilemap::draw(sf::RenderWindow& window){
		sf::RenderStates render_states;
		render_states.texture = mp_texture;
		window.draw(m_vertex_array, render_states);
    }
}
