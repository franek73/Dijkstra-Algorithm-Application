#include "PriorityQueue.h"
#include <iostream>

using namespace std;

PriorityQueueElement::PriorityQueueElement()
{
    priority = 0;
    value = 0;
    next = nullptr;
}

PriorityQueue::PriorityQueue() {
    first_element = nullptr;
    number_of_elements = 0;
}

PriorityQueue::~PriorityQueue()
{
    PriorityQueueElement* current_element = first_element;
    while (current_element != nullptr)
    {
        PriorityQueueElement* next_element = current_element->next;
        delete current_element;
        current_element = next_element;
    }
    first_element = nullptr;
    number_of_elements = 0;
}

void PriorityQueue::Add_Element(int priority, int value) {
    PriorityQueueElement* new_element = new PriorityQueueElement;
    new_element->priority = priority;
    new_element->value = value;
    new_element->next = nullptr;


    if (first_element == nullptr || priority < first_element->priority) {
        new_element->next = first_element;
        first_element = new_element;
    }
    else {
        PriorityQueueElement* current_element = first_element;
        while (current_element->next != nullptr && priority >= current_element->next->priority) {
            current_element = current_element->next;
        }
        new_element->next = current_element->next;
        current_element->next = new_element;
    }
    number_of_elements++;
}

void PriorityQueue::Remove_Element() {
    if (first_element != nullptr) {
        PriorityQueueElement* removed_element = first_element;
        first_element = first_element->next;
        delete removed_element;
        number_of_elements--;
    }
}