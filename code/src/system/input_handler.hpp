#pragma once

#include <SFML/Graphics.hpp>
#include "../scene/scene_manager.hpp"

class main_menu;

class Command
{
public:
    virtual ~Command() = default;

    virtual void execute(sf::Event& ev, sf::RenderWindow& window)
    {
        std::cout << "no implementation!" << std::endl;
    }
};

class StoreMapCommand : public Command
{
    using Action = std::function<void(sf::Event&, const sf::Vector2f& mouse_position)>;
public:
    StoreMapCommand(Action action)
    {
        action_ = action;
    }

    void execute(sf::Event& ev, sf::RenderWindow& window) override
    {
        sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        action_(ev, mouse_position);
    }

private:
    Action action_;
};

class MoveRightCommand : public Command
{
public:
    MoveRightCommand() {}
};

class input_handler
{
public:
    input_handler()
    {

    }


    void handle_events(sf::RenderWindow& window, sf::Event& ev)
    {
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::KeyPressed)
            {
                auto it = keyCmdMap.find(ev.key.code);
                if (it != keyCmdMap.end())
                {
                    it->second->execute(ev, window);
                }
            }

            if (ev.type == sf::Event::MouseButtonPressed)
            {
                auto it = mouseCmdMap.find(ev.mouseButton.button);
                if (it != mouseCmdMap.end())
                {
                    it->second->execute(ev, window);
                }
            }

            if (ev.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }

    void bindKeyToCmd(sf::Keyboard::Key key, std::shared_ptr<Command> cmd)
    {
        keyCmdMap[key] = cmd;
    }

    void bindMouseToCmd(sf::Mouse::Button button, std::shared_ptr<Command> cmd)
    {
        mouseCmdMap[button] = cmd;
    }

private:
    std::shared_ptr<Command> right_click_command;

    std::map<sf::Keyboard::Key, std::shared_ptr<Command>> keyCmdMap;
    std::map<sf::Mouse::Button, std::shared_ptr<Command>> mouseCmdMap;
};
