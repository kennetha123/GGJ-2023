#pragma once
#include "ui_models.hpp"
#include <stack>

namespace ui
{
    class ui_manager
    {
    public:
        static ui_manager& instance();

        void push(std::shared_ptr<controller::base_controller> view);
        void pop();
        void remove(const std::shared_ptr<controller::base_controller>& target_view);
        int size() const;
        void update(float dt);
        void draw(sf::RenderWindow& window);
        void on_button_click(const sf::Vector2f& mouse_position);
        void register_button(button& button);

    private:
        ui_manager();
        ui_manager(const ui_manager&) = delete;
        void operator=(const ui_manager&) = delete;

        std::vector<button*> buttons_registered_;
        std::stack<std::shared_ptr<controller::base_controller>> stack_;
        sf::View ui_camera_;
    };

}

namespace ui
{
    ui_manager& ui_manager::instance()
    {
        static ui_manager instance;
        return instance;
    }

    ui_manager::ui_manager() : ui_camera_(sf::FloatRect(0, 0, 800, 600))
    {
    }

    void ui_manager::push(std::shared_ptr<controller::base_controller> view)
    {
        stack_.push(view);
    }

    void ui_manager::pop()
    {
        if (!stack_.empty())
        {
            stack_.pop();
        }
    }

    void ui_manager::remove(const std::shared_ptr<controller::base_controller>& target_view)
    {
        std::stack<std::shared_ptr<controller::base_controller>> temp_stack;

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

    int ui_manager::size() const
    {
        return stack_.size();
    }

    void ui_manager::update(float dt)
    {
        if (!stack_.empty())
        {
            stack_.top()->update(dt);
        }
    }

    void ui_manager::draw(sf::RenderWindow& window)
    {
        window.setView(ui_camera_);

        std::stack<std::shared_ptr<controller::base_controller>> temp_stack = stack_;

        while (!temp_stack.empty())
        {
            temp_stack.top()->draw(window);
            temp_stack.pop();
        }
    }

    void ui_manager::on_button_click(const sf::Vector2f& mouse_position)
    {
        for (auto button : buttons_registered_)
        {
            button->checkClick(mouse_position);
        }
    }

    void ui_manager::register_button(button& button)
    {
        buttons_registered_.push_back(&button);
    }

}
