#include "input_output.h"
#include "../algorithms/dijkstra.h"
#include "../consts.h"
#include <iostream>
#include <cstdio>

void ReadFlights(int* hash_table, MyVector<MyVector<FieldDistancePair>>& graph) {
    int number_of_flights;
    scanf("%d", &number_of_flights);
    getchar();

    for (int i = 0; i < number_of_flights; i++) {
        int distance, source_index, destination_index;

        char* source_city = new char[kCityNameBuffer];
        char* destination_city = new char[kCityNameBuffer];

        int counter = 0;
        char c = getchar();
        while (c != ' ') {
            source_city[counter++] = c;
            c = getchar();
        }
        source_city[counter] = '\0';

        counter = 0;
        c = getchar();
        while (c != ' ') {
            destination_city[counter++] = c;
            c = getchar();
        }
        destination_city[counter] = '\0';

        scanf("%d", &distance);
        getchar();

        MyString source_city_str(source_city);
        MyString destination_city_str(destination_city);
        source_index = hash_table[source_city_str.Hash()];
        destination_index = hash_table[destination_city_str.Hash()];

        graph[source_index].PushBack({ destination_index, distance });

        delete[] source_city;
        delete[] destination_city;
    }
}

void PrintOutput(MyVector<FieldDijkstra>& shortest_route, MyVector<MyString>& city_names, int source_city_index, int destination_city_index, bool query_type) {
    std::cout << shortest_route[destination_city_index].distance;

    if (query_type) {
        MyVector<int> route_indexes;
        FindRouteIndexes(shortest_route, route_indexes, source_city_index, destination_city_index);

        bool first_city = true;
        for (int i = route_indexes.size() - 1; i > 0; i--) {
            int city_idx = route_indexes[i];
            if ((int)city_names.size() > city_idx && !city_names[city_idx].IsEmpty()) {
                std::cout << " " << city_names[city_idx];
                first_city = false;
            }
        }
    }
    std::cout << std::endl;
}

void ReadQueries(int*& hash_table, MyVector<MyVector<FieldDistancePair>>& graph, MyVector<MyString>& city_names) {
    MyVector<FieldDijkstra> shortest_route(graph.size());
    int number_of_queries;
    std::cin >> number_of_queries;

    for (int i = 0; i < number_of_queries; i++) {
        MyString source_city, destination_city;
        bool query_type;

        std::cin >> source_city >> destination_city >> query_type;

        int source_index = hash_table[source_city.Hash()];
        int destination_index = hash_table[destination_city.Hash()];

        DijkstraSearch(graph, shortest_route, source_index);

        PrintOutput(shortest_route, city_names, source_index, destination_index, query_type);
    }
}
