#pragma once

namespace dw
{
	class Time
	{
	public:
		static void setDeltaTime(float dt)
		{
			delta_time = dt;
		}

		static float getDeltaTime()
		{
			return delta_time;
		}

	private:
		static float delta_time;
	};
}

