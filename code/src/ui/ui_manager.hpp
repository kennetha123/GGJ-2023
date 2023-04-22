#pragma once
#include "ui_models.hpp"

namespace ui
{
	class ui_manager
	{
	public:
		ui_manager(const sf::Font& font) : fps_view_(font)
		{
			fps_model_ = std::make_unique<fps_model>();
		}

		void update_fps(float dt)
		{
			fps_timer += dt;
			frame_count++;

			if (fps_timer >= 1.0f)
			{
				int fps = static_cast<int>(frame_count / fps_timer);
				fps_model_->set_fps(fps);
				fps_view_.update(100);
				frame_count = 0;
				fps_timer = 0;
			}

		}

		fps_view get_fps_view() { return fps_view_; }

	private:
		std::unique_ptr<fps_model> fps_model_;
		fps_view fps_view_;

		int frame_count = 0;
		float fps_timer = 0;
	};
}