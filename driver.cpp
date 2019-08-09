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


	int tmp;
	// ===== Show mainMenu ===== //
	tmp = uiManager.showMainMenu(&eventManager, &screenManager, &uiManager);
	if (tmp == 2||tmp==-1) { // player pressed show leaderboard
		return 0;
	}

// ==== Game start/Restart Loop ==== //
	while (true) {
		tmp = gmManager.startGame(eventManager, uiManager, player);
		switch (tmp) { // prefoming actions depending on what player pressed after gameover screeen
			case 1: // player pressed restart
				break;
			case 2: // player pressed quit
				return 0;
			default:
				return -2;
		}
	}
}