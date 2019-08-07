//
// Created by vhundef on 01.07.19.
//

#ifndef COURSEWORK_GAMEMANAGER_H
#define COURSEWORK_GAMEMANAGER_H


#include "asteroid.h"

class GameManager {
private:

	int wave{0};
	ScreenManager *screenManager;
	int elapsed = 0, current = 0, timeSinceSecond = 0, frames = 0, next{}, avgFPS = 100; //avgFPS - Avg fps per seconds
	int framerate = 59;
	SDL_Event event; ///< Holds last event
	list<Asteroid> asteroids;

	void prestartInit() {
		// ===== Setting GMmanager initial values
		setWave(1);
		setFramerate(300);
		asteroids.emplace_back(screenManager);
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
				avgFPS = frames;
				frames = 0;
			}
		} else {
			next = SDL_GetTicks();
			if (next - current < 1000.0 / framerate) {
				SDL_Delay(1000.f / framerate - (next - current));
			}
		}
		swtch = !swtch;
	}

	int startGame(EventManager eventManager, UI_Manager uiManager, Player player) {
		prestartInit();
		while (true) {
			if (asteroids.empty()) {
				asteroids.emplace_back(screenManager);
			}
			capFPS();

			event = eventManager.getEvent();
			{
				if (event.type == SDL_QUIT) {
					cout << "EventManager: got ESC button press. Quiting..." << endl;
					break;
				}
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
					player.setMovementDirection(-1);

				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
					player.setMovementDirection(1);

				if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN)
					player.setMovementSpeed(0);

				if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP)
					player.setMovementSpeed(1);
				if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
					player.shoot();
			}
			screenManager->clearScreen();

			/* ==== Redrawing game objects ====*/
			uiManager.drawBg();
			uiManager.drawHUD(player.getHealth(), player.getScore());
			player.reDraw();
			asteroids.remove_if(Asteroid::removalCheck);
			/* ==== Check for collisions ====*/
			for (auto &asteroid : asteroids) {
				player.setHealth(-asteroid.reDraw());
				player.weapon.particles.remove_if(Particle::removalCheck);
				for (auto &particle : player.weapon.particles) {
					asteroid.checkForOverlap(&particle);
				}
				if (asteroid.shouldBreak) {
					cout << "Asteroid Breaking" << endl;
					player.setScore(asteroid.getSize() * 7);
					asteroids.emplace_back(screenManager, asteroid.getX() + asteroid.getSize() * 10, asteroid.getY(),
					                       asteroid.getMovementByX(),
					                       asteroid.getMovementByY() / 2, asteroid.getSize());
					asteroids.emplace_back(screenManager, asteroid.getX() - asteroid.getSize() * 10, asteroid.getY(),
					                       asteroid.getMovementByX(),
					                       asteroid.getMovementByY() / 2, asteroid.getSize());
					asteroid.setIsOnScreen(false);
				}
			}
			screenManager->updateScreen();
			capFPS();

			if (player.getHealth() <= 0) {
				return uiManager.showGameOver(&eventManager, screenManager, &uiManager);
				break;
			}
		}
	}
};


#endif //COURSEWORK_GAMEMANAGER_H
