#include "UI/UiManager.h"

namespace UI
{
    UiManager::UiManager() : ui_camera_(sf::FloatRect(0, 0, 800, 600))
    {
    }

    void UiManager::push(std::shared_ptr<Controller::BaseController> view)
    {
        stack_.push(view);
    }

    void UiManager::pop()
    {
        if (!stack_.empty())
        {
            stack_.pop();
        }
    }

    void UiManager::remove(const std::shared_ptr<Controller::BaseController>& target_view)
    {
        std::stack<std::shared_ptr<Controller::BaseController>> temp_stack;

        while (!stack_.empty())
        {
            auto top_view = stack_.top();
            stack_.pop();

            if (top_view != target_view)
            {
                temp_stack.push(top_view);
            }
        }

        while (!temp_stack.empty())
        {
            stack_.push(temp_stack.top());
            temp_stack.pop();
        }
    }

    int UiManager::size() const
    {
        return stack_.size();
    }

    void UiManager::update(float dt)
    {
        if (!stack_.empty())
        {
            stack_.top()->update(dt);
        }
    }

    void UiManager::static_draw(sf::RenderTexture& render_tex)
    {
        std::stack<std::shared_ptr<Controller::BaseController>> temp_stack = stack_;

        while (!temp_stack.empty())
        {
            temp_stack.top()->static_draw(render_tex);
            temp_stack.pop();
        }
    }

    void UiManager::dynamic_draw(sf::RenderWindow& window)
    {
        window.setView(ui_camera_);

    }

    void UiManager::registerButton(Button& button)
    {
        buttons_registered_.push_back(&button);
    }

}
