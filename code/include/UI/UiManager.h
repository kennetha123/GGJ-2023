#pragma once
#include "UiController.h"
#include <stack>
#include "render/Renderer.h"
namespace UI
{
    class UiManager
    {
    public:
        UiManager();
        void push(std::shared_ptr<Controller::BaseController> view);
        void pop();
        void remove(const std::shared_ptr<Controller::BaseController>& target_view);
        int size() const;
        void update(float dt);
        void registerButton(Button& button);
        std::stack<std::shared_ptr<Controller::BaseController>> stack_;

    private:

        std::vector<Button*> buttons_registered_;
    };

}