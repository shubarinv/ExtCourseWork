//
// Created by vhundef on 25.06.19.
//

#ifndef COURSEWORK_UI_MANAGER_H
#define COURSEWORK_UI_MANAGER_H


#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <fstream>
#include <list>
#include "GameObject.h"
#include "ScreenManager.h"
#include "MapManager.h"
#include "Tank.h"
#include "BotController.h"

class UI_Manager {
private:
    TTF_Font *fnt;
    ScreenManager *screenManager = nullptr;
    SDL_Color text_color;
    SDL_Surface *text_surface = nullptr;


    struct LdbrdRecord {
        string name;
        int score;

        LdbrdRecord(string name_, int score_) {
            name = name_;
            score = score_;
        }

        bool operator<(const LdbrdRecord &other) {
            return score > other.score;
        }
    };

    list <LdbrdRecord> leaderBoardParsed;


public:
    UI_Manager(ScreenManager *screenMgr) {
        screenManager = screenMgr;
        if (TTF_Init()) { // init of SDL_TFF lib
            throw runtime_error("UI_Manager: Failed to init SDL_TTF ");
        }

        fnt = TTF_OpenFont("Hack.ttf", 20); ///< setting font and font size
        if (!fnt) {
            printf("UI_Manager: %s\n", TTF_GetError());
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
        drawText((x + width / 2) - 10 * (text.length() / 2.0), (y + height / 2) - 12, text, textColor);
    }


    /**
     * @brief Draws HUD(text like player money, level, etc)
    **/
    void drawHUD(int health, int money) {
        drawText(10, 10, "Health:" + to_string(health), 0xFFFFFF);
        drawText(screenManager->getScreenWidth() - 125, 10, "Score:" + to_string(money), 0xFFFFFF);
    }

    /**
     * @brief Draws mainMenu
     * @return (-1) if player pressed ESC, (1) if player pressed start, (2) if player pressed quit
    **/
    int showMainMenu(EventManager *eventMgr, ScreenManager *screenMgr, UI_Manager *UI_Mgr, MapManager *mapManager) {
        SDL_Event event;

        int selectedOption{1};
        UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, ">  start  <", 0xffffff);
        UI_Mgr->drawText((int) (0.5 * screenMgr->screenUnit),
                         (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.8), "quit", 0xffffff);

        mapManager->getCurrentMap()->reDraw();
        screenMgr->updateScreen();
        Tank tank1 = Tank(screenManager, mapManager);
        Tank tank2 = Tank(screenManager, mapManager);
        BotController botController1 = BotController(&tank1, screenManager);
        BotController botController2 = BotController(&tank2, screenManager);
        tank1.spawnAtRandomLocation();
        tank2.spawnAtRandomLocation();
        parseLeaderboard();

        /* Polling events */
        while (true) {

            /* Handling input */
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
            /* Redrawing menu/leaderboard */
            SDL_Delay(5);
            screenMgr->clearScreen();
            mapManager->getCurrentMap()->reDraw();
            botController1.moveTank();
            botController2.moveTank();
            botController1.controlledTank->reDraw();
            botController2.controlledTank->reDraw();
            UI_Mgr->showLeaderBoard();
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
                default:
                    break;
            }
            screenMgr->updateScreen();

        }
    }

/**
 * @brief reads file that's called leaderBoard, then adds data from this file to the list
 **/
    void parseLeaderboard() {
        leaderBoardParsed.clear();
        std::ifstream infile("leaderBoard");
        string name;
        int score;
        while (infile >> name >> score) {
            leaderBoardParsed.emplace_back(name, score);
        }
        infile.close();
        leaderBoardParsed.sort();
        if (leaderBoardParsed.empty()) {
            cout << "WARNING: LeaderBoard Empty either file is empty or error occurred" << endl;
        }
    }

/**
 * @brief shows gameOver and leaderboard screen
 **/
    int showGameOver(EventManager *eventMgr, ScreenManager *screenMgr, int score) {
        SDL_Event event;
        screenMgr->clearScreen();
        drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, ">  Restart  <", 0xffffff);
        drawText((int) (0.5 * screenMgr->screenUnit),
                 (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.8), "quit", 0xffffff);
        parseLeaderboard();
        screenMgr->updateScreen();
        int selectedOption{1};
        while (true) {
            /* Input handling */
            event = eventMgr->getEvent();
            if (event.type == SDL_QUIT) {
                cout << "EventManager: got ESC button press. Quiting..." << endl;
                return -1;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
                return selectedOption;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN) {
                if (selectedOption == 2)selectedOption = 1;
                else
                    selectedOption++;
            } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP) {
                if (selectedOption == 1)selectedOption = 2;
                else
                    selectedOption--;
            }
            /* UI redraw */
            SDL_Delay(5);
            screenMgr->clearScreen();
            showLeaderBoard();
            drawText(screenMgr->getScreenWidth() / 2 - 50, screenMgr->getScreenHeight() - 50,
                     "GAME OVER!\nScore:" + to_string(score),
                     0xff0000);
            switch (selectedOption) {
                case 1:
                    drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, ">  restart  <",
                             0xffffff);
                    drawText((int) (0.5 * screenMgr->screenUnit),
                             (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.8), "quit", 0xffffff);
                    break;
                case 2:
                    drawText((int) (0.5 * screenMgr->screenUnit), 3 * screenMgr->screenUnit, "restart",
                             0xffffff);
                    drawText((int) (0.5 * screenMgr->screenUnit),
                             (int) (3 * screenMgr->screenUnit + screenMgr->screenUnit * 0.8), ">  quit  <",
                             0xffffff);
                    break;
                default:
                    break;
            }
            screenMgr->updateScreen();

        }
    }

/**
 * @brief shows leaderBoard
 **/
    void showLeaderBoard() {
        int i = 4;
        createButton(screenManager->getScreenWidth() / 2, screenManager->getScreenHeight() / 12 - 10,
                     screenManager->getScreenWidth() / 4, screenManager->getScreenHeight() / 20 + 31,
                     "Player Name", 0x4d4d4d, 0xFFFFff);
        createButton(screenManager->getScreenWidth() / 2 + screenManager->getScreenWidth() / 4,
                     screenManager->getScreenHeight() / 12 - 10, screenManager->getScreenWidth() / 4,
                     screenManager->getScreenHeight() / 20 + 31, "Score", 0x4d4d4d, 0xFFFFff);
        for (auto &record : leaderBoardParsed) {
            createButton(screenManager->getScreenWidth() / 2, screenManager->getScreenHeight() / 20 + 20 * i,
                         screenManager->getScreenWidth() / 4, 20,
                         record.name, 0x4d4d4d, 0xFFFF00);
            createButton(screenManager->getScreenWidth() / 2 + screenManager->getScreenWidth() / 4,
                         screenManager->getScreenHeight() / 20 + 20 * i,
                         screenManager->getScreenWidth() / 4, 20, to_string(record.score), 0x4d4d4d, 0xFFFF00);
            Draw_HLine(screenManager->getMainSurface(), screenManager->getScreenWidth() / 2,
                       screenManager->getScreenHeight() / 20 + 20 * i + 19,
                       screenManager->getScreenWidth(), 0x0);
            Draw_VLine(screenManager->getMainSurface(),
                       screenManager->getScreenWidth() / 2 + screenManager->getScreenWidth() / 4,
                       screenManager->getScreenHeight() / 20 + 20 * i,
                       screenManager->getScreenHeight() / 20 + 20 * i + 18, 0xffffff);
            i++;
        }
    }

/**
 * @brief allows to enter some text
 **/
    string input() {
        SDL_Event event;
        string str;
        string tmp;
        screenManager->clearScreen();
        createButton(0, screenManager->getScreenHeight() / 6, screenManager->getScreenWidth(), 20,
                     "Please enter player name", 0x00, 0xffff00);

        createButton(0, screenManager->getScreenHeight() / 2, screenManager->getScreenWidth(), 20,
                     "Player Name: " + str, 0x3C3C3C, 0xffff00);

        createButton(0, screenManager->getScreenHeight() - screenManager->getScreenHeight() / 6,
                     screenManager->getScreenWidth(), 20,
                     "Press enter to continue", 0x00, 0xffff00);
        screenManager->updateScreen();

        while (SDL_WaitEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            } else if (event.key.keysym.sym == SDLK_BACKSPACE && event.type == SDL_KEYDOWN) {
                str = str.substr(0, str.size() - 1);
            } else if (event.key.keysym.sym == SDLK_RETURN) {
                return str;
            } else if (event.type == SDL_KEYDOWN) {
                str.append(EventManager::eventToStr(event.key.keysym.sym));
            }
            screenManager->clearScreen();
            createButton(0, screenManager->getScreenHeight() / 6, screenManager->getScreenWidth(), 20,
                         "Please enter player name", 0x00, 0xffff00);

            createButton(0, screenManager->getScreenHeight() / 2, screenManager->getScreenWidth(), 20,
                         "Player Name: " + str, 0x3C3C3C, 0xffff00);

            createButton(0, screenManager->getScreenHeight() - screenManager->getScreenHeight() / 6,
                         screenManager->getScreenWidth(), 20,
                         "Press enter to continue", 0x00, 0xffff00);
            screenManager->updateScreen();
        }
        return str;
    }


};


#endif //COURSEWORK_UI_MANAGER_H
