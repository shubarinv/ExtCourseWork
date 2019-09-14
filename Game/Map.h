//
// Created by vhundef on 06.09.2019.
//

#ifndef NEWCOURSEWORK_MAP_H
#define NEWCOURSEWORK_MAP_H


#include <fstream>
#include <iostream>
#include <list>
#include "Wall.h"

using namespace std;

class Map {
public:

    Map(ScreenManager *sceenMgr, int mapNum) {
        screenManager = sceenMgr;
        mapNumber = mapNum;
    }

    list<Wall> walls;

    void readMapFromFile() {
        int mapNum{0};
        std::ifstream mapsFile("../Game/maps.tnks");
        if (mapsFile.is_open()) {
            std::string line;
            int rowNum{0}, column{0};
            while (getline(mapsFile, line)) {
                if (line[0] == '#') {
                    continue;
                } else if (line[0] == '-') {
                    if (mapNum == mapNumber) break;
                    mapNum++;
                    cout << "MAP" << line << endl;
                    rowNum = 0;
                    if (!walls.empty()) {
                        walls.clear();
                    }
                } else if (!line.empty()) {
                    if (mapNum == mapNumber) {
                        column = 0;
                        for (char i : line) {
                            if (i != ' ' && i != '\n') {
                                if (i == '1') {
                                    walls.emplace_back(screenManager, true);
                                    walls.back().setLocation(column, rowNum);
                                }
                                if (i == '2') {
                                    walls.emplace_back(screenManager, false);
                                    walls.back().setLocation(column, rowNum);
                                }
                                column++;
                            }
                        }
                        rowNum++;
                    }
                }
            }
        }
        if (mapNum != mapNumber) {
            cout << "NO SUCH MAP FOUND!" << endl;
            mapNumber = -255;
        }
    }

    void reDraw() {
        walls.remove_if(removalCheck);
        for (auto &wall : walls) {
            wall.reDraw();
        }
    }


    bool checkForCollision(GameObject::coords coords, bool pathChecking = false, int wallDmg = 50) {
        c2AABB obj, wallR;
        obj.min = c2V(coords.x1, coords.y1);
        obj.max = c2V(coords.x2, coords.y2);
        for (auto &wall : walls) {
            wallR.min = c2V(wall.getX(), wall.getY());
            wallR.max = c2V(wall.getX() + wall.getSize(), wall.getY() + wall.getSize());
            if (c2AABBtoAABB(obj, wallR) != 0) {
                if (!pathChecking) {
                    if (coords.x2 - coords.x1 <= 20)
                        wall.setHp(-wallDmg);
                }
                return true;
            }

        }
        return false;
    }

    static bool removalCheck(const Wall &wall) {
        return wall.getHp() <= 0;
    }

    int mapNumber{0};
private:
    ScreenManager *screenManager;
};


#endif //NEWCOURSEWORK_MAP_H
