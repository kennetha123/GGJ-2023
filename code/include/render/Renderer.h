#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <set>
#include "system/Observer.hpp"

enum class RenderLayer
{
	BACKGROUND,
	MIDGROUND,
	PROPS,
	CHARACTER,
	FOREGROUND,
	UI
};

enum class RenderBehavior
{
	STATIC,
	DYNAMIC
};

using LayerKey = std::pair<RenderLayer, RenderBehavior>;

class RenderManager
{
public:
	RenderManager();
	void addDrawable(sf::Drawable& drawable, RenderLayer layer, RenderBehavior behavior);
	void draw(sf::RenderWindow& window);
	void setLayerDirty(RenderLayer layer);
	RenderLayer intToRenderLayer(int layer);
	void clear();
private:
	std::map<LayerKey, std::vector<std::reference_wrapper<sf::Drawable>>> layers;
	std::map<RenderLayer, sf::RenderTexture> staticTextures;
	std::set<RenderLayer> dirtyStaticLayers;
};