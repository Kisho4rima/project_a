cmake_minimum_required(VERSION 3.0)

project(project_a)

set(SOURCE_FILES Src/main.cpp Entites/Player.cpp Entites/Player.h Src/Game.cpp Header/Game.h States/State.cpp States/State.h States/GameState.cpp States/GameState.h Entites/Entity.cpp Entites/Entity.h States/MainMenuState.cpp States/MainMenuState.h "Resource Files/Button.cpp" "Resource Files/Button.h" Components/MovementComponent.cpp Components/MovementComponent.h Components/AnimationComponent.cpp Components/AnimationComponent.h)

# Find SFML
set(SFML_DIR "C:/libraries/SFML-2.5.1 GCC/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system audio network REQUIRED)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
