#pragma once

#include <SFML/Graphics.hpp>
#include "../system/observer.hpp"

namespace UI
{
    class Button : public sf::Drawable
    {
    public:
        Button(const sf::Font& font, const std::string& text, float x, float y);
        bool checkClick(const sf::Vector2f& mouse_position);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void setOnClickCb(std::function<void()> callback);

    private:
        sf::Text button_text;
        sf::RectangleShape button_image;
        sf::FloatRect global_bounds;
        std::function<void()> on_click_callback;
    };
}
