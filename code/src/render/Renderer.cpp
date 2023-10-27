#include "render/Renderer.h"
#include "spdlog/spdlog.h"
RenderManager::RenderManager()
{

}

void RenderManager::addDrawable(sf::Drawable& drawable, RenderLayer layer, RenderBehavior behavior) 
{
    LayerKey key = { layer, behavior };
    layers[key].push_back(drawable);
    if (behavior == RenderBehavior::STATIC) 
    {
        setLayerDirty(layer);
    }
}

void RenderManager::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Transparent);

    auto log = spdlog::get("main");

    for (const auto& layer : { 
        RenderLayer::BACKGROUND, 
        RenderLayer::MIDGROUND,
        RenderLayer::PROPS,
        RenderLayer::CHARACTER,
        RenderLayer::FOREGROUND, 
        RenderLayer::UI })
    {
        log->debug("Processing layer: {}", static_cast<int>(layer));

        for (const auto& behavior : { RenderBehavior::STATIC, RenderBehavior::DYNAMIC })
        {
            log->debug("Processing behavior: {}", static_cast<int>(behavior));
            LayerKey key = { layer, behavior };

            if (behavior == RenderBehavior::STATIC && staticTextures[layer].getSize() != window.getSize())
            {
                staticTextures[layer].create(window.getSize().x, window.getSize().y);
            }

            sf::Vector2f offset(48 * 5, 48 * 5);

            if (behavior == RenderBehavior::STATIC)
            {
                if (dirtyStaticLayers.find(layer) != dirtyStaticLayers.end())
                {
                    log->debug("Layer {} is marked as dirty.", static_cast<int>(layer));
                    auto& texture = staticTextures[layer];
                    texture.clear(sf::Color::Transparent);
                    
                    int index = 0;
                    for (auto& drawable : layers[key])
                    {
                        sf::FloatRect drawableBounds = sf::FloatRect(0, 0, 800, 600);

                        // Only draw the drawable if it is within the region of interest
                        if (drawableBounds.left + drawableBounds.width >= offset.x &&
                            drawableBounds.left <= offset.x + window.getSize().x &&
                            drawableBounds.top + drawableBounds.height >= offset.y &&
                            drawableBounds.top <= offset.y + window.getSize().y)
                        {
                            sf::Transform transform;
                            transform.translate(-offset);  // Translate by negative offset to draw in correct position on the texture
                            texture.draw(drawable, transform);
                        }
                    }
                    texture.display();
                    dirtyStaticLayers.erase(layer);
                }
                window.draw(sf::Sprite(staticTextures[layer].getTexture()));
            }
            else
            {
                for (auto& drawable : layers[key])
                {
                    log->debug("Drawing dynamic drawable...");
                    window.draw(drawable);
                }
            }
        }
    }

    log->debug("Ending draw process...");
    window.display();
}

void RenderManager::setLayerDirty(RenderLayer layer) 
{
    dirtyStaticLayers.insert(layer);
}

RenderLayer RenderManager::intToRenderLayer(int layer)
{
    return static_cast<RenderLayer>(layer);
}

void RenderManager::clear()
{
    layers.clear();
    staticTextures.clear();
}