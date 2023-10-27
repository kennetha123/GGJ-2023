#include "UI/UiManager.h"

namespace UI
{
    UiManager::UiManager()
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

    void UiManager::registerButton(Button& button)
    {
        buttons_registered_.push_back(&button);
    }

}
