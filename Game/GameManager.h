//
// Created by vhundef on 01.07.19.
//

#ifndef COURSEWORK_GAMEMANAGER_H
#define COURSEWORK_GAMEMANAGER_H


#include <fstream>
#include "SDL/SDL.h"

class GameManager {
private:

    int wave{0};
    ScreenManager *screenManager;
    int elapsed = 0, current = 0, timeSinceSecond = 0, frames = 0, next{}; //avgFPS - Avg fps per second
    int framerate = 59;
    SDL_Event event{}; ///< Holds last event

    void prestartInit() {
        // ===== Setting GMmanager initial values
        setWave(1);
        setFramerate(300);
    }

    static void writeScoreToFile(const string &playerName, int Score) {
        std::ofstream outfile;

        outfile.open("leaderBoard", std::ios_base::app);
        outfile << playerName << " " << Score << "\n";
        outfile.close();
    }


public:

    explicit GameManager(ScreenManager *screenMgr) {
        screenManager = screenMgr;
    }

    void setFramerate(int purposedFPS) {
        GameManager::framerate = purposedFPS;
    }

    void setWave(int wv) {
        cout << "Set wave was called...\nWave now " << wv << endl;
        wave = wv;
    }

    bool swtch = true;

    void capFPS() {
        if (swtch) {
            elapsed = SDL_GetTicks() - current;
            current += elapsed;
            timeSinceSecond += elapsed;
            frames++;
            if (timeSinceSecond >= 1000) {
                timeSinceSecond = 0;
                frames = 0;
            }
        } else {
            next = SDL_GetTicks();
            if (next - current < 1000.0 / framerate) {
                SDL_Delay(1000.f / (float) framerate - (float) (next - current));
            }
        }
        swtch = !swtch;
    }

    int startGame(EventManager eventManager, UI_Manager uiManager, Tank player) {
        prestartInit();
        SDL_Rect test;
        test.x = 100;
        test.y = 100;

        while (true) {
            capFPS();


            event = eventManager.getEvent();
            {
                if (event.type == SDL_QUIT) {
                    cout << "EventManager: got ESC button press. Quiting..." << endl;
                    break;
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
                    player.setMovementDirection(-1);
                    player.setMovementSpeed(1);
                } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
                    player.setMovementDirection(1);
                    player.setMovementSpeed(1);
                } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
                    player.setMovementDirection(2);
                    player.setMovementSpeed(1);
                } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) {
                    player.setMovementDirection(-2);
                    player.setMovementSpeed(1);
                }

                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
                    player.shoot();
                if (event.type == SDL_KEYUP) {
                    cout << "No event" << timeSinceSecond << endl;
                    player.setMovementSpeed(0);
                }
            }
            screenManager->clearScreen();
            screenManager->drawImage("../Game/Sprites/Tank_L.png", &test);
            /* ==== Redrawing game objects ====*/
            uiManager.drawBg();
            uiManager.drawHUD(player.getHealth(), player.getScore());
            player.reDraw();
            /* ==== Check for collisions ====*/

            screenManager->updateScreen();

            capFPS();


            if (player.getHealth() <= 0) {
                writeScoreToFile(uiManager.input(),
                                 player.getScore()); ///< Asks user to input PlayerName than writes it and player score to the leaderBoard file
                return uiManager.showGameOver(&eventManager, screenManager, player.getScore());
            }
        }
        return -0xf;
    }
};


#endif //COURSEWORK_GAMEMANAGER_H
