#pragma once
#include "data_structures/my_string.h"

struct BoardDimensions {
    int w;
    int h;
    int size;

    BoardDimensions() : w(0), h(0), size(0) {}
    BoardDimensions(int width, int height) : w(width), h(height), size(width * height) {}
};

struct FieldDistancePair {
    int field_index;
    int neighbor_field_distance;

    FieldDistancePair() : field_index(0), neighbor_field_distance(0) {}
    FieldDistancePair(int index, int distance) : field_index(index), neighbor_field_distance(distance) {}
};

struct City {
    MyString name;
    int vertex_index;

    City() : vertex_index(0) {}
    City(const MyString& city_name, int index) : name(city_name), vertex_index(index) {}
};

struct FieldDijkstra {
    int field_index;
    int distance;
    int previous_field_index;
    bool is_visited;

    FieldDijkstra() : field_index(0), distance(0), previous_field_index(0), is_visited(false) {}
    FieldDijkstra(int index, int dist, int prev_index, bool visited = false)
        : field_index(index), distance(dist), previous_field_index(prev_index), is_visited(visited) {}
};
