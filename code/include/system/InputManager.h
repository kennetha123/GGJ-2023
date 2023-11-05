#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "scene/SceneManager.h"
#include <spdlog/spdlog.h>
class Command
{
public:
    virtual ~Command() = default;

    virtual void execute(sf::RenderWindow& window);
};

class StoreMapCommand : public Command
{
    using Action = std::function<void(const sf::Vector2f& mouse_position)>;
public:
    StoreMapCommand(Action action_);
    void execute(sf::RenderWindow& window) override;

private:
    Action action;
};

class KeyboardCommand : public Command
{
    using Action = std::function<void()>;
public:
    KeyboardCommand(Action on_press, Action on_release = []() {});
    void execute(sf::RenderWindow& window) override;

private:
    Action on_pressed;
    Action on_released;

    std::shared_ptr<spdlog::logger> log;

};

class InputManager
{
public:
    InputManager();

    void handleEvents(sf::RenderWindow& window);
    void bindKeyToCmd(sf::Keyboard::Key key, std::shared_ptr<Command> cmd);
    void bindMouseToCmd(sf::Mouse::Button button, std::shared_ptr<Command> cmd);

private:
    std::map<sf::Keyboard::Key, std::shared_ptr<Command>> keyCmdMap;
    std::map<sf::Mouse::Button, std::shared_ptr<Command>> mouseCmdMap;

    std::shared_ptr<spdlog::logger> log;
};
