#include "system/tile_manager.h"

void tile_manager::tile_parser(const std::string& json_file_path) 
{
    std::string prepath = "../resources/maps/";
    Tiled2SFML tile_manager;
    tilemapData map_data = tile_manager.tilemapParse(json_file_path);
    
    // register texture
    for (size_t i = 0; i < map_data.tilesets.size(); i++)
    {
        tileset_data.push_back(tile_manager.tilesetParse(prepath + map_data.tilesets[i].source));
        register_tile_texture(prepath + tileset_data[i].img_source_path, tileset_data[i].tileset_name);
    }
    
    for (size_t layer_idx = 0; layer_idx < map_data.layers.size(); layer_idx++)
    {
        // iterate through all data from each layer
        for (size_t data_idx = 0; data_idx < map_data.layers[layer_idx].data.size(); data_idx++)
        {
            tile_v2 t;
           
            int data = map_data.layers[layer_idx].data[data_idx];
            int tileset_idx = 0;

            int i = 0;
            int temp_data = 0;

            t.layer_index = layer_idx;
            // always +1 because Tiled gid start from 1.
            // TODO: bad implementation
            while (true)
            {
                if (i <= map_data.tilesets.size() - 1)
                {
                    if (data > map_data.tilesets[i].first_gid - 1)
                    {
                        tileset_idx = i;
                        temp_data = data - map_data.tilesets[i].first_gid;
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

            sf::Texture& tx = load_tile_texture(tileset_data[tileset_idx].tileset_name);

            t.sprite.setTexture(tx);
            int x_rect = (data % tileset_data[tileset_idx].column) * tileset_data[tileset_idx].tile_width;
            int y_rect = (data / tileset_data[tileset_idx].column) * tileset_data[tileset_idx].tile_height;

            t.sprite.setTextureRect(
                sf::IntRect(x_rect, y_rect,
                    map_data.tile_width,
                    map_data.tile_height));

            int x = (data_idx * map_data.tile_width) % (map_data.tile_width * map_data.tilemap_width);
            int y = ((data_idx * map_data.tile_height) / (map_data.tile_width * map_data.tilemap_width)) * map_data.tile_height;
            t.sprite.setPosition(sf::Vector2f(x, y));
            if (data == 0)
            {
                t.sprite.setColor(sf::Color::Transparent);
            }
            tiles.push_back(t);

            //int data = map_data.layers[layer_idx].data[data_idx];

            //t.sprite.setTexture(*tx);
            //t.sprite.setTextureRect(sf::IntRect(48, 48, 48, 48));
            //t.sprite.setPosition(sf::Vector2f(0.0f, 0.0f));
            //t.sprite.setTextureRect(
            //    sf::IntRect(
            //    (data * tileset_data[tileset_idx].tile_width) % tileset_data[tileset_idx].img_source_width,
            //        (data % (tileset_data[tileset_idx].img_source_height / tileset_data[tileset_idx].tile_height)) * tileset_data[tileset_idx].tile_height,
            //        map_data.tile_width,
            //        map_data.tile_height));

            //t.sprite.setPosition(sf::Vector2f((width_idx * map_data.tile_width) % map_data.tilemap_width,
            //    height_idx * map_data.tile_height % map_data.tilemap_height));

            //tiles.push_back(t);
        }
    }
}

void tile_manager::draw(sf::RenderWindow& window, const sf::Vector2f& player_position, int layer)
{
    for (const auto& tile : tiles)
    {
       // if (tile.layer_index == layer)// && is_near_player(tile.sprite.getPosition(), player_position, render_distance))
        {
            window.draw(tile.sprite, sf::BlendAlpha);
        }
    }
}

bool tile_manager::check_collision(const sf::Vector2f& new_position)
{
    for (const auto& tile : tiles)
    {
 //       if (tile.tile_type->is_collidable())
        {
            sf::FloatRect tile_bounds = tile.sprite.getGlobalBounds();
            sf::FloatRect new_position_bounds(new_position.x, new_position.y, pixel_size, pixel_size);

            if (tile_bounds.intersects(new_position_bounds))
            {
                return true;
            }
        }
    }
    return false;
}


bool tile_manager::is_near_player(const sf::Vector2f& tile_position, const sf::Vector2f& player_position, float render_distance)
{
    float dx = tile_position.x - player_position.x;
    float dy = tile_position.y - player_position.y;
    float distance_squared = dx * dx + dy * dy;
    return distance_squared <= render_distance * render_distance;
}

void tile_manager::register_tile_texture(const std::string& image_path, const std::string& texture_name)
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

sf::Texture& tile_manager::load_tile_texture(const std::string& texture_name)
{
    auto it = tile_textures.find(texture_name);
    if (it == tile_textures.end()) 
    {
        throw std::runtime_error("Texture not found: " + texture_name);
    }
    return *(it->second);
}
