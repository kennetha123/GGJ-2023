#pragma once
#include <iostream>
#include <vector>
#include <memory>

class Scene
{
public:
    Scene() {}

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};

class SceneManager
{
public:
    SceneManager() {}

public:
    void update(float dt)
    {
        if (!scenes.empty())
        {
            scenes.back()->update(dt);
        }
    }

    void draw(sf::RenderWindow& window)
    {
        if (!scenes.empty())
        {
            scenes.back()->draw(window);
        }
    }

    void push_scene(std::shared_ptr<Scene> new_scene)
    {
        if (!scenes.empty())
        {
            std::cout << "scene overlaped! is this intended?" << std::endl;
        }

        scenes.push_back(new_scene);
    }

    void pop_scene()
    {
        if (!scenes.empty())
        {
            scenes.back().reset();
            scenes.pop_back();
        }
    }

    void load_scene(std::shared_ptr<Scene> new_scene)
    {
        pop_scene();
        push_scene(new_scene);
    }

    std::shared_ptr<Scene> current_scene() const
    {
        if (!scenes.empty())
        {
            return scenes.back();
        }
        else
        {
            return nullptr;
        }
    }

private:
    std::vector<std::shared_ptr<Scene>> scenes;
};
