#include "tiled2sfml.h"

void Tiled2SFML::tileParser(const std::string& tilemap_path, const std::string& filename)
{
	Tiled2SFML tile_manager;
	tilemap_data = tile_manager.tilemapParse(tilemap_path + filename);

	uint32_t size_map = tilemap_data.tilemap_width * tilemap_data.tilemap_height;
	tile_data.reserve(size_map);
	tile_sprite.reserve(size_map * tilemap_data.layers.size());

	// register texture
	for (size_t i = 0; i < tilemap_data.tilesets.size(); i++)
	{
		std::string rel_path = tilemap_path + tilemap_data.tilesets[i].source;
		size_t last_slash = rel_path.find_last_of('/');
		if (last_slash != std::string::npos)
		{
			rel_path = rel_path.substr(0, last_slash + 1);
		}
		tileset_data.push_back(tile_manager.tilesetParse(tilemap_path + tilemap_data.tilesets[i].source));
		registerTileTexture(rel_path + tileset_data[i].img_source_path, tileset_data[i].tileset_name);
	}

	for (size_t layer_idx = 0; layer_idx < tilemap_data.layers.size(); layer_idx++)
	{
		// iterate through all data from each layer
		for (size_t data_idx = 0; data_idx < tilemap_data.layers[layer_idx].data.size(); data_idx++)
		{
			TileObject t_data;
			TileSprite t_sprite;
			int data = tilemap_data.layers[layer_idx].data[data_idx];
			int tileset_idx = 0;

			t_sprite.layer_index = layer_idx;

			if (layer_idx > 0)
			{
				t_data = tile_data[data_idx];
			}

			for (size_t i = 0; i < collision_layer.size(); i++)
			{
				if (t_sprite.layer_index == collision_layer[i] && data > 0)
				{
					t_data.get_component<Collision>()->is_collide = true;
				}
			}

			// always -1 because Tiled gid start from 1.
			// this loops for search which tileset will be used,
			// since Tiled only provide first gid, used for determine
			// index of first tile grid in image tileset.
			// TODO: bad implementation
			int i = 0;
			int temp_data = 0;
			while (true)
			{
				if (i <= tilemap_data.tilesets.size() - 1)
				{
					if (data > tilemap_data.tilesets[i].first_gid - 1)
					{
						tileset_idx = i;
						temp_data = data - tilemap_data.tilesets[i].first_gid;
						i++;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			data = temp_data;

			sf::Texture& tx = loadTileTexture(tileset_data[tileset_idx].tileset_name);

			t_sprite.sprite.setTexture(tx);
			int x_rect = (data % tileset_data[tileset_idx].column) * tileset_data[tileset_idx].tile_width;
			int y_rect = (data / tileset_data[tileset_idx].column) * tileset_data[tileset_idx].tile_height;

			t_sprite.sprite.setTextureRect(
				sf::IntRect(x_rect, y_rect,
					tilemap_data.tile_width,
					tilemap_data.tile_height));

			int x = (data_idx * tilemap_data.tile_width) % (tilemap_data.tile_width * tilemap_data.tilemap_width);
			int y = ((data_idx * tilemap_data.tile_height) / (tilemap_data.tile_width * tilemap_data.tilemap_width)) * tilemap_data.tile_height;
			t_sprite.sprite.setPosition(sf::Vector2f(x, y));

			if (data == 0)
			{
				t_sprite.sprite.setColor(sf::Color::Transparent);
			}

			if (tile_data.size() <= data_idx)
			{
				tile_data.push_back(t_data);
			}
			else
			{
				tile_data[data_idx] = t_data;
			}
			tile_sprite.push_back(t_sprite);
		}
	}
}

void Tiled2SFML::registerTileTexture(const std::string& image_path, const std::string& texture_name)
{
	if (!tile_textures.empty())
	{
		auto path_stored = tile_textures.find(texture_name);
		if (path_stored != tile_textures.end())
		{
			return;
		}
	}

	auto texture = std::make_shared<sf::Texture>();
	if (!texture->loadFromFile(image_path))
	{
		printf("Failed to load file!");
	}
	else
	{
		tile_textures[texture_name] = texture;
	}
}

sf::Texture& Tiled2SFML::loadTileTexture(const std::string& texture_name)
{
	auto it = tile_textures.find(texture_name);
	if (it == tile_textures.end())
	{
		throw std::runtime_error("Texture not found: " + texture_name);
	}
	return *(it->second);
}

uint32_t Tiled2SFML::positionToIndex(sf::Vector2f pos)
{
	int x = pos.x / tilemap_data.tile_width;
	int y = pos.y / tilemap_data.tile_height;
	int result = x + (y * tilemap_data.tilemap_width);
	return result;
}

sf::Vector2f Tiled2SFML::indexToPosition(int index)
{
	int y = index / tilemap_data.tilemap_width;
	int x = index % tilemap_data.tilemap_width;
	return sf::Vector2f(x, y);
}

void Tiled2SFML::setCollisionLayer(std::vector<int>&& layers)
{
	collision_layer = layers;
}

TilemapData Tiled2SFML::tilemapParse(const std::string& json_path)
{
	std::ifstream input_file(json_path);

	if (!input_file.is_open())
	{
		std::cerr << "Failed to open file " << json_path << std::endl;
	}

	TilemapData result;
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
		Layer l;
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
		Tileset t;
		t.first_gid = tileset_m["firstgid"];
		t.source = tileset_m["source"];

		result.tilesets.push_back(t);
	}

	return result;
}

TilesetData Tiled2SFML::tilesetParse(const std::string& tileset_tsx_path)
{
	TilesetData data;
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
