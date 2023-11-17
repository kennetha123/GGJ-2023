#pragma once

#include <SFML/Graphics.hpp>
#include "../system/observer.hpp"

namespace UI
{
    class Button : public sf::Drawable, public sf::Transformable
    {
    public:
        Button(const std::string& image_path, const sf::Font& font, const std::wstring& text, float x, float y);
        bool checkClick(const sf::Vector2f& mouse_position);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void setOnClickCb(std::function<void()> callback);
        sf::FloatRect getGlobalBounds() const;

    private:
        sf::Text button_text;
        sf::RectangleShape button_image;
        sf::FloatRect global_bounds;
        std::function<void()> on_click_callback;
        sf::Sprite sprite;
        sf::Texture texture;
    };
}
