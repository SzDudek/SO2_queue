//
// Created by sdudek on 29.03.24.
//

#ifndef SO2_QUEUE_COORDINATES_H
#define SO2_QUEUE_COORDINATES_H


class Coordinates {
    int x;
    int y;

public:

    Coordinates(int x, int y);

    Coordinates(const Coordinates& other);

    Coordinates& operator=(const Coordinates& other);

    bool operator== (const Coordinates& cords) const;

    bool operator!= (const Coordinates& cords) const;

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    void setCords(int x, int y);
};


#endif //SO2_QUEUE_COORDINATES_H
