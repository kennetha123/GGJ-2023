#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <set>
#include "system/Observer.hpp"

enum class RenderLayer {
	BACKGROUND,
	MIDGROUND,
	PROPS,
	CHARACTER,
	FOREGROUND,
	UI,
};

enum class RenderBehavior
{
	STATIC,
	DYNAMIC
};

using LayerKey = std::pair<RenderLayer, RenderBehavior>;
using LayerData = std::pair<std::reference_wrapper<sf::Drawable>, std::reference_wrapper<sf::Transformable>>;

class RenderManager
{
public:
	RenderManager();
	void addDrawable(sf::Drawable& drawable, sf::Transformable& transformable, RenderLayer layer, RenderBehavior behavior);
	void draw(sf::RenderWindow& window);
	void setLayerDirty(RenderLayer layer);
	RenderLayer intToRenderLayer(int layer);
	void setCamera(sf::View& view);
	sf::View& getCamera();
	void initRenderer(const sf::Vector2i& size);
	void initRenderer(size_t x, size_t y);
	void clear();

private:
	std::map<LayerKey, std::vector<LayerData>> layers;
	std::map<RenderLayer, sf::RenderTexture> staticTextures;
	std::set<RenderLayer> dirtyStaticLayers;
	static const std::array<RenderLayer, 6> all_layers;
	sf::View main_camera;

	sf::FloatRect getBounds(const sf::Drawable& drawable, const sf::Transformable& transformable);
};