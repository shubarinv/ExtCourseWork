//
// Created by vhundef on 16.09.2019.
//

#ifndef TANKSCOURSEWORKRD_UI_RULES_HPP
#define TANKSCOURSEWORKRD_UI_RULES_HPP

#include "ui_base.hpp"

class UIRules : private virtual UI_Base {
private:
	bool embeded{false};
	int offsetX{0};
public:
	UIRules(ScreenManager *screenMgr, bool embeded = false) {
		screenManager = screenMgr;
		if (TTF_Init()) { // init of SDL_TFF lib
			throw runtime_error("UI_Manager: Failed to init SDL_TTF ");
		}

		fnt = TTF_OpenFont("Hack.ttf", fontSize); ///< setting font and font size

		if (!fnt) {
			printf("UI: %s\n", TTF_GetError());
		}
		this->embeded = embeded;

		if (embeded) {
			offsetX = screenManager->getScreenWidth() / 2;
		}
	}

	void show() {
		if (!embeded) screenManager->clearScreen();
		createButton(
				offsetX, screenManager->getScreenHeight() / 6,
				screenManager->getScreenWidth(), 20,
				"Try to kill as many tanks as possible to get the highest score.", 0x00,
				0xffffff);
		createButton(offsetX, screenManager->getScreenHeight() / 6 + 22,
		             screenManager->getScreenWidth(), 20,
		             "If you hit enemy tank, you get 15 points.", 0x00, 0xffcc99);
		createButton(offsetX, screenManager->getScreenHeight() / 6 + 44,
		             screenManager->getScreenWidth(), 20,
		             "Player can take max of three hits.", 0x00, 0xffcc99);
		createButton(offsetX, screenManager->getScreenHeight() / 6 + 66,
		             screenManager->getScreenWidth(), 20,
		             "Use up, down, left, right arrows to move.", 0x00, 0xffff6f);
		createButton(offsetX, screenManager->getScreenHeight() / 6 + 88,
		             screenManager->getScreenWidth(), 20,
		             "Wall can be destroyed with two hits.", 0x00, 0xffffff);
		createButton(offsetX, screenManager->getScreenHeight() / 6 + 110,
		             screenManager->getScreenWidth(), 20,
		             "Bounding walls are indestructible.", 0x00, 0xff9999);
		createButton(
				offsetX, screenManager->getScreenHeight() / 6 + 132,
				screenManager->getScreenWidth(), 20,
				"Max of 3 tanks including player can be on screen at the same time.",
				0x00, 0xffffff);
		createButton(offsetX, screenManager->getScreenHeight() - 80,
		             screenManager->getScreenWidth(), 20,
		             "Press any button to return to main menu", 0x00, 0xccff99);
		createButton(offsetX, screenManager->getScreenHeight() - 40,
		             screenManager->getScreenWidth(), 20,
		             "Made by Vladimir Shubarin in 2019.", 0x00, 0x808080);
		screenManager->updateScreen();
		SDL_Event event;
		while (SDL_WaitEvent(&event)) {
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
				break;
			}
		}
	}
};

#endif // TANKSCOURSEWORKRD_UI_RULES_HPP