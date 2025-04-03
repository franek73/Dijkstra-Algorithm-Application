#include <iostream>
using namespace std;
#include "String.h"

String::String() {
	size = 1;
	str = new char[size];
	str[0] = '\0';
}
String::~String() {
	int i = 0;
	while (i<size)
	{
		i++;
		if (str[i] == '\0')
		{
			delete[] str;
			break;	
		}
	}
}

void String::Set_String(const char* tmp) 
{
	int i = 0;
	delete[] str;
	while (tmp[i] != '\0')
	{
		i++;
	}
	size = i + 1;
	str = new char[size];
	i = 0;
	while (tmp[i] != '\0')
	{
		str[i] = tmp[i];
		i++;
	}
	str[i] = '\0';
};

String& String::operator=(const String& right)
{
	int i = 0;
	delete[] str;
	while (right.str[i] != '\0')
	{
		i++;
	}
	size = i + 1;
	str = new char[size];
	i = 0;
	while (right.str[i] != '\0')
	{
		str[i] = right.str[i];
		i++;
	}
	str[i] = '\0';

	return *this;
}
String& String::operator=(const char* right)
{
	int i = 0;
	delete[] str;
	while (right[i] != '\0')
	{
		i++;
	}
	size = i + 1;
	str = new char[size];
	i = 0;
	while (right[i] != '\0')
	{
		str[i] = right[i];
		i++;
	}
	str[i] = '\0';
	return *this;
}

bool String::operator==(const String& right) const
{
	if (right.size > this->size || this->size > right.size)
	{

		return false;
	}
	else
	{
		int i = 0;
		while (right.str[i] != '\0')
		{
			if (str[i] != right.str[i])
			{
				return false;
			}
			i++;
		}
		return true;
	}
}
bool String::operator==(const char* right) const
{
	int i = 0;
	while (right[i] != '\0')
	{
		if (str[i] != right[i])
		{
			return false;
		}
		i++;
	}
	return true;
}

ostream& operator<<(ostream& os, const String& str) {
	os << str.str;
	return os;
}

char& String::operator[](int index) {
	return str[index];
}

String::String(const String& other) {
	size = other.size;
	str = new char[size];
	for (int i = 0; i < size; i++) {
		str[i] = other.str[i];
	}
}
String::String(const char* right) {
	size = 0;
	while (right[size] != '\0') {
		size++;
	}
	size++; 
	str = new char[size];
	for (int i = 0; i < size; i++) {
		str[i] = right[i];
	}
}