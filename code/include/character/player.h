#pragma once
#include "system/components.h"
#include <memory>

class player : public entity
{
public:
    player(const std::string& image_path);
    ~player() = default;

    void update(float dt);
    void draw(sf::RenderWindow& window);
    void set_tile_manager(std::shared_ptr<TileManager> tile_mgr);

    sf::Sprite sprite;
    std::unique_ptr<animation_component> player_animation;
    std::unique_ptr<movement_component> player_movement;

private:
    sf::Texture player_texture;
    int sprite_width = 48, sprite_height = 48;
};