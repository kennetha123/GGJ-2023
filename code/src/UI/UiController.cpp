#include "UI/UiController.h"
#include "system/InputManager.h"

namespace UI
{
	namespace Controller
	{
		FpsController::FpsController(const sf::Font& font) : fps_view(font)
		{ 
		}

		FpsController::~FpsController()
		{
		}

		void FpsController::update(float dt)
		{
			fps_timer += dt;
			frame_count++;
			fps_view.update(fps_model);

			if (fps_timer >= 1.0f)
			{
				int fps = static_cast<int>(frame_count / fps_timer);
				fps_model.setFps(fps);
				frame_count = 0;
				fps_timer = 0;
			}
		}

		MainMenuController::MainMenuController(const sf::Font& font) :
			mm_view(font) 
		{
		}

		MainMenuController::~MainMenuController()
		{
		}

		void MainMenuController::update(float dt)
		{

		}

		void MainMenuController::onClick()
		{
			Button& new_game = *mm_view.new_game_button;
			Button& load_game = *mm_view.load_game_button;
			Button& settings = *mm_view.settings_button;
			Button& quit = *mm_view.quit_button;

			std::shared_ptr<StoreMapCommand> store_map_cmd = std::make_shared<StoreMapCommand>([&](const sf::Vector2f& mouse_position) {
				new_game.checkClick(mouse_position);
				load_game.checkClick(mouse_position);
				settings.checkClick(mouse_position);
				quit.checkClick(mouse_position);
				});

			ServiceLocator::getService<InputManager>().bindMouseToCmd(sf::Mouse::Left, store_map_cmd);
		}

		void DialogController::update(float dt)
		{
			dialog_view.update(dialog_model);
		}

		void DialogController::displayDialogBox()
		{
			auto& render = ServiceLocator::getService<RenderManager>();
			render.addDrawable(dialog_view.box, dialog_view.box, RenderLayer::UI, RenderBehavior::STATIC);
			render.addDrawable(dialog_view.display_text, dialog_view.display_text, RenderLayer::UI, RenderBehavior::DYNAMIC);
			sf::View& camera = ServiceLocator::getService<RenderManager>().getCamera();
			sf::Vector2f cam_pos = camera.getCenter() - 0.5f * camera.getSize();
			dialog_view.box.setPosition(cam_pos.x + 320, cam_pos.y + 500);
		}

		void DialogController::hideDialogBox()
		{
			auto& render = ServiceLocator::getService<RenderManager>();
			render.removeDrawable(dialog_view.box, dialog_view.box, RenderLayer::UI, RenderBehavior::STATIC);
			render.removeDrawable(dialog_view.display_text, dialog_view.display_text, RenderLayer::UI, RenderBehavior::DYNAMIC);
		}

		void DialogController::setText(const std::wstring& txt, const sf::Font& font)
		{
			dialog_view.setText(txt, font);
		}


	}
}