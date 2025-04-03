#include "Graph.h"
#include <iostream>

using namespace std;

int Hash(String name)
{
    const size_t p = 37;
    const size_t m = 99991;
    size_t hash_value = 0;
    size_t p_pow = 1;

    for (int i = 0; i < name.size; i++) {
        hash_value = (hash_value + ((name[i] - 'a' + 1) * p_pow) % m) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value % 100000;
}

HashMapElement::HashMapElement()
{
    next = nullptr;
    value = 0;
}

void HashMap::Add_Element_To_HashMap(String key, int value) {
    HashMapElement* new_element = new HashMapElement();
    new_element->key = key;
    new_element->value = value;
    new_element->next = nullptr;

    if (first_element == nullptr) {
        first_element = new_element;
    }
    else {
        HashMapElement* current_element = first_element;
        while (current_element->next != nullptr) {
            current_element = current_element->next;
        }
        current_element->next = new_element;
    }
}

HashMap::HashMap()
{
    first_element = nullptr;
}

HashMap::~HashMap()
{
    HashMapElement* current_element = first_element;
    while (current_element != nullptr) {
        HashMapElement* next_element = current_element->next;
        delete current_element;
        current_element = next_element;
    }
    first_element = nullptr;
}

Edge::Edge()
{
    next = nullptr;
    previous = nullptr;
    distance = 0;
}

Edge::Edge(String name, int distance)
{
    next = nullptr;
    previous = nullptr;
    this->destination_city_name = name;
    this->distance = distance;

}

Vertex::Vertex()
{
    this->city_name = "NULL";
    this->x = 0;
    this->y = 0;
    index = 0;
}

void Vertex::Print()
{
    cout << city_name << "/"<<index<<": ";
    edges.Print();
}

Vertex::Vertex(String name, int x, int y)
{
    this->city_name = name;
    this->x = x;
    this->y = y;
    index = 0;
}

EdgeList::EdgeList()
{
    first_edge = nullptr;
    end_edge = nullptr;
}

EdgeList::~EdgeList()
{
}

void EdgeList::Add_New_Edge(int distance, String name)
{
    Edge* new_edge = new Edge(name, distance);
    if (end_edge != nullptr) {
        end_edge->next = new_edge;
        end_edge = new_edge;
    }
    else {
        first_edge = new_edge;
        end_edge = new_edge;
    }
}

void EdgeList::Print() const
{
    if (first_edge != nullptr)
    {
        Edge* last_edge = first_edge;
        while (last_edge!= nullptr)
        {
            cout << last_edge->distance << "|" << last_edge->destination_city_name<<", ";
            last_edge = last_edge->next;
        }
    }
}

int Graph::Find_Value_By_Key(String key) const {
    int hash = Hash(key);
    HashMapElement* current_element = hashmap[hash].first_element;
    while (current_element != nullptr) {
        if (current_element->key == key) {
            return current_element->value;
        }
        current_element = current_element->next;
    }
    return -1;
}

void Graph::Add_Vertex(String name, int x, int y)
{
    Vertex v(name, x, y);
    vertices.Add_New_Element(v);
    vertices[number_of_cities].index = number_of_cities;

    int hash = Hash(name);
    hashmap[hash].Add_Element_To_HashMap(name, number_of_cities);
    number_of_cities++;
}

void Graph::Add_Edge_To_Vertex(String vertex, String destination, int distance)
{
    for (int i = 0; i < vertices.number_of_elements; i++)
    {
        if (vertices[i].city_name == vertex)
        {
            vertices[i].edges.Add_New_Edge(distance, destination);
        }
    }

}

void Graph::Add_Edge_To_Vertex(int vertex_index, String destination, int distance)
{
        vertices[vertex_index].edges.Add_New_Edge(distance, destination);
}

void Graph::Print()
{
    for (int i = 0; i < vertices.number_of_elements; i++)
    {
            vertices[i].Print();
            cout << endl;
    }
}

String Graph::Find_City_By_XY(int x, int y)
{
    for (int i = 0; i < vertices.number_of_elements; i++)
    {
        if (vertices[i].x == x && vertices[i].y == y)
        {
            return vertices[i].city_name;
        }
    }
    return vertices[0].city_name;
}

void Graph::Find_Roads(char** map, int rows, int cols)
{
    bool** bool_map = new bool* [rows];
    for (int i = 0; i < rows; i++) {
        bool_map[i] = new bool[cols];
    }
    bool is_found = true;
    RoadList roads;

    for (int i = 0; i < vertices.number_of_elements; i++)
    {
        Road* first_road;
        if (is_found == true)
        {
        
        for (int y = 0; y < rows; y++) 
          {
            for (int j = 0; j < cols; j++) 
            {
                bool_map[y][j] = false;
            }
           }
        }

        roads.Add_Road(vertices[i].x, vertices[i].y, 0);
        first_road = roads.first_road;
        is_found = false;
        while (roads.first_road!=nullptr)
        {
            first_road = roads.first_road;
            if (first_road->x != 0)
            {
                if (bool_map[first_road->x - 1][first_road->y] == false)
                {    
                if (map[first_road->x - 1][first_road->y] == '#')
                {
                    roads.Add_Road(first_road->x - 1, first_road->y, first_road->distance + 1);
                    bool_map[first_road->x - 1][first_road->y] = true;
                    is_found = true;
                }
                else if (map[first_road->x - 1][first_road->y] == '*' && (vertices[i].x != (first_road->x - 1) || vertices[i].y != first_road->y))
                {

                    String destination = Find_City_By_XY(first_road->x - 1, first_road->y);
                    Add_Edge_To_Vertex(vertices[i].index, destination, first_road->distance + 1);



                }
            }
            }
            if (first_road->x < (rows - 1))
            {
                if (bool_map[first_road->x + 1][first_road->y] == false)
                {
                    if (map[first_road->x + 1][first_road->y] == '#')
                    {
                        roads.Add_Road(first_road->x + 1, first_road->y, first_road->distance + 1);
                        bool_map[first_road->x + 1][first_road->y] = true;
                        is_found = true;
                    }
                    else if (map[first_road->x + 1][first_road->y] == '*' && (vertices[i].x != (first_road->x + 1) || vertices[i].y != first_road->y))
                    {
                        String destination = Find_City_By_XY(first_road->x + 1, first_road->y);
                        Add_Edge_To_Vertex(vertices[i].index, destination, first_road->distance + 1);

                    }
                }
            }
            if (first_road->y != 0)
            {
                if (bool_map[first_road->x][first_road->y - 1] == false)
                {
                    if (map[first_road->x][first_road->y - 1] == '#')
                    {
                        roads.Add_Road(first_road->x, first_road->y - 1, first_road->distance + 1);
                        bool_map[first_road->x][first_road->y-1] = true;
                        is_found = true;
                    }
                    else if (map[first_road->x][first_road->y - 1] == '*' && (vertices[i].x != first_road->x || vertices[i].y != (first_road->y - 1)))
                    {
                        String destination = Find_City_By_XY(first_road->x, first_road->y - 1);
                        Add_Edge_To_Vertex(vertices[i].index, destination, first_road->distance + 1);


                    }
                }
            }
            if (first_road->y < (cols - 1))
            {
                if (bool_map[first_road->x][first_road->y + 1] == false)
                {
                    if (map[first_road->x][first_road->y + 1] == '#')
                    {
                        roads.Add_Road(first_road->x, first_road->y + 1, first_road->distance + 1);
                        bool_map[first_road->x][first_road->y+1] = true;
                        is_found = true;
                    }
                    else if (map[first_road->x][first_road->y + 1] == '*' && (vertices[i].x != first_road->x || vertices[i].y != (first_road->y + 1)))
                    {
                        String destination = Find_City_By_XY(first_road->x, first_road->y + 1);
                        Add_Edge_To_Vertex(vertices[i].index, destination, first_road->distance + 1);


                    }
                }
            }

            roads.Remove_First_Road();

        }

    }
    
    for (int i = 0; i < rows; i++) 
    {
        delete[] bool_map[i];
    }
    delete[] bool_map;
}

String Graph::Find_City_Name(int x, int y, int cols, char** map)
{

    String s;
    char c[100];
    if (y == 0 || map[x][y - 1] == '.' || map[x][y - 1] == '#' || map[x][y - 1] == '*')
    {
        for (int i = 0; i <= cols; i++)
        {
            if (y == cols || map[x][y] == '.' || map[x][y] == '#' || map[x][y] == '*')
            {
                c[i] = '\0';
                break;
            }
            else
            {
                c[i] = map[x][y];
                y++;
            }
        }
    }
    else
    {
        int k = y;
        for (int i = k; i >= 0; i--)
        {
            if (map[x][y] == '.' || map[x][y] == '#')
            {
                y++;
                break;
            }
            else y--;
        }
        for (int i = 0; i <= cols; i++)
        {
            if (y == cols || map[x][y] == '.' || map[x][y] == '#' || map[x][y] == '*')
            {
                c[i] = '\0';
                break;
            }
            else
            {
                c[i] = map[x][y];
                y++;
            }
        }
    }

    s.Set_String(c);
    return s;
}

String Graph::Get_City_Name(int index)
{
   return vertices[index].city_name;
}

void Graph::Add_Cities(char** map, int rows, int cols)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == '*')
            {
                if (i != 0 && map[i - 1][j] != '#' && map[i - 1][j] != '.' && map[i - 1][j] != '*')
                {
                    String name = Find_City_Name(i - 1, j, cols, map);
                    Add_Vertex(name, i, j);
                }

                else if (i != 0 && j != 0 && map[i - 1][j - 1] != '#' && map[i - 1][j - 1] != '.' && map[i - 1][j - 1] != '*')
                {
                    String name = Find_City_Name(i - 1, j - 1, cols, map);
                    Add_Vertex(name, i, j);
                }

                else if (j != 0 && map[i][j - 1] != '#' && map[i][j - 1] != '.' && map[i][j - 1] != '*')
                {
                    String name = Find_City_Name(i, j - 1, cols, map);
                    Add_Vertex(name, i, j);
                }

                else if (i < (rows - 1) && j != 0 && map[i + 1][j - 1] != '#' && map[i + 1][j - 1] != '.' && map[i + 1][j - 1] != '*')
                {
                    String name = Find_City_Name(i + 1, j - 1, cols, map);
                    Add_Vertex(name, i, j);
                }

                else if (i < (rows - 1) && map[i + 1][j] != '#' && map[i + 1][j] != '.' && map[i + 1][j] != '*')
                {
                    String name = Find_City_Name(i + 1, j, cols, map);
                    Add_Vertex(name, i, j);
                }

                else if (i < (rows - 1) && j < (cols - 1) && map[i + 1][j + 1] != '#' && map[i + 1][j + 1] != '.' && map[i + 1][j + 1] != '*')
                {
                    String name = Find_City_Name(i + 1, j + 1, cols, map);
                    Add_Vertex(name, i, j);
                }

                else if (j < (cols - 1) && map[i][j + 1] != '#' && map[i][j + 1] != '.' && map[i][j + 1] != '*')
                {
                    String name = Find_City_Name(i, j + 1, cols, map);
                    Add_Vertex(name, i, j);
                }

                else if (i != 0 && j < (cols - 1) && map[i - 1][j + 1] != '#' && map[i - 1][j + 1] != '.' && map[i - 1][j + 1] != '*')
                {
                    String name = Find_City_Name(i - 1, j + 1, cols, map);
                    Add_Vertex(name, i, j);
                }
            }
        }
    }
}

void Graph::Dijkstra(String start, String destination, int command) {

    Vector<int> distances(number_of_cities);
    Vector<int> previous(number_of_cities);
    Vector<bool> visited(number_of_cities);
    PriorityQueue queue;

    for (int i = 0; i < number_of_cities; i++)
    {
        distances[i] = INT_MAX;
        previous[i] = -1;
        visited[i] = false;
    }

    int start_index = Find_Value_By_Key(start);
    int end_index = Find_Value_By_Key(destination);

    distances[start_index] = 0;
    queue.Add_Element(0, start_index);

    while (queue.number_of_elements != 0) {
        int vertex_index = queue.first_element->value;
        queue.Remove_Element();

        if (visited[vertex_index] == false)
        {
            visited[vertex_index] = true;

            Vertex curr_vertex = vertices[vertex_index];
            Edge* curr_edge = vertices[vertex_index].edges.first_edge;
            while (curr_edge != nullptr) {

                int destination_index = Find_Value_By_Key(curr_edge->destination_city_name);
                
                int distance = curr_edge->distance;

                if (!visited[destination_index] && distances[vertex_index] + distance < distances[destination_index]) {
                    distances[destination_index] = distances[vertex_index] + distance;
                    previous[destination_index] = vertex_index;
                    queue.Add_Element(distances[destination_index], destination_index);
                }
                
                curr_edge = curr_edge->next;
            }
        }
    }

    if (previous[end_index] != -1 && command==1) {
        
        cout << distances[end_index]<<" ";
         Vector<String> path(number_of_cities);
         int curr_vertex = end_index;
         while (curr_vertex != -1) {
             String s=Get_City_Name(curr_vertex);
             path.Add_New_Element(s);
             curr_vertex = previous[curr_vertex];
         }
         for (int i = (path.number_of_elements-1); i >= 0; i--) {
             if (path[i] == start || path[i] == destination)
             {

             }
             else {
                 cout << path[i]<<" ";
             }
         }
         cout << endl;
    }
    else if (previous[end_index] != -1)
    {
        cout << distances[end_index] << endl;
    }
    else 
    {
        cout << 0 <<endl;
    }
};