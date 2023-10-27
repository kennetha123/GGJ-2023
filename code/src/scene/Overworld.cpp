#include "scene/Overworld.h"

Overworld::Overworld() :
	Scene(),
	main_character("../resources/Actor_sangoku01.png"),
	game_camera(sf::FloatRect(0, 0, 800, 600))
{
	auto& log = spdlog::get("main");
	log->debug("Overworld constructor");

	tiled2Sfml.setCollisionLayer({ 1, 4 });
	tiled2Sfml.tileParser("../resources/maps/", "prologue.json");
	main_character.setTilemap(tiled2Sfml);
	//main_character.sprite.setPosition(tiled2Sfml.coordToPosition(26, 5));

	auto& render = ServiceLocator::getService<RenderManager>();
	render.clear();
	for (auto& tile : tiled2Sfml.getTileSprite())
	{
		render.addDrawable(tile.sprite, render.intToRenderLayer(tile.layer_index), RenderBehavior::STATIC);
	}

	render.addDrawable(main_character.sprite, RenderLayer::CHARACTER, RenderBehavior::DYNAMIC);

	main_character.onPlayerMove([&]() {
		render.setLayerDirty(RenderLayer::BACKGROUND);
		render.setLayerDirty(RenderLayer::PROPS);
		render.setLayerDirty(RenderLayer::MIDGROUND);
		render.setLayerDirty(RenderLayer::FOREGROUND);
		});

}

void Overworld::update(float dt)
{
	game_camera.setCenter(main_character.sprite.getPosition());
	main_character.update(dt);
}

void Overworld::draw(sf::RenderWindow& window)
{
	window.setView(game_camera);
}

bool Overworld::isNearPlayer(const sf::Vector2f& tile_position, const sf::Vector2f& player_position, float render_distance)
{
	float dx = tile_position.x - player_position.x;
	float dy = tile_position.y - player_position.y;
	float distance_squared = dx * dx + dy * dy;
	return distance_squared <= render_distance * render_distance;
}
