#include "system/tile_manager.h"

void tile_manager::tile_parser(const std::string& json_file_path, const std::string& image_file_name) 
{
    std::ifstream input_file(json_file_path);

    if (!input_file.is_open()) 
    {
        std::cerr << "Failed to open file " << json_file_path << std::endl;
        return;
    }

    nlohmann::json json_data = nlohmann::json::parse(input_file);

    const auto& layers = json_data["layers"];
    for (const auto& layer : layers) 
    {
        if (layer["type"] == "tilelayer") 
        {
            const auto& data = layer["data"];
            int width = layer["width"];
            int height = layer["height"];

            for (int y = 0; y < height; ++y) 
            {
                for (int x = 0; x < width; ++x) 
                {
                    uint32_t tile_idx = data[y * width + x];
                    if (tile_idx > 0) 
                    {

                        std::string file = "../resources/" + image_file_name;
                        load_tile_image(file);

                        bool is_collidable = (layer_index == 0 && tile_idx > 0);
                        std::shared_ptr<tile_type> tile_type_ = std::make_shared<tile_type>(image_file_name, tile_idx, is_collidable);

                        const auto& texture = *(tile_textures[file]);
                        tile tile_ptr(tile_type_, texture);

                        tile_ptr.sprite.setPosition(x * pixel_size, y * pixel_size);

                        // Store the layer index in the tile
                        tile_ptr.layer_index = layer_index;

                        size_t idx = (tile_ptr.tile_type->get_tile_idx() - 1) % rect_tile_x;
                        size_t idy = (tile_ptr.tile_type->get_tile_idx() - 1) / rect_tile_y;
                        tile_ptr.sprite.setTextureRect(sf::IntRect((idx * pixel_size), (idy * pixel_size), pixel_size, pixel_size));

                        tiles.push_back(tile_ptr);
                    }
                }
            }
            ++layer_index;
        }
    }
}

void tile_manager::draw(sf::RenderWindow& window, const sf::Vector2f& player_position, int layer)
{
    for (const auto& tile : tiles)
    {
        if (tile.layer_index == layer && tile.layer_index > 0 && is_near_player(tile.sprite.getPosition(), player_position, render_distance))
        {
            window.draw(tile.sprite);
        }
    }
}

bool tile_manager::check_collision(const sf::Vector2f& new_position)
{
    for (const auto& tile : tiles)
    {
        if (tile.tile_type->is_collidable())
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

void tile_manager::load_tile_image(const std::string& image_path)
{
    if (!tile_textures.empty())
    {
        auto path_stored = tile_textures.find(image_path);
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
        tile_textures[image_path] = texture;
    }
}