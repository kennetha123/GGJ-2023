#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <map>
#include "../../json/json.hpp"
#include "object.hpp"
#include "system/ecs/entity.hpp"

struct tile : public entity {
public:
    tile(const sf::Texture& texture)
    {
        sprite = add_component<sprite_component>(texture);
        transform = add_component<transform_component>(*this);
    }

    std::shared_ptr<sprite_component> sprite;
    std::shared_ptr<transform_component> transform;

    std::string tile_file = "";
    uint32_t tile_idx = 0;
    int layer_index = 0;
};

class tile_manager {
public:
    /// <summary>
    /// used for parsing tiles into game tile.
    /// </summary>
    /// <param name="json_file_path">file path of json with extensions.</param>
    /// <param name="image_file_name">file name for image with file extension.</param>
    void tile_parser(const std::string& json_file_path, const std::string& image_file_name) 
    {
        std::ifstream input_file(json_file_path);

        if (!input_file.is_open()) 
        {
            std::cerr << "Failed to open file " << json_file_path << std::endl;
            return;
        }

        nlohmann::json::parser_callback_t ignore_comments_and_exceptions = [](int depth, nlohmann::json::parse_event_t event, nlohmann::json& parsed) 
        {
            // Ignore comments
            if (event == nlohmann::json::parse_event_t::key && parsed.dump() == "#") 
            {
                return false;
            }
            return true;
        };

        nlohmann::json json_data = nlohmann::json::parse(input_file, ignore_comments_and_exceptions);

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

                            const auto& texture = *(tile_textures[file]);
                            tile tile_ptr(texture);

                            tile_ptr.tile_idx = tile_idx;
                            tile_ptr.tile_file = image_file_name;
                            tile_ptr.transform->set_position(x * pixel_size, y * pixel_size);

                            // Store the layer index in the tile
                            tile_ptr.layer_index = layer_index;

                            size_t idx = (tile_ptr.tile_idx - 1) % rect_tile_x;
                            size_t idy = (tile_ptr.tile_idx - 1) / rect_tile_y;
                            tile_ptr.sprite->set_texture_rect(sf::IntRect((idx * pixel_size), (idy * pixel_size), pixel_size, pixel_size));

                            tiles.push_back(tile_ptr);
                        }
                    }
                }

                // Increment layer_index after processing the current layer
                ++layer_index;
            }
        }
    }

    void draw(sf::RenderWindow& window, const sf::Vector2f& player_position, int layer)
    {
        for (const auto& tile : tiles)
        {
            if (tile.layer_index == layer && is_near_player(tile.transform->get_position(), player_position, render_distance))
            {
                window.draw(tile.sprite->get_sprite());
            }
        }
    }

private:
    /// <summary>
    /// check if player near tiles, so it can optimize the draw function when it is
    /// too far from the view scenes.
    /// </summary>
    /// <param name="tile_position">tile position.</param>
    /// <param name="player_position">player position.</param>
    /// <param name="render_distance">how far it can draw in pixel unit.</param>
    /// <returns></returns>
    bool is_near_player(const sf::Vector2f& tile_position, const sf::Vector2f& player_position, float render_distance) 
    {
        float dx = tile_position.x - player_position.x;
        float dy = tile_position.y - player_position.y;
        float distance_squared = dx * dx + dy * dy;
        return distance_squared <= render_distance * render_distance;
    }
private:
    /// <summary>
    /// load tile images and store it inside tile_textures.
    /// this function need to be called before using any tile_textures.
    /// </summary>
    /// <param name="image_path"></param>
    void load_tile_image(const std::string& image_path) 
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

private:
    std::map<std::string, std::shared_ptr<sf::Texture>> tile_textures;
    std::vector<tile> tiles;
    int layer_index = 0;

    size_t rect_tile_x = 8;
    size_t rect_tile_y = 8;
    size_t pixel_size = 32;
    float render_distance = 550.0f;
};
