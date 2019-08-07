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
			cout << "Not Yet Inplemented" << endl;
			return -1;
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
				cout << "Not Yet Inplemented" << endl;
				return -1;
			case 3:
				return 0;
			default:
				return -2;
		}
	}
}