#pragma once
#include <iostream>
#include <vector>
#include <memory>

class game_context;

class scene
{
public:
    scene(game_context& game_ctx) : context(game_ctx) {}

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

protected:
    game_context& context;
};

class scene_manager
{
public:
    static scene_manager& instance()
    {
        static scene_manager instance;
        return instance;
    }

private:
    scene_manager() {}

    scene_manager(const scene_manager&) = delete;
    void operator=(const scene_manager&) = delete;

public:
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

    void push_scene(std::shared_ptr<scene> new_scene)
    {
        if (!scenes_.empty())
        {
            std::cout << "scene overlaped! is this intended?" << std::endl;
        }

        scenes_.push_back(new_scene);
    }

    void pop_scene()
    {
        if (!scenes_.empty())
        {
            scenes_.back().reset();
            scenes_.pop_back();
        }
    }

    void load_scene(std::shared_ptr<scene> new_scene)
    {
        pop_scene();
        push_scene(new_scene);
    }

    std::shared_ptr<scene> current_scene() const
    {
        if (!scenes_.empty())
        {
            return scenes_.back();
        }
        else
        {
            return nullptr;
        }
    }

private:
    std::vector<std::shared_ptr<scene>> scenes_;
};
