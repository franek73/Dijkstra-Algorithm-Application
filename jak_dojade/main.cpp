#include <iostream>
#include "String.h"
#include "Vector.h"
#include "Graph.h"

using namespace std;

#define CHAR_TABLE_SIZE 50

int main() {

    Graph graph;

    int rows, cols, sign = 0;
    char c, ch[CHAR_TABLE_SIZE];
    String start, end;

    cin >> cols;
    cin >> rows;

    graph.vertices.Set_Size(cols*rows/2);

    char** map_chars = new char* [rows];
    for (int i = 0; i < rows; i++) 
    {
        map_chars[i] = new char[cols];
    }

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            sign = (char)getchar();
            c = (char)sign;

            if (c != '\n')
            {
                map_chars[i][j] = c;
            }
            else j--;   
        }
    }

    graph.Add_Cities(map_chars, rows, cols);
    graph.Find_Roads(map_chars, rows, cols);

    int number_of_air_roads;
    cin >> number_of_air_roads;

    sign = 0;
    for (int i = 0; i < number_of_air_roads; i++)
    {
        int distance;
        int y = 0;
        c = '\0';
        while (c != ' ')
        {
            sign = (char)getchar();
            c = (char)sign;

            if (c != '\n' && c != ' ')
            {
                ch[y] = c;
                y++;
            }
        }
       
        ch[y] = '\0';
        y = 0;
        start.Set_String(ch);
        c = '\0';
        while (c != ' ')
        {
            sign = (char)getchar();
            c = (char)sign;
            if (c != '\n' && c != ' ')
            {
                ch[y] = c;
                y++;
            }
        }
        ch[y] = '\0';
        end.Set_String(ch);
        cin >> distance;
        int start_index = graph.Find_Value_By_Key(start);
        graph.Add_Edge_To_Vertex(start_index, end, distance);
    }

    int number_of_commands;
    cin >> number_of_commands;

    sign = 0;
    for (int i = 0; i < number_of_commands; i++)
    {
        int command;
        int y = 0;
        c = '\0';
        while (c != ' ')
        {
            sign = (char)getchar();
            c = (char)sign;
            if (c != '\n' && c != ' ')
            {
                ch[y] = c;
                y++;
            }
        }
        
        ch[y] = '\0';
        y = 0;
        start.Set_String(ch);
        c = '\0';
        while (c != ' ')
        {
            sign = (char)getchar();
            c = (char)sign;
            if (c != '\n' && c != ' ')
            {
                ch[y] = c;
                y++;
            }
        }
        ch[y] = '\0';
        end.Set_String(ch);
        cin >> command;
        graph.Dijkstra(start, end, command);
    }

    for (int i = 0; i < rows; i++)
    {
        delete[] map_chars[i];
    }
    delete[] map_chars;

    return 0;
}