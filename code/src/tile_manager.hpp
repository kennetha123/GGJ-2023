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

struct tile : public object {
public:
    void set_world_pos(int x, int y) {
        sprite.setPosition(x, y);
    }

    sf::Vector2i get_world_pos() const {
        return static_cast<sf::Vector2i>(sprite.getPosition());
    }

    std::string tile_file;
    uint32_t tile_idx;
};

class tile_manager {
public:
    /// <summary>
    /// used for parsing tiles into game tile.
    /// </summary>
    /// <param name="json_file_path">file path of json with extensions.</param>
    /// <param name="image_file_name">file name for image with file extension.</param>
    void tile_parser(const std::string& json_file_path, const std::string& image_file_name) {
        std::ifstream input_file(json_file_path);

        if (!input_file.is_open()) {
            std::cerr << "Failed to open file " << json_file_path << std::endl;
            return;
        }

        nlohmann::json::parser_callback_t ignore_comments_and_exceptions = [](int depth, nlohmann::json::parse_event_t event, nlohmann::json& parsed) {
            // Ignore comments
            if (event == nlohmann::json::parse_event_t::key && parsed.dump() == "#") {
                return false;
            }
            return true;
        };

        nlohmann::json json_data = nlohmann::json::parse(input_file, ignore_comments_and_exceptions);

        const auto& layers = json_data["layers"];
        for (const auto& layer : layers) {
            if (layer["type"] == "tilelayer") {
                const auto& data = layer["data"];
                int width = layer["width"];
                int height = layer["height"];

                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        uint32_t tile_idx = data[y * width + x];
                        if (tile_idx > 0) {
                            std::unique_ptr<tile> tile_ptr = std::make_unique<tile>();
                            tile_ptr->tile_idx = tile_idx;
                            tile_ptr->tile_file = image_file_name;

                            tile_ptr->set_world_pos(x * pixel_size, y * pixel_size);

                            std::string file = "../resources/" + tile_ptr->tile_file;
                            load_tile_image(file);
                            tile_ptr->set_texture(*(tile_textures[file]));

                            size_t idx = (tile_ptr->tile_idx - 1) % rect_tile_x;
                            size_t idy = (tile_ptr->tile_idx - 1) / rect_tile_y;
                            tile_ptr->sprite.setTextureRect(sf::IntRect((idx * pixel_size), (idy * pixel_size), pixel_size, pixel_size));

                            tiles.push_back(std::move(*tile_ptr));
                        }
                    }
                }
            }
        }

        std::cout << "tiles 0 : " << tiles[0].get_world_pos().x << " " << tiles[0].get_world_pos().y << std::endl;
    }

    void render(sf::RenderWindow& window, const sf::Vector2f& player_position, float render_distance) {
        for (size_t i = 0; i < tiles.size(); ++i) {
            if (is_near_player(tiles[i].sprite.getPosition(), player_position, render_distance)) {
                window.draw(tiles[i].sprite);
            }
        }
    }

private:
    bool is_near_player(const sf::Vector2f& tile_position, const sf::Vector2f& player_position, float render_distance) {
        float dx = tile_position.x - player_position.x;
        float dy = tile_position.y - player_position.y;
        float distance_squared = dx * dx + dy * dy;
        return distance_squared <= render_distance * render_distance;
    }
private:
    void load_tile_image(const std::string& image_path) {
        if (!tile_textures.empty()) {
            auto path_stored = tile_textures.find(image_path);
            if (path_stored != tile_textures.end()) {
                return;
            }
        }

        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(image_path)) {
            printf("Failed to load file!");
        }
        else {
            tile_textures[image_path] = texture;
        }
    }private:
    std::map<std::string, std::shared_ptr<sf::Texture>> tile_textures;
    std::vector<tile> tiles;
    size_t rect_tile_x = 8;
    size_t rect_tile_y = 8;
    size_t pixel_size = 32;
};
