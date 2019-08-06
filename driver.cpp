//
// Created by vhundef on 25.06.19.
//

#include "Game/ScreenManager.h"
#include "Game/UI_Manager.h"
#include "Game/EventManager.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Game/GameManager.h"

// ===== GameManagers initialisation ==== //
ScreenManager screenManager; ///< This thing is required to draw on screen
UI_Manager uiManager(&screenManager); ///< This one is required to draw UI
EventManager eventManager; ///< Checks for events
SDL_Event event; ///< Holds last event
Player player(&screenManager); ///< Player obj
list<Enemy> enemyShips; ///< Array that holds all enemy's
GameManager gmManager(&screenManager, &enemyShips); ///< Implements gamelogic

bool stopThreads = false;

/**
 * @brief Draws background(sky, water)
 **/
void drawBg(ScreenManager *screenMgr) {
    screenMgr->draw_Rect(0, 0, screenMgr->getScreenWidth(), 100, 0x87CEEB);
    screenMgr->draw_Rect(0, 100, screenMgr->getScreenWidth(), screenMgr->getScreenHeight(), 0x006994);
}

int showMainMenu(EventManager *eventMgr, ScreenManager *screenMgr, UI_Manager *UI_Mgr) {
    screenMgr->draw_Rect(0, 0, screenMgr->getScreenWidth(), screenMgr->getScreenHeight(), 0xffffff);
    UI_Mgr->createButton(screenMgr->getScreenWidth() / 2 - 120, 180, 250, 60, "Start new game", 0xb791d8, 0x0);
    UI_Mgr->createButton(screenMgr->getScreenWidth() / 2 - 120, 280, 250, 60, "Leader Board", 0xb791d8, 0x0);
    UI_Mgr->createButton(screenMgr->getScreenWidth() / 2 - 120, 380, 250, 60, "Quit", 0xb791d8, 0x0);
    screenMgr->updateScreen();
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
            stopThreads = true;
            return -1;
        }
    }
    return 0;
}

static bool removalCheck(Enemy enmy) {
    if (enmy.getHealth() < 0) enmy.shouldBeRemoved = true;
    return enmy.shouldBeRemoved && enmy.canBeRemoved;
}


int th_checkHitsPlayer(void *unused) {
    while (!stopThreads) {
        enemyShips.remove_if(removalCheck);
        for (auto &enemyShip : enemyShips) {
            player.weapon.particles.remove_if(Particle::removalCheck);
            for (auto &particle : player.weapon.particles) {
                gmManager.checkForHits(&enemyShip, &particle);
            }
        }
    }
    cout << "Thread (checkHitsPlayer) got stop command... Quiting" << endl;
    return 0;
}

int th_checkHitsEnemy(void *unused) {
    while (!stopThreads) {
        for (auto &enemyShip : enemyShips) {
            gmManager.enemyShoot(&player, &enemyShip);
            enemyShip.weapon.particles.remove_if(Particle::removalCheck);
            for (auto &particle : enemyShip.weapon.particles) {
                GameManager::checkForHits(&player, &particle);
            }
        }
    }
    cout << "Thread (checkHitsEnemy) got stop command... Quiting" << endl;
    return 0;
}

bool checkIfEnemyWasKilled(Enemy enemy) {
    return enemy.getHealth() <= 0;
}

int main() {

    gmManager.setWave(1);
    gmManager.setFramerate(300);
    SDL_Thread *checkHitsPlayer_Thread;
    checkHitsPlayer_Thread = SDL_CreateThread(th_checkHitsPlayer, nullptr);
    if (checkHitsPlayer_Thread == nullptr) {
        fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
        throw;
    }

    SDL_Thread *checkHitsEnemy_Thread;
    checkHitsEnemy_Thread = SDL_CreateThread(th_checkHitsEnemy, nullptr);
    if (checkHitsEnemy_Thread == nullptr) {
        fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
        throw;
    }

    // ===== Show mainMenu ===== //

    if (showMainMenu(&eventManager, &screenManager, &uiManager) == -1) return 0;

    // ===== Game itself ====== //
    while (true) {
        gmManager.capFPS();
        drawBg(&screenManager);
        uiManager.drawHUD(player.getHealth(), player.getMoney());
        enemyShips.remove_if(checkIfEnemyWasKilled);
        event = eventManager.getEvent();
        {
            if (event.type == SDL_QUIT) {
                cout << "EventManager: got ESC button press. Quiting..." << endl;
                stopThreads = true;
                SDL_WaitThread(checkHitsPlayer_Thread, nullptr);
                SDL_WaitThread(checkHitsEnemy_Thread, nullptr);
                break;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
                player.setMovementDirection(-1);

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
                player.setMovementDirection(1);

            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN)
                player.setMovementSpeed(0);

            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP)
                player.setMovementSpeed(1);
            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
                player.shoot();
        }
        player.reDraw();

        ///@brief reDraws all enemy ships
        for (auto &enemyShip : enemyShips) {
            enemyShip.reDraw();
        }
        screenManager.updateScreen();
        gmManager.checkForNewWave();
        gmManager.capFPS();
    }
    return 0;
}