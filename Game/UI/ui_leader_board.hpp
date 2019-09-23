//
// Created by vhundef on 23.09.2019.
//

#ifndef TANKSCOURSEWORKRD_UI_LEADER_BOARD_HPP
#define TANKSCOURSEWORKRD_UI_LEADER_BOARD_HPP


#include "ui_base.hpp"

class UILeaderBoard : private virtual UI_Base {
private:
	SDL_Event event;

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

	list<LdbrdRecord> leaderBoardParsed;
public:
	explicit UILeaderBoard(ScreenManager *screenMgr) {
		screenManager = screenMgr;
		if (TTF_Init()) { // init of SDL_TFF lib
			throw runtime_error("UI_Manager: Failed to init SDL_TTF ");
		}

		fnt = TTF_OpenFont("Hack.ttf", fontSize); ///< setting font and font size

		if (!fnt) {
			printf("UI: %s\n", TTF_GetError());
		}
	}

	void show() {
		screenManager->clearScreen();
		parseLeaderboard();
		showLeaderBoard();
		changeFontSize(30);
		createButton(0, 0, screenManager->getScreenWidth(), 50,
		             "LeaderBoard (TOP 26)", 0x303030,
		             0xffffff);
		changeFontSize(20);
		createButton(0, screenManager->getScreenHeight() - 100, screenManager->getScreenWidth(), 50,
		             "Press ENTER to return to main menu", 0x0,
		             0xffffff);
		screenManager->updateScreen();

		while (SDL_WaitEvent(&event)) {
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
				break;
			}
		}
	}

private:
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
 * @brief shows leaderBoard
 **/
	void showLeaderBoard() {
		int i = 4;
		createButton(0, screenManager->getScreenHeight() / 12 - 10,
		             screenManager->getScreenWidth() / 2, screenManager->getScreenHeight() / 20 + 31,
		             "Player Name", 0x4d4d4d, 0xFFFFff);
		createButton(screenManager->getScreenWidth() / 2,
		             screenManager->getScreenHeight() / 12 - 10, screenManager->getScreenWidth() / 2,
		             screenManager->getScreenHeight() / 20 + 31, "Score", 0x4d4d4d, 0xFFFFff);
		int j = 0;
		if (leaderBoardParsed.empty()) {
			createButton(0, screenManager->getScreenHeight() / 12,
			             screenManager->getScreenWidth(), screenManager->getScreenHeight() / 20 + 31,
			             "NO DATA", 0x4d4d4d, 0xff6363);
		} else {
			for (auto &record : leaderBoardParsed) {
				j++;
				if (j > 26) break;
				createButton(0, screenManager->getScreenHeight() / 20 + 20 * i,
				             screenManager->getScreenWidth() / 2, 20,
				             record.name, 0x4d4d4d, 0xFFFF00);
				createButton(screenManager->getScreenWidth() / 2,
				             screenManager->getScreenHeight() / 20 + 20 * i,
				             screenManager->getScreenWidth() / 2, 20, to_string(record.score), 0x4d4d4d, 0xFFFF00);
				Draw_HLine(screenManager->getMainSurface(), 0,
				           screenManager->getScreenHeight() / 20 + 20 * i + 19,
				           screenManager->getScreenWidth(), 0x0);
				Draw_VLine(screenManager->getMainSurface(),
				           screenManager->getScreenWidth() / 2,
				           screenManager->getScreenHeight() / 20 + 20 * i,
				           screenManager->getScreenHeight() / 20 + 20 * i + 18, 0xffffff);
				i++;
			}
		}
	}
};


#endif //TANKSCOURSEWORKRD_UI_LEADER_BOARD_HPP
