#include "system/Collision.h"
#include <SFML/Graphics.hpp>

//bool Collision::checkCollision(const Collision& col, const sf::Sprite& origin, const sf::Vector2f& destination)
//{
//
//	if (col.is_collide)
//	{
//		sf::FloatRect tile_bounds = origin.getGlobalBounds();
//		sf::FloatRect new_position_bounds
//			(destination.x, 
//			destination.y, 
//			48, 
//			48);
//
//		if (tile_bounds.intersects(new_position_bounds))
//		{
//			return true;
//		}
//	}
//	return false;
	/*int idx = tiled2Sfml.positionToIndex(sprite.getPosition());
	if (tiled2Sfml.getTileDataId(idx).has_collision)
	{
		sf::FloatRect tile_bounds = tiled2Sfml.getTileSpriteId(idx).sprite.getGlobalBounds();
		sf::FloatRect new_position_bounds(new_position.x, new_position.y, tiled2Sfml.getTilemapData().tile_width, tiled2Sfml.getTilemapData().tile_height);

		if (tile_bounds.intersects(new_position_bounds))
		{
			return true;
		}
	}
	return false;*/
//}
