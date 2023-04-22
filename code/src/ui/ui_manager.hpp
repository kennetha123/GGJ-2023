#pragma once
#include "ui_models.hpp"
#include <stack>

namespace ui
{
	class ui_manager
	{
    public:
        ui_manager() : ui_camera(sf::FloatRect(0, 0, 800, 600))
        {

        }

        void push(std::shared_ptr<controller::fps_controller> view)
        {
            stack_.push(view);
        }

        void pop()
        {
            if (!stack_.empty())
            {
                stack_.pop();
            }
        }

        void remove(const std::shared_ptr<controller::fps_controller>& target_view)
        {
            std::stack<std::shared_ptr<controller::fps_controller>> temp_stack;

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

        int size() const
        {
            return stack_.size();
        }

        void update(float dt)
        {
            if (!stack_.empty())
            {
                stack_.top()->update(dt);
            }
        }

        void draw(sf::RenderWindow& window)
        {
            window.setView(ui_camera);

            std::stack<std::shared_ptr<controller::fps_controller>> temp_stack = stack_;

            while (!temp_stack.empty())
            {
                temp_stack.top()->draw(window);
                temp_stack.pop();
            }
        }

	private:
        std::stack<std::shared_ptr<controller::fps_controller>> stack_;
        sf::View ui_camera;
	};
}