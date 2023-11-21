#include "scene/Overworld.h"
#include "UI/UiManager.h"
#include "UI/UiController.h"
#include "audio/AudioManager.h"
#include "utils/Logs.h"

Overworld::Overworld() :
	Scene(),
	render(ServiceLocator::getService<RenderManager>()),
	main_character("../resources/Actor_sangoku01.png", sf::Vector2i(48, 48)),
	game_camera(sf::FloatRect(0, 0, 1280, 720))
{
	Logs::instance().log("scene", spdlog::level::debug, "Overworld Constructor");

	font.loadFromFile("../resources/font/arial.ttf");

	tiled2Sfml.setCollisionLayer({ 1, 4 });
	tiled2Sfml.tileParser("../resources/maps/", "prologue.json");
	main_character.setTilemap(tiled2Sfml);
	main_character.setNPC(&npcm);
	main_character.sprite.setPosition(tiled2Sfml.coordToPosition(11, 11));
	npcm.setNPCScene("../resources/NPC/Overworld.json");

	render.clear();

	auto& ui = ServiceLocator::getService<UI::UiManager>();

	std::shared_ptr<UI::Controller::FpsController> fps_ctrl = std::make_shared<UI::Controller::FpsController>(font);
	ui.push(fps_ctrl);

	for (auto& tile : tiled2Sfml.getTileSprite())
	{
		render.addDrawable(tile.sprite, tile.sprite, render.intToRenderLayer(tile.layer_index), RenderBehavior::STATIC);
	}

	for (auto& npc : npcm.npcs)
	{
		npc->setTilemap(tiled2Sfml);
		render.addDrawable(npc->sprite, npc->sprite, RenderLayer::CHARACTER, RenderBehavior::DYNAMIC);
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

	auto& audio = ServiceLocator::getService<AudioManager>();
	audio.addBgm("main_bgm", "../resources/Audio/Big Day Out.ogg");
	audio.playBgm("main_bgm", true, 50.f);

}

void Overworld::update(float dt)
{
	main_character.update(dt);
	for (auto& npc : npcm.npcs)
	{
		npc->update(dt);
	}

	render.getCamera().setCenter(main_character.sprite.getPosition());
}