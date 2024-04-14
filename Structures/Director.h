//
// Created by sdudek on 29.03.24.
//

#ifndef SO2_QUEUE_DIRECTOR_H
#define SO2_QUEUE_DIRECTOR_H


#include <thread>
#include "Station.h"

class Director : public Station {
    int targetedStation;
    volatile bool direct;
    std::thread threadId;
public:
    Director(int id, Coordinates pos);

    int getTarget() const;

    void changeTarget();

    void draw();

    void stop();
};


#endif //SO2_QUEUE_DIRECTOR_H
