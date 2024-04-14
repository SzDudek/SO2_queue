//
// Created by sdudek on 29.03.24.
//

#include "Coordinates.h"

Coordinates::Coordinates(int x, int y):x(x),y(y) {}

int Coordinates::getX() const {
    return x;
}

void Coordinates::setX(int x) {
    Coordinates::x = x;
}

int Coordinates::getY() const {
    return y;
}

void Coordinates::setY(int y) {
    Coordinates::y = y;
}

void Coordinates::setCords(int x, int y) {
    Coordinates::x = x;
    Coordinates::y = y;
}

bool Coordinates::operator==(const Coordinates &cords) const {
    if(cords.getX() == x && cords.getY() == y) return true;
    return false;
}

bool Coordinates::operator!=(const Coordinates &cords) const {
    if(cords.getX() == x && cords.getY() == y) return false;
    return true;
}

Coordinates &Coordinates::operator=(const Coordinates &other){
    x = other.getX();
    y = other.getY();
    return *this;
}

Coordinates::Coordinates(const Coordinates &other):x(other.getX()),y(other.getY()){}


