#include "UI/Button.h"

namespace UI
{
    Button::Button(const sf::Font& font, const std::string& text, float x, float y)
    {
        button_text.setFont(font);
        button_text.setString(text);
        button_text.setCharacterSize(30);
        button_text.setFillColor(sf::Color::White);

        sf::FloatRect text_bounds = button_text.getLocalBounds();
        button_text.setOrigin(text_bounds.width / 2.0f, text_bounds.height / 2.0f);
        button_text.setPosition(x, y);

        // Adjust position so that the rectangle is centered on the text
        button_image.setFillColor(sf::Color::Blue);
        button_image.setSize(sf::Vector2f(text_bounds.width * 2.0f, text_bounds.height * 1.5f));
        button_image.setOrigin(button_image.getSize() / 2.0f);
        button_image.setPosition(x, y);
        global_bounds = button_image.getGlobalBounds();
    }

    bool Button::checkClick(const sf::Vector2f& mouse_position)
    {
        if (global_bounds.contains(mouse_position))
        {
            if (on_click_callback)
            {
                on_click_callback();
            }
            return true;
        }

        return false;
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(button_image, states);
        target.draw(button_text, states);
    }

    void Button::setOnClickCb(std::function<void()> callback)
    {
        on_click_callback = callback;
    }
}