#pragma once
#include <tinyxml2.h>
#include <json.hpp>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "system/Collision.h"

using namespace tinyxml2;
using json = nlohmann::json;

/*
* The reason why data and image separated, is because how tiled works,
* when you have multiple layers for example 30x20 grid and 5 layers,
* the true tile is 600, but the image that need to be rendered is 5x600
* which is 3k image, while we only need 600 tile data.
*/

struct TileObject : public GameObject
{
	TileObject()
	{
		this->add_component<Collision>();
	}
};

struct TileSprite
{
	int layer_index = 0;
	sf::Sprite sprite;
};

struct Layer
{
	std::vector<uint32_t> data;
	uint32_t height;
	uint32_t width;
	uint32_t id;
	std::string name;
	uint32_t opacity;
	std::string type;
	bool is_visible;
	uint32_t x;
	uint32_t y;
};

struct Tileset
{
	uint32_t first_gid;
	std::string source;
};

struct TilesetData
{
	std::string tiled_version;
	std::string tileset_name;
	uint32_t tile_width;
	uint32_t tile_height;
	uint32_t column;
	std::string img_source_path;
	uint32_t img_source_width;
	uint32_t img_source_height;
};

struct TilemapData
{
	int compression_level;
	uint32_t tilemap_height;
	uint32_t tilemap_width;
	bool is_infinite;
	std::vector<Layer> layers;
	uint32_t next_layer_id;
	uint32_t next_object_id;
	std::string orientation;
	std::string render_order;
	std::string tiled_version;
	uint32_t tile_height;
	uint32_t tile_width;
	std::vector<Tileset> tilesets;
	std::string type;
	std::string version;
};

class Tiled2SFML
{
private:
	std::map<std::string, std::shared_ptr<sf::Texture>> tile_textures;
	std::vector<TilesetData> tileset_data;
	TilemapData tilemap_data;
	std::vector<TileObject> tile_data;
	std::vector<TileSprite> tile_sprite;
	std::vector<int> collision_layer;

public:
	void tileParser(const std::string& tilemap_path, const std::string& filename);
	uint32_t positionToIndex(sf::Vector2f pos);
	sf::Vector2f indexToPosition(int index);
	/// <summary>
	/// set which layer that entirely work as collision.
	/// this need to be called before tileParser() happens.
	/// </summary>
	/// <param name="layers">literal value vector for layer listed.</param>
	void setCollisionLayer(std::vector<int>&& layers);
	inline TilemapData Tiled2SFML::getTilemapData() const
	{
		return tilemap_data;
	}

	inline std::vector<TilesetData> Tiled2SFML::getTilesetData() const
	{
		return tileset_data;
	}

	inline std::vector<TileSprite> Tiled2SFML::getTileSprite() const
	{
		return tile_sprite;
	}

	inline std::vector<TileObject> Tiled2SFML::getTileData() const
	{
		return tile_data;
	}

	inline TileObject Tiled2SFML::getTileDataId(int index) const
	{
		return tile_data[index];
	}
	inline TileSprite Tiled2SFML::getTileSpriteId(int index) const
	{
		return tile_sprite[index];
	}
private:
	TilemapData tilemapParse(const std::string& json_path);
	TilesetData tilesetParse(const std::string& tileset_tsx_path);
	void registerTileTexture(const std::string& image_path, const std::string& texture_name);
	sf::Texture& loadTileTexture(const std::string& texture_name);
};