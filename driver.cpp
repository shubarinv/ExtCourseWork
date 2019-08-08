//
// Created by vhundef on 25.06.19.
//

#include "Game/EventManager.h"
#include "Game/UI_Manager.h"
#include "Game/Player.h"
#include "Game/GameManager.h"


/**
 * @brief Draws background(sky, water)
 **/


int main() {
	// ===== GameManagers initialisation ==== //
	ScreenManager screenManager; ///< This thing is required to draw on screen
	UI_Manager uiManager(&screenManager); ///< This one is required to draw UI
	EventManager eventManager; ///< Checks for events
	SDL_Event event; ///< Holds last event
	Player player(&screenManager); ///< Player obj
	GameManager gmManager(&screenManager); ///< Implements gamelogic



	// ===== Show mainMenu ===== //
	int tmp = uiManager.showMainMenu(&eventManager, &screenManager, &uiManager);
	switch (tmp) {
		case 1:
			break;
		case 2:
			uiManager.showLeaderBoard();
			while (true) {
				event = eventManager.getEvent();
				if (event.type == SDL_QUIT) {
					cout << "EventManager: got ESC button press. Quiting..." << endl;
					return -1;
				}
				if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) {
					break;
				}
			}
			break;
		case 3:
			return 0;
		default:
			return -2;
	}

	// ==== Game start/Restart Loop ==== //
	while (true) {
		tmp = gmManager.startGame(eventManager, uiManager, player);
		switch (tmp) {
			case 1:
				break;
			case 2:
				uiManager.showLeaderBoard();
				while (true) {
					event = eventManager.getEvent();
					if (event.type == SDL_QUIT) {
						cout << "EventManager: got ESC button press. Quiting..." << endl;
						return -1;
					}
					if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) {
						break;
					}
				}
				break;
			case 3:
				return 0;
			default:
				return -2;
		}
	}
}