//
// Created by vhundef on 14.09.2019.
//

#ifndef TANKSCOURSEWORKRD_GAME_MANAGER_HPP
#define TANKSCOURSEWORKRD_GAME_MANAGER_HPP

#include "EventManager.h"
#include "ScreenManager.h"
#include "UI/ui_manager.hpp"
#include "bot_controller.hpp"
#include "tank.hpp"
#include <SDL/SDL_events.h>

class GameManager {
public:
	GameManager() {
		while (startGame() != -1) {
			tanks.clear();
			bots.clear();
			score = 0;
		}
	}

private:
	SDL_Event event{};
	ScreenManager screenManager;
	EventManager eventManager;
	list <BotController> bots;
	list <Tank> tanks;
	MapManager mapManager{&screenManager};
	int score{0};

	static bool checkForCollision(Particle *particle, Tank *tank) {
		return particle->location.x1 >= tank->getLocation().x1 &&
		       particle->location.x2 <= tank->getLocation().x2 &&
		       particle->location.y1 >= tank->getLocation().y1 &&
		       particle->location.y2 <= tank->getLocation().y2;
	}

	int startGame() {
		mapManager.setCurrentMap(1);
		Tank player(&screenManager, &mapManager, true);
		UIManager uiManager{&screenManager, &mapManager, &player};
		uiManager.show('m');
		if (uiManager.whatToShow == 'q') {
			return -1;
		}
		mapManager.setCurrentMap(GameObject::randIntInRange(2, 6));

		player.spawnAtRandomLocation();

		spawnBot();
		spawnBot();

		screenManager.setFramerate(170);

		while (true) {
			tanks.remove_if(Tank::removalCheck);
			bots.remove_if(BotController::removalCheck);
			screenManager.clearScreen();
			mapManager.getCurrentMap()->redraw();

			if (tanks.empty()) {
				bots.clear();

				spawnBot();
				spawnBot();
			}
			/* ==== Redrawing game objects ====*/
			for (auto &bot : bots) {
				bot.moveTank();
				bot.controlledTank->redraw();
				bot.shootPlayer(player.getLocation());
			}
			player.redraw();
			/* ==== Check for collisions ==== */
			for (auto &particle : player.weapon.particles) {
				for (auto &tank : tanks) {
					if (checkForCollision(&particle, &tank)) {
						cout << "Particle is now offscreen" << endl;
						particle.isOnScreen = false;
						score += 15;
						tank.applyDamage(-25);
					}
				}
				if (mapManager.getCurrentMap()->checkForCollision(particle.location)) {
					particle.isOnScreen = false;
				}
			}

			event = eventManager.getEvent();
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
				player.setMovementDirection(-1);
				player.setMovementSpeed(1);
			} else if (event.type == SDL_KEYDOWN &&
			           event.key.keysym.sym == SDLK_RIGHT) {
				player.setMovementDirection(1);
				player.setMovementSpeed(1);
			} else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
				player.setMovementDirection(2);
				player.setMovementSpeed(1);
			} else if (event.type == SDL_KEYDOWN &&
			           event.key.keysym.sym == SDLK_DOWN) {
				player.setMovementDirection(-2);
				player.setMovementSpeed(1);
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
				player.shoot();

			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
				uiManager.show('p');
			}

			if (event.type == SDL_KEYUP)
				player.setMovementSpeed(0);
			if (uiManager.whatToShow == 'q') {
				return -1;
			}

			uiManager.show('h', score);

			for (auto &tank : tanks) {
				for (auto &particle : tank.weapon.particles) {
					if (checkForCollision(&particle, &player)) {
						particle.isOnScreen = false;
						player.applyDamage(-25); // THIS IS TEMPORARY
					}
					if (mapManager.getCurrentMap()->checkForCollision(
							particle.location)) {
						particle.isOnScreen = false;
						cout << "Removed particle" << endl;
					}
				}
			}

			screenManager.updateScreen();
			if (player.getHP() <= 0) {
				uiManager.show('g', score);
				if (uiManager.whatToShow == 'q') {
					return -1;
				}
				break;
			}
		}
		return 1;
	}

	void spawnBot() {
		tanks.emplace_back(&screenManager, &mapManager);
		bots.emplace_back(&tanks.back(), &screenManager);
		tanks.back().spawnAtRandomLocation();
	}
};

#endif // TANKSCOURSEWORKRD_GAME_MANAGER_HPP
