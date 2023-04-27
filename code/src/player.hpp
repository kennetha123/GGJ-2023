#pragma once
#include "object.hpp"
#include "system/ecs/entity.hpp"
#include <SFML/Graphics.hpp>
#include "tile_manager.hpp"
#include <memory>

class player : public entity
{
public:
    player(const std::string& image_path);
    ~player() = default;

    void movement(float dt);
    void draw(sf::RenderWindow& window);
    void set_tilemap(std::shared_ptr<tile_manager> tile_mgr);

    sf::Sprite sprite;
    std::unique_ptr<animation_component> player_animation;

private:
    sf::Texture player_texture;
    int sprite_width = 48, sprite_height = 48;
    std::shared_ptr<tile_manager> tile_manager_;
    bool is_moving = false;
    sf::Vector2f initial_position;
    sf::Vector2f move_direction;
    float elapsed_time;
    float grid_size = 32.0f;
    float move_duration = 0.2f;

    void handle_animation(float dt, int row);
    void handle_movement(float dt);
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

    // Create the animated sprite objects
    player_animation = std::make_unique<animation_component>(sprite, all_frames, 0.1f);
}

void player::movement(float dt)
{
    handle_animation(dt, -1);
    handle_movement(dt);
}

void player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void player::set_tilemap(std::shared_ptr<tile_manager> tile_mgr)
{
    tile_manager_ = tile_mgr;
}

void player::handle_animation(float dt, int row)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        row = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        row = 3;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        row = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        row = 2;
    }

    if (row != -1)
    {
        player_animation->update(dt, row);
    }
}

void player::handle_movement(float dt)
{
    if (is_moving)
    {
        elapsed_time += dt;
        float move_fraction = elapsed_time / move_duration;

        if (move_fraction >= 1.0f)
        {
            is_moving = false;
            move_fraction = 1.0f;
        }

        sprite.setPosition(initial_position + sf::Vector2f(move_fraction * move_direction.x, move_fraction * move_direction.y));
    }

    if (!is_moving)
    {
        sf::Vector2f dest;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            dest = sf::Vector2f(-grid_size, 0.0f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            dest = sf::Vector2f(0.0f, -grid_size);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            dest = sf::Vector2f(0.0f, grid_size);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            dest = sf::Vector2f(grid_size, 0.0f);
        }

        if (!tile_manager_->check_collision(sprite.getPosition() + dest))
        {
            is_moving = true;
            move_direction = dest;
            initial_position = sprite.getPosition();
            elapsed_time = 0;
        }
    }
}