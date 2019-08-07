//
// Created by vhundef on 01.07.19.
//

#ifndef COURSEWORK_GAMEMANAGER_H
#define COURSEWORK_GAMEMANAGER_H


class GameManager {
private:
	void resetEnemies() {
		/*   enemies->clear();*/
	}

	void spawnEnemies(int wv) {/*
        for (int i = 0; i < wv * 2; ++i) {
            enemies->push_back(*new Enemy());
        }
        for (auto &enemy : *enemies) {
            enemy.init(screenManager);
        }*/
		cout << "spawnEnemy fun is not implemented" << endl;
	}


	int wave{0};
	ScreenManager *screenManager;
	int elapsed = 0, current = 0, timeSinceSecond = 0, frames = 0, next{}, avgFPS = 100; //avgFPS - Avg fps per seconds
	int framerate = 59;
public:

	explicit GameManager(ScreenManager *screenMgr) {
		screenManager = screenMgr;
	}

	void setFramerate(int purposedFPS) {
		GameManager::framerate = purposedFPS;
	}

	void setWave(int wv) {
		cout << "Set wave was called...\nWave now " << wv << endl;
		GameManager::wave = wv;
		resetEnemies();
		spawnEnemies(wave);

	}

	void checkForNewWave() {
		/*if (enemies->empty()) {
			setWave(++wave);
			cout << "==================" << endl << "NEW Wave, now " << wave << endl << "==================" << endl;
		}*/
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
};


#endif //COURSEWORK_GAMEMANAGER_H
