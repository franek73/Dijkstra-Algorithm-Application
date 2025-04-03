#pragma once
#include <iostream>
#include "String.h"
#include "Vector.h"

class PriorityQueueElement {
public:
    int priority;
    int value;
    PriorityQueueElement* next;

    PriorityQueueElement();
};

class PriorityQueue {
public:
    PriorityQueueElement* first_element;
    int number_of_elements;

    PriorityQueue();
    ~PriorityQueue();

    void Add_Element(int priority, int value);
    void Remove_Element();
};