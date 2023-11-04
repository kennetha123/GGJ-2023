#include "system/InputManager.h"

void Command::execute(sf::Event& ev, sf::RenderWindow& window)
{
    
}

StoreMapCommand::StoreMapCommand(Action action_)
{
    action = action_;
}

void StoreMapCommand::execute(sf::Event& ev, sf::RenderWindow& window)
{
    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    action(ev, mouse_position);
}

KeyboardCommand::KeyboardCommand(Action on_press, Action on_release)
{
    on_press = on_pressed;
    on_release = on_released;
}

void KeyboardCommand::execute(sf::Event& ev, sf::RenderWindow& window)
{
    if (ev.type == sf::Event::KeyPressed)
    {
        on_pressed();
    }

    if (ev.type == sf::Event::KeyReleased)
    {
        on_released();
    }
}

InputManager::InputManager()
{

}

void InputManager::handleEvents(sf::RenderWindow& window, sf::Event& ev)
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

void InputManager::bindKeyToCmd(sf::Keyboard::Key key, std::shared_ptr<Command> cmd)
{
    keyCmdMap[key] = cmd;
}

void InputManager::bindMouseToCmd(sf::Mouse::Button button, std::shared_ptr<Command> cmd)
{
    mouseCmdMap[button] = cmd;
}