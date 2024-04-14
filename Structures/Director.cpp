//
// Created by sdudek on 29.03.24.
//

#include "Director.h"
#include <ncurses.h>
#include <chrono>
#include <thread>

Director::Director(int id, Coordinates pos) : Station(id, pos), direct(true),threadId(&Director::changeTarget,this) {
    targetedStation = 0;
}

int Director::getTarget() const {
    return targetedStation;
}

void Director::changeTarget() {
    while(direct){
        std::this_thread::sleep_for(std::chrono::seconds(3));
        if(targetedStation!=2) targetedStation+=1;
        else targetedStation = 0;
    }
}

void Director::draw(){
    switch (targetedStation) {
        case 0:
            mvaddch(getYPos(),getXPos(),ACS_UARROW);
            break;
        case 1:
            mvaddch(getYPos(),getXPos(),ACS_RARROW);
            break;
        case 2:
            mvaddch(getYPos(),getXPos(),ACS_DARROW);
            break;
    }
}

void Director::stop() {
    direct = false;
    threadId.join();
}
