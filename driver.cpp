//
// Created by vhundef on 25.06.19.
//

#include "Game/ScreenManager.h"
#include "Game/UI_Manager.h"
#include "Game/EventManager.h"
#include "Game/Player.h"
#include "Game/GameManager.h"
#include "Game/asteroid.h"


/**
 * @brief Draws background(sky, water)
 **/
int bgX[50];
int bgY[50];

void drawBg(ScreenManager *screenMgr) {
	for (int i = 0; i < 50; ++i) {
		Draw_Pixel(screenMgr->getMainSurface(), bgX[i], bgY[i], 0xF5F5DC);
	}
}

[[deprecated]]int showMainMenu(EventManager *eventMgr, ScreenManager *screenMgr, UI_Manager *UI_Mgr) {
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

	Asteroid asteroid1(screenMgr);
	Asteroid asteroid2(screenMgr);
	Asteroid asteroid3(screenMgr);
	Asteroid asteroid4(screenMgr);
	Asteroid asteroid5(screenMgr);
	Asteroid asteroid6(screenMgr);
	Asteroid asteroid7(screenMgr);
	Asteroid asteroid8(screenMgr);
	Asteroid asteroid9(screenMgr);
	Asteroid asteroid10(screenMgr);

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
		SDL_Delay(10);
		screenMgr->draw_Rect(0, 0, screenMgr->getScreenWidth(), screenMgr->getScreenHeight(), 0x0);
		drawBg(screenMgr);
		asteroid1.reDraw();
		asteroid2.reDraw();
		asteroid3.reDraw();
		asteroid4.reDraw();
		asteroid5.reDraw();
		asteroid6.reDraw();
		asteroid7.reDraw();
		asteroid8.reDraw();
		asteroid9.reDraw();
		asteroid10.reDraw();
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

	// ===== Generating background ==== //
	for (int i = 0; i < 50; i++) {
		bgX[i] = GameObject::randIntInRange(1, screenManager.getScreenWidth() - 1);
		bgY[i] = GameObject::randIntInRange(1, screenManager.getScreenHeight() - 1);
	}

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
				player.setMovementDirection(-1);

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
				player.setMovementDirection(1);

			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN)
				player.setMovementSpeed(0);

			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP)
				player.setMovementSpeed(1);
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
				//     player.shoot();
				true;
		}
		player.reDraw();

		screenManager.updateScreen();
		gmManager.checkForNewWave();
		gmManager.capFPS();
	}
	return 0;
}