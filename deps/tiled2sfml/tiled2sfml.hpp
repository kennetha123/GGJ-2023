#pragma once
#include <tinyxml2.h>
#include <json.hpp>
#include <iostream>

using namespace tinyxml2;
using json = nlohmann::json;

struct layer
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

struct tileset
{
	uint32_t first_gid;
	std::string source;
};

struct tilesetData
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

struct tilemapData
{
	int compression_level;
	uint32_t tilemap_height;
	uint32_t tilemap_width;
	bool is_infinite;
	std::vector<layer> layers;
	uint32_t next_layer_id;
	uint32_t next_object_id;
	std::string orientation;
	std::string render_order;
	std::string tiled_version;
	uint32_t tile_height;
	uint32_t tile_width;
	std::vector<tileset> tilesets;
	std::string type;
	std::string version;
};

class Tiled2SFML
{
public:
	void GenerateTile(const std::string& map_path)
	{
		tilemapParse(map_path);

		//parse image

	}

	tilemapData tilemapParse(const std::string& json_path)
	{
		std::ifstream input_file(json_path);

		if (!input_file.is_open())
		{
			std::cerr << "Failed to open file " << json_path << std::endl;
		}

		tilemapData result;
		json j = json::parse(input_file);

		result.compression_level = j["compressionlevel"];
		result.tilemap_height = j["height"];
		result.tilemap_width = j["width"];
		result.is_infinite = j["infinite"];
		result.next_layer_id = j["nextlayerid"];
		result.next_object_id = j["nextobjectid"];
		result.orientation = j["orientation"];
		result.render_order = j["renderorder"];
		result.tiled_version = j["tiledversion"];
		result.tile_height = j["tileheight"];
		result.tile_width = j["tilewidth"];
		result.type = j["type"];
		result.version = j["version"];

		// Parsing layers
		for (const auto& layer_m : j["layers"])
		{
			layer l;
			l.data = layer_m["data"].get<std::vector<uint32_t>>();
			l.height = layer_m["height"];
			l.width = layer_m["width"];
			l.id = layer_m["id"];
			l.name = layer_m["name"];
			l.opacity = layer_m["opacity"];
			l.type = layer_m["type"];
			l.is_visible = layer_m["visible"];
			l.x = layer_m["x"];
			l.y = layer_m["y"];

			result.layers.push_back(l);
		}

		// Parsing tilesets
		for (const auto& tileset_m : j["tilesets"])
		{
			tileset t;
			t.first_gid = tileset_m["firstgid"];
			t.source = tileset_m["source"];

			result.tilesets.push_back(t);
		}

		return result;
	}

	tilesetData tilesetParse(const std::string& tileset_tsx_path)
	{
		tilesetData data;
		XMLDocument doc;
		if (doc.LoadFile(tileset_tsx_path.c_str()) != XML_SUCCESS)
		{
			std::cerr << "Failed to load tileset tsx file " << doc.ErrorName() << std::endl;
			throw std::runtime_error("Failed to load XML");
		}

		if (doc.Error()) {
			std::cerr << "XML Parsing Error: " << doc.ErrorName() << std::endl;
		}

		XMLElement* tileset = doc.FirstChildElement("tileset");
		if (tileset == NULL)
		{
			std::cerr << "Failed to find <tileset> element in the XML." << std::endl;
			throw std::runtime_error("Failed to find <tileset> element");
		}

		data.tiled_version = tileset->Attribute("tiledversion");
		data.tileset_name = tileset->Attribute("name");
		data.tile_width = tileset->IntAttribute("tilewidth");
		data.tile_height = tileset->IntAttribute("tileheight");
		data.column = tileset->IntAttribute("columns");

		XMLElement* image = tileset->FirstChildElement("image");
		if (!image)
		{
			std::cerr << "Failed to find <image> element in the XML." << std::endl;
			throw std::runtime_error("Failed to find <image> element");
		}

		data.img_source_path = image->Attribute("source");
		data.img_source_width = image->IntAttribute("width");
		data.img_source_height = image->IntAttribute("height");

		return data;
	}	
};