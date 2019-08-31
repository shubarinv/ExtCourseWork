//
// Created by vhundef on 27.08.2019.
//

#ifndef NEWCOURSEWORK_MAPMANAGER_H
#define NEWCOURSEWORK_MAPMANAGER_H


#include <list>
#include <fstream>
#include "ScreenManager.h"
#include "Wall.h"

#define CUTE_C2_IMPLEMENTATION

#include "Lib/cute_c2.h"

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

    static bool removalCheck(const Wall &wall) {
        return wall.getHp() <= 0;
    }

    void reDraw() {
        map.remove_if(removalCheck);
        for (auto &wall : map) {
            wall.reDraw();
        }
    }

    bool checkforCollision(GameObject::coords coords, bool pathChecking = false) {
        c2AABB obj, wallR;
        obj.min = c2V(coords.x1, coords.y1);
        obj.max = c2V(coords.x2, coords.y2);
        for (auto &wall : map) {
            wallR.min = c2V(wall.getX(), wall.getY());
            wallR.max = c2V(wall.getX() + wall.getSize(), wall.getY() + wall.getSize());
            if (c2AABBtoAABB(obj, wallR) != 0) {
                if (!pathChecking) {
                    if (coords.x2 - coords.x1 <= 20)
                        wall.setHp(-50);
                }
                return true;
            }

        }
        return false;
    }
};


#endif //NEWCOURSEWORK_MAPMANAGER_H
