//
// Created by sdudek on 29.03.24.
//
#include <unistd.h>
#include <ncurses.h>
#include "Client.h"
#include "globals.h"

Client::Client(int speed, char letter, const Coordinates &direction) :
        speed(speed),
        letter(letter),
        position(
                {5, 10}),
        direction(
                direction), running(true), finalDirection(false), toErase(false),
        threadId(&Client::moveClient, this) {
}

Client::Client(int speed, char letter) : speed(speed), letter(letter), position({5, 10}), direction({30, 10}),
                                         running(true), finalDirection(false), toErase(false),
                                         threadId(&Client::moveClient, this) {
}

void Client::moveClient() {
    while (running) {
        if(position != direction){
            if (position.getY() != direction.getY()) {
                if (position.getY() < direction.getY())
                    position.setY(position.getY() + 1);
                else if (position.getY() > direction.getY())
                    position.setY(position.getY() - 1);
            } else {
                if (position.getX() < direction.getX())
                    position.setX(position.getX() + 1);
                else
                    position.setX(position.getX() - 1);
            }
        }
        else if(finalDirection) {
            running = false;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            toErase = true;
        }
        else{
            finalDirection = true;
            direction = stations[targetedStation].getPos();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / speed));
    }
}

void Client::joinThread() {
    running = false;
    threadId.join();
}

int Client::getXPos() const {
    return position.getX();
}

int Client::getYPos() const {
    return position.getY();
}

Coordinates Client::getPos() const {
    return position;
}

void Client::setDirection(Coordinates newDirection) {
    finalDirection = true;
    direction.setX(newDirection.getX());
    direction.setY(newDirection.getY());
}

void Client::draw() const {
    mvaddch(position.getY(), position.getX(), letter);
}

bool Client::getToErase() const {
    return toErase;
}


