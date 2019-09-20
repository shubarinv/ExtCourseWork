cmake_minimum_required(VERSION 3.14)
project(TanksCourseWorkRD)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})
find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_draw REQUIRED)
find_package(SDL_image REQUIRED)
# Workaround for the non-working REQUIRED flag
if (NOT SDL_FOUND)
    message(FATAL_ERROR "SDL not found!")
endif (NOT SDL_FOUND)

link_libraries(
        ${SDL_LIBRARY}
        ${SDLDRAW_LIBRARY}
        ${SDLTTF_LIBRARY}
        ${SDLIMAGE_LIBRARY}
        SDLmain # Sadly not included in SDL_LIBRARY variable
)
set(CMAKE_CXX_STANDARD 17)

add_executable(TanksCourseWorkRD Driver.cpp Game/Lib/cute_c2.h Game/Map.h Game/MapManager.h Game/Wall.h Game/EventManager.h Game/game_manager.hpp Game/ScreenManager.h Game/game_object.hpp Game/moveable_object.hpp Game/stationary_object.hpp Game/sprite.hpp Game/drawable_object.hpp Game/tank.hpp Game/bot_controller.hpp Game/weapon.hpp Game/UI/ui_base.hpp Game/UI/ui_manager.hpp Game/UI/ui_main_menu.hpp Game/UI/ui_rules.hpp)