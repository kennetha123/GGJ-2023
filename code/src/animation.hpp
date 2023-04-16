#include "system/ecs/entity.hpp"

class animation
{
public:
	animation(std::shared_ptr<sprite_component> sprite_comp, const std::vector<std::vector<sf::IntRect>>& frames, float frame_time) :
		sprite_comp_(sprite_comp), frames_(frames), frame_time_(frame_time)
	{

	}

	void update(float delta_time, int row)
	{
		if (row >= frames_.size()) 
		{
			return;
		}

		elapsed_time += delta_time;

		if (elapsed_time >= frame_time_)
		{
			elapsed_time = 0;
			current_frame = (current_frame + 1) % frames_[row].size();
			sprite_comp_->set_texture_rect(frames_[row][current_frame]);
		}
	}

private:
	std::shared_ptr<sprite_component> sprite_comp_;
	std::vector<std::vector<sf::IntRect>> frames_;
	float frame_time_;
	float elapsed_time = 0;
	int current_frame = 0;
};