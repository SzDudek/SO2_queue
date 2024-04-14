//
// Created by sdudek on 30.03.24.
//

#include "Station.h"

Station::Station(int id, Coordinates pos):id(id),pos(pos){
}

int Station::getId() const {
    return id;
}

int Station::getXPos() const {
    return pos.getX();
}

int Station::getYPos() const {
    return pos.getY();
}

Coordinates Station::getPos() const {
    return pos;
}
