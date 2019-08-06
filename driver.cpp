//
// Created by vhundef on 25.06.19.
//

#include "Game/ScreenManager.h"
#include "Game/UI_Manager.h"
#include "Game/EventManager.h"
#include "Game/Player.h"
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

	int selectedOption{1};
	UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, ">  start", 0xffffff);
	UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
	                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.4), "leaderBoard", 0xffffff);
	UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
	                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.8), "quit", 0xffffff);


	screenMgr->updateScreen();

	/* Polling events */
	while (true) {
		event = eventMgr->getEvent();
		if (event.type == SDL_QUIT) {
			cout << "EventManager: got ESC button press. Quiting..." << endl;
			return -1;
		}
		if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) {
			return selectedOption;
		}
		if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN) {
			if (selectedOption == 3)selectedOption = 1;
			else
				selectedOption++;
		} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP) {
			if (selectedOption == 1)selectedOption = 3;
			else
				selectedOption--;
		}
		screenMgr->draw_Rect(0, 0, screenMgr->getScreenWidth(), screenMgr->getScreenHeight(), 0x0);
		switch (selectedOption) {
			case 1:
				UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, ">  start", 0xffffff);
				UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
				                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.4), "leaderBoard",
				                 0xffffff);
				UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
				                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.8), "quit", 0xffffff);
				break;
			case 2:
				UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, "start", 0xffffff);
				UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
				                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.4), ">  leaderBoard",
				                 0xffffff);
				UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
				                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.8), "quit", 0xffffff);
				break;
			case 3:
				UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, "start", 0xffffff);
				UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
				                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.4), "leaderBoard",
				                 0xffffff);
				UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
				                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.8), ">  quit", 0xffffff);
				break;
		}
		screenMgr->updateScreen();
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
	int tmp = showMainMenu(&eventManager, &screenManager, &uiManager);
	switch (tmp) {
		case 1:
			break;
		case 2:
			cout << "Not Yet Inplemented" << endl;
			return -1;
		case 3:
			return 0;
		default:
			return -2;
	}

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