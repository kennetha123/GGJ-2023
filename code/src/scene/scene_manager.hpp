#pragma once
#include <SFML/Graphics.hpp>

class scene
{
public:
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};

class scene_manager
{
public:
    scene_manager() {}

    void update(float dt)
    {
        if (scenes_.empty())
        {
            return;
        }

        scenes_.back()->update(dt);
    }

    void render(sf::RenderWindow& window)
    {
        if (scenes_.empty())
        {
            return;
        }

        scenes_.back()->render(window);
    }

    void pushScene(std::shared_ptr<scene> scene)
    {
        scenes_.push_back(scene);
    }

    void popScene()
    {
        if (scenes_.empty())
        {
            return;
        }

        scenes_.pop_back();
    }

private:
    std::vector<std::shared_ptr<scene>> scenes_;
};