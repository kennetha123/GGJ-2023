#include "UI/Button.h"
#include <spdlog/spdlog.h>
namespace UI
{
    Button::Button(const std::string& image_path, const sf::Font& font, const std::wstring& text, float x, float y)
    {
        auto log = spdlog::get("main");

        if (!texture.loadFromFile(image_path))
        {
            log->error("Button texture failed to load!");
        }

        button_text.setFont(font);
        button_text.setString(text);
        button_text.setCharacterSize(30);
        button_text.setFillColor(sf::Color::White);

        sf::FloatRect text_bounds = button_text.getLocalBounds();
        button_text.setOrigin(text_bounds.width / 2.0f, text_bounds.height / 2.0f);
        button_text.setPosition(x, y);

        // Adjust position so that the rectangle is centered on the text
        button_image.setTexture(&texture);
  //      button_image.setSize(sf::Vector2f(text_bounds.width * 2.0f, text_bounds.height * 1.5f));
        button_image.setSize(sf::Vector2f(200.0f * 1.5f, 80.0f * 1.5f));
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
        states.transform *= getTransform();
        target.draw(button_image, states);
        target.draw(button_text, states);
    }

    void Button::setOnClickCb(std::function<void()> callback)
    {
        on_click_callback = callback;
    }

    sf::FloatRect Button::getGlobalBounds() const
    {
        return button_image.getGlobalBounds();
    }
}