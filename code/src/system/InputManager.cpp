#include "system/InputManager.h"
#include <time.h>
#include <chrono>
void Command::execute(sf::RenderWindow& window)
{
    
}

StoreMapCommand::StoreMapCommand(Action action_)
{
    action = action_;
}

void StoreMapCommand::execute(sf::RenderWindow& window)
{
    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    action(mouse_position);
}

KeyboardCommand::KeyboardCommand(Action on_press, Action on_release)
{
    on_pressed = on_press;
    on_released = on_release;
}

void KeyboardCommand::execute(sf::RenderWindow& window)
{
    on_pressed();
}

InputManager::InputManager()
{
    log = spdlog::get("main");
}

void InputManager::handleEvents(sf::RenderWindow& window)
{
    sf::Event ev;

    while (window.pollEvent(ev))
    {
        if (ev.type == sf::Event::MouseButtonPressed)
        {
            auto it = mouseCmdMap.find(ev.mouseButton.button);
            if (it != mouseCmdMap.end())
            {
                it->second->execute(window);
            }
        }

        if (ev.type == sf::Event::Closed)
        {
            window.close();
        }
    }

    for (const auto& [key, cmd] : keyCmdMap)
    {
        if (sf::Keyboard::isKeyPressed(key))
        {
            cmd->execute(window);
        }
    }
}

void InputManager::bindKeyToCmd(sf::Keyboard::Key key, std::shared_ptr<Command> cmd)
{
    keyCmdMap[key] = cmd;
}

void InputManager::bindMouseToCmd(sf::Mouse::Button button, std::shared_ptr<Command> cmd)
{
    mouseCmdMap[button] = cmd;
}