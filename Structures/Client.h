//
// Created by sdudek on 29.03.24.
//

#ifndef SO2_QUEUE_CLIENT_H
#define SO2_QUEUE_CLIENT_H


#include <cstdlib>
#include <thread>
#include <condition_variable>
#include "Coordinates.h"

class Client {
    bool volatile running;
    bool volatile finalDirection;
    bool volatile toErase;
    bool directed;
    const int speed;
    const int destIndex;
    const char letter;
    Coordinates position;
    const Coordinates director;
    const Coordinates destination;
    std::thread threadId;
public:
    Client(int speed, char letter, const Coordinates &director, const Coordinates &destination, const int &destIndex);

    Client(int speed, char letter, const Coordinates &destination, const int &destIndex);

    void moveClient();

    void joinThread();

    int getXPos() const;

    int getYPos() const;

    bool getToErase() const;

    Coordinates getPos() const;

//    void setDirection(const Coordinates& newDirection);

    void draw() const;
};


#endif //SO2_QUEUE_CLIENT_H
