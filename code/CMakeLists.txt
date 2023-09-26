set(GAME_CODE
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/object.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/game_context.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/character/player.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/scene/scene_manager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/scene/overworld.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/scene/battleworld.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/scene/main_menu.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/ui_manager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/ui_models.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/button.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/ecs/components.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/observer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/input_handler.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/event_handler.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/game_event_handler.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/Collision.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/Animator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/audio/audio_manager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/utils/Time.cpp
	
	PARENT_SCOPE
)

message("write all file")