//
// Created by vhundef on 25.06.19.
//

#include <list>
#include "Game/ScreenManager.h"
#include "Game/EventManager.h"
#include "Game/asteroid.h"
#include "Game/UI_Manager.h"
#include "Game/Player.h"
#include "Game/GameManager.h"


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

int showMainMenu(EventManager *eventMgr, ScreenManager *screenMgr, UI_Manager *UI_Mgr) {
	SDL_Event event;
	screenMgr->clearScreen();

	int selectedOption{1};
	UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, ">  start", 0xffffff);
	UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
	                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.4), "leaderBoard", 0xffffff);
	UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
	                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.8), "quit", 0xffffff);


	screenMgr->updateScreen();

	list<Asteroid> astroids;
	for (int i = 0; i < 10; ++i) {
		astroids.emplace_back(screenMgr);
	}

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
		SDL_Delay(5);
		screenMgr->clearScreen();
		drawBg(screenMgr);
		for (auto &asteroid : astroids) {
			asteroid.reDraw();
		}
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
	list<Asteroid> astroids;
	astroids.emplace_back(&screenManager);
	// ===== Game itself ====== //
	while (true) {
		gmManager.capFPS();

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
				player.shoot();
		}
		screenManager.clearScreen();

		/* ==== Redrawing game objects ====*/
		drawBg(&screenManager);
		uiManager.drawHUD(player.getHealth(), player.getMoney());
		player.reDraw();
		astroids.remove_if(Asteroid::removalCheck);
		/* ==== Check for collisions ====*/
		for (auto &asteroid : astroids) {
			asteroid.reDraw();
			player.weapon.particles.remove_if(Particle::removalCheck);
			for (auto &particle : player.weapon.particles) {
				asteroid.checkForOverlap(&particle);
			}
			if (asteroid.shouldBreak) {
				cout << "Asteroid Breaking" << endl;
				astroids.emplace_back(&screenManager, asteroid.getX(), asteroid.getY(), asteroid.getMovementByX(),
				                      asteroid.getMovementByY() - 1, asteroid.getSize());
				astroids.emplace_back(&screenManager, asteroid.getX(), asteroid.getY(), asteroid.getMovementByX(),
				                      asteroid.getMovementByY() - 1, asteroid.getSize());
				asteroid.setIsOnScreen(false);
			}
		}

		screenManager.updateScreen();

		gmManager.checkForNewWave();
		gmManager.capFPS();
	}
	return 0;
}