//
// Created by vhundef on 16.09.2019.
//

#ifndef TANKSCOURSEWORKRD_UI_MANAGER_HPP
#define TANKSCOURSEWORKRD_UI_MANAGER_HPP

#include "ui_main_menu.hpp"
#include "ui_rules.hpp"
#include "ui_pause_menu.hpp"
#include "ui_hud.hpp"
#include "ui_game_over.hpp"
#include "ui_leader_board.hpp"

class UIManager {
private:
	ScreenManager *screenManager;
	MapManager *mapManager;
	Tank *player;
public:
	char whatToShow = '-';
	char prevWhatToShow = '-';

	UIManager(ScreenManager *screenMgr, MapManager *mapMgr, Tank *tank) {
		screenManager = screenMgr;
		mapManager = mapMgr;
		player = tank;
	}

	/// @brief prints selected UIWidget to screen @param UIWidget m - mainMenu;
	/// r - rules; o - gameOver; h - HUD
	void show(char UIWidget, int param = {-1}) {
		whatToShow = UIWidget;
		while (true) {
			if (whatToShow == 'm') {
				UIMainMenu mainMenu(screenManager, mapManager);
				mainMenu.show();
				if (mainMenu.selectedOption == 2) {
					whatToShow = 'l';
					prevWhatToShow = 'm';
				}
				if (mainMenu.selectedOption == 3) {
					whatToShow = 'r';
					prevWhatToShow = 'm';
				} else if (mainMenu.selectedOption == 1) {
					break;
				} else if (mainMenu.selectedOption == 4) {
					whatToShow = 'q';
					break;
				}
			} else if (whatToShow == 'r') {
				UIRules rules(screenManager);
				rules.show();
				whatToShow = prevWhatToShow;
			} else if (whatToShow == 'p') {
				UIPauseMenu pauseMenu(screenManager);
				pauseMenu.show();
				if (pauseMenu.selectedOption == 2) {
					whatToShow = 'r';
					prevWhatToShow = 'p';
				} else if (pauseMenu.selectedOption == 1) {
					break;
				} else if (pauseMenu.selectedOption == 3) {
					whatToShow = 'q';
					break;
				}
			} else if (whatToShow == 'h') {
				UIHUD hud(screenManager, player);
				hud.show(param);
				break;
			} else if (whatToShow == 'g') {
				ui_game_over gameOver(screenManager, param);
				gameOver.show();
				whatToShow = '-';
				break;
			} else if (whatToShow == 'l') {
				UILeaderBoard leaderBoard(screenManager);
				leaderBoard.show();
				whatToShow = prevWhatToShow;
			} else {
				cout << "WAIT A MINUTE!!!  ADon't know that widget (" << whatToShow << ")" << endl;
				break;
			}
		}
	}
};

#endif // TANKSCOURSEWORKRD_UI_MANAGER_HPP
