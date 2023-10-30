#include "scene/SceneManager.h"

void SceneManager::update(float dt)
{
    if (!scenes.empty())
    {
        scenes.back()->update(dt);
    }
}

void SceneManager::pushScene(std::shared_ptr<Scene> new_scene)
{
    if (!scenes.empty())
    {
        std::cout << "scene overlaped! is this intended?" << std::endl;
    }

    scenes.push_back(new_scene);
}

void SceneManager::popScene()
{
    if (!scenes.empty())
    {
        scenes.back().reset();
        scenes.pop_back();
    }
}

void SceneManager::loadScene(std::shared_ptr<Scene> new_scene)
{
    popScene();
    pushScene(new_scene);
}

std::shared_ptr<Scene> SceneManager::currentScene() const
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