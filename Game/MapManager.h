//
// Created by vhundef on 27.08.2019.
//

#ifndef NEWCOURSEWORK_MAPMANAGER_H
#define NEWCOURSEWORK_MAPMANAGER_H


#include <list>
#include <fstream>
#include "ScreenManager.h"
#include "Wall.h"

class MapManager {
private:
    ScreenManager *screenManager;
    //TODO function that reads maps from file
    list<Wall> map;

    void readMapFromFile() {
        std::ifstream mapsFile("../Game/maps.tnks");
        if (mapsFile.is_open()) {
            std::string line;
            int rowNum{0}, column{0};
            while (getline(mapsFile, line)) {
                if (line[0] == '#') {
                    cout << "SKIPPED->" << line << endl;
                    continue;
                } else if (line[0] == '-') {
                    cout << "MAP" << line << endl;
                    rowNum = 0;
                } else if (!line.empty()) {
                    column = 0;
                    for (char i : line) {
                        if (i != ' ' && i != '\n') {
                            if (i != '0') {
                                map.emplace_back(screenManager);
                                map.back().setLocation(column, rowNum);
                            }
                            column++;
                        }
                    }
                    rowNum++;
                }
            }
        }
    }

public:
    explicit MapManager(ScreenManager *screenMgr) {
        screenManager = screenMgr;
        readMapFromFile();
    }

    void reDraw() {
        for (auto &wall : map) {
            wall.reDraw();
        }
    }
};


#endif //NEWCOURSEWORK_MAPMANAGER_H
