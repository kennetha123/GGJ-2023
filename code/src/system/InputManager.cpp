#include "system/InputManager.h"
#include <time.h>
#include <chrono>
#include "utils/Logs.h"

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

void KeyboardCommand::executeRelease(sf::RenderWindow& window)
{
    on_released();
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

        if (isKeyReleased(key))
        {
            cmd->executeRelease(window);
        }
    }
}

void InputManager::bindKeyToCmd(sf::Keyboard::Key key, std::shared_ptr<Command> cmd)
{
    keyCmdMap[key] = cmd;
    keyStates[key] = false;
}

void InputManager::bindMouseToCmd(sf::Mouse::Button button, std::shared_ptr<Command> cmd)
{
    mouseCmdMap[button] = cmd;
}

bool InputManager::isKeyReleased(sf::Keyboard::Key key) 
{
    auto it = keyStates.find(key);
    if (it != keyStates.end()) 
    {
        bool wasPressed = it->second;
        bool isPressed = sf::Keyboard::isKeyPressed(key);
        it->second = isPressed;
        return wasPressed && !isPressed;
    }
    return false;
}