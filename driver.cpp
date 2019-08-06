//
// Created by vhundef on 25.06.19.
//

#include "Game/ScreenManager.h"
#include "Game/UI_Manager.h"
#include "Game/EventManager.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Game/GameManager.h"


/**
 * @brief Draws background(sky, water)
 **/
void drawBg(ScreenManager *screenMgr) {
    screenMgr->draw_Rect(0, 0, screenMgr->getScreenWidth(), 100, 0x87CEEB);
    screenMgr->draw_Rect(0, 100, screenMgr->getScreenWidth(), screenMgr->getScreenHeight(), 0x006994);
}

int showMainMenu(EventManager *eventMgr, ScreenManager *screenMgr, UI_Manager *UI_Mgr) {
    SDL_Event event;

    screenMgr->draw_Rect(0, 0, screenMgr->getScreenWidth(), screenMgr->getScreenHeight(),
                         0x0); ///< Filling screen with solid color
    /* Drawing Buttons on screen */
    UI_Mgr->createButton(screenMgr->getScreenWidth() / 2 - 120, 180, 250, 60, "Start new game", 0xb791d8, 0xf);
    UI_Mgr->createButton(screenMgr->getScreenWidth() / 2 - 120, 280, 250, 60, "Leader Board", 0xb791d8, 0xf);
    UI_Mgr->createButton(screenMgr->getScreenWidth() / 2 - 120, 380, 250, 60, "Quit", 0xb791d8, 0xf);
    screenMgr->updateScreen();

    /* Polling events */
    while (true) {
        event = eventMgr->getEvent();
        if (event.type == SDL_QUIT) {
            cout << "EventManager: got ESC button press. Quiting..." << endl;
            return -1;
        }

        if ((eventMgr->getMousePosX() > screenMgr->getScreenWidth() / 2 - 120) &&
            (eventMgr->getMousePosX() < screenMgr->getScreenWidth() / 2 + 130) && (eventMgr->getMousePosY() > 180) &&
            (eventMgr->getMousePosY() < 240) &&
            (event.type == SDL_MOUSEBUTTONDOWN)) {
            break;
        }
        if ((eventMgr->getMousePosX() > screenMgr->getScreenWidth() / 2 - 120) &&
            (eventMgr->getMousePosX() < screenMgr->getScreenWidth() / 2 + 130) && (eventMgr->getMousePosY() > 280) &&
            (eventMgr->getMousePosY() < 340) &&
            (event.type == SDL_MOUSEBUTTONDOWN)) {
            throw runtime_error("NOT YET IMPLEMENTED");
        }
        if ((eventMgr->getMousePosX() > screenMgr->getScreenWidth() / 2 - 120) &&
            (eventMgr->getMousePosX() < screenMgr->getScreenWidth() / 2 + 130) && (eventMgr->getMousePosY() > 380) &&
            (eventMgr->getMousePosY() < 440) &&
            (event.type == SDL_MOUSEBUTTONDOWN)) {
            cout << "MainMenu: Quit button pressed. Quiting..." << endl;
            return -1;
        }
    }
    return 0;
}

int main() {
    // ===== GameManagers initialisation ==== //
    ScreenManager screenManager; ///< This thing is required to draw on screen
    UI_Manager uiManager(&screenManager); ///< This one is required to draw UI
    EventManager eventManager; ///< Checks for events
    SDL_Event event; ///< Holds last event
    Player player(&screenManager); ///< Player obj
    GameManager gmManager(&screenManager); ///< Implements gamelogic

    // ===== Show mainMenu ===== //
    if (showMainMenu(&eventManager, &screenManager, &uiManager) == -1) return 0;

    // ===== Setting GMmanager initial values
    gmManager.setWave(1);
    gmManager.setFramerate(300);

    // ===== Game itself ====== //
    while (true) {
        gmManager.capFPS();
        drawBg(&screenManager);
        uiManager.drawHUD(player.getHealth(), player.getMoney());

        event = eventManager.getEvent();
        {
            if (event.type == SDL_QUIT) {
                cout << "EventManager: got ESC button press. Quiting..." << endl;
                break;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
                //   player.setMovementDirection(-1);
                true;

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
                //    player.setMovementDirection(1);
                true;

            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN)
                //     player.setMovementSpeed(0);
                true;

            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP)
                //     player.setMovementSpeed(1);
                true;
            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
                //     player.shoot();
                true;
        }
        //   player.reDraw();

        screenManager.updateScreen();
        gmManager.checkForNewWave();
        gmManager.capFPS();
    }
    return 0;
}