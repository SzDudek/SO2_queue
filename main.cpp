#include <iostream>
#include <ncurses.h>
#include "Structures/Client.h"
#include "Structures/Station.h"
#include <vector>
#include <random>
#include <memory>
#include <thread>

std::vector<Station> stations{{0,{60,5}},{1,{60,10}},{2,{60,15}}};
std::vector<std::shared_ptr<Client*>> clients;
int directorX = 30;
int directorY = 10;
bool generate = true;
int targetedStation = 0;
bool direct = true;

std::mutex vectorMutex;
std::mutex directorMutex;
std::condition_variable directorCV;

void changeTarget() {
    while(direct){
        std::this_thread::sleep_for(std::chrono::seconds(3));
        {
            std::lock_guard<std::mutex> lock(directorMutex);
            if(targetedStation!=2) targetedStation+=1;
            else targetedStation = 0;
        }
        directorCV.notify_all();
    }
}

void drawDirector(){
    switch (targetedStation) {
        case 0:
            mvaddch(directorY,directorX,ACS_UARROW);
            break;
        case 1:
            mvaddch(directorY,directorX,ACS_RARROW);
            break;
        case 2:
            mvaddch(directorY,directorX,ACS_DARROW);
            break;
    }
}

void drawCorridor(){
    for(int i = 9; i<directorX-1; ++i) {
        mvaddch(directorY-1, i, '-');
        mvaddch(directorY+1, i, '-');
    }

    for(int i = 0; i<4;++i){
        mvaddch(directorY+i+2,directorX-2,'|');
        mvaddch(directorY-i-2,directorX-2,'|');
    }

    for(int i = 0; i<stations[0].getXPos() - directorX; ++i){
        mvaddch(directorY-1,directorX+2+i,'-');
        mvaddch(directorY+1,directorX+2+i,'-');
    }

    for(int i = 0;i<3;++i){
        mvaddch(directorY-2-i,directorX+2,'|');
        mvaddch(directorY+2+i,directorX+2,'|');
    }

    for(int i = 0 ; i<stations[0].getXPos() - directorX; ++i){
        mvaddch(directorY-4,directorX+2+i,'-');
        mvaddch(directorY+4,directorX+2+i,'-');
    }

    for(int i = 0 ; i<stations[0].getXPos() - directorX+3; ++i){
        mvaddch(directorY-6,directorX-1+i,'-');
        mvaddch(directorY+6,directorX-1+i,'-');
    }
}

void  generateClients(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr_speed(0,4);
    std::uniform_int_distribution<> distr_sleep(1,3);
    std::uniform_int_distribution<> dest_index(0,2);
    char letter;
    int speed, dest;
    while(generate){
        speed = 1 + distr_speed(gen);
        dest = dest_index(gen);
        switch (dest) {
            case 0:
                letter = '0';
                break;
            case 1:
                letter = '1';
                break;
            case 2:
                letter = '2';
                break;
        }
        auto newClient = std::make_shared<Client*>(new Client{speed,letter,{directorX,directorY},stations[dest].getPos(),dest});
        vectorMutex.lock();
        clients.emplace_back(newClient);
        vectorMutex.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1*distr_sleep(gen)));
    }
}


int main() {

//    auto testCLient = std::make_shared<Client*>( new Client(3,'T'));
//    clients.emplace_back(testCLient);

    initscr();
    curs_set(0);
    nodelay(stdscr, TRUE);

    std::thread clientGenerator(generateClients);
    std::thread director(changeTarget);

    while(true){
        erase();
        drawCorridor();
        for( auto& client : clients){
            (*client)->draw();
        }

        drawDirector();

        refresh();

        bool erased = false;

        for(auto client = clients.begin();client!=clients.end();){
            erased = false;
            for(auto& station : stations){
                if((*(*client))->getPos() == station.getPos() && (*(*client))->getToErase()){
                    vectorMutex.lock();
                    client = clients.erase(client);
                    vectorMutex.unlock();
                    erased = true;
                    break;
                }
            }
            if(!erased) ++client;
        }
        int ch = getch();
        if(ch == ' ') {
            generate = false;
            clientGenerator.join();
            direct = false;
            director.join();
            for(auto& client : clients) {
                (*client)->joinThread();
            }
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    endwin();

    return 0;
}
