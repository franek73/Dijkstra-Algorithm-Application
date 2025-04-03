#include "RoadList.h"
#include <iostream>

using namespace std;

Road::Road()
{
    x = 0;
    y = 0;
    distance = 0;
    next = nullptr;
}

Road::Road(int x, int y, int distance)
{
    this->x = x;
    this->y = y;
    this->distance = distance;
    next = nullptr;
}

RoadList::~RoadList()
{
    Road* current_road = first_road;
    while (current_road != nullptr)
    {
        Road* next_road = current_road->next;
        delete current_road;
        current_road = next_road;
    }
    first_road = nullptr;
    end_road = nullptr;
}

RoadList::RoadList()
{
    first_road = nullptr;
    end_road = nullptr;
}

void RoadList::Add_Road(int x, int y, int distance) {
    Road* new_road = new Road(x, y, distance);
    if (end_road != nullptr) {
        end_road->next = new_road;
        end_road = new_road;
    }
    else {
        first_road = new_road;
        end_road = new_road;
    }
}

void RoadList::Remove_First_Road() {
    if (first_road != nullptr) {
        Road* temp = first_road;
        first_road = first_road->next;
        if (first_road == nullptr) {
            end_road = nullptr;
        }
        delete temp;
    }
}