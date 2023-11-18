set(GAME_CODE
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/Object.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ServiceLocator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/character/Player.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/character/Character.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/character/NPC.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/render/Renderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/scene/SceneManager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/scene/Overworld.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/scene/Battleworld.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/scene/MainMenu.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/UiManager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/UiModel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/UiView.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/UiController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/Button.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/UI/Dropdown.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/ecs/Components.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/InputManager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/GameEventManager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/Collision.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/Animator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/system/Settings.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/audio/AudioManager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/utils/Time.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/utils/Localization.cpp
	
	PARENT_SCOPE
)

message("write all file")