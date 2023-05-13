#pragma once
#include "../system/ecs/components.h"
#include "attributes.hpp"
#include <memory>

class player : public entity
{
public:
    player(const std::string& image_path);
    ~player() = default;

    void update(float dt);
    void draw(sf::RenderWindow& window);
    void set_tile_manager(std::shared_ptr<tile_manager> tile_mgr);

    sf::Sprite sprite;
    std::unique_ptr<animation_component> player_animation;
    std::unique_ptr<movement_component> player_movement;

private:
    sf::Texture player_texture;
    int sprite_width = 48, sprite_height = 48;
};

player::player(const std::string& image_path)
{
    if (!player_texture.loadFromFile(image_path))
    {
        printf_s("Failed to load file!");
    }

    sprite.setTexture(player_texture);
    sprite.setTextureRect(sf::IntRect(0, 0, sprite_width, sprite_height));
    sprite.setPosition(0.0f, 0.0f);

    std::vector<std::vector<sf::IntRect>> all_frames = {
        { // Down
            {48, 0, sprite_width, sprite_height},
            {0, 0, sprite_width, sprite_height},
            {48, 0, sprite_width, sprite_height},
            {96, 0, sprite_width, sprite_height},
        },
        { // Left
            {48, 48, sprite_width, sprite_height},
            {0, 48, sprite_width, sprite_height},
            {48, 48, sprite_width, sprite_height},
            {96, 48, sprite_width, sprite_height},
        },
        { // Right
            {48, 96, sprite_width, sprite_height},
            {0, 96, sprite_width, sprite_height},
            {48, 96, sprite_width, sprite_height},
            {96, 96, sprite_width, sprite_height},
        },
        { // Up
            {48, 144, sprite_width, sprite_height},
            {0, 144, sprite_width, sprite_height},
            {48, 144, sprite_width, sprite_height},
            {96, 144, sprite_width, sprite_height},
        }
    };

    player_animation = std::make_unique<animation_component>(sprite, all_frames, 0.1f);
    player_movement = std::make_unique<movement_component>(sprite);
}

void player::update(float dt)
{
    player_animation->handle_animation(dt, -1);
    player_movement->handle_movement(dt);
}

void player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void player::set_tile_manager(std::shared_ptr<tile_manager> tile_mgr)
{
    player_movement->set_tile_manager(tile_mgr);
}