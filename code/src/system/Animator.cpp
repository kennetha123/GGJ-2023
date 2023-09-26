#include "system/Animator.h"
#include "utils/Time.h"
#include <iostream>

void Animation::Play(const std::string& anim_name, sf::Sprite& sprite)
{
	elapsed_time += dw::Time::getDeltaTime();

	if (elapsed_time >= 1.0f / speed)
	{
		elapsed_time = 0;
		current_frame = (current_frame + 1) % frames.size();
		sprite.setTextureRect(frames[current_frame]);
	}
}

void Animation::setFrame(const std::vector<sf::IntRect>& frame)
{
	frames = frame;
}

void Animator::PlayAnimation(const std::string& anim_name, sf::Sprite& sprite)
{
	animations[anim_name].Play(anim_name, sprite);
}

