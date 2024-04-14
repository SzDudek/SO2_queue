#include <iostream>
#include <ncurses.h>
#include "Structures/Client.h"
#include "Structures/Station.h"
#include "Structures/Director.h"
#include <unistd.h>
#include <vector>
#include <random>
#include <memory>
#include <thread>

std::vector<Station> stations{{0,{60,5}},{1,{60,10}},{2,{60,15}}};
std::vector<std::shared_ptr<Client*>> clients;
Director director(0, {30, 10});
bool volatile generate = true;

void drawCorridor(){
    for(int i = 9; i<director.getXPos()-1; ++i) {
        mvaddch(director.getYPos()-1, i, '-');
        mvaddch(director.getYPos()+1, i, '-');
    }

    for(int i = 0; i<4;++i){
        mvaddch(director.getYPos()+i+2,director.getXPos()-2,'|');
        mvaddch(director.getYPos()-i-2,director.getXPos()-2,'|');
    }

    for(int i = 0; i<stations[0].getXPos() - director.getXPos(); ++i){
        mvaddch(director.getYPos()-1,director.getXPos()+2+i,'-');
        mvaddch(director.getYPos()+1,director.getXPos()+2+i,'-');
    }

    for(int i = 0;i<3;++i){
        mvaddch(director.getYPos()-2-i,director.getXPos()+2,'|');
        mvaddch(director.getYPos()+2+i,director.getXPos()+2,'|');
    }

    for(int i = 0 ; i<stations[0].getXPos() - director.getXPos(); ++i){
        mvaddch(director.getYPos()-4,director.getXPos()+2+i,'-');
        mvaddch(director.getYPos()+4,director.getXPos()+2+i,'-');
    }

    for(int i = 0 ; i<stations[0].getXPos() - director.getXPos()+3; ++i){
        mvaddch(director.getYPos()-6,director.getXPos()-1+i,'-');
        mvaddch(director.getYPos()+6,director.getXPos()-1+i,'-');
    }
}

void  generateClients(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr_letter(0,26);
    std::uniform_int_distribution<> distr_speed(0,4);
    std::uniform_int_distribution<> distr_sleep(1,3);
    char letter;
    int speed;
    while(generate){
        letter = 'A' + distr_letter(gen);
        speed = 1 + distr_speed(gen);
        auto newClient = std::make_shared<Client*>(new Client{speed,letter,{director.getXPos(),director.getYPos()}});
        clients.emplace_back(newClient);
        std::this_thread::sleep_for(std::chrono::seconds(1*distr_sleep(gen)));
    }
}


int main() {

    auto testCLient = std::make_shared<Client*>( new Client(3,'T'));
    clients.emplace_back(testCLient);

    initscr();
    curs_set(0);
    nodelay(stdscr, TRUE);

    std::thread clientGenerator(&generateClients);

    while(true){
        erase();
        drawCorridor();
        for( auto& client : clients){
            (*client)->draw();
        }

        director.draw();

        refresh();

        bool erased = false;

        for(auto client = clients.begin();client!=clients.end();){
            if((*(*client))->getPos() == director.getPos()){
                (*(*client))->setDirection(stations[director.getTarget()].getPos());
                ++client;
                continue;
            }
            erased = false;
            for(auto& station : stations){
                if((*(*client))->getPos() == station.getPos() && (*(*client))->getToErase()){
                    client = clients.erase(client);
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
            director.stop();
            for(auto& client : clients) {
                (*client)->joinThread();
            }
            break;
        }
    }
    endwin();

    return 0;
}
