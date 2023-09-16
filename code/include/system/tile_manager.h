#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <map>
#include "../../json/json.hpp"
#include "system/object.h"
#include "system/entity.h"
#include "../tiled2sfml/tiled2sfml.hpp"

class tile_type {
public:
    tile_type(const std::string& image_file_name, uint32_t tile_idx, bool is_collidable)
        : image_file_name(image_file_name), tile_idx_(tile_idx), is_collidable_(is_collidable) {}


private:
    std::string image_file_name;
    uint32_t tile_idx_;
    bool is_collidable_;

public:
    const std::string& get_image_file_name() const { return image_file_name; }
    uint32_t get_tile_idx() const { return tile_idx_; }
    bool is_collidable() const { return is_collidable_; }
};

/*
* The reason why data and image separated, is because how tiled works,
* when you have multiple layers for example 30x20 grid and 5 layers,
* the true tile is 600, but the image that need to be rendered is 5x600
* which is 3k image, while we only need 600 tile data.
*/
struct TileData
{
    bool has_collision = false;
};

struct TileImage
{
    int layer_index = 0;
    sf::Sprite sprite;
};

class TileManager {
public:
    /// <summary>
    /// used for parsing tiles into game tile.
    /// </summary>
    /// <param name="json_file_path">file path of json with extensions.</param>
    void tileParser(const std::string& json_file_path);

    /// <summary>
    /// draw tiles. Please make sure not drawing first layer as it
    /// designated for collision only.
    /// </summary>
    /// <param name="window">RenderWindow to get draw function.</param>
    /// <param name="player_position">to check player position for performance.</param>
    /// <param name="layer">specify the draw layer.</param>
    /// <param name="draw_player_func">function call for the +
    void draw(sf::RenderWindow& window, const sf::Vector2f& player_position, int player_layer, std::function<void()> draw_player_func);

    bool checkCollision(const sf::Vector2f& new_position);
    uint32_t positionToIndex(sf::Vector2f pos);
    sf::Vector2f indexToPosition(int index);
    void setCollisionLayer(std::vector<int>&& layers);

private:
    bool isNearPlayer(const sf::Vector2f& tile_position, const sf::Vector2f& player_position, float render_distance);

    void registerTileTexture(const std::string& image_path, const std::string& texture_name);

    sf::Texture& loadTileTexture(const std::string& texture_name);

private:
    std::map<std::string, std::shared_ptr<sf::Texture>> tile_textures;
    std::vector<tilesetData> tileset_data;
    tilemapData tilemap_data;
    std::vector<TileData> tile_data;
    std::vector<TileImage> tile_sprite;

    float render_distance = 550.0f;
    std::vector<int> collision_layer;
};
