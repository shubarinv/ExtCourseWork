//
// Created by vhundef on 20.09.2019.
//

#ifndef TANKSCOURSEWORKRD_UI_GAME_OVER_HPP
#define TANKSCOURSEWORKRD_UI_GAME_OVER_HPP


#include "ui_base.hpp"
#include "../EventManager.h"

class ui_game_over : private virtual UI_Base {
private:
	int score{-1};
	SDL_Event event{};
	string playerName{""};

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

	void writeScoreToFile() {
		std::ofstream outfile;

		outfile.open("leaderBoard", std::ios_base::app);
		outfile << playerName << " " << score << "\n";
		outfile.close();
	}

	list<LdbrdRecord> leaderBoardParsed;

public:
	int selectedOption{1};

	ui_game_over(ScreenManager *screenMgr, int score) {
		screenManager = screenMgr;
		if (TTF_Init()) { // init of SDL_TFF lib
			throw runtime_error("UI_Manager: Failed to init SDL_TTF ");
		}

		fnt = TTF_OpenFont("Hack.ttf", fontSize); ///< setting font and font size

		if (!fnt) {
			printf("UI: %s\n", TTF_GetError());
		}
		this->score = score;
	}

	void show() {
		playerName = input();
		screenManager->clearScreen();

		changeFontSize(22);
		createButton(0, 0, screenManager->getScreenWidth(), 50, "Well, this is GameOver", 0x0,
		             0xffffff);
		changeFontSize(20);
		writeScoreToFile(); ///< Asks user to input PlayerName than writes it and player score to the leaderBoard file
		parseLeaderboard();
		showLeaderBoard();
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
	 * @brief allows to enter some text
	 **/
	string input() {
		SDL_Event event;
		string str;
		string tmp;
		screenManager->clearScreen();
		createButton(0, screenManager->getScreenHeight() / 6, screenManager->getScreenWidth(), 20,
		             "Please enter player name (20 symbols max)", 0x00, 0xffff00);

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
				if (str.size() > 20) { continue; }
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
		for (auto &record : leaderBoardParsed) {
			j++;
			if (j > 26) break;
			if (record.name == playerName && record.score == score) {
				createButton(0, screenManager->getScreenHeight() / 20 + 20 * i,
				             screenManager->getScreenWidth() / 2, 20,
				             record.name, 0x4d4d4d, 0xc24100);
				createButton(screenManager->getScreenWidth() / 2,
				             screenManager->getScreenHeight() / 20 + 20 * i,
				             screenManager->getScreenWidth() / 2, 20, to_string(record.score), 0x4d4d4d, 0xc24100);
			} else {
				createButton(0, screenManager->getScreenHeight() / 20 + 20 * i,
				             screenManager->getScreenWidth() / 2, 20,
				             record.name, 0x4d4d4d, 0xFFFF00);
				createButton(screenManager->getScreenWidth() / 2,
				             screenManager->getScreenHeight() / 20 + 20 * i,
				             screenManager->getScreenWidth() / 2, 20, to_string(record.score), 0x4d4d4d, 0xFFFF00);
			}
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


};


#endif //TANKSCOURSEWORKRD_UI_GAME_OVER_HPP
