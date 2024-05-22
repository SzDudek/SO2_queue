//
// Created by sdudek on 29.03.24.
//
#include <unistd.h>
#include <ncurses.h>
#include <vector>
#include "Client.h"
#include "Station.h"

extern std::mutex directorMutex;
extern std::condition_variable directorCV;

extern std::vector<Station> stations;
extern int directorX;
extern int directorY;
extern bool generate;
extern int targetedStation;
extern bool direct;

Client::Client(int speed, char letter, const Coordinates &director, const Coordinates &destination,
               const int &destIndex) :
        speed(speed),
        letter(letter),
        position(
                {5, 10}),
        director(
                director), destination(destination), destIndex(destIndex), running(true), finalDirection(false),
        toErase(false), directed(false),
        threadId(&Client::moveClient, this) {
}

Client::Client(int speed, char letter, const Coordinates &destination, const int &destIndex) : speed(speed),
                                                                                               letter(letter),
                                                                                               position({5, 10}),
                                                                                               director({30, 10}),
                                                                                               destination(destination),
                                                                                               destIndex(destIndex),
                                                                                               running(true),
                                                                                               finalDirection(false),
                                                                                               toErase(false),
                                                                                               directed(false),
                                                                                               threadId(
                                                                                                       &Client::moveClient,
                                                                                                       this) {
}

void Client::moveClient() {
    while (running) {
        if(finalDirection){
            if(!directed){
                std::unique_lock<std::mutex> lock(directorMutex);
                directorCV.wait(lock, [this]{return (targetedStation == destIndex) || !running;});
                directed = true;
            }
            if (position != destination) {
                if (position.getY() != destination.getY()) {
                    if (position.getY() < destination.getY())
                        position.setY(position.getY() + 1);
                    else if (position.getY() > destination.getY())
                        position.setY(position.getY() - 1);
                } else {
                    if (position.getX() < destination.getX())
                        position.setX(position.getX() + 1);
                    else
                        position.setX(position.getX() - 1);
                }
            }
            else{
                running = false;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                toErase = true;
            }
        }
        else{
            if (position != director) {
                if (position.getY() != director.getY()) {
                    if (position.getY() < director.getY())
                        position.setY(position.getY() + 1);
                    else if (position.getY() > director.getY())
                        position.setY(position.getY() - 1);
                } else {
                    if (position.getX() < director.getX())
                        position.setX(position.getX() + 1);
                    else
                        position.setX(position.getX() - 1);
                }
            }
            else{
                finalDirection = true;
            }
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

//void Client::setDirection(const Coordinates &newDestination) {
//    finalDirection = true;
//    destination.setX(newDestination.getX());
//    destination.setY(newDestination.getY());
//}

void Client::draw() const {
    mvaddch(position.getY(), position.getX(), letter);
}

bool Client::getToErase() const {
    return toErase;
}


