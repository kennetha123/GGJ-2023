#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "scene/SceneManager.h"

class Command
{
public:
    virtual ~Command() = default;

    virtual void execute(sf::Event& ev, sf::RenderWindow& window);
};

class StoreMapCommand : public Command
{
    using Action = std::function<void(sf::Event&, const sf::Vector2f& mouse_position)>;
public:
    StoreMapCommand(Action action_);
    void execute(sf::Event& ev, sf::RenderWindow& window) override;

private:
    Action action;
};

class MoveRightCommand : public Command
{
public:
    MoveRightCommand() {}
};

class InputManager
{
public:
    InputManager();

    void handleEvents(sf::RenderWindow& window, sf::Event& ev);
    void bindKeyToCmd(sf::Keyboard::Key key, std::shared_ptr<Command> cmd);
    void bindMouseToCmd(sf::Mouse::Button button, std::shared_ptr<Command> cmd);

private:
    std::map<sf::Keyboard::Key, std::shared_ptr<Command>> keyCmdMap;
    std::map<sf::Mouse::Button, std::shared_ptr<Command>> mouseCmdMap;
};
