//
// Created by vhundef on 25.06.19.
//

#include "Game/EventManager.h"
#include "Game/UI_Manager.h"
#include "Game/Tank.h"
#include "Game/GameManager.h"

int main() {
    // ===== GameManagers initialisation ==== //
    ScreenManager screenManager; ///< This thing is required to draw on screen
    UI_Manager uiManager(&screenManager); ///< This one is required to draw UI
    EventManager eventManager; ///< Checks for events
    SDL_Event event; ///< Holds last event
    MapManager mapManager(&screenManager);
    Tank player(&screenManager, &mapManager); ///< Player obj
    GameManager gmManager(&screenManager, &mapManager); ///< Implements gamelogic



    int tmp;
    // ===== Show mainMenu ===== //
    mapManager.setCurrentMap(1);

    tmp = uiManager.showMainMenu(&eventManager, &screenManager, &uiManager, &mapManager);
    if (tmp == 2 || tmp == -1) { // player pressed quit/ESC
        return 0;
    }

// ==== Game start/Restart Loop ==== //
    while (true) {
        tmp = gmManager.startGame(eventManager, uiManager, player);
        switch (tmp) { // performing actions depending on what player pressed after gameover screen
            case 1: // player pressed restart
                break;
            case 2: // player pressed quit
                return 0;
            default:
                return -2;
        }
    }
}
