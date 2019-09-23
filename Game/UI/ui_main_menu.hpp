//
// Created by vhundef on 16.09.2019.
//

#ifndef TANKSCOURSEWORKRD_UI_MAIN_MENU_HPP
#define TANKSCOURSEWORKRD_UI_MAIN_MENU_HPP

#include "../MapManager.h"
#include "ui_base.hpp"
#include "ui_manager.hpp"
#include "../tank.hpp"
#include "../bot_controller.hpp"

class UIMainMenu : private virtual UI_Base {
private:
	MapManager *mapManager;

public:
	int selectedOption{1};

	UIMainMenu(ScreenManager *screenMgr, MapManager *mapMgr) {
		screenManager = screenMgr;
		if (TTF_Init()) { // init of SDL_TFF lib
			throw runtime_error("UI_Manager: Failed to init SDL_TTF ");
		}

		fnt = TTF_OpenFont("Hack.ttf", fontSize); ///< setting font and font size

		if (!fnt) {
			printf("UI: %s\n", TTF_GetError());
		}
		mapManager = mapMgr;
		mapManager->setCurrentMap(1);
	}

	void show() {

		drawText((int) (0.5 * screenManager->screenUnit),
		         3 * screenManager->screenUnit, ">  start  <", 0xffffff);

		drawText((int) (0.5 * screenManager->screenUnit * 3 - 5),
		         (int) (3 * screenManager->screenUnit +
		                screenManager->screenUnit * 0.4),
		         "leaderboard", 0xffffff);
		drawText(
				(int) (0.5 * screenManager->screenUnit * 3 - 5),
				(int) (3 * screenManager->screenUnit + screenManager->screenUnit * 0.8),
				"rules", 0xffffff);

		drawText((int) (0.5 * screenManager->screenUnit),
		         (int) (3 * screenManager->screenUnit + screenManager->screenUnit * 1.2),
		         "quit", 0xffffff);

		screenManager->updateScreen();

		/* Polling events */
		while (!chooseOption()) {
			/* Redrawing menu */
			SDL_Delay(3);
			screenManager->clearScreen();

			mapManager->getCurrentMap()->redraw();

			changeFontSize(40);
			createButton(0, 0, screenManager->getScreenWidth(), 50, "TANKS", 0x0,
			             0xffffff);
			changeFontSize(20);

			updateMenu();
			screenManager->updateScreen();
		}
	}

private:
	bool chooseOption() {
		/* Handling input */
		SDL_Event event;

		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			cout << "EventManager: got ESC button press. Quiting..." << endl;
			selectedOption = -1;
			return true;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
			return true;
		}
		if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN) {
			if (selectedOption == 4)
				selectedOption = 1;
			else
				selectedOption++;
		} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP) {
			if (selectedOption == 1)
				selectedOption = 4;
			else
				selectedOption--;
		}
		return false;
	}

	void updateMenu() {
		switch (selectedOption) {
			case 1:

				drawText((int) (0.5 * screenManager->screenUnit * 2 - 10),
				         3 * screenManager->screenUnit, ">  Start  <", 0xffffff);


				drawText((int) (0.5 * screenManager->screenUnit * 3 - 5),
				         (int) (3 * screenManager->screenUnit +
				                screenManager->screenUnit * 0.4),
				         "leaderboard", 0xffffff);

				drawText((int) (0.5 * screenManager->screenUnit * 3 - 5),
				         (int) (3 * screenManager->screenUnit +
				                screenManager->screenUnit * 0.8),
				         "rules", 0xffffff);

				drawText((int) (0.5 * screenManager->screenUnit * 3 - 5),
				         (int) (3 * screenManager->screenUnit +
				                screenManager->screenUnit * 1.2),
				         "quit", 0xffffff);
				break;
			case 2:

				drawText((int) (0.5 * screenManager->screenUnit * 3 - 9),
				         3 * screenManager->screenUnit, "start", 0xffffff);

				drawText((int) (0.5 * screenManager->screenUnit * 2 - 6),
				         (int) (3 * screenManager->screenUnit +
				                screenManager->screenUnit * 0.4),
				         ">  Leaderboard  <", 0xffffff);

				drawText((int) (0.5 * screenManager->screenUnit * 3 - 5),
				         (int) (3 * screenManager->screenUnit +
				                screenManager->screenUnit * 0.8),
				         "rules", 0xffffff);

				drawText((int) (0.5 * screenManager->screenUnit * 3 - 5),
				         (int) (3 * screenManager->screenUnit +
				                screenManager->screenUnit * 1.2),
				         "quit", 0xffffff);
				break;
			case 3:

				drawText((int) (0.5 * screenManager->screenUnit * 3 - 9),
				         3 * screenManager->screenUnit, "start", 0xffffff);

				drawText((int) (0.5 * screenManager->screenUnit * 3 - 5),
				         (int) (3 * screenManager->screenUnit +
				                screenManager->screenUnit * 0.4),
				         "leaderboard", 0xffffff);

				drawText((int) (0.5 * screenManager->screenUnit * 2 - 6),
				         (int) (3 * screenManager->screenUnit +
				                screenManager->screenUnit * 0.8),
				         ">  Rules  <", 0xffffff);

				drawText((int) (0.5 * screenManager->screenUnit * 3 - 5),
				         (int) (3 * screenManager->screenUnit +
				                screenManager->screenUnit * 1.2),
				         "quit", 0xffffff);
				break;

			case 4:
				drawText((int) (0.5 * screenManager->screenUnit * 3 - 9),
				         3 * screenManager->screenUnit, "start", 0xffffff);

				drawText((int) (0.5 * screenManager->screenUnit * 3 - 5),
				         (int) (3 * screenManager->screenUnit +
				                screenManager->screenUnit * 0.4),
				         "leaderboard", 0xffffff);

				drawText((int) (0.5 * screenManager->screenUnit * 3 - 5),
				         (int) (3 * screenManager->screenUnit +
				                screenManager->screenUnit * 0.8),
				         "rules", 0xffffff);

				drawText((int) (0.5 * screenManager->screenUnit * 2 - 6),
				         (int) (3 * screenManager->screenUnit +
				                screenManager->screenUnit * 1.2),
				         ">  Quit  <", 0xffffff);
				break;
			default:
				break;
		}
	}
};

#endif // TANKSCOURSEWORKRD_UI_MAIN_MENU_HPP
