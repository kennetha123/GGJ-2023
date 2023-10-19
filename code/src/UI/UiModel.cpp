#include "UI/UiModel.h"

namespace UI
{
	namespace Model
	{
		void FpsModel::setFps(float fps)
		{
			this->fps = fps;
		}

		float FpsModel::getFps() const
		{
			return fps;
		}
	}
}