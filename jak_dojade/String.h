#pragma once
#include <iostream>
using namespace std;

class String {
public:
    char* str;
    int size;

    String();
    ~String();

    void Set_String(const char* tmp);
    
    String& operator=(const String& right);
    String& operator=(const char* right);
    
    bool operator==(const String& right) const;
    bool operator==(const char* right) const;
    
    friend ostream& operator<<(ostream& os, const String& str);
    
    char& operator[](int index);
    
    String(const String& other);
    String(const char* right);
};