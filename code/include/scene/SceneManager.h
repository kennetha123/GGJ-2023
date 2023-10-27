#pragma once

#include "render/Renderer.h"
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
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void pushScene(std::shared_ptr<Scene> new_scene);
    void popScene();
    void loadScene(std::shared_ptr<Scene> new_scene);
    std::shared_ptr<Scene> currentScene() const;

private:
    std::vector<std::shared_ptr<Scene>> scenes;
};
