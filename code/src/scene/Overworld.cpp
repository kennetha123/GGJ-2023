#include "scene/Overworld.h"
#include "UI/UiManager.h"
#include "UI/UiController.h"

Overworld::Overworld() :
	Scene(),
	render(ServiceLocator::getService<RenderManager>()),
	main_character("../resources/Actor_sangoku01.png", sf::Vector2i(48, 48)),
	game_camera(sf::FloatRect(0, 0, 800, 600))
{
	auto& log = spdlog::get("main");
	log->debug("Overworld constructor");

	font.loadFromFile("../resources/font/arial.ttf");

	tiled2Sfml.setCollisionLayer({ 1, 4 });
	tiled2Sfml.tileParser("../resources/maps/", "prologue.json");
	main_character.setTilemap(tiled2Sfml);
	main_character.sprite.setPosition(tiled2Sfml.coordToPosition(11, 10));

	render.clear();

	auto& ui = ServiceLocator::getService<UI::UiManager>();

	std::shared_ptr<UI::Controller::FpsController> fps_ctrl = std::make_shared<UI::Controller::FpsController>(font);
	ui.push(fps_ctrl);

	for (auto& tile : tiled2Sfml.getTileSprite())
	{
		render.addDrawable(tile.sprite, tile.sprite, render.intToRenderLayer(tile.layer_index), RenderBehavior::STATIC);
	}

	render.addDrawable(main_character.sprite, main_character.sprite, RenderLayer::CHARACTER, RenderBehavior::DYNAMIC);
	render.setCamera(game_camera);
	TilemapData tilemap = tiled2Sfml.getTilemapData();

	render.initRenderer(tilemap.tilemap_width * tilemap.tile_width, tilemap.tilemap_height * tilemap.tile_height);

	main_character.onCharacterMove([&]() {
		render.setLayerDirty(RenderLayer::BACKGROUND);
		render.setLayerDirty(RenderLayer::PROPS);
		render.setLayerDirty(RenderLayer::MIDGROUND);
		render.setLayerDirty(RenderLayer::FOREGROUND);
		});

}

void Overworld::update(float dt)
{
	main_character.update(dt);
	render.getCamera().setCenter(main_character.sprite.getPosition());
}