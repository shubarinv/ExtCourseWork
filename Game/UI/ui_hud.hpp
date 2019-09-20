//
// Created by vhundef on 20.09.2019.
//

#ifndef TANKSCOURSEWORKRD_UI_HUD_HPP
#define TANKSCOURSEWORKRD_UI_HUD_HPP


#include "ui_base.hpp"

using namespace std;

class UIHUD : private virtual UI_Base {
private:
	Tank *player{};
public:
	explicit UIHUD(ScreenManager *screenMgr, Tank *tnk_player) {
		screenManager = screenMgr;
		if (TTF_Init()) { // init of SDL_TFF lib
			throw runtime_error("UI_Manager: Failed to init SDL_TTF ");
		}

		fnt = TTF_OpenFont("Hack.ttf", fontSize); ///< setting font and font size

		if (!fnt) {
			printf("UI: %s\n", TTF_GetError());
		}
		player = tnk_player;
	}

	void show(int param) {
		drawText(5, 10, "HP: " + to_string(player->getHP()), 0xffffff);
		drawText(screenManager->getScreenWidth() - 130, 10, "Score: " + to_string(param), 0xffffff);
	}
};


#endif //TANKSCOURSEWORKRD_UI_HUD_HPP
