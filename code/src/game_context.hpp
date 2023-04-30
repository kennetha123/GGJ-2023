#pragma once
#include <SFML/Graphics.hpp>

#include "ui/ui_manager.hpp"
#include "audio/audio_manager.hpp"
#include "system/input_handler.hpp"
#include "system/game_event_handler.hpp"

class scene_manager;

class game_context
{
public:
	game_context(ui::ui_manager & ui_mgr, scene_manager& scene_mgr, audio_manager& audio_mgr, input_handler& input_hndl, event_handler& event_hndl) :
		ui_manager_(ui_mgr),
		scene_manager_(scene_mgr),
		audio_manager_(audio_mgr),
		input_handler_(input_hndl),
		event_handler_(event_hndl)
	{

	}

	ui::ui_manager& ui_manager_;
	scene_manager& scene_manager_;
	audio_manager& audio_manager_;
	input_handler& input_handler_;
	event_handler& event_handler_;
};