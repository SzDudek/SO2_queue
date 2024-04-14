//
// Created by sdudek on 29.03.24.
//

#ifndef SO2_QUEUE_STATION_H
#define SO2_QUEUE_STATION_H


#include "Coordinates.h"

class Station {
    const int id;
    const Coordinates pos;
public:

    Station(int id, Coordinates pos);

    int getId() const;

    int getXPos() const;

    int getYPos() const;

    Coordinates getPos() const;
};

#endif //SO2_QUEUE_STATION_H
