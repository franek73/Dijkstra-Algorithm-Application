#pragma once
#include <iostream>

using namespace std;

template <class T>
class Vector {
public:
	T* elements;
	int size;
	int number_of_elements;

	Vector() {
		size = 0;
		elements = nullptr;
		number_of_elements = 0;	
	}

	Vector(int size) {
		this->size = size;
		elements = new T[size];
		for (int i = 0; i < size; i++) {
			elements[i] = T();
		}
		number_of_elements = 0;
	}

	~Vector() {
		delete[] elements;
	}

	T& operator[](int index) {
     	return elements[index];
	}

	void Set_Size(int new_size) 
	{
		T* tmp = new T[new_size];
		for (int i = 0; i < number_of_elements; i++) {
			tmp[i] = elements[i];
		}

		delete[] elements;
		elements = tmp;
		size = new_size;
	}

	void Add_New_Element(T new_Element)
	{	
		if (number_of_elements == size)
		{
	    int length = size+1;
		Set_Size(length);
	    }

		elements[number_of_elements] = new_Element;
		number_of_elements++;
	}

	Vector<T>& operator=(const Vector<T>& right)
	{
		delete[] elements; 
		size = right.size; 

		elements = new T[size]; 
		for (int i = 0; i < size; i++) {
			elements[i] = right.elements[i]; 
		}

		return *this; 
	}

	void Clear() {
		delete[] elements;
		elements = nullptr;
		size = 0;
		number_of_elements = 0;
	}

	bool operator==(const T& value) {
		for (int i = 0; i < number_of_elements; i++) {
			if (elements[i] == value) {
				return true;
			}
		}
		return false;
	}

	void Remove_First_Element() {
		if (number_of_elements > 0) {
			for (int i = 0; i < number_of_elements - 1; i++) {
				elements[i] = elements[i + 1];
			}
			number_of_elements--;
		}
	}

};