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

	sf::Vector2i get_world_pos()
	{
		return static_cast<sf::Vector2i>(sprite.getPosition());
	}

	std::string tile_file;
	uint32_t tile_idx;
};

class tile_manager
{
	std::map<std::string, sf::Texture> tile_textures;
	std::vector<tile> tiles;
public:
	tile_manager()
	{
		tiles.reserve(1024);
	}

	/// <summary>
	/// load image and store to image reference.
	/// </summary>
	/// <param name="image_path">specify image file path.</param>
	/// <returns>is on database.</returns>
	bool image_loader(const std::string& image_path)
	{
		if (!tile_textures.empty())
		{
			auto path_stored = tile_textures.find(image_path);
			if (path_stored == tile_textures.end())
			{
				return true;
			}
		}

		sf::Texture texture;
		if (!texture.loadFromFile(image_path))
		{
			printf_s("Failed to load file!");
		}

		tile_textures[image_path] = texture;
		return false;
	}

	void tile_parser(std::vector<tile>& result, const std::string& file_path)
	{
		std::ifstream input_file(file_path);

		if (!input_file.is_open())
		{
			std::cerr << "Failed to open file " << file_path << std::endl;
		}

		std::string content((std::istreambuf_iterator<char>(input_file)),
			std::istreambuf_iterator<char>());

		// use heap because will be destroy coz vector
		std::unique_ptr<tile> tile_ptr = std::make_unique<tile>();

		int curr_pos = 0;
		int last_pos = content.length();
		int after_end = 0;

		while (curr_pos < last_pos)
		{
			int start = content.find_first_of("\"", after_end);
			int end = content.find_first_of("\"", start + 1);
			after_end = end + 1;

			std::cout << "number of line of first quote : " << start << std::endl;
			std::cout << "number of line of second quote : " << end << std::endl;
			if (end != std::string::npos)
			{
				// extract the information for each tile
				std::string tile_info = content.substr(start + 1, end - start - 1);
				std::cout << "tile info : " << tile_info << std::endl;
				int x, y;
				char delimiter = ',';
				std::istringstream iss(tile_info);

				iss >> x >> delimiter >> y >> delimiter >> tile_ptr->tile_idx >> delimiter >> tile_ptr->tile_file;
				std::string file = "../resources/" + tile_ptr->tile_file + ".png";

				if (!image_loader(file))
				{
					//std::cout << "file name : " << tile_ptr->tile_file << std::endl;
				}
				tile_ptr->set_texture(tile_textures[file]);
				tile_ptr->sprite.setTextureRect(
					sf::IntRect(((tile_ptr->tile_idx - 1) % 8 * 32), 
						((tile_ptr->tile_idx - 1) / 8 * 32), 32, 32));
				tile_ptr->set_world_pos(x, y);

				result.push_back(*tile_ptr);

				// move start to the next tile information
				start = content.find_first_of("\"", after_end);
				end = content.find_first_of("\"", start + 1);
				if (end == 0)
				{
					break;
				}
				curr_pos = end;

			}
		}
	}

	void generate_tiles()
	{
		tile_parser(tiles, "../resources/test_parser.txt");

	}

	void render(sf::RenderWindow& window)
	{
		for (size_t i = 0; i < tiles.size(); ++i)
		{
			window.draw(tiles[i].sprite);
		}
	}
};