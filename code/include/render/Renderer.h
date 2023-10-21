#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "system/Observer.hpp"

class Renderer
{
public:
	virtual void dynamic_draw(sf::RenderWindow& window) = 0;
	virtual void static_draw(sf::RenderTexture& render_tex) = 0;
};

class RenderManager
{
public:
	RenderManager(sf::RenderWindow& window, sf::RenderTexture& render_tex);
	void initRenderer();
	void registerRenderer(std::shared_ptr<Renderer> renderer);
	void draw();

	void setNeedRedraw(bool value);
	bool getNeedRedraw() const;

private:
	sf::RenderWindow& render_window;
	sf::RenderTexture& render_texture;
	std::vector<std::shared_ptr<Renderer>> renderers;
	bool isNeedRedraw = true;
	sf::Sprite cached_sprite;
};