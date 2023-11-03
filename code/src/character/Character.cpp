#include "character/Character.h"
#include "utils/Time.h"

Character::Character(const std::string& image_path, const sf::Vector2i& sprite_size)
{
    log = spdlog::get("main");
	if (!player_texture.loadFromFile(image_path))
	{
		printf_s("Failed to load file!");
	}

	sprite.setTexture(player_texture);
	sprite.setTextureRect(sf::IntRect(0, 0, sprite_size.x, sprite_size.y));

	this->addComponent<Collision>();
}

void Character::update(float dt)
{
    if (is_moving)
    {
        mov_elapsed_time += dw::Time::getDeltaTime();
        float move_fraction = mov_elapsed_time / move_duration;

        sf::Vector2f pos;
        pos.x = initial_position.x + move_fraction * (move_target.x - initial_position.x);
        pos.y = initial_position.y + move_fraction * (move_target.y - initial_position.y);

        sprite.setPosition(pos);
        log->info("pos x {} , y {}", pos.x, pos.y);
        if (move_fraction >= 1.0f)
        {
            move_fraction = 1.0f;
            is_moving = false;
            sprite.setPosition(move_target);  // Ensure we snap exactly to our target
        }

        if (onCharacterMoveCallback)
        {
            onCharacterMoveCallback();
        }
    }
}

void Character::move(const sf::Vector2f& direction)
{
    // Assuming directions are normalized (length = 1) like sf::Vector2f(0,1) for down
    move_target = sprite.getPosition() + direction * 48.0f;

    //if (!checkCollision(move_target))
    {
        is_moving = true;
        mov_elapsed_time = 0;
        initial_position = sprite.getPosition();
    }

    anim.setParam("move_x", move_destination.x);
    anim.setParam("move_y", move_destination.y);
}

void Character::setTilemap(Tiled2SFML& tiled2Sfml_)
{
	tiled2Sfml = std::make_unique<Tiled2SFML>(tiled2Sfml_);
}

bool Character::checkCollision(const sf::Vector2f& dest)
{
	int idx = tiled2Sfml->positionToIndex(dest);
	if (tiled2Sfml->getTileDataId(idx).getComponent<Collision>()->is_collide)
	{
		return true;
	}
	return false;
}

void Character::onCharacterMove(std::function<void()> func)
{
	onCharacterMoveCallback = func;
}