#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include "object.hpp"

struct tile : public object
{
public:
	void set_world_pos(int x, int y)
	{
		sprite.setPosition(x, y);
	}

	sf::Vector2i get_world_pos() const
	{
		return static_cast<sf::Vector2i>(sprite.getPosition());
	}

	std::string tile_file;
	uint32_t tile_idx;
};

class tile_manager
{
public:
	void generate_tiles()
	{
		tile_parser("../resources/test_parser.txt");
	}

	void render(sf::RenderWindow& window)
	{
		for (size_t i = 0; i < tiles.size(); ++i)
		{
			window.draw(tiles[i].sprite);
		}
	}

private:
	/// <summary>
	/// load image and store to image reference.
	/// </summary>
	/// <param name="image_path">specify image file path.</param>
	void load_image(const std::string& image_path)
	{
		if (!tile_textures.empty())
		{
			auto path_stored = tile_textures.find(image_path);
			if (path_stored == tile_textures.end())
			{
				return;
			}
		}

		sf::Texture texture;
		if (!texture.loadFromFile(image_path))
		{
			printf_s("Failed to load file!");
		}

		tile_textures[image_path] = std::move(texture);
	}

	/// <summary>
	/// parse tile information to data structure format.
	/// </summary>
	/// <param name="tile_info">tile info file that already separated.</param>
	/// <param name="tile_ptr">pointer to tile.</param>
	std::unique_ptr<tile> parse_tile_info(const std::string& tile_info)
	{
		std::unique_ptr<tile> tile_ptr = std::make_unique<tile>();
		int x, y;
		char delimiter = ',';
		std::istringstream iss(tile_info);
		iss >> x >> delimiter >> y >> delimiter >> tile_ptr->tile_idx >> delimiter >> tile_ptr->tile_file;
		tile_ptr->set_world_pos(x, y);
		return tile_ptr;
	}

	/// <summary>
	/// parse from .txt file (custom file)
	/// to data structure in engine.
	/// </summary>
	/// <param name="file_path">file location.</param>
	void tile_parser(const std::string& file_path)
	{
		std::ifstream input_file(file_path);

		if (!input_file.is_open())
		{
			std::cerr << "Failed to open file " << file_path << std::endl;
			return;
		}

		std::string content((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());

		size_t start = 0;

		while ((start = content.find("\"", start)) != std::string::npos)
		{
			size_t end = content.find("\"", start + 1);

			// extract the information for each tile
			std::string tile_info = content.substr(start + 1, end - start - 1);
			std::cout << "tile info : " << tile_info << std::endl;
			std::unique_ptr<tile> tile_ptr = parse_tile_info(tile_info);
			std::string file = "../resources/" + tile_ptr->tile_file + ".png";

			load_image(file);
			tile_ptr->set_texture(tile_textures[file]);

			size_t idx = (tile_ptr->tile_idx - 1) % rect_tile_x;
			size_t idy = (tile_ptr->tile_idx - 1) / rect_tile_y;
			tile_ptr->sprite.setTextureRect(sf::IntRect((idx * pixel_size), (idy * pixel_size), pixel_size, pixel_size));

			tiles.push_back(std::move(*tile_ptr));

			start = end + 1;
		}
	}

private:
	std::map<std::string, sf::Texture> tile_textures;
	std::vector<tile> tiles;
	size_t rect_tile_x = 8;
	size_t rect_tile_y = 8;
	size_t pixel_size = 32;
};