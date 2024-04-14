//
// Created by sdudek on 29.03.24.
//

#ifndef SO2_QUEUE_CLIENT_H
#define SO2_QUEUE_CLIENT_H


#include <cstdlib>
#include <thread>
#include "Coordinates.h"

class Client {
    bool volatile running;
    bool volatile finalDirection;
    bool volatile toErase;
    const int speed;
    const char letter;
    Coordinates position;
    Coordinates direction;
    std::thread threadId;
public:
    Client(int speed, char letter, const Coordinates &direction);

    Client(int speed, char letter);

    void moveClient();

    void joinThread();

    int getXPos() const;

    int getYPos() const;

    bool getToErase() const;

    Coordinates getPos() const;

    void setDirection(Coordinates newDirection);

    void draw() const;
};


#endif //SO2_QUEUE_CLIENT_H
