#include "system/tile_manager.h"

void TileManager::tileParser(const std::string& json_file_path)
{
    std::string prepath = "../resources/maps/";
    Tiled2SFML tile_manager;
    tilemap_data = tile_manager.tilemapParse(json_file_path);

    uint32_t size_map = tilemap_data.tilemap_width * tilemap_data.tilemap_height;
    tile_data.reserve(size_map);
    tile_sprite.reserve(size_map * tilemap_data.layers.size());

    // register texture
    for (size_t i = 0; i < tilemap_data.tilesets.size(); i++)
    {
        tileset_data.push_back(tile_manager.tilesetParse(prepath + tilemap_data.tilesets[i].source));
        registerTileTexture(prepath + tileset_data[i].img_source_path, tileset_data[i].tileset_name);
    }
    
    for (size_t layer_idx = 0; layer_idx < tilemap_data.layers.size(); layer_idx++)
    {
        // iterate through all data from each layer
        for (size_t data_idx = 0; data_idx < tilemap_data.layers[layer_idx].data.size(); data_idx++)
        {
            TileData t_data;
            TileImage t_sprite;
            int data = tilemap_data.layers[layer_idx].data[data_idx];
            int tileset_idx = 0;

            t_sprite.layer_index = layer_idx;
            
            if (layer_idx > 0)
            {
                t_data = tile_data[data_idx];
            }

            for (size_t i = 0; i < collision_layer.size(); i++)
            {
                if (t_sprite.layer_index == collision_layer[i] && data > 0)
                {
                    t_data.has_collision = true;
                }
            }

            // always -1 because Tiled gid start from 1.
            // this loops for search which tileset will be used,
            // since Tiled only provide first gid, used for determine
            // index of first tile grid in image tileset.
            // TODO: bad implementation
            int i = 0;
            int temp_data = 0;
            while (true)
            {
                if (i <= tilemap_data.tilesets.size() - 1)
                {
                    if (data > tilemap_data.tilesets[i].first_gid - 1)
                    {
                        tileset_idx = i;
                        temp_data = data - tilemap_data.tilesets[i].first_gid;
                        i++;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            data = temp_data;

            sf::Texture& tx = loadTileTexture(tileset_data[tileset_idx].tileset_name);

            t_sprite.sprite.setTexture(tx);
            int x_rect = (data % tileset_data[tileset_idx].column) * tileset_data[tileset_idx].tile_width;
            int y_rect = (data / tileset_data[tileset_idx].column) * tileset_data[tileset_idx].tile_height;

            t_sprite.sprite.setTextureRect(
                sf::IntRect(x_rect, y_rect,
                    tilemap_data.tile_width,
                    tilemap_data.tile_height));

            int x = (data_idx * tilemap_data.tile_width) % (tilemap_data.tile_width * tilemap_data.tilemap_width);
            int y = ((data_idx * tilemap_data.tile_height) / (tilemap_data.tile_width * tilemap_data.tilemap_width)) * tilemap_data.tile_height;
            t_sprite.sprite.setPosition(sf::Vector2f(x, y));
            if (data == 0)
            {
                t_sprite.sprite.setColor(sf::Color::Transparent);
            }

            if (tile_data.size() <= data_idx)
            {
                tile_data.push_back(t_data);
            }
            else
            {
                tile_data[data_idx] = t_data;
            }
            tile_sprite.push_back(t_sprite);
        }
    }
}

void TileManager::draw(sf::RenderWindow& window, const sf::Vector2f& player_position, int player_layer, std::function<void()> draw_player_func)
{
    for (size_t layer_idx = 0; layer_idx < tilemap_data.layers.size(); layer_idx++)
    {
        if (layer_idx == player_layer)
        {
            draw_player_func();
            int a = 9;
        }
        else
        {
            for (const auto& tile : tile_sprite)
            {
                if (tile.layer_index == layer_idx && isNearPlayer(tile.sprite.getPosition(), player_position, render_distance))
                {
                    window.draw(tile.sprite, sf::BlendAlpha);
                }
            }
        }
    }   
}

void TileManager::setCollisionLayer(std::vector<int>&& layers)
{
    collision_layer = layers;
}

bool TileManager::checkCollision(const sf::Vector2f& new_position)
{
    int idx = positionToIndex(new_position);
    if (tile_data[idx].has_collision)
    {
        sf::FloatRect tile_bounds = tile_sprite[idx].sprite.getGlobalBounds();
        sf::FloatRect new_position_bounds(new_position.x, new_position.y, tilemap_data.tile_width, tilemap_data.tile_height);

        if (tile_bounds.intersects(new_position_bounds))
        {
            return true;
        }
    }
    return false;
}

bool TileManager::isNearPlayer(const sf::Vector2f& tile_position, const sf::Vector2f& player_position, float render_distance)
{
    float dx = tile_position.x - player_position.x;
    float dy = tile_position.y - player_position.y;
    float distance_squared = dx * dx + dy * dy;
    return distance_squared <= render_distance * render_distance;
}

void TileManager::registerTileTexture(const std::string& image_path, const std::string& texture_name)
{
    if (!tile_textures.empty())
    {
        auto path_stored = tile_textures.find(texture_name);
        if (path_stored != tile_textures.end())
        {
            return;
        }
    }

    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(image_path))
    {
        printf("Failed to load file!");
    }
    else
    {
        tile_textures[texture_name] = texture;
    }
}

sf::Texture& TileManager::loadTileTexture(const std::string& texture_name)
{
    auto it = tile_textures.find(texture_name);
    if (it == tile_textures.end()) 
    {
        throw std::runtime_error("Texture not found: " + texture_name);
    }
    return *(it->second);
}

uint32_t TileManager::positionToIndex(sf::Vector2f pos)
{
    int x = pos.x / tilemap_data.tile_width;
    int y = pos.y / tilemap_data.tile_height;
    int result = x + (y * tilemap_data.tilemap_width);
    return result;
}

sf::Vector2f TileManager::indexToPosition(int index)
{
    int y = index / tilemap_data.tilemap_width;
    int x = index % tilemap_data.tilemap_width;
    return sf::Vector2f(x, y);
}