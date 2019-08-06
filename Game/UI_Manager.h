//
// Created by vhundef on 25.06.19.
//

#ifndef COURSEWORK_UI_MANAGER_H
#define COURSEWORK_UI_MANAGER_H


#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_draw.h>

class UI_Manager {
private:
    TTF_Font *fnt;
    ScreenManager *screenManager = nullptr;
    SDL_Color text_color;
    SDL_Surface *text_surface = nullptr;

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
        drawText((x + width / 2) - 10 * (text.length() / 2.0), y + height / 2 - 10, text, textColor);
    }


    /**
     * @brief Draws HUD(text like player money, level, etc)
    **/
    void drawHUD(int health, int money) {
        drawText(10, 10, "Health:" + to_string(health), 0x0);
        drawText(screenManager->getScreenWidth() - 100, 10, "Money:" + to_string(money), 0x0);
    }

};


#endif //COURSEWORK_UI_MANAGER_H
