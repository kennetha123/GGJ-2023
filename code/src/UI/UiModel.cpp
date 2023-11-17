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

		void SettingsMenuModel::setResolution(int x, int y)
		{
			resolution = sf::Vector2i(x, y);
		}

		void SettingsMenuModel::setResolution(sf::Vector2i size)
		{
			resolution = size;
		}

		sf::Vector2i SettingsMenuModel::getResolution() const
		{
			return resolution;
		}
	}
}