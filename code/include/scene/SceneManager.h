#pragma once

#include "render/Renderer.h"
#include <iostream>
#include <vector>
#include <memory>

class Scene : public Renderer
{
public:
    Scene() {}

    virtual void update(float dt) = 0;
    virtual void static_draw(sf::RenderTexture& render_tex) override {};
    virtual void dynamic_draw(sf::RenderWindow& window) override {};
};

class SceneManager : public Renderer
{
public:
    SceneManager() {}

public:
    void update(float dt);
    void static_draw(sf::RenderTexture& render_tex) override;
    void dynamic_draw(sf::RenderWindow& window) override;
    void pushScene(std::shared_ptr<Scene> new_scene);
    void popScene();
    void loadScene(std::shared_ptr<Scene> new_scene);
    std::shared_ptr<Scene> currentScene() const;

private:
    std::vector<std::shared_ptr<Scene>> scenes;
};
