#pragma once
#include <iostream>
#include "String.h"
#include "Vector.h"

class Road {
public:
    int distance;
    int x, y;
    Road* next;

    Road();
   
    Road(int x, int y, int distance);
};

class RoadList {
public:
    Road* first_road;
    Road* end_road;

    RoadList();
    ~RoadList();

    void Add_Road(int x, int y, int distance);
    void Remove_First_Road();
};
