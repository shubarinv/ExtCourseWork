//
// Created by vhundef on 16.09.2019.
//

#ifndef TANKSCOURSEWORKRD_UI_BASE_HPP
#define TANKSCOURSEWORKRD_UI_BASE_HPP

#include "ui_manager.hpp"
#include <SDL/SDL_video.h>
#include <SDL/SDL_ttf.h>
#include "../ScreenManager.h"


class UI_Base {
protected:
	TTF_Font *fnt{};
	ScreenManager *screenManager = nullptr;
	SDL_Color text_color{};
	SDL_Surface *text_surface = nullptr;
	int fontSize{20};

	void changeFontSize(int size) {
		fontSize = size;
		fnt = TTF_OpenFont("Hack.ttf", fontSize); ///< setting font and font size
		if (!fnt) {
			printf("UI: %s\n", TTF_GetError());
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
		drawText((x + width / 2) - fontSize / 2 * (text.length() / 2.0), (y + height / 2) - fontSize / 2 - 3, text,
		         textColor);
	}
};


#endif //TANKSCOURSEWORKRD_UI_BASE_HPP
