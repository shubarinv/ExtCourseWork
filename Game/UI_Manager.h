//
// Created by vhundef on 25.06.19.
//

#ifndef COURSEWORK_UI_MANAGER_H
#define COURSEWORK_UI_MANAGER_H


#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <fstream>
#include "GameObject.h"
#include "asteroid.h"

class UI_Manager {
private:
	TTF_Font *fnt;
	ScreenManager *screenManager = nullptr;
	SDL_Color text_color;
	SDL_Surface *text_surface = nullptr;
	int bgX[100];
	int bgY[100];

public:
	UI_Manager(ScreenManager *screenMgr) {
		screenManager = screenMgr;
		if (TTF_Init()) {
			throw runtime_error("UI_Manager: Failed to init SDL_TTF ");
		}
		fnt = TTF_OpenFont("Roboto-Regular.ttf", 20);
		if (!fnt) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
			// handle error
		}
		// ===== Generating background ==== //
		for (int i = 0; i < 100; i++) {
			bgX[i] = GameObject::randIntInRange(1, screenManager->getScreenWidth() - 1);
			bgY[i] = GameObject::randIntInRange(1, screenManager->getScreenHeight() - 1);
		}
	}

	/**
	 * @param x - Horizontal position of text (in pixels)
	 * @param y - Vertical position of text (in pixels)
	 * @param text - Text that you want to add to the screen
	 **/
	void drawText(int x, int y, const string &text, int textColor) {
		text_color.r = (textColor & 0x00ff0000) / 0x10000;
		text_color.g = (textColor & 0x0000ff00) / 0x100;
		text_color.b = textColor & 0x000000ff;
		// text_color.g=textColor%10-textColor%1000;
		//text_color.b=textColor%1000;
		text_surface = TTF_RenderUTF8_Solid(fnt, text.c_str(), text_color);

		SDL_Rect textBg;
		textBg.x = x;
		textBg.y = y;

		SDL_BlitSurface(text_surface, nullptr, screenManager->getMainSurface(), &textBg);
		SDL_FreeSurface(text_surface);
		text_surface = nullptr;

	}

	/**
	 * @param x - Horizontal position of text (in pixels)
	 * @param y - Vertical position of text (in pixels)
	 * @param width - width of a button
	 * @param height - height if a button
	 * @param text - Text that you want to add to the screen
	 * @param textColor - Color of the text that will be added to the button
	 **/
	void createButton(int x, int y, int width, int height, const string &text, int btnColor, int textColor) {
		screenManager->draw_Rect(x, y, width, height, btnColor);
		drawText((x + width / 2) - 10 * (text.length() / 2.0), (y + height / 2) - 12, text, textColor);
	}


	/**
	 * @brief Draws HUD(text like player money, level, etc)
	**/
	void drawHUD(int health, int money) {
		drawText(10, 10, "Health:" + to_string(health), 0xFFFFFF);
		drawText(screenManager->getScreenWidth() - 100, 10, "Score:" + to_string(money), 0xFFFFFF);
	}


	void drawBg() {
		for (int i = 0; i < 100; ++i) {
			Draw_Pixel(screenManager->getMainSurface(), bgX[i], bgY[i], 0xF5F5DC);
		}
	}

	int showMainMenu(EventManager *eventMgr, ScreenManager *screenMgr, UI_Manager *UI_Mgr) {
		SDL_Event event;
		screenMgr->clearScreen();

		int selectedOption{1};
		UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, ">  start  <", 0xffffff);
		UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
		                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.8), "quit", 0xffffff);


		screenMgr->updateScreen();

		list <Asteroid> astroids;
		for (int i = 0; i < 10; ++i) {
			astroids.emplace_back(screenMgr);
		}

		/* Polling events */
		while (true) {
			astroids.remove_if(Asteroid::removalCheck);
			if (astroids.size() < 10) {
				astroids.emplace_back(screenMgr);
			}
			event = eventMgr->getEvent();
			if (event.type == SDL_QUIT) {
				cout << "EventManager: got ESC button press. Quiting..." << endl;
				return -1;
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) {
				return selectedOption;
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN) {
				if (selectedOption == 2)selectedOption = 1;
				else
					selectedOption++;
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP) {
				if (selectedOption == 1)selectedOption = 3;
				else
					selectedOption--;
			}
			SDL_Delay(5);
			screenMgr->clearScreen();
			drawBg();
			UI_Mgr->showLeaderBoard();
			for (auto &asteroid : astroids) {
				asteroid.reDraw();
			}
			switch (selectedOption) {
				case 1:
					UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, ">  start  <",
					                 0xffffff);
					UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
					                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.5), "quit", 0xffffff);
					break;
				case 2:
					UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, "start", 0xffffff);
					UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
					                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.5), ">  quit  <",
					                 0xffffff);
					break;
			}
			screenMgr->updateScreen();

		}
	}

	int showGameOver(EventManager *eventMgr, ScreenManager *screenMgr, UI_Manager *UI_Mgr, int score) {
		SDL_Event event;
		screenMgr->clearScreen();
		UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, ">  Restart  <", 0xffffff);
		UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
		                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.8), "quit", 0xffffff);
		screenMgr->updateScreen();
		int selectedOption{1};
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
			drawBg();
			UI_Mgr->showLeaderBoard();
			UI_Mgr->drawText(screenMgr->getScreenWidth() / 2 - 50, screenMgr->getScreenHeight() - 50,
			                 "GAME OVER!\nScore:" + to_string(score),
			                 0xff0000);
			switch (selectedOption) {
				case 1:
					UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, ">  restart  <",
					                 0xffffff);
					UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
					                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.8), "quit", 0xffffff);
					break;
				case 2:
					UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, "restart",
					                 0xffffff);
					UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
					                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.8), ">  quit  <",
					                 0xffffff);
					break;
			}
			screenMgr->updateScreen();

		}
	}

	void showLeaderBoard() {
		std::ifstream infile("leaderBoard");
		string name;
		int score;
		int i = 4;
		//screenManager->clearScreen();
		createButton(screenManager->getScreenWidth() / 2, screenManager->getScreenHeight() / 12,
		             screenManager->getScreenWidth() / 4, screenManager->getScreenHeight() / 20 + 20,
		             "Player Name", 0x4d4d4d, 0xFFFFff);
		createButton(screenManager->getScreenWidth() / 2 + screenManager->getScreenWidth() / 4,
		             screenManager->getScreenHeight() / 12, screenManager->getScreenWidth() / 4,
		             screenManager->getScreenHeight() / 20 + 20, "Score", 0x4d4d4d, 0xFFFFff);
		while (infile >> name >> score) {
			createButton(screenManager->getScreenWidth() / 2, screenManager->getScreenHeight() / 20 + 20 * i,
			             screenManager->getScreenWidth() / 4, 20,
			             name, 0x4d4d4d, 0xFFFF00);
			createButton(screenManager->getScreenWidth() / 2 + screenManager->getScreenWidth() / 4,
			             screenManager->getScreenHeight() / 20 + 20 * i,
			             screenManager->getScreenWidth() / 4, 20, to_string(score), 0x4d4d4d, 0xFFFF00);
			Draw_HLine(screenManager->getMainSurface(), screenManager->getScreenWidth() / 2,
			           screenManager->getScreenHeight() / 20 + 20 * i + 19,
			           screenManager->getScreenWidth(), 0x0);
			Draw_VLine(screenManager->getMainSurface(),
			           screenManager->getScreenWidth() / 2 + screenManager->getScreenWidth() / 4,
			           screenManager->getScreenHeight() / 20 + 20 * i,
			           screenManager->getScreenHeight() / 20 + 20 * i + 18, 0xffffff);
			i++;
		}
		infile.close();
		screenManager->updateScreen();
	}
};


#endif //COURSEWORK_UI_MANAGER_H
