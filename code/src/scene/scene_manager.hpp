#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

class scene
{
public:
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};

class scene_manager
{
public:
    scene_manager() {}

    void update(float dt)
    {
        if (!scenes_.empty())
        {
            scenes_.back()->update(dt);
        }
    }

    void draw(sf::RenderWindow& window)
    {
        if (!scenes_.empty())
        {
            scenes_.back()->draw(window);
        }
    }

    void push_scene(std::shared_ptr<scene> scene)
    {
        if (!scenes_.empty())
        {
            std::cout << "scene overlaped! is this intended?" << std::endl;
        }

        scenes_.push_back(scene);

    }

    void pop_scene()
    {
        if (!scenes_.empty())
        {
            scenes_.pop_back();
        }
    }

private:
    std::vector<std::shared_ptr<scene>> scenes_;
};
