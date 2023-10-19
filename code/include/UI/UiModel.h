#pragma once

namespace UI
{
	namespace Model
	{
		class Model
		{
		public:
			virtual ~Model() = default;
		};

		class FpsModel : public Model
		{
		public:
			void setFps(float fps);
			float getFps() const;

		private:
			float fps = 0;
		};

		class MainMenuModel : public Model
		{
		};
	}

}