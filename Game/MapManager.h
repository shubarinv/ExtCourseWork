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
#include "Map.h"

class MapManager {
private:
    ScreenManager *screenManager;
    list<Map> maps;
    Map *currentMap{};
public:
    Map *getCurrentMap() const {
        return currentMap;
    }


public:
    explicit MapManager(ScreenManager *screenMgr) {
        int mapNumber{0};
        screenManager = screenMgr;
        while (maps.empty() || maps.back().mapNumber != -255) {
            maps.emplace_back(screenManager, ++mapNumber);
            maps.back().readMapFromFile();
            if (maps.back().mapNumber != -255) {
                cout << "Map " << mapNumber << " added" << endl;
            } else
                cout << "Map " << mapNumber << " NOT FOUND" << endl;
        }
    }

    void setCurrentMap(int mapNum) {
        for (auto &map : maps) {
            if (mapNum == map.mapNumber)
                currentMap = &map;
        }
        cout << "No such map" << endl;
    }

};


#endif //NEWCOURSEWORK_MAPMANAGER_H
