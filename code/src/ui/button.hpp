#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../system/observer.hpp"

class Button : public sf::Drawable, public Subject
{
public:
    Button(const sf::Font& font, const std::string& text, float x, float y)
    {
        button_text.setFont(font);
        button_text.setString(text);
        button_text.setCharacterSize(30);
        button_text.setFillColor(sf::Color::White);

        sf::FloatRect text_bounds = button_text.getLocalBounds();
        button_text.setOrigin(text_bounds.width / 2.0f, text_bounds.height / 2.0f);
        button_text.setPosition(x, y);

        // Adjust position so that the rectangle is centered on the text
        rectangleImage.setFillColor(sf::Color::Blue);
        rectangleImage.setSize(sf::Vector2f(text_bounds.width * 2.0f, text_bounds.height * 1.5f));
        rectangleImage.setOrigin(rectangleImage.getSize() / 2.0f);
        rectangleImage.setPosition(x, y);
        global_bounds = rectangleImage.getGlobalBounds();
    }

    bool checkClick(const sf::Vector2f& mouse_position)
    {
        if (global_bounds.contains(mouse_position))
        {
            notify();
            return true;
        }

        return false;
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(rectangleImage, states);
        target.draw(button_text, states);
    }

private:
    sf::Text button_text;
    sf::RectangleShape rectangleImage;
    sf::FloatRect global_bounds;
};
