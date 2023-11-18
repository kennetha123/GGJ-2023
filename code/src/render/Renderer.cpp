#include "render/Renderer.h"
#include "UI/Button.h"
#include "ServiceLocator.h"
#include "utils/Logs.h"

const std::array<RenderLayer, 6> RenderManager::all_layers = {
    RenderLayer::BACKGROUND,
    RenderLayer::MIDGROUND,
    RenderLayer::PROPS,
    RenderLayer::CHARACTER,
    RenderLayer::FOREGROUND,
    RenderLayer::UI
};

RenderManager::RenderManager()
{

}

void RenderManager::addDrawable(sf::Drawable& drawable, sf::Transformable& transformable, RenderLayer layer, RenderBehavior behavior)
{
    LayerKey key = { layer, behavior };
    layers[key].emplace_back(std::ref(drawable), std::ref(transformable));

    if (behavior == RenderBehavior::STATIC)
    {
        setLayerDirty(layer);
    }
}

void RenderManager::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Transparent);

    window.setView(main_camera);

    // Calculate the region of interest (ROI) based on the camera's position and size.
    sf::Vector2f center = main_camera.getCenter();
    sf::Vector2f size = main_camera.getSize();
    sf::FloatRect roi(center.x - size.x / 2, center.y - size.y / 2, size.x, size.y);

    // Debug ROI
    sf::RectangleShape roiRect(sf::Vector2f(roi.width, roi.height));
    roiRect.setPosition(roi.left, roi.top);
    roiRect.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red

    for (const auto& layer : all_layers)
    {
        Logs::instance().log("render", spdlog::level::debug, "Processing layer: {}", static_cast<int>(layer));

        for (const auto& behavior : { RenderBehavior::STATIC, RenderBehavior::DYNAMIC })
        {
            Logs::instance().log("render", spdlog::level::debug, "Processing behavior: {}", static_cast<int>(behavior));
            LayerKey key = { layer, behavior };

            if (behavior == RenderBehavior::STATIC)
            {
                if (dirtyStaticLayers.find(layer) != dirtyStaticLayers.end())
                {
                    Logs::instance().log("render", spdlog::level::debug, "Layer {} is marked as dirty.", static_cast<int>(layer));
                    auto& texture = staticTextures[layer];
                    texture.clear(sf::Color::Transparent);
                    
                    for (auto& data : layers[key])
                    {
                        sf::Drawable& drawable = data.first.get();
                        sf::Transformable& transformable = data.second.get();
                        sf::FloatRect bounds = getBounds(drawable, transformable);

                        if (roi.intersects(bounds))
                        {
                            texture.draw(drawable);
                        }
                    }
                    texture.display();
                    dirtyStaticLayers.erase(layer);
                }
                window.draw(sf::Sprite(staticTextures[layer].getTexture()));
            }
            else
            {
                for (auto& data : layers[key])
                {
                    sf::Drawable& drawable = data.first.get();
                    sf::Transformable& transformable = data.second.get();
                    sf::FloatRect bounds = getBounds(drawable, transformable);

                    if (layer == RenderLayer::UI)
                    {
                        sf::RectangleShape ruiRect(sf::Vector2f(bounds.width, bounds.height));
                        ruiRect.setPosition(bounds.left, bounds.top);
                        ruiRect.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red

                        window.draw(ruiRect);

                    }

                    if (roi.intersects(bounds))
                    {
                        window.draw(drawable);
                    }
                }
            }
        }
    }
    
    //window.draw(roiRect);
    Logs::instance().log("render", spdlog::level::debug, "Ending draw process...");
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

void RenderManager::setCamera(sf::View& view)
{
    main_camera = view;
}

sf::View& RenderManager::getCamera()
{
    return main_camera;
}

void RenderManager::clear()
{
    layers.clear();
    staticTextures.clear();
}

sf::FloatRect RenderManager::getBounds(const sf::Drawable& drawable, const sf::Transformable& transformable)
{    
    if (const auto* sprite = dynamic_cast<const sf::Sprite*>(&drawable))
    {
        return sprite->getGlobalBounds();
    }
    else if (const auto* shape = dynamic_cast<const sf::Shape*>(&drawable))
    {
        return shape->getGlobalBounds();
    }
    else if (const auto* text = dynamic_cast<const sf::Text*>(&drawable))
    {
        return text->getGlobalBounds();
    }
    else if (const auto* button = dynamic_cast<const UI::Button*>(&drawable))
    {
        return button->getGlobalBounds();
    }

    return {};
}

void RenderManager::initRenderer(const sf::Vector2i& size)
{
    for (const auto& layer : all_layers)
    {
        staticTextures[layer].create(size.x, size.y);
    }
}

void RenderManager::initRenderer(size_t x, size_t y)
{

    for (const auto& layer : all_layers)
    {
        staticTextures[layer].create(x, y);
    }
}