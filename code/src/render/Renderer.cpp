#include "render/Renderer.h"

RenderManager::RenderManager(sf::RenderWindow& window, sf::RenderTexture& render_tex) :
	render_window(window), render_texture(render_tex)
{
}

void RenderManager::initRenderer()
{
    render_texture.create(render_window.getSize().x, render_window.getSize().y);
    render_texture.clear();

    for (size_t i = 0; i < renderers.size(); i++)
    {
        renderers[i]->static_draw(render_texture);
    }

    render_texture.display();

}

void RenderManager::registerRenderer(std::shared_ptr<Renderer> renderer)
{
    renderers.push_back(renderer);
}

void RenderManager::draw()
{
    if (getNeedRedraw())
    {
        render_texture.clear();
        for (size_t i = 0; i < renderers.size(); i++)
        {
            renderers[i]->static_draw(render_texture);
        }
        render_texture.display();
        setNeedRedraw(false);
    }

    render_window.clear(sf::Color::Cyan);
    cached_sprite.setTexture(render_texture.getTexture());
    render_window.draw(cached_sprite);
    for (size_t i = 0; i < renderers.size(); i++)
    {
        renderers[i]->dynamic_draw(render_window);
    }
    render_window.display();

}

void RenderManager::setNeedRedraw(bool value) {
    if (isNeedRedraw != value) {
        isNeedRedraw = value;
        //notify();
    }
}

bool RenderManager::getNeedRedraw() const {
    return isNeedRedraw;
}