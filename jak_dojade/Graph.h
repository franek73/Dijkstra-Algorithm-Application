#pragma once
#include <iostream>
#include "String.h"
#include "Vector.h"
#include "PriorityQueue.h"
#include "RoadList.h"

#define HASH_MAP_SIZE 100000

using namespace std;

class HashMapElement
{
public:
    String key;
    int value;
    HashMapElement* next;

    HashMapElement();
};

class HashMap {
public:
    HashMapElement* first_element;

    HashMap();
    ~HashMap();

    void Add_Element_To_HashMap(String key, int value);
};

class Edge {
public:
    String destination_city_name;
    int distance;
    Edge* next;
    Edge* previous;

    Edge();
    Edge(String name, int distance);
};

class EdgeList {
public:
    Edge* first_edge;
    Edge* end_edge;

    EdgeList();
    ~EdgeList();

    void Add_New_Edge(int distance, String name);
    void Print() const;
};

class Vertex {
public:
    String city_name;
    EdgeList edges;
    int x, y;
    int index;

    Vertex();
    Vertex(String name, int x, int y);
    void Print();
};

class Graph {
public:
    Vector<Vertex> vertices;
    HashMap hashmap[HASH_MAP_SIZE];
    int number_of_cities = 0;

    int Find_Value_By_Key(String key) const;
    void Add_Vertex(String name, int x, int y);
    void Add_Edge_To_Vertex(String vertex, String destination, int distance);
    void Add_Edge_To_Vertex(int vertex_index, String destination, int distance);
    void Print();
    void Find_Roads(char** map, int rows, int cols);
    String Find_City_By_XY(int x, int y);
    void Add_Cities(char** map, int rows, int cols);
    String Find_City_Name(int x, int y, int cols, char** map);
    void Dijkstra(String start, String destination, int command);
    String Get_City_Name(int index);
};