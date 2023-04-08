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
    class scene_manager() {}

    void update(float dt)
    {
        if (m_scenes.empty())
        {
            return;
        }

        m_scenes.back()->update(dt);
    }

    void render(sf::RenderWindow& window)
    {
        if (m_scenes.empty())
        {
            return;
        }

        m_scenes.back()->render(window);
    }

    void pushScene(scene* scene)
    {
        m_scenes.push_back(scene);
    }

    void popScene()
    {
        if (m_scenes.empty())
        {
            return;
        }

        m_scenes.pop_back();
    }

private:
    std::vector<scene*> m_scenes;
};